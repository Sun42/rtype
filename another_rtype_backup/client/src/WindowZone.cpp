#include "WindowZone.h"
#include "RClient.h"
#include "Collision.h"
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
		if (Collision::PixelPerfectTest((*spr1->getSprite()), (*spr2->getSprite())))
	{
	  if (spr1->getId() == shipId) // Si c'est mon joueur qui touche quelqueChose
	    {
	      if (!spr1->touched(RClient::getInstance()->getTime()))
		{
		  RClient::getInstance()->exitDie();
		}
	    }
	  else // Sinon c'est une de mes balle qui touche QuelqueChose autre qu'un player
	    {
	      unsigned int idBall, idVictim, idVictimBall, lifeShip, powerShoot;
	      unsigned char typeVictim;
	      Weapon* weap = dynamic_cast<Weapon*>(spr1);
	      if (weap)
		{
		  idBall = spr1->getId();
		  powerShoot = weap->getPower();
		  if (spr2->getTypeSpriteEntity() == TYPEWEAPON)
		    {
		      //std::cerr << "1\n";
		      Weapon* weap2 = static_cast<Weapon*>(spr2);
		      idVictim = weap2->getOwner();
		      idVictimBall = spr2->getId();
		      lifeShip = 1;
		      typeVictim = 'W';
		    }
		  if (spr2->getTypeSpriteEntity() == TYPESHIP)
		    {
		      //std::cerr << "2\n";
		      Ship* ship = static_cast<Ship*>(spr2);
		      idVictim = spr2->getId();
		      idVictimBall = 0;
		      lifeShip = ship->getLife();
		      typeVictim = 'S';
		    }
		  network->funcSendCollision(idBall, idVictim, idVictimBall, lifeShip, powerShoot, typeVictim);
		  network->funcSendCollision(0, weap->getOwner(), spr1->getId(), 1, powerShoot, 'W');
		}
	    }
	}
    }
}


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
	  Weapon * weapon = static_cast<Weapon*>(sprite);
	      if (weapon->getOwner() == RClient::getInstance()->getShipId())
		this->_myEntities.push_back(sprite);
	      else
		this->_otherEntities.push_back(sprite);
	}
    }
}

void	WindowZone::delSpriteEntity(SpriteEntity* sprite)
{
  if (!sprite)
    {
      return ;
    }
  if (this->checkIfExist(sprite))
    {
      if (sprite->getTypeSpriteEntity() != TYPEWEAPON)
	{
	  if (RClient::getInstance()->getShipId() == sprite->getId())
	    {
	      this->_myEntities.remove(sprite);
	    }
	  else
	    {
	      this->_otherEntities.remove(sprite);
	    }
	}
      else if (sprite->getTypeSpriteEntity() == TYPEWEAPON)
	{
	  Weapon * weapon = static_cast<Weapon*>(sprite);
	      if (weapon->getOwner() == RClient::getInstance()->getShipId())
		{
		  this->_myEntities.remove(sprite);
		}
	      else
		{
		  this->_otherEntities.remove(sprite);
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
	  Weapon	*tmpSprite = static_cast<Weapon *>(*it);
	      if (tmpSprite->getOwner() == ownerId)
		return (*it);
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
