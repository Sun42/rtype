#ifndef SPRITEFACTORY_HPP_
# define SPRITEFACTORY_HPP_

#include <list>

#include "SpriteEntity.h"
#include "DynamicLib.h"

class	SpriteFactory
{
 public:
  static SpriteFactory*	getInstance();
  static void		destroyInstance();

  SpriteEntity*			buildSprite(std::list<DynamicLib *>::const_iterator it,
					    std::list<DynamicLib *>::const_iterator itend,
					    unsigned int id, float timeOfCreation,
					    float posX, float posY, int type);

  template<typename T>
    SpriteEntity*		buildSprite(unsigned int, float, float, float, T);

 private:
  SpriteFactory();
  ~SpriteFactory();

 private:
  static SpriteFactory*			_instance;

#ifdef _WIN32
  typedef SpriteEntity*	(*methodPtrShip)(unsigned int id, float timeOfCreation, float posXOnMap, float posYOnMap);
  typedef SpriteEntity*	(*methodPtrWeapon)(unsigned int ownerid, float timeOfCreation, float posXOnMap, float posYOnMap);
  typedef SpriteEntity*	(*methodPtrDecor)(unsigned int id, float timeOfCreation, float posXOnMap, float posYOnMap);

  std::map<typeShip, methodPtrShip>	_ptrMapShip;
  std::map<typeWeapon, methodPtrWeapon>	_ptrMapWeapon;
  std::map<typeDecor, methodPtrDecor>	_ptrMapDecor;
#else
  void			unloadLibrary(std::list<DynamicLib *>& libs);

  std::list<DynamicLib *>		_weaponLibs;
  std::list<DynamicLib *>		_shipLibs;
  std::list<DynamicLib *>		_decorLibs;
#endif // _WIN32
};

#endif // SPRITEFACTORY_HPP_
