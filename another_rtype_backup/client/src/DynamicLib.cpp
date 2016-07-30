#include "DynamicLib.h"
#ifdef _WIN32
# include "WLoaderLib.h"
#else
# include "ULLoaderLib.h"
#endif // _WIN32

/*********************************************************************/

DynamicLib::DynamicLib() :
  _handlelib(0), _symIdentify(0), _symBuilder(0)
{
}

DynamicLib::~DynamicLib()
{
#ifdef _WIN32
  WLoaderLib	loader;
#else
  ULLoaderLib	loader;
#endif
  loader.UnloadLibrary(this->_handlelib);
}

/*********************************************************************/

void		DynamicLib::setHandlelib(HANDLELIB src)
{
  this->_handlelib = src;
}

void		DynamicLib::setSymIdentify(PTRSYMBOL src)
{
  this->_symIdentify = src;

}

void		DynamicLib::setSymBuilder(PTRSYMBOL src)
{
  this->_symBuilder = src;
}

HANDLELIB	DynamicLib::getHandlelib(void) const
{
  return (this->_handlelib);
}

/*********************************************************************/

int	DynamicLib::getId() const
{
  DynamicLib::dllGetId getIdSprite = (DynamicLib::dllGetId)this->_symIdentify;
  return (getIdSprite());
}

SpriteEntity*	DynamicLib::create(unsigned int id, float timeOfCreation, float posX, float posY) const
{
  DynamicLib::dllCreate createSprite = (DynamicLib::dllCreate)this->_symBuilder;
  return (createSprite(id, timeOfCreation, posX, posY));
}
