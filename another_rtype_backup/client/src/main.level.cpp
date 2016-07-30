#include <boost/archive/xml_iarchive.hpp>
#include <boost/archive/xml_oarchive.hpp>
#include <fstream>
#include <cstdlib>
#include "RClient.h"


void	testParams(int argc, char **argv)
{
  if (argc != 2)
    {
      std::cerr << "Usage: ./scenarioGenerator fileName" << std::endl;
      ::exit (-1);
    }
  if (strlen(argv[1]) <  4)
    {
      std::cerr << "Len of fileName should be > 4 chars" << std::endl;
      exit(-1);
    }
}

int	main(int argc, char** argv)
{
  testParams(argc, argv);
  Level level(0);
  level.fillLevel();
  std::ofstream     xmlfile(argv[1], std::ios_base::out & std::ios_base::trunc);
  if (xmlfile.is_open())
    {
      boost::archive::xml_oarchive  archivexml(xmlfile);
      archivexml << BOOST_SERIALIZATION_NVP(level);
      xmlfile.close();
    }
  else
    {
      std::cerr << "Error while opening : " << std::endl;
      return(EXIT_FAILURE);
    }
  return (EXIT_SUCCESS);
}
