#ifndef WEAPON_H_
# define WEAPON_H_

#include "SpriteEntity.h"

class	Weapon : public SpriteEntity
{
 public:
  Weapon(int speed, float timeOfCreation, float posXOnMap,
 float posYOnMap, const char* imgPath, unsigned int power,
 unsigned int ownerId);
  Weapon(Weapon const & rhs);
  ~Weapon();
  Weapon&	operator=(Weapon const & rhs);

  unsigned int	getOwner() const;
  void		setOwner(unsigned int ownerid);
  unsigned int	getPower() const;
  unsigned int	getWeaponId();
  typeWeapon	getWeapon(unsigned int i) const;

  unsigned int	touched(float currentTime);

  virtual void	execActions(float currentTime) = 0;
  virtual void	spriteUp() = 0;
  virtual void	spriteDown() = 0;
  virtual void	spriteLeft() = 0;
  virtual void	spriteRight() = 0;

 protected:
  static unsigned int	_cptId;
  unsigned int		_owner;
  unsigned int		_power;
};



#endif // WEAPON_H_
