#include <sstream>

#include "Cmd.h"
#include "Action.h"
#include "RClient.h"
#include "NetworkClient.h"
#include "Ship.h"
#include "WindowManager.h"

//a remove je pense useless
Action::Action() : _mPtr()
{
  this->fillMapPtr();
}


//surcharge ship
Action::Action(unsigned int spriteid, typeAction typeaction,
	       typeSpriteEntity typeSprite, typeShip typeship, std::string param):
  _spriteId(spriteid), _typeAction(typeaction),
  _typeSpriteEntity(typeSprite),  _typeShip(typeship), _params(param)
{
  this->fillMapPtr();
}

//surcharge weapon
Action::Action(typeAction typeaction,
	       typeSpriteEntity typeSprite, typeWeapon typeweapon,
	       std::string param, unsigned int ownerid):
  _typeAction(typeaction),
  _typeSpriteEntity(typeSprite),  _typeWeapon(typeweapon),
  _params(param), _weaponOwnerId(ownerid)
{
  this->fillMapPtr();
}

//surcharge decor
Action::Action(unsigned int spriteid, typeAction typeaction,
	       typeSpriteEntity typeSprite, typeDecor typedecor, std::string param):
  _spriteId(spriteid), _typeAction(typeaction),
  _typeSpriteEntity(typeSprite),  _typeDecor(typedecor), _params(param)
{
  this->fillMapPtr();
}


Action::Action(const Action& rhs):
  _spriteId(rhs._spriteId),_typeAction(rhs._typeAction),
  _typeSpriteEntity(rhs._typeSpriteEntity),_typeShip(rhs._typeShip),
  _typeWeapon(rhs._typeWeapon),_typeDecor(rhs._typeDecor),
  _params(rhs._params),_mPtr(rhs._mPtr),_weaponOwnerId(rhs._weaponOwnerId)
{
}


Action::~Action()
{
}

Action& Action::operator=(const Action& rhs)
{
  if (this != &rhs)
    {
      this->_spriteId = rhs._spriteId;
      this->_typeAction = rhs._typeAction;
      this->_typeSpriteEntity = rhs._typeSpriteEntity;
      this->_typeShip = rhs._typeShip;
      this->_typeWeapon = rhs._typeWeapon;
      this->_typeDecor = rhs._typeDecor;
      this->_params = rhs._params;
      this->_mPtr = rhs._mPtr;
      this->_weaponOwnerId = rhs._weaponOwnerId;
    }
  return (*this);
}


void	Action::fillMapPtr()
{
  this->_mPtr.push_back(&Action::create);
  this->_mPtr.push_back(&Action::move);
  this->_mPtr.push_back(&Action::jump);
  this->_mPtr.push_back(&Action::destroy);
  this->_mPtr.push_back(&Action::shoot);
}

void	Action::execAction()
{
  (this->*this->_mPtr[this->_typeAction])();
}

void	Action::move()
{
  SpriteEntity*	tmpsprite = 0;
  Cmd mycmd(this->_params);

  if (this->_typeSpriteEntity == TYPEWEAPON)
    {
      unsigned spriteId = static_cast<unsigned int>(mycmd.getIntParam(2));
      tmpsprite = WindowManager::getInstance()->getWeaponInZone(spriteId, this->_weaponOwnerId);
      if (!tmpsprite)
	{
	  std::cerr<< "Action::Move() can't get Weapon" <<std::endl;
	  exit(1);
	}
    }
  else
    tmpsprite = WindowManager::getInstance()->getShipInZone(this->_spriteId);
  if (tmpsprite)
    tmpsprite->setDirection(mycmd.getParam(1)[0]);
}

// usage new ACTION(spriteId, JUMP , TYPESHIP un peu inutile mais bon(PLAYER1 || PLAYER2 || PLAYER3 || PLAYER4), "x y")
void		Action::jump()
{
  Cmd mycmd(this->_params);
  if (this->_typeSpriteEntity != TYPESHIP)
    return ;
  WindowManager* wm =  WindowManager::getInstance();
  SpriteEntity*	spr = wm->getShipInZone(this->_spriteId);
  if (!spr)
    return;
  spr->setPosition(mycmd.getFloatParam(1),mycmd.getFloatParam(2));
  wm->updateSpriteInZone(spr);
}

