#include "Server.h"

/*********************************************************************/
Server* Server::_instance = 0;
/*********************************************************************/

Server*	Server::createInstance(short int port)
{
  if (Server::_instance == 0)
    {
      std::cout << "Creation du serveur\n";
      Server::_instance = new Server(port);
    }
  return (Server::_instance);
}

Server*	Server::getInstance()
{
  return Server::_instance;
}

void	Server::killInstance()
{
  if (Server::_instance)
    delete Server::_instance;
}

/*********************************************************************/

Server::Server(short int port)
  : _socket(this->_io_service, boost::asio::ip::udp::endpoint(boost::asio::ip::udp::v4(), port)), _numIdGame(1)
{
  this->_socket.async_receive_from(
				   boost::asio::buffer(this->_bufferReceiv, Server::sizeBuffer), this->_sender_endpoint,
				   boost::bind(&Server::handle_receive_from, this,
					       boost::asio::placeholders::error,
					       boost::asio::placeholders::bytes_transferred));
}

Server::~Server()
{
}

/*********************************************************************/

void	Server::run()
{
  this->_io_service.run();
}

void	Server::sendTo(boost::asio::ip::udp::endpoint & endpoint, Packet const & data)
{
  std::vector<unsigned char>	*bufToSend = data.getData();
  this->_socket.async_send_to(boost::asio::buffer(*bufToSend), endpoint,
			      boost::bind(&Server::handle_send_to, this,
					  boost::asio::placeholders::error,
					  boost::asio::placeholders::bytes_transferred, bufToSend));
}

void	Server::handle_receive_from(const boost::system::error_code& error, size_t bytes_recvd)
{
  if (!error && bytes_recvd > 0)
    {
      std::cout << "\nNew Requete : "<< std::endl;
      for (unsigned int i = 0; i < bytes_recvd; i++)
	{
	  std::cout << "[" << (int)_bufferReceiv[i] << "]";
	}
      this->_mutexPlayers.lock();
      Player*	playerUse = this->selectPlayer();
      playerUse->addPacketRecv(this->_bufferReceiv, bytes_recvd);
      playerUse->exec();
      this->_mutexPlayers.unlock();
    }
  this->_socket.async_receive_from(boost::asio::buffer(this->_bufferReceiv, Server::sizeBuffer), this->_sender_endpoint,
				   boost::bind(&Server::handle_receive_from, this,
					       boost::asio::placeholders::error,
					       boost::asio::placeholders::bytes_transferred));
}

void	Server::handle_send_to(const boost::system::error_code& err, size_t sizeSent, std::vector<unsigned char>* bufferSent)
{
  std::cout << "Size Sent : " << sizeSent << std::endl;
  if (!err)
    {
      delete bufferSent;
    }
//   else
//     {
//       if (sizeSent != bufferSent->size())
// 	{
// 	  this->_socket.async_send_to(boost::asio::buffer(*bufferSent), endpoint,
// 				      boost::bind(&Server::handle_send_to, this,
// 						  boost::asio::placeholders::error,
// 						  boost::asio::placeholders::bytes_transferred, bufferSent));

// 	}
//     }
}

/*********************************************************************/

Player*		Server::selectPlayer()
{
  std::list<Player *>::iterator it = this->_players.begin();
  std::list<Player *>::iterator it_end = this->_players.end();
  std::cout << "Nb players on server : " << this->_players.size() << std::endl;
  for (; it != it_end; ++it)
    {
      if (this->_sender_endpoint == (*it)->getEndPoint())
	return (*it);
    }
  std::cerr << "New player from " << this->_sender_endpoint << std::endl;
  this->_players.push_back(new Player(this->_sender_endpoint));
  return (this->_players.back());
}

Game*		Server::createGame(std::string & name, unsigned char nbPlayerMax)
{
  boost::mutex::scoped_lock	lock(this->_mutexGames);

  this->_games.push_back(new Game(name, nbPlayerMax, this->_numIdGame));
  std::cout << "Nb games : " << this->_games.size() << std::endl;
  ++this->_numIdGame;
  return (this->_games.back());
}

Packet		Server::listGame()
{
  Packet	listPacket;

  this->_mutexGames.lock();
  std::list<Game*>::iterator	it = this->_games.begin();
  std::list<Game*>::iterator	itEnd = this->_games.end();
  std::cout << "NB Games : " << this->_games.size() << std::endl;
  for(; it != itEnd; ++it)
    {
      listPacket << (*it)->getId() << (*it)->getName();
    }
  this->_mutexGames.unlock();
  return (listPacket);
}

Game*		Server::findGame(int idGameSearch)
{
  boost::mutex::scoped_lock	lock(this->_mutexGames);
  std::list<Game*>::iterator	it = this->_games.begin();
  std::list<Game*>::iterator	itEnd = this->_games.end();

  for(; it != itEnd; ++it)
    {
      if ((*it)->getId() == idGameSearch)
	{
	  return (*it);
	}
    }
  return 0;
}

bool		Server::existingGame(std::string const & nameGame)
{
  boost::mutex::scoped_lock		lock(this->_mutexGames);

  std::list<Game*>::const_iterator	it = this->_games.begin();
  std::list<Game*>::const_iterator	itEnd = this->_games.end();

  for(; it != itEnd; ++it)
    {
      if ((*it)->getName() == nameGame)
	{
	  return (true);
	}
    }
  return (false);
}

void		Server::destroyPlayer(Player * player)
{
  this->_mutexPlayers.lock();
  this->_players.remove(player);
  this->_mutexPlayers.unlock();
}

void		Server::destroyGame(Game * game)
{
  this->_mutexGames.lock();
  this->_games.remove(game);
  this->_mutexGames.unlock();
}
