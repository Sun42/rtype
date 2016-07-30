#include <iostream>
#include "Weapon.h"

/*********************************************************************/
unsigned int Weapon::_cptId = 42;

/*********************************************************************/

Weapon::Weapon(int speed, float timeOfCreation,
	       float posXOnMap, float posYOnMap, const char* imgPath,
	       unsigned power, unsigned ownerId):
  SpriteEntity(Weapon::_cptId, speed, timeOfCreation,
	       posXOnMap, posYOnMap, imgPath, 1), _owner(ownerId), _power(power)
{
//   std::cout<< "Weapon::Weapon() : id: "<< Weapon::_cptId
// 	   << " d'owner: "<< ownerId <<std::endl;
  Weapon::_cptId++;
  this->setTypeSpriteEntity(TYPEWEAPON);
}

Weapon::Weapon(Weapon const & rhs) :
  SpriteEntity(rhs), _owner(rhs._owner), _power(rhs._power)
{
}

Weapon&	Weapon::operator=(Weapon const & rhs)
{
  if (this != &rhs)
    {
      this->_owner = rhs._owner;
      this->_power = rhs._power;
    }
  return (*this);
}

Weapon::~Weapon()
{
}

/*********************************************************************/

unsigned int	Weapon::getOwner() const
{
  return (this->_owner);
}

void		Weapon::setOwner(unsigned int ownerid)
{
  this->_owner = ownerid;
}

unsigned int	Weapon::getPower() const
{
  return (this->_power);
}

unsigned int	Weapon::getWeaponId()
{
  return (this->getId());
}

typeWeapon		Weapon::getWeapon(unsigned int /*i*/) const
{
  return (WEAPON1);
}

/*********************************************************************/

unsigned int	Weapon::touched(float)
{
  return (1);
}
