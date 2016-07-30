#ifndef FILELOADER_H_
# define FILELOADER_H_

#include <list>
#include <string>

#include <boost/filesystem/path.hpp>
#include <boost/filesystem/operations.hpp>
#include <boost/filesystem/convenience.hpp>
#include <boost/archive/xml_iarchive.hpp>
#include <boost/archive/xml_oarchive.hpp>
#include <boost/serialization/list.hpp>

#include "DynamicLib.h"
#include "Level.h"
#ifdef _WIN32
#include "WLoaderLib.h"
#else
#include "ULLoaderLib.h"
#endif // _WIN32

class	FileLoader
{
 public:
  FileLoader();
  ~FileLoader();
  void		setDirectory(std::string const &);
  void		setExtension(std::string const &);

  bool		isValidFile(std::string const &) const;
  bool		isValidDirectory(boost::filesystem::path const &) const;

  void		runInDirectory(std::string const &, std::list<DynamicLib *>&) const;
  void		runInDirectory(std::string const &, std::list<Level *>&) const;

 private:
  FileLoader(FileLoader const &);
  FileLoader&	operator=(FileLoader const &);

  std::list<std::string>		_extensions;
  std::list<boost::filesystem::path>	_directory;
};

#endif // FILELOADER_H_