void		Action::create()
{
  Cmd mycmd(this->_params);
  SpriteEntity* spr = 0;
  float timeOC =  RClient::getInstance()->getTime();
  SpriteFactory* SpF = SpriteFactory::getInstance();
  float x = mycmd.getFloatParam(1);
  float y = mycmd.getFloatParam(2);

  if (this->_typeSpriteEntity == TYPESHIP)
    spr = SpF->buildSprite<typeShip>(this->_spriteId, timeOC, x, y, this->_typeShip);
  if (this->_typeSpriteEntity == TYPEWEAPON)
    {
      spr = SpF->buildSprite<typeWeapon>(this->_weaponOwnerId , timeOC, x, y, this->_typeWeapon);
      if (!spr)
	{
	  std::cerr<< " Can't load Sprite of type" << this->_typeSpriteEntity << std::endl;
	  exit(1);
    	}
      if (this->_weaponOwnerId == RClient::getInstance()->getShipId())
	{
	  NetworkClient*	network = RClient::getInstance()->getNetwork();
	  network->funcSendShoot(static_cast<unsigned char>(this->_typeWeapon),
				 static_cast<unsigned int>(x), static_cast<unsigned int>(y));
	}
    }
  if (this->_typeSpriteEntity == TYPEDECOR)
    spr = SpF->buildSprite<typeDecor>(this->_spriteId, timeOC, x, y, this->_typeDecor);
  if (!spr)
    {
      std::cerr<< " Can't load Sprite of type" << this->_typeSpriteEntity << std::endl;
      exit(1);
    }
  WindowManager::getInstance()->addSpriteInZone(spr);
}


// _spriteId, TYPESPRITEENTITY, killerID
void				Action::destroy()
{
  std::cerr<< "Demande de destruction";
  WindowManager* wm = WindowManager::getInstance();
  RClient*	rc =  RClient::getInstance();
  SpriteEntity*	spr = 0;
  Cmd	mycmd(this->_params);
  if (this->_typeSpriteEntity == TYPESHIP)
    {
      std::cerr<< " du vaisseau " << this->_spriteId << std::endl;
      unsigned int killerId = mycmd.getIntParam(1);
      spr = wm->getShipInZone(this->_spriteId);
      //std::cout<< this->_spriteId<< std::endl;
      Ship* ship = dynamic_cast<Ship *>(spr);
      if (!ship)
	return ;
      if (this->_spriteId != rc->getShipId() && killerId == rc->getShipId())
	rc->setScore(ship->getLife() * 100);
    }
  if (this->_typeSpriteEntity == TYPEWEAPON)
    {
      std::cerr<< " d'une arme" << std::endl;
      unsigned int spriteId = mycmd.getIntParam(1);
      spr = wm->getWeaponInZone(spriteId, this->_weaponOwnerId);
    }
  //std::cerr<< "Avant destruction du sprite"<< std::endl;
  if (spr)
    {
      wm->delSpriteInZones(spr);
      if (this->_typeSpriteEntity == TYPESHIP)
	{
	  std::ostringstream os;
	  os << spr->getSprite()->GetPosition().x;
	  os << " ";
	  os << spr->getSprite()->GetPosition().y;
	  Action explodeAction((this->_spriteId * 2) + 50, CREATE, TYPEDECOR, EXPLOSION1, os.str());
	  explodeAction.execAction();
	}
    }
  else
    std::cerr<< "le sprite est NULL" <<std::endl;
  //std::cerr<< "Apres destruction du sprite"<< std::endl;
  delete spr;
}

//specific pour enemi scenario
void		Action::shoot()
{
  WindowManager*	wm = WindowManager::getInstance();
  RClient*		rc = RClient::getInstance();
  SpriteEntity*		myspr = wm->getShipInZone(this->_weaponOwnerId);
  SpriteEntity*		newspr;
  SpriteFactory*	SpF = SpriteFactory::getInstance();
  float			timeOC =  rc->getTime();
  Cmd			mycmd(this->_params);
  if (!myspr)
    {
      std::cerr<< "Can't get owner of weapon"<<std::endl;
      exit(-1);
    }
  newspr = SpF->buildSprite<typeWeapon>(this->_weaponOwnerId , timeOC,
  myspr->getSprite()->GetPosition().x + mycmd.getFloatParam(1),
  myspr->getSprite()->GetPosition().y + mycmd.getFloatParam(2),
 this->_typeWeapon);
  if (!newspr)
    {
      std::cerr<< " Can't load Sprite of type" << this->_typeSpriteEntity << std::endl;
      exit(1);
    }
  if (!newspr)
    {
      std::cerr<< " Can't load Sprite of type" << this->_typeSpriteEntity << std::endl;
      exit(1);
    }
  wm->addSpriteInZone(newspr);
}
