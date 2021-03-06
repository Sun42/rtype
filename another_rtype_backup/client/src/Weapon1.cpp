#include <sstream>
#include "Weapon1.h"

#ifdef _WIN32
SpriteEntity*	BuilderWeapon1(unsigned int idOwner, float timeOfCreation, float posXOnMap, float posYOnMap)
{
  return (new Weapon1(timeOfCreation, posXOnMap, posYOnMap, idOwner));
}

float Weapon1::getFrequency()
{
  return (0.15f);
}

#else
extern "C"
{

typeWeapon	GetType()
{
  return (WEAPON1);
}

SpriteEntity*	Builder(unsigned int idOwner, float timeOfCreation, float posXOnMap, float posYOnMap)
{
  return (new Weapon1(timeOfCreation, posXOnMap, posYOnMap, idOwner));
}

}
#endif


Weapon1::Weapon1(float timeOfCreation, float posXOnMap,
		 float posYOnMap, unsigned int ownerId):
  Weapon(700, timeOfCreation, posXOnMap, posYOnMap, "./sprites/weapon1.png",
	 1, ownerId), _scenario()
{
  this->setWidthHeight(17, 12);
  this->setPosOnSprite(2, 0);
  this->fillSprite();

}

Weapon1::~Weapon1()
{

}

Weapon1::Weapon1(const Weapon1& rhs):
Weapon(rhs), _scenario(rhs._scenario)
{
}

Weapon1& Weapon1::operator=(const Weapon1&)
{
	return (*this);
}

void	Weapon1::insert_action(Action* action,  float time,
		      std::list< std::pair<Action *, float> >& actions)
{
  std::pair<Action *, float> act;
  act.first = action;
  act.second = time;
  actions.push_back(act);
}

void	Weapon1::pop_actions(unsigned int /*id*/, float time,
			     std::list< std::pair<Action *, float> >& actions)
{
  std::stringstream params;
  if (this->_owner < 5)
    params << "R ";
  else
    params << "L ";
  params << this->getId();
  insert_action(new Action(MOVE, TYPEWEAPON, WEAPON1, params.str(), this->_owner), time, actions);
}

//utilite de la fonction = ??
void	Weapon1::scenarioCreator(std::list< std::pair<Action *, float> >& actions)
{
  float time  = 0;
  pop_actions(1/*??*/ , time, actions);
}

void				Weapon1::fillSprite()
{
  std::list< std::pair<Action *, float> > & myActions = this->_scenario.addActions();
  scenarioCreator(myActions);
}

void		Weapon1::execActions(float currentTime)
{
  std::list<std::pair<Action *, float> >::iterator  it = this->_scenario.addActions().begin();
  std::list<std::pair<Action *, float> >::iterator  save;
  while (it != this->_scenario.addActions().end() && (*it).second < currentTime)
    {
      if ((*it).second <= (currentTime - this->_timeOfCreation))
	{
	  save = it;
	  (*save).first->execAction();
	  ++it;
	  this->_scenario.addActions().remove(*save);
	}
      else
	++it;
    }
}

void				Weapon1::spriteUp()
{
	this->setPosOnSprite(4, 0);
}

void				Weapon1::spriteDown()
{
	this->setPosOnSprite(0, 0);
}

void				Weapon1::spriteLeft()
{
	this->setPosOnSprite(2, 0);
}

void				Weapon1::spriteRight()
{
	this->setPosOnSprite(1, 0);
}

