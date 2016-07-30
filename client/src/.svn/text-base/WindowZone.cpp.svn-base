#include "WindowZone.h"
#include "RClient.h"
#include "WindowManager.h"
#include "Weapon.h"
#include "Ship.h"
#include "NetworkClient.h"

WindowZone::WindowZone():
  _myEntities(), _otherEntities()
{
}

WindowZone::WindowZone(const WindowZone& rhs):
  _myEntities(rhs._myEntities), _otherEntities(rhs._otherEntities)
{
}

WindowZone::~WindowZone()
{
}

WindowZone& WindowZone::operator=(const WindowZone& rhs)
{
  if (this != &rhs)
    {
      this->_myEntities = rhs._myEntities;
      this->_otherEntities = rhs._otherEntities;
    }
  return (*this);
}

bool	WindowZone::checkObject(SpriteEntity* spr1, SpriteEntity* spr2)
{
  if ((!spr2->isPlayer()) &&
      spr1->getDeepness() == spr2->getDeepness())
    return (true);
  return (false);
}

void	WindowZone::checkCollisionSprite(SpriteEntity* spr1, SpriteEntity* spr2)
{
	NetworkClient*	network = RClient::getInstance()->getNetwork();
  unsigned int	shipId = RClient::getInstance()->getShipId();

  if (this->checkObject(spr1, spr2))
    {
      if (Collision::PixelPerfectTest(*spr1->getSprite(), *spr2->getSprite()))
	{
	  if (spr1->getId() == shipId) // Si c'est mon joueur qui touche quelqueChose
	    {
	      if (!spr1->touched(RClient::getInstance()->getTime()))
		{
		  std::cout << "BOUUUUUUUUUUUUUUMMMMMMMMMM" << std::endl;
		  network->funcSendDeco();
		  RClient::getInstance()->getApp()->Close();
		  exit (-1);
		}
	    }
	  else // Sinon c'est une de mes balle qui touche QuelqueChose autre qu'un player
	    {
	      std::cout << "BOUUUUUUUUUUUUUUMMMMMMMMMM2222222222" << std::endl;
	      unsigned int idBall, idVictim, idVictimBall, lifeShip, powerShoot;
	      unsigned char typeVictim;
	      Weapon* weap = dynamic_cast<Weapon*>(spr1);
	      std::cerr << "BOUUUUUMMMMMMMM\n";
	      if (weap)
		{
		  //std::cout << "WEAP\n";
		  idBall = spr1->getId();
		  powerShoot = weap->getPower();
		  if (spr2->getTypeSpriteEntity() == TYPEWEAPON)
		    {
		      //std::cerr << "1\n";
		      Weapon* weap2 = dynamic_cast<Weapon*>(spr2);
		      if (!weap2)
			return;
		      idVictim = weap2->getOwner();
		      idVictimBall = spr2->getId();
		      lifeShip = 1;
		      typeVictim = 'W';
		    }
		  if (spr2->getTypeSpriteEntity() == TYPESHIP)
		    {
		      //std::cerr << "2\n";
		      Ship* ship = dynamic_cast<Ship*>(spr2);
		      if (!ship)
			return ;
		      idVictim = spr2->getId();
		      idVictimBall = 0;
		      lifeShip = ship->getLife();
		      typeVictim = 'S';
		    }
		  network->funcSendCollision(idBall, idVictim, idVictimBall, lifeShip, powerShoot, typeVictim);
		  network->funcSendCollision(0, weap->getOwner(), spr1->getId(), 1, powerShoot, 'W');
		}
	      //envoi du sprite touche dans le reseau;
	      //this->_delEntities.push_back(spr1);
	      //this->_delEntities.push_back(spr2);
	      //animation explosion
	    }
	}
    }
}

/*void	WindowZone::call_destroy(SpriteEntity* sp1, SpriteEntity* sp2)
{
//surcharge ship

Action::Action(unsigned int spriteid, typeAction typeaction,
	       typeSpriteEntity typeSprite, typeShip typeship, std::string param):
  _spriteId(spriteid), _typeAction(typeaction),
  _typeSpriteEntity(typeSprite),  _typeShip(typeship), _params(param)
  }*/

