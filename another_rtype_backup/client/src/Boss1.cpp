#include <sstream>
#include "Boss1.h"


#ifdef _WIN32
SpriteEntity*	BuilderBoss1(unsigned int id, float timeOfCreation, float posXOnMap, float posYOnMap)
{
	return (new Boss1(id, timeOfCreation, posXOnMap, posYOnMap));
}
#else
extern "C"
{
typeShip	GetType()
{
  return (BOSS1);
}

  SpriteEntity*	Builder(unsigned int id, float timeOfCreation, float posXOnMap, float posYOnMap)
  {
    return (new Boss1(id, timeOfCreation, posXOnMap, posYOnMap));
  }
}
#endif

Boss1::Boss1(unsigned int id, float timeOfCreation, float posXOnMap, float posYOnMap):
  Ship(id, 0, timeOfCreation, posXOnMap, posYOnMap, "./sprites/r-typesheet32.png", 150), _scenario()
{
  this->setWidthHeight(260.f, 145.f);
  this->setPosOnSprite(0.f, 0.f);
  this->fillSprite();
  this->_sprite.SetScale(2.f, 2.f);
}

Boss1::~Boss1()
{

}

Boss1::Boss1(const Boss1& rhs):
Ship(rhs), _scenario(rhs._scenario)
{
}

Boss1& Boss1::operator=(const Boss1&)
{
	return (*this);
}

void	Boss1::insert_action(Action* action,  float time,
		      std::list< std::pair<Action *, float> >& actions)
{
  std::pair<Action *, float> act;
  act.first = action;
  act.second = time;
  actions.push_back(act);
}

void	Boss1::create_shoot(float time,  std::list< std::pair<Action *, float> >& actions)
{
  insert_action(new Action(SHOOT, TYPEWEAPON, WEAPON4, "-5 20", this->getId()), time, actions);
  insert_action(new Action(SHOOT, TYPEWEAPON, WEAPON4, "-10 50", this->getId()), time, actions);
  insert_action(new Action(SHOOT, TYPEWEAPON, WEAPON4, "-30 30", this->getId()), time, actions);
}

void	Boss1::pop_actions(unsigned int /*id*/, float time, std::list< std::pair<Action *, float> >& actions)
{
  int i = 0;
  this->insert_action(new Action(this->getId(), MOVE,TYPESHIP, BOSS1, "L 0 0"), time, actions);
  time += 1;
  while (i < 1000)
    {
      this->insert_action(new Action(this->getId(), MOVE,TYPESHIP, BOSS1, "D 0 0"), time, actions);
      time += 0.3;
      this->insert_action(new Action(this->getId(), MOVE,TYPESHIP, BOSS1, "L 0 0"), time, actions);
      time += 0.3;
      this->insert_action(new Action(this->getId(), MOVE,TYPESHIP, BOSS1, "U 0 0"), time, actions);
      time += 0.3;
      this->insert_action(new Action(this->getId(), MOVE,TYPESHIP, BOSS1, "R 0 0"), time, actions);
      time += 0.3;
      //this->insert_action(new Action(this->getId(), MOVE,TYPESHIP, BOSS1, "U 0 0"), time, actions);
      i++;
      this->create_shoot(time, actions);
    }
  this->insert_action(new Action(this->getId(), MOVE,TYPESHIP, BOSS1, "0 0 0"), time, actions);
}


void	Boss1::scenarioCreator(std::list< std::pair<Action *, float> >& actions)
{
  float time  = 0;
  pop_actions(1 , time, actions);
}

void				Boss1::fillSprite()
{
  std::list< std::pair<Action *, float> > & myActions = this->_scenario.addActions();
  scenarioCreator(myActions);
}

void		Boss1::execActions(float currentTime)
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

void				Boss1::spriteUp()
{
  this->setPosOnSprite(0, 0);
}

void				Boss1::spriteDown()
{
  this->setPosOnSprite(1, 1);
}

void				Boss1::spriteLeft()
{
  this->setPosOnSprite(0, 1);
}

void				Boss1::spriteRight()
{
  this->setPosOnSprite(1, 0);
}

