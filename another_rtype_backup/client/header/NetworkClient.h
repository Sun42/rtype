#ifndef __NETWORKCLIENT_H__
# define __NETWORKCLIENT_H__

#include <boost/asio.hpp>
#include <boost/bind.hpp>
#include <boost/thread.hpp>

#include "Packet.h"
#include "Action.h"

class	NetworkClient
{
 public:
  static unsigned int const					sizeBuffer = 1024;

  NetworkClient(char const * ip, char const * port);
  ~NetworkClient();

  void		run();
  void		handle_receive_from(const boost::system::error_code& , size_t);
  void		handle_send_to(const boost::system::error_code& err, size_t sizeSent, std::vector<unsigned char>* bufferSent);

  void		initGame(char * nameGame, char nbPlayer);
  void		checkNetwork(std::list<Action*>& actions);

  void		funcSendNew(unsigned char nbPlayerMax, std::string & nameGame);
  void		funcSendList();
  void		funcSendJoin(unsigned int idGame);
  void		funcSendDeco();
  void		funcSendMove(unsigned char direction);
  void		funcSendCollision(unsigned int idBall, unsigned int idVictim, unsigned int idVictimBall, 
				  unsigned int lifeShip, unsigned int powerShoot, unsigned char typeVictim);
  void		funcSendShoot(unsigned char idWeapon, unsigned int X, unsigned int Y);

 private:
  NetworkClient(NetworkClient const &);
  NetworkClient &	operator=(NetworkClient const &);

  void			sendTo(Packet & pack);
  bool			execRecv(std::list<Action*>& actions);
  void			funcRecvCreation(Packet & packet, std::list<Action*>&);
  void			funcRecvList(Packet & packet, std::list<Action*>&);
  void			funcRecvJoin(Packet & packet, std::list<Action*>& actions);
  void			funcRecvBegin(Packet & packet, std::list<Action*>& actions);
  void			funcRecvDeco(Packet & packet, std::list<Action*>& actions);
  void			funcRecvMove(Packet & packet, std::list<Action*>& actions);
  void			funcRecvKollision(Packet & packet, std::list<Action*>& actions);
  void			funcRecvShoot(Packet & packet, std::list<Action*>& actions);

 private:
  typedef void (NetworkClient::*ptfunc_t)(Packet&, std::list<Action*>&);
  boost::asio::io_service					_io_service;
  boost::asio::ip::udp::endpoint				_endpointRecv;
  boost::asio::ip::udp::endpoint				_endpointSend;
  boost::asio::ip::udp::socket					_socket;
  boost::asio::ip::udp::resolver				_resolver;
  boost::asio::ip::udp::resolver::iterator			_itSocket;
  boost::array<unsigned char, NetworkClient::sizeBuffer>	_bufferReceiv;

  Packet*							_usePacket;
  boost::mutex							_mutexTabPacket;
  std::list<Packet*>						_tabPacket;
  int								_idGame;
  unsigned char							_idShip;
  std::string							_nameGame;
  std::map<char, ptfunc_t>					_mapPtFunc;
};

#endif /* !__NETWORKCLIENT_H__ */