void	WindowZone::checkCollision()
{
  std::list<SpriteEntity *>::iterator it = this->_myEntities.begin();
  std::list<SpriteEntity *>::iterator ite = this->_myEntities.end();
  for(; it != ite; ++it)
    {
      std::list<SpriteEntity *>::iterator it2 = this->_otherEntities.begin();
      std::list<SpriteEntity *>::iterator ite2 = this->_otherEntities.end();
      for(; it2 != ite2; ++it2)
	{
	  this->checkCollisionSprite((*it), (*it2));
	}
    }
  /*
  if (this->_delEntities.size())
    {
      std::list<SpriteEntity *>::iterator save;
      it = this->_delEntities.begin();
      WindowManager*	windowmanager = WindowManager::getInstance();
      while (it != this->_delEntities.end())
	{
	  save = it;
	  ++it;
	  windowmanager->delSpriteInZones((*save));
	  this->_delEntities.erase(save);
	}
    }
  */
}

bool	WindowZone::checkIfExist(SpriteEntity* sprite)
{
  std::list<SpriteEntity *>::iterator it = this->_myEntities.begin();
  std::list<SpriteEntity *>::iterator ite = this->_myEntities.end();
  for(; it != ite; ++it)
    {
      if (sprite->getId() == (*it)->getId())
	return (true);
    }
  it = this->_otherEntities.begin();
  ite = this->_otherEntities.end();
  for(; it != ite; ++it)
    {
      if (sprite->getId() == (*it)->getId())
	return (true);
    }
  return (false);
}

void	WindowZone::addSpriteEntity(SpriteEntity* sprite)
{
  if (!this->checkIfExist(sprite))
    {
      if (sprite->getTypeSpriteEntity() != TYPEWEAPON)
	{
	  if (RClient::getInstance()->getShipId() == sprite->getId())
	    {
	      this->_myEntities.push_back(sprite);
	    }
	  else
	    {
	      this->_otherEntities.push_back(sprite);
	    }
	}
      else if (sprite->getTypeSpriteEntity() == TYPEWEAPON)
	{
	  Weapon * weapon = dynamic_cast<Weapon*>(sprite);
	  if (weapon)
	    {
	      if (weapon->getOwner() == RClient::getInstance()->getShipId())
		this->_myEntities.push_back(sprite);
	      else
		this->_otherEntities.push_back(sprite);
	    }
	}
    }
}

void	WindowZone::delSpriteEntity(SpriteEntity* sprite)
{
  //std::cout<< "WindowZone::delSpriteEntity():" <<std::endl;
  if (!sprite)
    {
      //std::cout<< "Demande del d 'un Sprite NULL" <<std::endl;
      return ;
    }
  //std::cout<< "Demande del du Sprite: "<< sprite->getId() <<std::endl;
  if (this->checkIfExist(sprite))
    {
      //std::cout<< "le sprite a ete trouve "<<std::endl;
      if (sprite->getTypeSpriteEntity() != TYPEWEAPON)
	{
	  //std::cout<< "le sprite est un vaisseau "<< std::endl;
	  if (RClient::getInstance()->getShipId() == sprite->getId())
	    {
	      //std::cout<< "Del sprite dans myEntities"<<std::endl;
	      this->_myEntities.remove(sprite);
	    }
	  else
	    {
	      //std::cout<< "Del sprite dans otherentities"<<std::endl;
	      this->_otherEntities.remove(sprite);
	    }
	}
      else if (sprite->getTypeSpriteEntity() == TYPEWEAPON)
	{
	  Weapon * weapon = dynamic_cast<Weapon*>(sprite);
	  if (weapon)
	    {
	      //std::cout<< "le sprite est un Weapon "<< std::endl;
	      if (weapon->getOwner() == RClient::getInstance()->getShipId())
		{
		  //std::cout<< "Del sprite dans myEntities"<<std::endl;
		  this->_myEntities.remove(sprite);
		}
	      else
		{
		  //std::cout<< "Del sprite dans otherentities"<<std::endl;
		  this->_otherEntities.remove(sprite);
		}
	    }
	}
    }
}

