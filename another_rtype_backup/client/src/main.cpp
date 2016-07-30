#include <boost/archive/xml_iarchive.hpp>
#include <boost/archive/xml_oarchive.hpp>
#include <fstream>
#include <cstdlib>
#include "RClient.h"


void	testParams(int argc, char **argv)
{
  if (argc != 5)
    {
      std::cerr << "Usage: " << argv[0] << " <ip> <port> <nameGame> <nbPlayer>" << std::endl;
      ::exit (-1);
    }
  if (::strlen(argv[4]) != 1 || !(*argv[4] >= '1' && *argv[4] <= '4'))
    {
      std::cerr << "nbPlayer : 2 to 4" << std::endl;
      ::exit (-1);
    }
}

int	main(int argc, char** argv)
{
  testParams(argc, argv);
  RClient* client = RClient::getInstance();
  client->run(argv);
  RClient::destroyInstance();
  return (EXIT_SUCCESS);
}
