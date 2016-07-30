#ifndef __PLAYER_H__
# define __PLAYER_H__

#include <boost/asio.hpp>
#include <boost/thread.hpp>

#include "Packet.h"

class	Game;

class	Player
{
 public:
  Player(boost::asio::ip::udp::endpoint& endpoint);
  Player(Player const &);
  ~Player();

  Player&				operator=(Player const &);
  bool					operator==(Player const &) const;

  boost::asio::ip::udp::endpoint&	getEndPoint();
  int					getIdShip() const;
  void					setIdShip(int);

  void					addPacketRecv(boost::array<unsigned char,1024> & buf, unsigned int len);
  void					exec();
  void					sendPacket(Packet & pack);

 private:
  void					funcCreation(Packet & pack);
  void					funcList(Packet & pack);
  void					funcJoin(Packet & pack);
  void					funcJoin2(Packet & pack, Game * findGame, int idGameAsk);
  void					funcDeco(Packet & pack);
  void					funcMove(Packet & pack);
  void					funcKollision(Packet & pack);
  void					funcShoot(Packet & pack);
  void					funcNextLevel(Packet & pack);

 private:
  typedef void (Player::*ptfunc_t)(Packet &);
  boost::asio::ip::udp::endpoint 	_endpoint;
  Game *				_game;
  int					_idShip;
  boost::mutex				_mutexPacketRecv;
  Packet				_packetRecv;
  std::map<char, ptfunc_t>		_mapPtFunc;
};

#endif /* !__PLAYER_H__ */
