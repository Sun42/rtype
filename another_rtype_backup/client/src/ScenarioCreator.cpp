#include <list>

#include "Action.h"

void insert_action(Action* action,  float time,
		      std::list< std::pair<Action *, float> >& actions
		      )
{
  std::pair<Action *, float> act;
  act.first = action;
  act.second = time;
  actions.push_back(act);
}


void pop_ennemi(unsigned int id, float time, std::list< std::pair<Action *, float> >& actions)
{
  insert_action(new Action(id, CREATE, TYPESHIP, MONSTER1, "1200 512"), time, actions);
}


void pop_ennemi2(unsigned int id, float time, std::list< std::pair<Action *, float> >& actions)
{
  insert_action(new Action(id, CREATE, TYPESHIP, MONSTER2, "1200 100"), time, actions);
}

void	pop_boss(unsigned id, float time, std::list< std::pair<Action *, float> >& actions)
{
  insert_action(new Action(id, CREATE, TYPESHIP, BOSS1, "800 800"), time, actions);
}

void scenarioCreator(std::list< std::pair<Action *, float> >& actions)
{
  int id = 5;
  float time  = 10;
  for (int j = 0; j < 30; ++j)
    {
      pop_ennemi(id++ , time, actions);
      if ((int)time % 2)
	pop_ennemi2(id++ , time, actions);
      time  += 1;
    }
  time += 10;
  pop_boss(++id, time, actions);
}
