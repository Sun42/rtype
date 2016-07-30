#include <iostream>
#include "Decor.h"

/*********************************************************************/

Decor::Decor(unsigned int idDecor, int speed, float timeOfCreation,
	       float posXOnMap, float posYOnMap, const char* imgPath, unsigned int deep):
  SpriteEntity(idDecor, speed, timeOfCreation,
  posXOnMap, posYOnMap, imgPath, deep)
{
  this->setTypeSpriteEntity(TYPEDECOR);
}

Decor::Decor(Decor const & rhs) :
  SpriteEntity(rhs)
{
}

Decor&	Decor::operator=(Decor const &)
{
  return (*this);
}

Decor::~Decor()
{
}

/*********************************************************************/
