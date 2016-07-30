#include <fstream>

#include "FileLoader.h"

/*********************************************************************/

FileLoader::FileLoader() :
  _extensions(), _directory()
{
}

FileLoader::~FileLoader()
{
}

/*********************************************************************/

void		FileLoader::setDirectory(std::string const & directory)
{
  boost::filesystem::path	path(directory);
  if (this->isValidDirectory(directory))
    this->_directory.push_back(path);
}

void		FileLoader::setExtension(std::string const & ext)
{
  this->_extensions.push_back(ext);
}

/*********************************************************************/

bool		FileLoader::isValidDirectory(boost::filesystem::path const & directory) const
{
  if (!boost::filesystem::exists(directory))
    std::cerr << "Path not found" << std::endl;
  else
    if (boost::filesystem::is_directory(directory))
      return (true);
    else
      std::cerr << "You must specify a directory" << std::endl;
  return (false);
}

bool		FileLoader::isValidFile(std::string const & path) const
{
  boost::filesystem::path	mypath(path);
  return (find(this->_extensions.begin(), this->_extensions.end(), boost::filesystem::extension(mypath)) != this->_extensions.end());
}

/*********************************************************************/

void	FileLoader::runInDirectory(std::string const & directory, std::list<DynamicLib *>& listlib) const
{
  boost::filesystem::path	path(directory);
  if (this->isValidDirectory(directory))
    {
      boost::filesystem::directory_iterator dir_itr_end;
      DynamicLib*	onelib;
#ifdef _WIN32
      WLoaderLib	loader;
#else
      ULLoaderLib	loader;
#endif
      for (boost::filesystem::directory_iterator dir_itr((path)); dir_itr != dir_itr_end; ++dir_itr)
	{
	  if (boost::filesystem::is_regular_file(dir_itr->status()) && this->isValidFile(dir_itr->path().string()))
	    {
	      onelib = new DynamicLib();
	      onelib->setHandlelib(loader.LoadingLibrary(dir_itr->path().string()));
	      onelib->setSymIdentify(loader.GetSymbol(onelib->getHandlelib(), "GetType"));
	      onelib->setSymBuilder(loader.GetSymbol(onelib->getHandlelib(), "Builder"));
	      listlib.push_back(onelib);
	    }
	}
    }
}

void		FileLoader::runInDirectory(std::string const & directory, std::list<Level *>& listLevel) const
{
  boost::filesystem::path	path(directory);
  if (this->isValidDirectory(directory))
    {
      std::cout << std::endl << "Directory : " << path << std::endl;
      boost::filesystem::directory_iterator dir_itr_end;
      for (boost::filesystem::directory_iterator dir_itr((path)); dir_itr != dir_itr_end; ++dir_itr)
	{
	  if (boost::filesystem::is_regular_file(dir_itr->status()) && this->isValidFile(dir_itr->path().string()))
	    {
	      std::ifstream	xmlfile(dir_itr->path().string().c_str());
	      if (xmlfile.is_open())
		{
		  std::cout << "Load file : " << dir_itr->path().string()<< std::endl;
		  try
		    {
		      boost::archive::xml_iarchive	archivexml(xmlfile);
		      Level*				oneLevel = new Level();
		      try
			{
			  archivexml >> BOOST_SERIALIZATION_NVP(oneLevel);
			  listLevel.push_front(oneLevel);
			}
		      catch (std::exception const & e)
			{
			  std::cerr << "Failed during acquisition" << e.what() << std::endl;
			}
		    }
		  catch (std::exception const & e)
		    {
		      std::cerr << "Error:" << e.what() << std::endl;
		    }
		  xmlfile.close();
		}
	      else
		{
		  std::cerr << "Error while opening : " << dir_itr->path() << std::endl;
		}
	    }

	}
    }
}
