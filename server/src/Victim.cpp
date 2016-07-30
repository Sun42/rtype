#include "Victim.h"

/*********************************************************************/

Victim::Victim(unsigned int id, unsigned int idBall, unsigned char typeVictim, int life) :
  _idVictim(id), _idVictimBall(idBall),_typeVictim(typeVictim), _life(life), _idKiller(Victim::NOKILLER), _idBallKiller(Victim::NOKILLER)
{
}

Victim::~Victim()
{
}

Victim::Victim(Victim const & rhs) :
  _idVictim(rhs._idVictim), _idVictimBall(rhs._idVictimBall),_typeVictim(rhs._typeVictim), _life(rhs._life), _idKiller(rhs._idKiller), _idBallKiller(rhs._idBallKiller)
{
}

/*********************************************************************/

Victim&		Victim::operator=(Victim const & rhs)
{
  if (this != & rhs)
    {
      this->_idVictim = rhs._idVictim;
      this->_idVictimBall = rhs._idVictimBall;
      this->_typeVictim = rhs._typeVictim;
      this->_life = rhs._life;
      this->_idKiller = rhs._idKiller;
      this->_idBallKiller = rhs._idBallKiller;
    }
  return (*this);
}


Victim&		Victim::operator-=(unsigned char powerShoot)
{
  this->_life -= powerShoot;
  if (this->_life < 0)
    this->_life = 0;
  return (*this);
}

/*********************************************************************/

void		Victim::setKiller(unsigned int idkiller, unsigned int idBallKiller)
{
  this->_idKiller = idkiller;
  this->_idBallKiller = idBallKiller;
}

unsigned int	Victim::getIdKiller() const
{
  return (this->_idKiller);
}

unsigned int	Victim::getIdBallKiller() const
{
  return (this->_idBallKiller);
}

unsigned int	Victim::getIdVictim() const
{
  return (this->_idVictim);
}

unsigned int	Victim::getIdVictimBall() const
{
  return (this->_idVictimBall);
}

unsigned char		Victim::getTypeVictim() const
{
  return (this->_typeVictim);
}

/*********************************************************************/

bool		Victim::isTheVictim(unsigned int idVictim, unsigned int victimBall, unsigned char typeVictim) const
{
  return (this->_idVictim == idVictim && this->_idVictimBall == victimBall && this->_typeVictim == typeVictim);
}

bool		Victim::isKilled() const
{
  return (!(this->_idKiller == Victim::NOKILLER));
}

bool		Victim::isDead() const
{
  return (!this->_life);
}
