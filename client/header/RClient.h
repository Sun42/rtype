#ifndef RCLIENT_H_
#define RCLIENT_H_

#include <list>

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>


#include "Action.h"
#include "Level.h"
#include "Input.h"
#include "NetworkClient.h"

class	RClient
{
 public:
  static RClient*	getInstance();
  static void		destroyInstance();

  sf::RenderWindow*	getApp() const;
  NetworkClient*	getNetwork() const;
  float			getTime() const;
  void			setShipId(unsigned int shipid);
  unsigned int		getShipId() const;
  void			setLevel(int level);
  int				getLevel(int level) const;
  std::string		getScore();
  void				setScore(unsigned int score);

  void			run(char ** argv);
  void			loadLevels(const std::string& path);
  void			loadNetwork(char ** argv);
  void			loop();
  void			start();
  void			execLevel() const;
  void			startGame();
  void			playMusic();

 private:
  RClient();
  RClient(const RClient& r);
  ~RClient();
  RClient& operator=(const RClient& r);

 private:
  sf::RenderWindow*	_app;
  int			_frameRate;
  std::list<Level *>	_levels;
  NetworkClient*	_network;
  Input*		_input;
  static RClient*	_instance;
  int			_currentLevel;
  unsigned int		_shipId;
  bool			_waitBegin;
  boost::mutex	_mutexScore;
  unsigned int	_score;
  sf::Music*	_music;
};

#endif //! RCLIENT_H_
