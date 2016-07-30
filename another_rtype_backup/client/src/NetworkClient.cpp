#include <sstream>

#include "NetworkClient.h"
#include "Ship.h"
#include "RClient.h"

//////////
#include <iostream>

using boost::asio::ip::udp;

NetworkClient::NetworkClient(char const * ip, char const * port):
  _endpointRecv(boost::asio::ip::udp::v4(), 0),
  _endpointSend(boost::asio::ip::address::from_string(ip), ::atoi(port)),
  _socket(this->_io_service, this->_endpointRecv),
  _resolver(this->_io_service),
  _itSocket(this->_resolver.resolve(udp::resolver::query(udp::v4(), ip, port))),
  _usePacket(0),
  _idGame(0),
  _idShip(0)
{
  this->_mapPtFunc['N'] = &NetworkClient::funcRecvCreation;
  this->_mapPtFunc['L'] = &NetworkClient::funcRecvList;
  this->_mapPtFunc['J'] = &NetworkClient::funcRecvJoin;
  this->_mapPtFunc['B'] = &NetworkClient::funcRecvBegin;
  this->_mapPtFunc['D'] = &NetworkClient::funcRecvDeco;
  this->_mapPtFunc['M'] = &NetworkClient::funcRecvMove;
  this->_mapPtFunc['K'] = &NetworkClient::funcRecvKollision;
  this->_mapPtFunc['S'] = &NetworkClient::funcRecvShoot;

  this->_socket.async_receive_from(boost::asio::buffer(this->_bufferReceiv, NetworkClient::sizeBuffer), this->_endpointRecv,
                                   boost::bind(&NetworkClient::handle_receive_from, this,
                                               boost::asio::placeholders::error,
                                               boost::asio::placeholders::bytes_transferred));
}

NetworkClient::~NetworkClient()
{}

void	NetworkClient::run()
{
  this->_io_service.run();
}

void	NetworkClient::handle_receive_from(const boost::system::error_code& error, size_t sizeRecv)
{
  if (this->_usePacket == 0)
    {
      this->_usePacket = new Packet;
    }
  if (!error && sizeRecv > 0)
    {
      this->_usePacket->add(this->_bufferReceiv, sizeRecv);
      if (this->_usePacket->checkLen())
	{
	  this->_mutexTabPacket.lock();
	  this->_tabPacket.push_back(this->_usePacket);
	  this->_usePacket = 0;
	  this->_mutexTabPacket.unlock();
	}
      else
	std::cerr << "Incomplet Packet" << std::endl;
    }
  this->_socket.async_receive_from(boost::asio::buffer(this->_bufferReceiv, NetworkClient::sizeBuffer), this->_endpointRecv,
                                   boost::bind(&NetworkClient::handle_receive_from, this,
                                               boost::asio::placeholders::error,
                                               boost::asio::placeholders::bytes_transferred));
}

void	NetworkClient::handle_send_to(const boost::system::error_code& err, size_t , std::vector<unsigned char>* bufferSent)
{
  if (!err)
    {
      delete bufferSent;
    }
}

void	NetworkClient::initGame(char * nameGame, char nbPlayer)
{
  this->_nameGame = nameGame;
  unsigned char nbPlayerVal = nbPlayer - '0';
  this->funcSendNew(nbPlayerVal, this->_nameGame);
  this->funcSendList();
}

void	NetworkClient::sendTo(Packet & pack)
{
  pack.addHead();
  std::vector<unsigned char>    *bufToSend = pack.getData();
  this->_socket.async_send_to(boost::asio::buffer(*bufToSend), this->_endpointSend,
                              boost::bind(&NetworkClient::handle_send_to, this,
                                          boost::asio::placeholders::error,
                                          boost::asio::placeholders::bytes_transferred, bufToSend));
}

void	NetworkClient::funcSendNew(unsigned char nbPlayerMax, std::string & nameGame)
{
  Packet	pack;

  pack << static_cast<unsigned char>('N');
  pack << nbPlayerMax;
  pack << nameGame;
  this->sendTo(pack);
}

void	NetworkClient::funcSendList()
{
  Packet	pack;

  pack << static_cast<unsigned char>('L');
  this->sendTo(pack);
}

void	NetworkClient::funcSendJoin(unsigned int idGame)
{
  Packet	pack;

  pack << static_cast<unsigned char>('J');
  pack << idGame;
  this->sendTo(pack);
}

void	NetworkClient::funcSendDeco()
{
  Packet	pack;

  pack << static_cast<unsigned char>('D');
  this->sendTo(pack);
}

void	NetworkClient::funcSendMove(unsigned char direction)
{
  Packet	pack;

  pack << static_cast<unsigned char>('M');
  pack << this->_idShip;
  pack << direction;
  this->sendTo(pack);
}

//idWeapon = id de l'arme qui tue
//idVictime = id de la personne visee
// idVictimBall (id de l'arme de la personne visee si c'est weapon vs weapon sinon idVictimBall == 0)
//lifeShip: vie max de 'idVictim
//typeVictim
/*
idWeapon : 42
id Victim : 5
typeVictim : S
idVictimBall : 0
lifeShip(): 3
powerShoot:1
*/
void		NetworkClient::funcSendCollision(unsigned int idWeapon, unsigned int idVictim, unsigned int idVictimBall, 
						 unsigned int lifeShip, unsigned int powerShoot, unsigned char typeVictim)
{
  //42 5 0 3 1 S
  Packet	pack;
  pack << static_cast<unsigned char>('K');
  pack << idWeapon;
  pack << idVictim;
  pack << idVictimBall;
  pack << lifeShip;
  pack << powerShoot;
  pack << typeVictim;
  this->sendTo(pack);
}

