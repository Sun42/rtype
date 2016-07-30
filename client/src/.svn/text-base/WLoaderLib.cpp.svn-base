#include "WLoaderLib.h"
#include "ExceptionLoaderLib.h"

/*********************************************************************/

WLoaderLib::WLoaderLib()
{
}

WLoaderLib::~WLoaderLib()
{
}

/*********************************************************************/

HANDLELIB	WLoaderLib::LoadingLibrary(std::string const & path)
{
  HMODULE	handlelib = ::LoadLibrary(LPCSTR(path.c_str()));
  std::cout << path << " -- handlelib --> " << handlelib << std::endl;
  if (handlelib == NULL)
    {
      throw (ExceptionLoaderLib::ExceptionLoaderLib("Impossible to load the Library"));
    }
  return (handlelib);
}

PTRSYMBOL	WLoaderLib::GetSymbol(HANDLELIB handlelib, std::string const & symbolname)
{
  FARPROC	ptrfunc = (PTRSYMBOL)GetProcAddress(handlelib, symbolname.c_str());

  if (ptrfunc == NULL)
    {
      throw (ExceptionLoaderLib("Symbol Not find"));
    }
  std::cout << "handleLib --> " << handlelib << " --- nom du symbol -->" << symbolname << " -- Value -->" << ptrfunc << std::endl;
  return (ptrfunc);
}

void	WLoaderLib::UnloadLibrary(HANDLELIB handlelib)
{
  std::cout << "Unload de -->" << handlelib << std::endl;
  if (::FreeLibrary(handlelib) == 0)
    {
      throw (ExceptionLoaderLib("Cannot close the dll"));
    }
}
