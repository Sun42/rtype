#include <sstream>
#include "Weapon4.h"

#ifdef _WIN32
SpriteEntity*	BuilderWeapon4(unsigned int idOwner, float timeOfCreation, float posXOnMap, float posYOnMap)
{
  return (new Weapon4(timeOfCreation, posXOnMap, posYOnMap, idOwner));
}

float Weapon4::getFrequency()
{
  return (0.15f);
}

#else
extern "C"
{

typeWeapon	GetType()
{
  return (WEAPON4);
}

SpriteEntity*	Builder(unsigned int idOwner, float timeOfCreation, float posXOnMap, float posYOnMap)
{
  return (new Weapon4(timeOfCreation, posXOnMap, posYOnMap, idOwner));
}

}
#endif


Weapon4::Weapon4(float timeOfCreation, float posXOnMap,
		 float posYOnMap, unsigned int ownerId):
  Weapon(500, timeOfCreation, posXOnMap, posYOnMap, "./sprites/weapon4.png",
	 1, ownerId), _scenario()
{
  this->setWidthHeight(17, 18);
  this->setPosOnSprite(3, 0);
  this->fillSprite();

}

Weapon4::~Weapon4()
{

}

Weapon4::Weapon4(const Weapon4& rhs):
Weapon(rhs), _scenario(rhs._scenario)
{
}

Weapon4& Weapon4::operator=(const Weapon4&)
{
	return (*this);
}

void	Weapon4::insert_action(Action* action,  float time,
		      std::list< std::pair<Action *, float> >& actions)
{
  std::pair<Action *, float> act;
  act.first = action;
  act.second = time;
  actions.push_back(act);
}

void	Weapon4::pop_actions(unsigned int /*id*/, float time,
			     std::list< std::pair<Action *, float> >& actions)
{
  std::stringstream params;
  if (this->_owner < 5)
    params << "R ";
  else
    params << "L ";
  params << this->getId();
  insert_action(new Action(MOVE, TYPEWEAPON, WEAPON4, params.str(), this->_owner), time, actions);
}

//utilite de la fonction = ??
void	Weapon4::scenarioCreator(std::list< std::pair<Action *, float> >& actions)
{
  float time  = 0;
  pop_actions(1/*??*/ , time, actions);
}

void				Weapon4::fillSprite()
{
  std::list< std::pair<Action *, float> > & myActions = this->_scenario.addActions();
  scenarioCreator(myActions);
}

void		Weapon4::execActions(float currentTime)
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

void				Weapon4::spriteUp()
{
	this->setPosOnSprite(4, 0);
}

void				Weapon4::spriteDown()
{
	this->setPosOnSprite(0, 0);
}

void				Weapon4::spriteLeft()
{
	this->setPosOnSprite(3, 0);
}

void				Weapon4::spriteRight()
{
	this->setPosOnSprite(1, 0);
}

