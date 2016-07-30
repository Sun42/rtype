#include <cstdlib>
#include <iostream>
#include <signal.h>

#include "Server.h"

void    enrConf(int)
{
  std::cout << "ByeBye !!" << std::endl;
  //Server::killInstance();
  exit(EXIT_FAILURE);
}


int	main(int argc, char* argv[])
{
  signal(SIGINT, enrConf);
  if (argc == 2)
    {
      try
	{
	  Server *	s = Server::createInstance(::atoi(argv[1]));
	  s->run();
	  Server::killInstance();
	}
      catch (std::exception& e)
	{
	  std::cerr << "Exception: " << e.what() << "\n";
	}
    }
  else
    {
      std::cerr << "Usage: " << argv[0] << " <port>\n";
    }
  return (EXIT_SUCCESS);
}
