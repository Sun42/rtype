#include "SpriteFactory.h"
#include "WindowManager.h"
#include "SpriteEntity.h"

#ifdef _WIN32
# include "Monster1.h"	//Ships
# include "Player1.h"	//Ships
# include "Player2.h"	//Ships
# include "Player3.h"	//Ships
# include "Player4.h"	//Ships
# include "Weapon1.h"	//Weapons
# include "Weapon2.h"	//Weapons
# include "Explosion1.h" //Explosion
#else
# include "FileLoader.h"
#endif // _WIN32

/*********************************************************************/
SpriteFactory*	SpriteFactory::_instance = 0;
/*********************************************************************/

SpriteFactory*	SpriteFactory::getInstance()
{
  if (!SpriteFactory::_instance)
    {
      SpriteFactory::_instance = new SpriteFactory();
    }
  return (SpriteFactory::_instance);
}

void	SpriteFactory::destroyInstance()
{
  if (SpriteFactory::_instance)
    {
      delete SpriteFactory::_instance;
      SpriteFactory::_instance = 0;
    }
}

/***************************** WINDOWS ****************************************/

#ifdef _WIN32

SpriteFactory::SpriteFactory(): _ptrMapShip(), _ptrMapWeapon(), _ptrMapDecor()
{
  this->_ptrMapShip[PLAYER1] = &::BuilderPlayer1;
  this->_ptrMapShip[PLAYER2] = &::BuilderPlayer2;
  this->_ptrMapShip[PLAYER3] = &::BuilderPlayer3;
  this->_ptrMapShip[PLAYER4] = &::BuilderPlayer4;
  this->_ptrMapShip[MONSTER1] = &::BuilderMonster1;
  this->_ptrMapWeapon[WEAPON1] = &::BuilderWeapon1;
  this->_ptrMapWeapon[WEAPON2] = &::BuilderWeapon2;
  this->_ptrMapDecor[EXPLOSION1] = &::BuilderExplosion1;
}

SpriteFactory::~SpriteFactory()
{
}

/*****************************/

template<>
SpriteEntity*	SpriteFactory::buildSprite<typeShip>(unsigned int id, float timeOfCreation, float posX, float posY, typeShip type)
{
  std::map<typeShip, methodPtrShip>::iterator	itFind = this->_ptrMapShip.find(type);
  if (itFind != this->_ptrMapShip.end())
    return (*((*itFind).second))(id, timeOfCreation, posX, posY);
  return (0);
}

template<>
SpriteEntity*	SpriteFactory::buildSprite<typeWeapon>(unsigned int ownerid, float timeOfCreation, float posX, float posY,
		typeWeapon type)
{
  //std::cout<< "SpriteFactory::buildSprite<typeWeapon>(): ownerid: "<< ownerid <<std::endl;

  std::map<typeWeapon, methodPtrWeapon>::iterator	itFind = this->_ptrMapWeapon.find(type);
  if (itFind != this->_ptrMapWeapon.end())
    return (*(*itFind).second)(ownerid, timeOfCreation, posX, posY);
  return (0);
}

template<>
SpriteEntity*	SpriteFactory::buildSprite<typeDecor>(unsigned int id, float timeOfCreation, float posX, float posY, typeDecor type)
{
  std::map<typeDecor, methodPtrDecor>::iterator		itFind = this->_ptrMapDecor.find(type);
  if (itFind != this->_ptrMapDecor.end())
    return (*(*itFind).second)(id, timeOfCreation, posX, posY);
  return (0);
}


/***************************** UNIX ****************************************/
#else

SpriteFactory::SpriteFactory()
{
  FileLoader	loader;
  //   #ifdef _WIN32
  //   loader.setExtension(".dll");
  // #else
  loader.setExtension(".so");
  //#endif
  std::cout << "\033[34mLoad des libs Ships" << std::endl;
  loader.runInDirectory("libs/ships/", this->_shipLibs);
  std::cout << "Load des libs Weapons" << std::endl;
  loader.runInDirectory("libs/weapons/", this->_weaponLibs);
  std::cout << "Load des libs Decors" << std::endl;
  loader.runInDirectory("libs/decors/", this->_decorLibs);
  std::cout << "\033[39m";
}

SpriteFactory::~SpriteFactory()
{
  std::cout << "\033[34mUnLoad des libs Weapons" << std::endl;
  this->unloadLibrary(this->_weaponLibs);
  std::cout << "\nUnLoad des libs Ships" << std::endl;
  this->unloadLibrary(this->_shipLibs);
  std::cout << "\nUNLoad des libs DEcor" << std::endl;
  this->unloadLibrary(this->_decorLibs);
  std::cout << "\033[39m";
}

/*****************************/

void	SpriteFactory::unloadLibrary(std::list<DynamicLib *>& libs)
{
  std::list<DynamicLib *>::const_iterator	it = libs.begin();
  std::list<DynamicLib *>::const_iterator	itend = libs.end();

  for (;it != itend; ++it)
    {
      delete *it;
    }
}

SpriteEntity*	SpriteFactory::buildSprite(std::list<DynamicLib *>::const_iterator it,
					   std::list<DynamicLib *>::const_iterator itend,
					   unsigned int id, float timeOfCreation,
					   float posX, float posY, int type)
{
  for (;it != itend; ++it)
    {
      if (type == (*it)->getId())
	{
	  return ((*it)->create(id, timeOfCreation, posX, posY));
	}
    }
  return (0);
}

template<>
SpriteEntity*	SpriteFactory::buildSprite<typeShip>(unsigned int id, float timeOfCreation, float posX, float posY, typeShip type)
{
  return (this->buildSprite(this->_shipLibs.begin(), this->_shipLibs.end(), id, timeOfCreation, posX, posY, static_cast<int>(type)));
}

template<>
SpriteEntity*	SpriteFactory::buildSprite<typeWeapon>(unsigned int ownerid, float timeOfCreation, float posX, float posY, typeWeapon type)
{
  return (this->buildSprite(this->_weaponLibs.begin(), this->_weaponLibs.end(), ownerid, timeOfCreation, posX, posY, static_cast<int>(type)));
}

template<>
SpriteEntity*	SpriteFactory::buildSprite<typeDecor>(unsigned int id, float timeOfCreation, float posX, float posY, typeDecor type)
{
  return (this->buildSprite(this->_decorLibs.begin(), this->_decorLibs.end(), id, timeOfCreation, posX, posY, static_cast<int>(type)));
}

#endif
