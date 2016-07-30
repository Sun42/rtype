#ifndef WINDOWMANAGER_H_
#define WINDOWMANAGER_H_

#include <vector>
#include <SFML/Graphics.hpp>
#include "WindowZone.h"

class WindowManager
{
 public:
  static WindowManager*	getInstance();
  static void		destroyInstance();

  void			addSpriteInZone(SpriteEntity* sprite);
  void			printMap() const;
  void			delSpriteInZones(SpriteEntity* sprite);
  SpriteEntity*		getShipInZone(unsigned int spriteid);
  SpriteEntity*		getWeaponInZone(unsigned int weaponId, unsigned int ownerId);
  void			execNonActioned() const;
  void			updateSpriteInZone(SpriteEntity* sprite);
  void			checkCollision();
  void			flushDestroyZones();

 private:
  WindowManager();
  WindowManager(const WindowManager& r);
  ~WindowManager();
  WindowManager& operator=(const WindowManager& r);


 private:
  static WindowManager*		_instance;
  int				_windowZoneSize;
  std::vector<WindowZone *>	_windowZones;
};

#endif //! WINDOWMANAGER_H_
