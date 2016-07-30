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


void scenarioCreator(std::list< std::pair<Action *, float> >& actions)
{
  int id = 5;
  float time  = 2;
  while (id < 100)
    {
      pop_ennemi(id++ , time, actions);
      time  += 1;
    }
}
