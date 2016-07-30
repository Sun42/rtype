#ifndef DECOR_H_
# define DECOR_H_

#include "SpriteEntity.h"

class	Decor : public SpriteEntity
{
 public:
  Decor(unsigned int idDecor, int speed, float timeOfCreation, float posXOnMap,
 float posYOnMap, const char* imgPath, unsigned int deep);
  Decor(Decor const & rhs);
  ~Decor();
  Decor&	operator=(Decor const & rhs);
  virtual unsigned int		touched(float currentTime) = 0;
  virtual void	execActions(float currentTime) = 0;
  virtual void	spriteUp() = 0;
  virtual void	spriteDown() = 0;
  virtual void	spriteLeft() = 0;
  virtual void	spriteRight() = 0;
 protected:
};



#endif // DECOR_H_
