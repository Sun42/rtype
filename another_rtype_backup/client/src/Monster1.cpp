#include <sstream>
#include "Monster1.h"


#ifdef _WIN32
SpriteEntity*	BuilderMonster1(unsigned int id, float timeOfCreation, float posXOnMap, float posYOnMap)
{
	return (new Monster1(id, timeOfCreation, posXOnMap, posYOnMap));
}
#else
extern "C"
{
typeShip	GetType()
{
  return (MONSTER1);
}

  SpriteEntity*	Builder(unsigned int id, float timeOfCreation, float posXOnMap, float posYOnMap)
  {
    return (new Monster1(id, timeOfCreation, posXOnMap, posYOnMap));
  }
}
#endif

Monster1::Monster1(unsigned int id, float timeOfCreation, float posXOnMap, float posYOnMap):
  Ship(id, 250, timeOfCreation, posXOnMap, posYOnMap, "./sprites/r-typesheet5.png", 1), _scenario()
{
  this->setWidthHeight(33.f, 36.f);
  this->setPosOnSprite(2.f, 0.f);
  this->fillSprite();
  this->_sprite.SetScale(2.f, 2.f);
}

Monster1::~Monster1()
{

}

Monster1::Monster1(const Monster1& rhs):
Ship(rhs), _scenario(rhs._scenario)
{
}

Monster1& Monster1::operator=(const Monster1&)
{
	return (*this);
}

void	Monster1::insert_action(Action* action,  float time,
		      std::list< std::pair<Action *, float> >& actions)
{
  std::pair<Action *, float> act;
  act.first = action;
  act.second = time;
  actions.push_back(act);
}

void	Monster1::create_shoot(float time,  std::list< std::pair<Action *, float> >& actions)
{
  insert_action(new Action(SHOOT, TYPEWEAPON, WEAPON1, "-5 20", this->getId()), time, actions);
}

void	Monster1::pop_actions(unsigned int /*id*/, float time, std::list< std::pair<Action *, float> >& actions)
{
  this->insert_action(new Action(this->getId(), MOVE,TYPESHIP, MONSTER1, "L 0 0"), time, actions);
  this->create_shoot(time, actions);
  time += 0.3;
  insert_action(new Action(this->getId(), MOVE,TYPESHIP, MONSTER1, "L 0 0"), time, actions);
  time += 0.5;
  this->create_shoot(time, actions);
  time += 0.3;
  insert_action(new Action(this->getId(), MOVE, TYPESHIP, MONSTER1, "d 0 0"), time, actions);
  time += 0.5;
  //this->create_shoot(time, actions);;
  insert_action(new Action(this->getId(), MOVE,TYPESHIP, MONSTER1, "L 0 0"), time, actions);
  time += 0.5;
  //this->create_shoot(time, actions);;
  insert_action(new Action(this->getId(), MOVE,TYPESHIP, MONSTER1, "l 0 0"), time, actions);
  time += 0.5;
  this->create_shoot(time, actions);;
  time += 0.3;
  insert_action(new Action(this->getId(), MOVE,TYPESHIP, MONSTER1, "L 0 0"), time, actions);
  time += 0.5;
  //this->create_shoot(time, actions);;
  insert_action(new Action(this->getId(), MOVE, TYPESHIP, MONSTER1, "d 0 0"), time, actions);
  time += 0.5;
  this->create_shoot(time, actions);;
  time += 0.3;
  insert_action(new Action(this->getId(), MOVE,TYPESHIP, MONSTER1, "L 0 0"), time, actions);
  time += 0.5;
  //this->create_shoot(time, actions);;
  insert_action(new Action(this->getId(), MOVE,TYPESHIP, MONSTER1, "l 0 0"), time, actions);
  time += 0.5;
  this->create_shoot(time, actions);;
  time += 0.3;
  insert_action(new Action(this->getId(), MOVE,TYPESHIP, MONSTER1, "L 0 0"), time, actions);
  time += 0.5;
  //this->create_shoot(time, actions);;
  insert_action(new Action(this->getId(), MOVE, TYPESHIP, MONSTER1, "d 0 0"), time, actions);
  time += 0.5;
  this->create_shoot(time, actions);;
  time += 0.3;
  insert_action(new Action(this->getId(), MOVE,TYPESHIP, MONSTER1, "L 0 0"), time, actions);
  time += 0.5;
  insert_action(new Action(this->getId(), MOVE,TYPESHIP, MONSTER1, "l 0 0"), time, actions);
}

void	Monster1::scenarioCreator(std::list< std::pair<Action *, float> >& actions)
{
  float time  = 0;
  pop_actions(1 , time, actions);
}

void				Monster1::fillSprite()
{
  std::list< std::pair<Action *, float> > & myActions = this->_scenario.addActions();
  scenarioCreator(myActions);
}

void		Monster1::execActions(float currentTime)
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

void				Monster1::spriteUp()
{
  this->setPosOnSprite(4, 0);
}

void				Monster1::spriteDown()
{
  this->setPosOnSprite(0, 0);
}

void				Monster1::spriteLeft()
{
  this->setPosOnSprite(2, 0);
}

void				Monster1::spriteRight()
{
  this->setPosOnSprite(2, 0);
}

