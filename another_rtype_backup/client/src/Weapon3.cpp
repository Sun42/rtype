#include <sstream>
#include "Weapon3.h"

#ifdef _WIN32
SpriteEntity*	BuilderWeapon3(unsigned int idOwner, float timeOfCreation, float posXOnMap, float posYOnMap)
{
  return (new Weapon3(timeOfCreation, posXOnMap, posYOnMap, idOwner));
}

float Weapon3::getFrequency()
{
  return (0.15f);
}

#else
extern "C"
{

typeWeapon	GetType()
{
  return (WEAPON3);
}

SpriteEntity*	Builder(unsigned int idOwner, float timeOfCreation, float posXOnMap, float posYOnMap)
{
  return (new Weapon3(timeOfCreation, posXOnMap, posYOnMap, idOwner));
}

}
#endif


Weapon3::Weapon3(float timeOfCreation, float posXOnMap,
		 float posYOnMap, unsigned int ownerId):
  Weapon(600, timeOfCreation, posXOnMap, posYOnMap, "./sprites/weapon3.png",
	 1, ownerId), _scenario()
{
  this->setWidthHeight(17, 12);
  this->setPosOnSprite(2, 0);
  this->fillSprite();

}

Weapon3::~Weapon3()
{

}

Weapon3::Weapon3(const Weapon3& rhs):
Weapon(rhs), _scenario(rhs._scenario)
{
}

Weapon3& Weapon3::operator=(const Weapon3&)
{
	return (*this);
}

void	Weapon3::insert_action(Action* action,  float time,
		      std::list< std::pair<Action *, float> >& actions)
{
  std::pair<Action *, float> act;
  act.first = action;
  act.second = time;
  actions.push_back(act);
}

void	Weapon3::pop_actions(unsigned int /*id*/, float time,
			     std::list< std::pair<Action *, float> >& actions)
{
  std::stringstream params;
  if (this->_owner < 5)
    params << "R ";
  else
    params << "L ";
  params << this->getId();
  insert_action(new Action(MOVE, TYPEWEAPON, WEAPON3, params.str(), this->_owner), time, actions);
}

//utilite de la fonction = ??
void	Weapon3::scenarioCreator(std::list< std::pair<Action *, float> >& actions)
{
  float time  = 0;
  pop_actions(1/*??*/ , time, actions);
}

void				Weapon3::fillSprite()
{
  std::list< std::pair<Action *, float> > & myActions = this->_scenario.addActions();
  scenarioCreator(myActions);
}

void		Weapon3::execActions(float currentTime)
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

void				Weapon3::spriteUp()
{
	this->setPosOnSprite(4, 0);
}

void				Weapon3::spriteDown()
{
	this->setPosOnSprite(0, 0);
}

void				Weapon3::spriteLeft()
{
	this->setPosOnSprite(2, 0);
}

void				Weapon3::spriteRight()
{
	this->setPosOnSprite(1, 0);
}

