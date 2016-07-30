#ifndef __GAME_H__
# define __GAME_H__

#include <list>

#include "Packet.h"
#include "Player.h"
#include "Victim.h"

class	Game
{
 public:
  Game(std::string & name, unsigned char nbPlayerMax, int idGame);
  ~Game();

  int		getId() const; // renvoie l ' id de la partie
  std::string const &	getName() const; // retourne le nom de la partie
  unsigned char		getLevel() const; // retourne le level courant
  unsigned int		getNbPlayers(); // retourne le nb de joueur de la partie
  unsigned int		getNbPlayerMax() const; // retourne le nb de joueur max de la game
  void			setPlaying(); // set le debut de la partie

  bool			canStartToPlay(); // permet de savoir s'il y a suffisament de joueur pour lancer la partie
  bool			isStarded() const; // savoir si les joueurs sont en train de jouer
  bool			addPlayerInGame(Player * player); // ajouter un joueur a la partie
  bool			askLevelUp(Player *); // demande pour passer au level up

  void			sendToAllPlayers(Packet & pack); // envoyer le packet a tous les joueurs
  void			sendToOtherPlayers(Packet & answerPacket, Player const * originPlayer); // envoyer le packet a tous les joueurs sauf celui passer en parametre
  void			deconnectionPlayer(Player *); // pour la deconnexion d un joueur
  void			collisionWithEnnemies(Player *, Packet &, unsigned int, unsigned int, unsigned int, unsigned int, unsigned int, unsigned char);
  void			levelUp(); // passe au level up

 private:
  Game(Game const &);
  Game &		operator=(Game const &);

 private:
  unsigned int		_idGame;	// identifiant de la partie
  std::string		_name;		// nom de la partie
  unsigned int		_nbPlayerMax;	// nombre de player max ds la partie
  bool			_playing;	// la partie a deja commence
  unsigned char		_idLevel;	// id du level en cours (commence a 0)
  boost::mutex		_mutexPlayers;
  std::list<Player *>	_players;	// joueurs ds la partie
  boost::mutex		_mutexPlayersConf;
  std::list<Player *>	_playersConf;	// liste des confirmations pour passer au niveau suivant
  boost::mutex		_mutexVictims;
  std::list<Victim>	_victims;	// victimes de collisions
};

#endif /* !__GAME_H__ */
