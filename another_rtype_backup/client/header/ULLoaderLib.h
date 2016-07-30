#ifndef ULLOADERLIB_H_
# define ULLOADERLIB_H_

#include "ILoaderLib.h"

class ULLoaderLib : public ILoaderLib
{
 public:
  ULLoaderLib();
  ~ULLoaderLib();

  virtual HANDLELIB	LoadingLibrary(std::string const &);
  virtual PTRSYMBOL	GetSymbol(HANDLELIB, std::string  const &);
  virtual void		UnloadLibrary(HANDLELIB);

 private:
  ULLoaderLib(ULLoaderLib const &);
  ULLoaderLib&		operator=(ULLoaderLib const &);
};

#endif // ULLOADERLIB_H_
