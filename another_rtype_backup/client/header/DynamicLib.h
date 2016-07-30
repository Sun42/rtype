#ifndef DYNAMICLIB_H_
# define DYNAMICLIB_H_

#include "ILoaderLib.h"
#include "SpriteEntity.h"

class	DynamicLib
{
 public:
  DynamicLib();
  DynamicLib(DynamicLib const &);
  ~DynamicLib();

  DynamicLib&	operator=(DynamicLib const &);

  HANDLELIB	getHandlelib(void) const ;
  void		setHandlelib(HANDLELIB);
  void		setSymIdentify(PTRSYMBOL);
  void		setSymBuilder(PTRSYMBOL);

  int		getId() const;
  SpriteEntity*	create(unsigned int id, float timeOfCreation, float posX, float posY) const;

 private:
  typedef int (*dllGetId)();
  typedef SpriteEntity*	(*dllCreate)(unsigned int, float, float, float);

  HANDLELIB	_handlelib;
  PTRSYMBOL	_symIdentify;
  PTRSYMBOL	_symBuilder;
};

#endif // DYNAMICLIB_H_
