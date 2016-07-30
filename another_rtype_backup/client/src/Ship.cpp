#include <sstream>
#include "Ship.h"
#include "RClient.h"
#include "Weapon1.h"
#include "Weapon2.h"

/*********************************************************************/

Ship::Ship(unsigned int id, int speed, float timeOfCreation,
	   float posXOnMap, float posYOnMap, const char* imgPath,
	   unsigned int life) :
  SpriteEntity(id,  speed, timeOfCreation, posXOnMap, posYOnMap, imgPath, 1),
  _lastTouchedTime(0),_life(life), _imgPath(imgPath), _weaponsInventory(),
  _currentWeapon(WEAPON1),  _lastShootTime()
{
  this->_weaponFrequencies[WEAPON1] = Weapon1::getFrequency();
  this->_weaponFrequencies[WEAPON2] = Weapon2::getFrequency();
  this->_weaponsInventory.push_back(WEAPON1);
  this->_weaponsInventory.push_back(WEAPON2);
  this->setTypeSpriteEntity(TYPESHIP);
}

Ship::Ship(const Ship& rhs):
  SpriteEntity(rhs),  _lastTouchedTime(rhs._lastTouchedTime), _life(rhs._life), _imgPath(rhs._imgPath.c_str()),
  _weaponsInventory(rhs._weaponsInventory),
  _currentWeapon(rhs._currentWeapon), _lastShootTime(rhs._lastShootTime)
{
}

Ship::~Ship()
{

}

Ship& Ship::operator=(const Ship& rhs)
{
  if (this != &rhs)
    {
      this->_life = rhs._life;
      this->_imgPath = rhs._imgPath;
      this->_weaponsInventory = rhs._weaponsInventory;
      this->_lastShootTime = rhs._lastShootTime;
      this->_lastTouchedTime = rhs._lastTouchedTime;
    }
  return (*this);
}

/*********************************************************************/

typeShip	Ship::getNumPlayer(unsigned int shipid)
{
  typeShip	tab[]=
    {
      PLAYER1,
      PLAYER2,
      PLAYER3,
      PLAYER4
    };
  return (tab[shipid]);
}

unsigned int	Ship::getLife() const
{
  return (this->_life);
}

/*********************************************************************/
void		Ship::shoot(std::list<Action*>& actions)
{
  if (this->_lastShootTime.GetElapsedTime() < this->_weaponFrequencies[this->_currentWeapon])
    return ;
  std::ostringstream os;
  os << this->getSprite()->GetPosition().x + Ship::decWeapX;
  os << " " << this->getSprite()->GetPosition().y + Ship::decWeapY;
  actions.push_back(new Action(CREATE, TYPEWEAPON,
			       this->_weaponsInventory[this->_currentWeapon],
			       (os.str()).c_str(), this->getId()));
  this->_lastShootTime.Reset();
}

unsigned int	Ship::touched(float currentTime)
{
  if (this->getId() == RClient::getInstance()->getShipId() && (currentTime - this->_lastTouchedTime) > 3)
    {
      this->_lastTouchedTime = currentTime;
      return (this->_life -= 1);
    }
  return (this->_life);
}


void Ship::changeWeapon()
{
  if (static_cast<unsigned>(this->_currentWeapon) < (this->_weaponsInventory.size() - 1))
    this->_currentWeapon = static_cast<typeWeapon>(this->_currentWeapon + 1);
  else
    this->_currentWeapon = WEAPON1;
}
