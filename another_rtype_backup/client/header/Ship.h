#ifndef SHIP_H
#define SHIP_H

#include <vector>
#include <list>
#include <map>
#include "SpriteEntity.h"
#include "Scenario.h"
#include "Weapon.h"
#include "RClient.h"

class Ship : public SpriteEntity
{
 public:
  static const unsigned int decWeapX = 55;
  static const unsigned int decWeapY = 15;

  Ship(unsigned int id, int speed, float timeOfCreation,
	   float posXOnMap, float posYOnMap, const char* imgPath,
	     unsigned int life);
  Ship(const Ship& rhs);
  virtual ~Ship();

  Ship&			operator=(const Ship& rhs);

  unsigned int		getLife() const;
  static typeShip	getNumPlayer(unsigned int shipid);

  void			shoot(std::list<Action*>& actions);
  unsigned int		touched(float currentTime);
  void			changeWeapon();
  virtual void		execActions(float currentTime) = 0;
  virtual void		spriteUp() = 0;
  virtual void		spriteDown() = 0;
  virtual void		spriteLeft() = 0;
  virtual void		spriteRight() = 0;

protected:
  float				_lastTouchedTime;

 private:
  unsigned int			_life;
  std::string			_imgPath;
  std::vector<typeWeapon>	_weaponsInventory;
  typeWeapon			_currentWeapon;
  sf::Clock			_lastShootTime;
  std::map<typeWeapon, float>	_weaponFrequencies;
};

#endif //SHIP_H
