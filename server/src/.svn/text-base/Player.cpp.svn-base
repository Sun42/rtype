#include "Server.h"
#include "Player.h"

/*********************************************************************/

Player::Player(boost::asio::ip::udp::endpoint& endpoint) :
  _endpoint(endpoint), _game(0), _idShip(-1)
{
  this->_mapPtFunc['N'] = &Player::funcCreation;
  this->_mapPtFunc['L'] = &Player::funcList;
  this->_mapPtFunc['J'] = &Player::funcJoin;
  this->_mapPtFunc['D'] = &Player::funcDeco;
  this->_mapPtFunc['M'] = &Player::funcMove;
  this->_mapPtFunc['K'] = &Player::funcKollision;
  this->_mapPtFunc['S'] = &Player::funcShoot;
  this->_mapPtFunc['C'] = &Player::funcNextLevel;
}

Player::Player(Player const & obj) :
  _endpoint(obj._endpoint)
{
}

Player::~Player()
{
  std::cout << "Player::~Player" << this->_endpoint << std::endl;
}

/*********************************************************************/

Player &	Player::operator=(Player const &)
{
  return (*this);
}

bool	Player::operator==(Player const & rhs) const
{
  return (this->_endpoint == rhs._endpoint);
}

/*********************************************************************/

boost::asio::ip::udp::endpoint&		Player::getEndPoint()
{
  return (this->_endpoint);
}

int	Player::getIdShip() const
{
  return (this->_idShip);
}

void	Player::setIdShip(int idShip)
{
  this->_idShip = idShip;
}

/*********************************************************************/

void	Player::addPacketRecv(boost::array<unsigned char,1024> & buf, unsigned int len)
{
  this->_mutexPacketRecv.lock();
  if (this->_packetRecv.checkLen())
    this->_packetRecv.reset();
  this->_packetRecv.add(buf, len);
  this->_mutexPacketRecv.unlock();
}

void	Player::sendPacket(Packet & pack)
{
  pack.addHead();
  Server::getInstance()->sendTo(this->_endpoint, pack);
}

void	Player::exec()
{
  this->_mutexPacketRecv.lock();

  std::cout << this->_packetRecv;
  std::map<char, ptfunc_t>::iterator itFind = this->_mapPtFunc.find(this->_packetRecv.getCmd());
  if (itFind != this->_mapPtFunc.end())
    {
      ptfunc_t	ptFunc = itFind->second;
      Packet	answerPacket;

      (this->*ptFunc)(answerPacket << static_cast<unsigned char>(itFind->first));
    }
  else
    std::cerr << "Unknown Command" << std::endl;
  this->_mutexPacketRecv.unlock();
}

/***************************PARTIE PROTOCOLE ***************************/

void	Player::funcCreation(Packet & answerPacket)
{
  std::cout << "Player::funcCreation"  << std::endl;
  int		idGame = -5;
  unsigned char	nbPlayerMax;
  std::string	nameGame;

  this->_packetRecv >> nbPlayerMax;
  this->_packetRecv >> nameGame;

  if (!this->_game)
    {
      idGame = -1;
      if (nbPlayerMax >= 2 && nbPlayerMax <= 4)
	{
	  idGame = -2;
	  Server*	instanceServer = Server::getInstance();
	  if (!instanceServer->existingGame(nameGame))
	    {
	      idGame = instanceServer->createGame(nameGame, nbPlayerMax)->getId();
	      std::cout << "Creation Partie(" << (int)nbPlayerMax << ") : " << nameGame << " -> id : " << idGame << std::endl;
	    }
	}
    }
  this->sendPacket(answerPacket << idGame);
}

void	Player::funcList(Packet & answerPacket)
{
  std::cout << "Player::funcList"  << std::endl;

  Packet tmpPack = Server::getInstance()->listGame();
  answerPacket += tmpPack;
  this->sendPacket(answerPacket);
}

