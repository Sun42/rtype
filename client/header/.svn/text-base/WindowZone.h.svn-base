#ifndef WINDOWZONE_H_
#define WINDOWZONE_H_

#include <list>
#include "SpriteEntity.h"
#include "Collision.h"

class WindowZone
{
 public:
  WindowZone();
  WindowZone(const WindowZone& r);
  ~WindowZone();
  WindowZone& operator=(const WindowZone& r);
  bool			checkIfExist(SpriteEntity* sprite);
  void			checkCollisionSprite(SpriteEntity* spr1, SpriteEntity* spr2);
  void			checkCollision();
  void			addSpriteEntity(SpriteEntity* sprite);
/*  void			delSpriteEntity(unsigned int id);*/
  bool			checkObject(SpriteEntity* spr1, SpriteEntity* spr2);
  void			printSprites() const;
  SpriteEntity*		getShipSprite(unsigned int spriteid);
  SpriteEntity*		getWeaponSprite(unsigned int weaponId, unsigned int ownerId);
  void			execNonActioned();
  void			delSpriteEntity(SpriteEntity* sprite);
  //void			flushDestroyZone(SpriteEntity* sp1, SpriteEntity* sp2);
  void			flushDestroyZone();
  void			call_destroy();
 private:
  std::list<SpriteEntity *>	_myEntities;
  std::list<SpriteEntity *>	_otherEntities;
  //std::list<SpriteEntity *>	_delEntities;
};

#endif //! WINDOWZONE_H_
