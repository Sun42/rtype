#ifndef ILOADER_LIB_H_
# define ILOADER_LIB_H_

#include <iostream>
#include <string>

#ifdef _WIN32
# include <windows.h>
typedef HMODULE	HANDLELIB;
typedef FARPROC	PTRSYMBOL;
#else
# include <dlfcn.h>
typedef void*	HANDLELIB;
typedef void*	PTRSYMBOL;
#endif // _WIN32

class	ILoaderLib
{
 public:
  virtual ~ILoaderLib(){}
  virtual HANDLELIB		LoadingLibrary(std::string const &) = 0;
  virtual PTRSYMBOL		GetSymbol(HANDLELIB, std::string  const &) = 0;
  virtual void			UnloadLibrary(HANDLELIB) = 0;
};

#endif // ILOADER_LIB_H_