void	Player::funcJoin(Packet & answerPacket)
{
  std::cout << "Player::funcJoin"  << std::endl;
  int	idGameAsk;
  this->_packetRecv >> idGameAsk;
  if (!this->_game)
    {
      if (idGameAsk >= 0)
	{
	  Server*	instanceServer = Server::getInstance();
	  Game*		findGame = instanceServer->findGame(idGameAsk);
	  if (!findGame)
	    this->sendPacket(answerPacket << static_cast<int>(-3));
	  else
	    {
	      if (!findGame->isStarded())
		this->funcJoin2(answerPacket, findGame, idGameAsk);
	      else
		this->sendPacket(answerPacket << static_cast<int>(-7));
	    }
	}
      else
	this->sendPacket(answerPacket << static_cast<int>(-3));
    }
}

void	Player::funcJoin2(Packet & answerPacket, Game * findGame, int idGameAsk)
{
  if (!findGame->addPlayerInGame(this))
    this->sendPacket(answerPacket << static_cast<int>(-4));
  else
    {
      this->_game = findGame;
      this->sendPacket(answerPacket << idGameAsk << static_cast<unsigned char>(this->_idShip) << static_cast<unsigned char>(this->_game->getNbPlayerMax()));
      if (this->_game->canStartToPlay())
	{
	  answerPacket.reset();
	  this->_game->setPlaying();
	  this->_game->sendToAllPlayers(answerPacket << static_cast<unsigned char>('B') << this->_game->getLevel());
	}
    }
}

void	Player::funcDeco(Packet &)
{
  std::cout << "Player::funcDeco" << std::endl;
  if (this->_game)
    {
      this->_game->deconnectionPlayer(this);
    }
  this->_game = 0;
  this->_idShip = -1;
  Server::getInstance()->destroyPlayer(this);
}

void	Player::funcMove(Packet & answerPacket)
{
  std::cout << "Player::funcMove" << std::endl;
  if (this->_game && this->_game->isStarded())
    {
      answerPacket = this->_packetRecv;
      this->_game->sendToOtherPlayers(answerPacket, this);
    }
}

void	Player::funcKollision(Packet & answerPacket)
{
  std::cerr << "Kollision~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << std::endl;
  if (this->_game && this->_game->isStarded())
    {
      unsigned int	idBallKiller, idVictim, idVictimBall, lifeOfShip, powerShoot;
      unsigned char	typeVictim;
      this->_packetRecv >> idBallKiller;
      this->_packetRecv >> idVictim;
      this->_packetRecv >> idVictimBall;
      this->_packetRecv >> lifeOfShip;
      this->_packetRecv >> powerShoot;
      this->_packetRecv >> typeVictim;
      std::cout << "idBallKiller " << idBallKiller << std::endl
		<< "idVictim " << idVictim << std::endl
		<< "idVictimBall " << idVictimBall << std::endl
		<< "lifeOfShip " << lifeOfShip << std::endl
		<< "powerShoot " << powerShoot << std::endl
		<< "typeVictim" << typeVictim << std::endl;
      this->_game->collisionWithEnnemies(this, answerPacket, idBallKiller, idVictim, idVictimBall, lifeOfShip, powerShoot, typeVictim);
    }
}

void	Player::funcShoot(Packet & answerPacket)
{
  std::cout << "Player::funcShoot" << std::endl;
  if (this->_game && this->_game->isStarded())
    {
      answerPacket = this->_packetRecv;
      this->_game->sendToOtherPlayers(answerPacket, this);
    }
}

void	Player::funcNextLevel(Packet & answerPacket)
{
  std::cout << "Player::funcNextLevel" << std::endl;
  if (this->_game && this->_game->isStarded())
    {
      if (this->_game->askLevelUp(this))
	{
	  this->_game->levelUp();
	  this->_game->sendToAllPlayers(answerPacket << this->_game->getLevel());
	}
    }
}
