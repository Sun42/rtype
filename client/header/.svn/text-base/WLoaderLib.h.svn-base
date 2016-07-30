#ifndef WLOADER_LIB_H_
# define WLOADER_LIB_H_

#include "ILoaderLib.h"

class WLoaderLib : public ILoaderLib
{
 public:
  WLoaderLib();
  ~WLoaderLib();

  virtual HANDLELIB	LoadingLibrary(std::string const &);
  virtual PTRSYMBOL	GetSymbol(HANDLELIB, std::string  const &);
  virtual void		UnloadLibrary(HANDLELIB);

 private:
  WLoaderLib(WLoaderLib const &);
  WLoaderLib&		operator=(WLoaderLib const &);
};

#endif // WLOADER_LIB_H_
