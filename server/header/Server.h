#ifndef SERVER_H_
# define SERVER_H_

#include <list>

#include <boost/bind.hpp>
#include <boost/asio.hpp>
#include <boost/thread.hpp>

#include "Packet.h"
#include "Game.h"
#include "Player.h"

class	Server
{
 public:
  static const unsigned int	sizeBuffer = 1024;
  static Server*	createInstance(short int port);
  static Server*	getInstance();
  static void		killInstance();

  void			run();
  void			sendTo(boost::asio::ip::udp::endpoint & endpoint, Packet const & data);
  void			handle_receive_from(const boost::system::error_code& , size_t);
  void			handle_send_to(const boost::system::error_code& , size_t, std::vector<unsigned char>*);

  bool			existingGame(std::string const &);
  Game*			createGame(std::string & name, unsigned char nbPlayerMax);
  Packet		listGame();
  Game*			findGame(int idSearch);
  void			destroyPlayer(Player * player);
  void			destroyGame(Game * game);

 private:
  Server(short int port);
  Server(Server const &);
  Server &		operator=(Server const &);
  ~Server();

  Player*		selectPlayer();

 private:
  static Server*					_instance;

  boost::asio::io_service				_io_service;
  boost::asio::ip::udp::socket				_socket;
  boost::asio::ip::udp::endpoint			_sender_endpoint;
  boost::array<unsigned char, Server::sizeBuffer>	_bufferReceiv;
  int							_numIdGame;
  boost::mutex						_mutexGames;
  std::list<Game *>					_games;
  boost::mutex						_mutexPlayers;
  std::list<Player *>					_players;
};

#endif // SERVER_H_
