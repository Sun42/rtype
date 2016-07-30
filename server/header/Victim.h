#ifndef VICTIM_H_
# define VICTIM_H_

class	Victim
{
 public:
  Victim(unsigned int, unsigned int, unsigned char, int);
  ~Victim();
  Victim(Victim const &);

  Victim&		operator=(Victim const &);
  Victim&		operator-=(unsigned char powerShoot);

  unsigned int		getIdVictim() const; // retourne l'id de l'ennemi
  unsigned int		getIdVictimBall() const;
  unsigned char		getTypeVictim() const;
  void			setKiller(unsigned int, unsigned int);
  unsigned int		getIdKiller() const;
  unsigned int		getIdBallKiller() const;

  bool			isTheVictim(unsigned int, unsigned int, unsigned char) const;
  bool			isDead() const; // vrai si l'ennemi a sa vie a 0
  bool			isKilled() const; // retourne si l'ennemi a ete tue

 private:
  static const unsigned char	NOKILLER = 5;
  unsigned int			_idVictim;	// id de l'ennemi (ds le cas d une arme, c'est l'id du proprietaire de la balle)
  unsigned int			_idVictimBall;	// id de la balle tuer (si c une balle)
  unsigned char			_typeVictim;	// le type de la victime (balle ou ennemy)
  int				_life;		// vie restante de l'ennemi
  unsigned int			_idKiller;	// id du killer
  unsigned int			_idBallKiller;
};

#endif // VICTIM_H_