void	WindowZone::printSprites() const
{
  std::list<SpriteEntity *>::const_iterator it = this->_otherEntities.begin();
  std::list<SpriteEntity *>::const_iterator ite = this->_otherEntities.end();
  sf::RenderWindow*	app = RClient::getInstance()->getApp();

  for(; it != ite; ++it)
    {
      if ((*it)->isActioned())
	{
	  app->Draw(*((*it)->getSprite()));
	  (*it)->setActioned(false);
	}
    }

  it = this->_myEntities.begin();
  ite = this->_myEntities.end();
  for(; it != ite; ++it)
    {
      if ((*it)->isActioned())
	{
	  app->Draw(*((*it)->getSprite()));
	  (*it)->setActioned(false);
	}
    }
}

SpriteEntity*	WindowZone::getWeaponSprite(unsigned int weaponId, unsigned int ownerId)
{
  std::list<SpriteEntity *>::const_iterator	it;
  std::list<SpriteEntity *>::const_iterator	ite;
  if (ownerId == RClient::getInstance()->getShipId())
    {
      it = this->_myEntities.begin();
      ite = this->_myEntities.end();
    }
  else
    {
      it = this->_otherEntities.begin();
      ite = this->_otherEntities.end();
    }
  for(; it != ite; ++it)
    {
      if ((*it)->getId() == weaponId &&
	  (*it)->getTypeSpriteEntity() == TYPEWEAPON)
	{
	  Weapon	*tmpSprite = dynamic_cast<Weapon *>(*it);
	  if (tmpSprite)
	    {
	      if (tmpSprite->getOwner() == ownerId)
		return (*it);
	    }
	}
    }
  return (0);
}

SpriteEntity*	WindowZone::getShipSprite(unsigned int spriteid)
{
  std::list<SpriteEntity *>::const_iterator	it;
  std::list<SpriteEntity *>::const_iterator	ite;
  if (spriteid == RClient::getInstance()->getShipId())
    {
      it = this->_myEntities.begin();
      ite = this->_myEntities.end();
    }
  else
    {
      it = this->_otherEntities.begin();
      ite = this->_otherEntities.end();
    }
  for(; it != ite; ++it)
    {
      if ((*it)->getId() == spriteid && (*it)->getTypeSpriteEntity() != TYPEWEAPON)
	{
	  return (*it);
	}
    }
  return (0);
}

void	WindowZone::execNonActioned()
{
  std::list<SpriteEntity *> movedsprite;
  std::list<SpriteEntity *>::const_iterator it = this->_otherEntities.begin();
  std::list<SpriteEntity *>::const_iterator ite = this->_otherEntities.end();
  RClient*	rclient = RClient::getInstance();
  for(; it != ite; ++it)
    {
      if ((*it)->isActioned() == false)
	{
	  (*it)->execActions(rclient->getTime());
	  if ((*it)->move() != '0')
	    {
	      movedsprite.push_back((*it));
	    }
	  (*it)->setActioned(true);
	}
    }
  it = this->_myEntities.begin();
  ite = this->_myEntities.end();
  for(; it != ite; ++it)
    {
      if ((*it)->isActioned() == false)
	{
	  (*it)->execActions(rclient->getTime());
	  if ((*it)->move() != '0')
	    {
	      movedsprite.push_back((*it));
	    }
	  (*it)->setActioned(true);
	}
    }
  it = movedsprite.begin();
  ite = movedsprite.end();
  for(WindowManager* windowmanager = WindowManager::getInstance(); it != ite; ++it)
    {
      windowmanager->updateSpriteInZone((*it));
    }
}

void	WindowZone::flushDestroyZone()
{
  std::list<SpriteEntity *>::iterator save;
  std::list<SpriteEntity *>::iterator it = this->_otherEntities.begin();
  while (it != this->_otherEntities.end())
    {
      save = it;
      ++it;
      this->_otherEntities.erase(save);
    }
  it = this->_myEntities.begin();
  while (it != this->_myEntities.end())
    {
      save = it;
      ++it;
      //WindowManager::getInstance()->delSpriteInZones((*save)); si tu le decommente faire un for et init le windowmanager ds une variable
      this->_myEntities.erase(save);
    }
}
