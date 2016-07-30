#include <boost/archive/xml_iarchive.hpp>
#include <boost/archive/xml_oarchive.hpp>
#include <fstream>
#include <cstdlib>
#include "RClient.h"


void	testParams(int argc)
{
  if (argc != 4)
    {
      std::cerr << "Usage: client_test <ip> <port> <nameGame>" << std::endl;
      ::exit (-1);
    }
}

int	main(int argc, char** argv)
{
  testParams(argc);
  Level level(0);
  level.fillLevel();
  std::ofstream     xmlfile("./levels/Scenario1.xml", std::ios_base::out & std::ios_base::trunc);
  if (xmlfile.is_open())
    {
      boost::archive::xml_oarchive  archivexml(xmlfile);
      archivexml << BOOST_SERIALIZATION_NVP(level);
      xmlfile.close();
    }
  else
    std::cerr << "Error while opening : " << std::endl;
  RClient* client = RClient::getInstance();
  client->run(argv);
  RClient::destroyInstance();
  return (EXIT_SUCCESS);
}

// std::ofstream     xmlfile("Scenario.xml", std::ios_base::out & std::ios_base::trunc);

// if (xmlfile.is_open())
//   {
//     boost::archive::xml_oarchive  archivexml(xmlfile);

//     archivexml << BOOST_SERIALIZATION_NVP(oneScneario);
//     xmlfile.close();
//   }
//  else
//    std::cerr << "Error while opening : " << (*it)->getLogin() << std::endl;
