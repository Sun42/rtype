#include "Server.h"
#include "Game.h"

/*********************************************************************/

Game::Game(std::string & name, unsigned char nbPlayerMax, int idGame):
  _idGame(idGame), _name(name), _nbPlayerMax(nbPlayerMax), _playing(false),_idLevel(0), _players(), _victims()
{
}

Game::~Game()
{
}

/*********************************************************************/

int	Game::getId() const
{
  return (this->_idGame);
}

std::string const &	Game::getName() const
{
  return (this->_name);
}

unsigned char		Game::getLevel() const
{
  return (this->_idLevel);
}

unsigned int		Game::getNbPlayers()
{
  boost::mutex::scoped_lock	lock(this->_mutexPlayers);
  return (this->_players.size());
}

unsigned int		Game::getNbPlayerMax() const
{
  return (this->_nbPlayerMax);
}

/*********************************************************************/

bool		Game::canStartToPlay()
{
  boost::mutex::scoped_lock	lock(this->_mutexPlayers);

  return (this->_players.size() == this->_nbPlayerMax);
}

bool	Game::isStarded() const
{
  return (this->_playing);
}

bool	Game::addPlayerInGame(Player * player)
{
  boost::mutex::scoped_lock	lock(this->_mutexPlayers);

  if (this->_players.size() < this->_nbPlayerMax)
    {
      player->setIdShip(this->_players.size());
      this->_players.push_back(player);
      return (true);
    }
  return (false);
}

bool			Game::askLevelUp(Player * player)
{
  boost::mutex::scoped_lock	lock(this->_mutexPlayersConf);

  std::list<Player*>::iterator itres = find(this->_playersConf.begin(), this->_playersConf.end(), player);
  if (itres == this->_playersConf.end())
    {
      this->_playersConf.push_back(player);
      if (this->getNbPlayers() == this->_playersConf.size())
	return (true);
    }
  return (false);
}

void	Game::setPlaying()
{
  this->_playing = true;
}

/*********************************************************************/


void	Game::sendToAllPlayers(Packet & pack)
{
  this->_mutexPlayers.lock();
  std::for_each(this->_players.begin(), this->_players.end(), boost::bind(&Player::sendPacket, _1, pack));
  this->_mutexPlayers.unlock();
}

void	Game::sendToOtherPlayers(Packet & answerPacket, Player const * originPlayer)
{
  this->_mutexPlayers.lock();
  std::list<Player*>::const_iterator	it = this->_players.begin();
  std::list<Player*>::const_iterator	itEnd = this->_players.end();

  for(; it != itEnd; ++it)
    {
      if (!(*it == originPlayer))
	(*it)->sendPacket(answerPacket);
    }
  this->_mutexPlayers.unlock();
}

void	Game::deconnectionPlayer(Player * player)
{
  boost::mutex::scoped_lock	lock(this->_mutexPlayers);
  if (this->_players.size() == 1)
    {
      Server::getInstance()->destroyGame(this);
      return ;
    }

  Packet	sendPacket;
  sendPacket << static_cast<unsigned char>('D') << static_cast<unsigned char>(player->getIdShip());
  std::list<Player*>::iterator	it = this->_players.begin();

  for(; it != this->_players.end(); ++it)
    {
      if ((*it) == player)
	this->_players.remove(*it);
      else
	(*it)->sendPacket(sendPacket);
    }
}

void	Game::collisionWithEnnemies(Player * sender, Packet & answerPacket,
				    unsigned int idBallKiller, unsigned int idVictim,
				    unsigned int idVictimBall, unsigned int lifeOfShip,
				    unsigned int powerShoot, unsigned char typeVictim)
{
  this->_mutexVictims.lock();

  std::list<Victim>::iterator	it = this->_victims.begin();
  std::list<Victim>::iterator	itEnd = this->_victims.end();

  for(; it != itEnd; ++it)
    {
      if ((*it).isTheVictim(idVictim, idVictimBall, typeVictim))
	break;
    }

  if (it == itEnd)
    {
      std::cerr << "new victim\n" << std::endl;
      this->_victims.push_front(Victim(idVictim, idVictimBall, typeVictim, lifeOfShip));
      it = this->_victims.begin();
    }
  std::cout << "isKilled? " << std::boolalpha << (*it).isKilled() << std::endl;
  if (!(*it).isKilled())
    {
      std::cout << "lifeOfShip" << lifeOfShip << "powerShoot " << powerShoot << std::endl;
      *it -= powerShoot;
      std::cout << "isKilled? " << std::boolalpha << (*it).isDead() << std::endl;
      if ((*it).isDead())
	{
	  std::cout << "la victime est morte\n" << std::endl;
	  (*it).setKiller(sender->getIdShip(), idBallKiller);
	  std::cout << "idKiller " << (*it).getIdKiller() << std::endl
		    << "idBallKiller " << (*it).getIdBallKiller()  << std::endl
		    << "typeVictim" << (*it).getTypeVictim() << std::endl
		    << "idVictim " << (*it).getIdVictim() << std::endl
		    << "idVictimBall " << (*it).getIdVictimBall() << std::endl;
      
	  this->sendToAllPlayers(answerPacket << (*it).getIdKiller() << (*it).getIdBallKiller() << (*it).getTypeVictim() << (*it).getIdVictim() << (*it).getIdVictimBall());
	}
    }
  else
    {
      std::cout << "idKiller " << (*it).getIdKiller() << std::endl
		<< "idBallKiller " << (*it).getIdBallKiller()  << std::endl
		<< "typeVictim" << (*it).getTypeVictim() << std::endl
		<< "idVictim " << (*it).getIdVictim() << std::endl
		<< "idVictimBall " << (*it).getIdVictimBall() << std::endl;

      this->sendToAllPlayers(answerPacket << (*it).getIdKiller() << (*it).getIdBallKiller() << (*it).getTypeVictim() << (*it).getIdVictim() << (*it).getIdVictimBall());
    }
  this->_mutexVictims.unlock();
}

void			Game::levelUp()
{
  this->_mutexVictims.lock();
  this->_victims.clear();
  this->_mutexVictims.unlock();
  this->_idLevel++;
  this->_mutexPlayersConf.lock();
  this->_playersConf.clear();
  this->_mutexPlayersConf.unlock();
}