void	NetworkClient::funcSendShoot(unsigned char idWeapon, unsigned int X, unsigned int Y)
{
  Packet	pack;

  pack << static_cast<unsigned char>('S');
  pack << this->_idShip;
  pack << idWeapon;
  pack << X;
  pack << Y;
  this->sendTo(pack);
}

void	NetworkClient::checkNetwork(std::list<Action*>& actions)
{
  if (!this->_mutexTabPacket.try_lock())
    return ;

  while (this->execRecv(actions)) ;

  this->_mutexTabPacket.unlock();
}

// verif coplienne  de action
bool	NetworkClient::execRecv(std::list<Action*>& actions)
{
  if (this->_tabPacket.size() <= 0)
    return false;
  Packet*	packet = this->_tabPacket.front();
  this->_tabPacket.pop_front();

  std::map<char, ptfunc_t>::iterator itFind = this->_mapPtFunc.find(packet->getCmd());
  if (itFind != this->_mapPtFunc.end())
    {
      ptfunc_t  ptFunc = itFind->second;
      (this->*ptFunc)(*packet, actions);

      delete packet;
      return true;
    }
  else
    std::cerr << "Unknown Command" << std::endl;

  delete packet;
  return false;
}

void	NetworkClient::funcRecvCreation(Packet & packet, std::list<Action*>&)
{
  int idGame;
  packet >> idGame;
}

void	NetworkClient::funcRecvList(Packet & packet, std::list<Action*>&)
{
  int	listIdGame;
  std::string	listNameGame;
  while (!packet.isEnd())
    {
      listNameGame = "";
      packet >> listIdGame;
      packet >> listNameGame;
      if (listNameGame == this->_nameGame)
	{
	  this->funcSendJoin(listIdGame);
	  break;
	}
    }
}

void	NetworkClient::funcRecvJoin(Packet & packet, std::list<Action*>& actions)
{
  packet >> this->_idGame;
  if (this->_idGame > 0)
    {
      packet >> this->_idShip;

      unsigned char nbMaxPlayer;
      packet >> nbMaxPlayer;


      int posXBase = 200;
      for (unsigned char i = 0; i < nbMaxPlayer; ++i)
	{
	  std::ostringstream pos;
	  pos << "0 " << posXBase << " 100";
	  posXBase += 100;
	  actions.push_back(new Action(i, CREATE, TYPESHIP, Ship::getNumPlayer(i), pos.str().c_str()));
	}
    }
  else
    {
      if (this->_idGame == -4)
	std::cerr << "The game is full" << std::endl;
      if (this->_idGame == -3)
	std::cerr << "async" << std::endl;
      if (this->_idGame == -6)
	std::cerr << "Player is in game" << std::endl;
      if (this->_idGame == -7)
	std::cerr << "Game already started" << std::endl;
      exit(-1);
    }
}

void	NetworkClient::funcRecvBegin(Packet & packet, std::list<Action*>&)
{
  unsigned char idLevel;

  packet >> idLevel;
  if (this->_idGame > 0)
    {
      RClient::getInstance()->setLevel(idLevel);
      RClient::getInstance()->setShipId(this->_idShip);
      RClient::getInstance()->startGame();
    }
}

void	NetworkClient::funcRecvDeco(Packet & packet, std::list<Action*>& actions)
{
  unsigned char	idShip;

  packet >> idShip;
  actions.push_back(new Action(static_cast<unsigned int>(idShip), DESTROY, TYPESHIP, PLAYER1, "42"));
}

void	NetworkClient::funcRecvMove(Packet & packet, std::list<Action*>& actions)
{
  unsigned char	idShip;
  unsigned char direction;

  packet >> idShip;
  packet >> direction;

  std::string	directionStr(1, static_cast<char>(direction));
  actions.push_back(new Action(idShip, MOVE, TYPESHIP, Ship::getNumPlayer(idShip), directionStr));
}

void	NetworkClient::funcRecvKollision(Packet & packet, std::list<Action*>& actions)
{
  unsigned int idKiller, idBall, idVictim, idVictimBall;
  unsigned char typeVictim;

  packet >> idKiller;
  packet >> idBall;
  packet >> typeVictim;
  packet >> idVictim;
  packet >> idVictimBall;
  if (typeVictim == 'S')
    {
      std::ostringstream os;
      os << idKiller;
      actions.push_back(new Action(idVictim, DESTROY, TYPESHIP, PLAYER1, (os.str()).c_str()));
    }
  if (typeVictim == 'W')
    {
      std::ostringstream os;
      os << idVictimBall;
      actions.push_back(new Action(DESTROY, TYPEWEAPON, WEAPON1, (os.str()).c_str(), idVictim));
    }
}

void	NetworkClient::funcRecvShoot(Packet & packet, std::list<Action*>& actions)
{
  unsigned char idShip;
  unsigned char recvTypeWeapon;
  unsigned int	x, y, shipx, shipy;
  packet >> idShip;
  packet >> recvTypeWeapon;
  packet >> x;
  packet >> y;
  std::ostringstream osJump;
  if (x < Ship::decWeapX)
	shipx = 0;
  else
	  shipx = x - Ship::decWeapX;
  if (y < Ship::decWeapY)
	shipy = 0;
  else
	  shipy = y - Ship::decWeapY;
  osJump << shipx << " " << shipy;
  actions.push_back(new Action(idShip, JUMP , TYPESHIP, Ship::getNumPlayer(idShip), (osJump.str()).c_str()));
  std::ostringstream osShoot;
  osShoot << x << " " << y;
  actions.push_back(new Action(CREATE, TYPEWEAPON,
                               static_cast<typeWeapon>(recvTypeWeapon),
                               (osShoot.str()).c_str(), static_cast<int>(idShip)));
}
