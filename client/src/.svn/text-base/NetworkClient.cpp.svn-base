#include <sstream>

#include "NetworkClient.h"
#include "Ship.h"
#include "RClient.h"

//////////
#include <iostream>

using boost::asio::ip::udp;

NetworkClient::NetworkClient(char const * ip, char const * port):
  _endpoint(boost::asio::ip::udp::v4(), 0),
  _socket(this->_io_service, this->_endpoint),
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

  this->_socket.async_receive_from(boost::asio::buffer(this->_bufferReceiv, NetworkClient::sizeBuffer), this->_endpoint,
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
  std::cout << "New Receive : " << std::endl;
  for (unsigned int i = 0; i < sizeRecv; i++)
    {
      std::cout << "[" << (int)_bufferReceiv[i] << "] -> ";
      if (_bufferReceiv[i] >= ' ' && _bufferReceiv[i] <= '~')
	std::cout << _bufferReceiv[i];
      else
	std::cout << ' ';
      std::cout << std::endl;
    }

  if (this->_usePacket == 0)
    {
      this->_usePacket = new Packet;
    }
  if (!error && sizeRecv > 0)
    {
      this->_usePacket->add(this->_bufferReceiv, sizeRecv);
      std::cout << "Packet size : " << this->_usePacket->getSize() << std::endl;
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
  this->_socket.async_receive_from(boost::asio::buffer(this->_bufferReceiv, NetworkClient::sizeBuffer), this->_endpoint,
                                   boost::bind(&NetworkClient::handle_receive_from, this,
                                               boost::asio::placeholders::error,
                                               boost::asio::placeholders::bytes_transferred));
}

// void	NetworkClient::handle_send_to(const boost::system::error_code& err, size_t sizeSent, std::vector<unsigned char>* bufferSent)
// {
//   std::cout << "Size Sent : " << sizeSent << std::endl;
//   if (!err)
//     {
//       delete bufferSent;
//     }
// }

void	NetworkClient::sendTo(Packet & pack)
{
  pack.addHead();
  std::vector<unsigned char>*	toSend = pack.getData();
  this->_socket.send_to(boost::asio::buffer(*toSend), *this->_itSocket);
  delete toSend;  
 //   std::vector<unsigned char>    *bufToSend = pack.getData();
//   this->_socket.async_send_to(boost::asio::buffer(*bufToSend), this->_endpoint,
//                               boost::bind(&NetworkClient::handle_send_to, this,
//                                           boost::asio::placeholders::error,
//                                           boost::asio::placeholders::bytes_transferred, bufToSend));
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
  std::cout << "I SEND MY DECONNECTION " << std::endl;
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
  std::cerr<< "NetWorkClient::funcSendCollision():";
  std::cerr << "idWeapon : " << idWeapon << "\nid Victim : " <<  idVictim << "\n typeVictim : " << typeVictim  << "\nidVictimBall : " << idVictimBall << "\n";
  std::cerr << "lifeShip(): "<< lifeShip<<  "powerShoot:"<< powerShoot <<std::endl;
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
  std::cout << "NetworkClient::funcRecvCreation"  << std::endl;

  int idGame;
  packet >> idGame;
  std::cout << "New Game : " << idGame << std::endl;
}

void	NetworkClient::funcRecvList(Packet & packet, std::list<Action*>&)
{
  std::cout << "NetworkClient::funcRecvList"  << std::endl;

  int	listIdGame;
  std::string	listNameGame;
  while (!packet.isEnd())
    {
      listNameGame = "";
      packet >> listIdGame;
      packet >> listNameGame;
      std::cout << "game(" << listIdGame << ") : " << listNameGame << std::endl;
    }
}

void	NetworkClient::funcRecvJoin(Packet & packet, std::list<Action*>& actions)
{
  std::cout << "NetworkClient::funcRecvJoin"  << std::endl;

  packet >> this->_idGame;
  std::cout << "game : " << this->_idGame;
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
      std::cout << " - idShip : " << (int)this->_idShip << std::endl;
    }
  else
    std::cout << std::endl;
}

void	NetworkClient::funcRecvBegin(Packet & packet, std::list<Action*>& actions)
{
  std::cout << "NetworkClient::funcRecvBegin"  << std::endl;
  unsigned char idLevel;

  packet >> idLevel;
  std::cout << "Join : " << (int)idLevel << std::endl;

  if (this->_idGame > 0)
    {
      std::cout << "START GAME" << std::endl;
      RClient::getInstance()->setLevel(idLevel);
      RClient::getInstance()->setShipId(this->_idShip);
      RClient::getInstance()->startGame();
    }
}

void	NetworkClient::funcRecvDeco(Packet & packet, std::list<Action*>& actions)
{
  unsigned char	idShip;

  packet >> idShip;
  
  std::cout << "NetworkClient::JAI RECU UNE DECOOOO" << std::endl;
  actions.push_back(new Action(static_cast<unsigned int>(idShip), DESTROY, TYPESHIP, PLAYER1, "42"));
  std::cout << "NetworkClient::funcRecvDeco" << std::endl;
}

void	NetworkClient::funcRecvMove(Packet & packet, std::list<Action*>& actions)
{
  std::cout << "NetworkClient::funcRecvMove" << std::endl;

  unsigned char	idShip;
  unsigned char direction;

  packet >> idShip;
  packet >> direction;

  std::string	directionStr(1, static_cast<char>(direction));
  actions.push_back(new Action(idShip, MOVE, TYPESHIP, Ship::getNumPlayer(idShip), directionStr));
}

void	NetworkClient::funcRecvKollision(Packet & packet, std::list<Action*>& actions)
{
  std::cout << "Kollision" << std::endl;
  unsigned int idKiller, idBall, idVictim, idVictimBall;
  unsigned char typeVictim;
  packet >> idKiller;
  packet >> idBall;
  packet >> typeVictim;
  packet >> idVictim;
  packet >> idVictimBall;

  std::cout << "idKiller : " << idKiller << "\nidBall : " <<  idBall << "\ntypeVictim : " << typeVictim  << "\nidVictimBall : " << idVictimBall << "\n";
  std::cout << " JE SUIS MALAAAAAAAAAADEEEEEEEEEEE " << idVictim << std::endl;
  if (typeVictim == 'S')
    {
      std::cout << "Ship";
      std::ostringstream os;
      os << idKiller;
      actions.push_back(new Action(idVictim, DESTROY, TYPESHIP, PLAYER1, (os.str()).c_str()));
    }
  if (typeVictim == 'W')
    {
      std::cout << "Weapon";
      std::ostringstream os;
      os << idVictimBall;
      actions.push_back(new Action(DESTROY, TYPEWEAPON, WEAPON1, (os.str()).c_str(), idKiller));
    }
  std::cout << "END";
}

void	NetworkClient::funcRecvShoot(Packet & packet, std::list<Action*>& actions)
{
  std::cout << "NetworkClient::funcRecvShoot" << std::endl;
  unsigned char idShip;
  unsigned char recvTypeWeapon;
  unsigned int	x;
  unsigned int	y;
  packet >> idShip;
  packet >> recvTypeWeapon;
  packet >> x;
  packet >> y;
  std::ostringstream os;
  os << x << " " << y;
  actions.push_back(new Action(idShip, JUMP , TYPESHIP, Ship::getNumPlayer(idShip), (os.str()).c_str()));
  actions.push_back(new Action(CREATE, TYPEWEAPON,
                               static_cast<typeWeapon>(recvTypeWeapon),
                               (os.str()).c_str(), static_cast<int>(idShip)));
}
