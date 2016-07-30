#include "Level.h"

void scenarioCreator(std::list< std::pair<Action *, float> >& actions);

/*********************************************************************/

Level::Level(int idlevel):
_idLevel(idlevel), _clock(), _scenario()
{
}


Level::Level():
  _idLevel(0), _clock(), _scenario()
  {
}

Level::~Level()
{
}

Level::Level(const Level& rhs): 
_idLevel(rhs._idLevel), _clock(rhs._clock), _scenario(rhs._scenario)
{
}

Level& Level::operator=(const Level& rhs)
{
  if (this != &rhs)
    {
      this->_idLevel = rhs._idLevel;
      this->_clock = rhs._clock;
      this->_scenario = rhs._scenario;
    }
  return (*this);
}

/*********************************************************************/

float Level::getTime() const
{
  return (this->_clock.GetElapsedTime());
}

/*********************************************************************/

void	Level::execScenario()
{
  float currentTime = this->_clock.GetElapsedTime();
  std::list<std::pair<Action *, float> >::iterator  it = this->_scenario.addActions().begin();
  std::list<std::pair<Action *, float> >::iterator  save;
  while (it != this->_scenario.addActions().end() && (*it).second < currentTime)
    {
      if ((*it).second <= currentTime)
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

void	Level::startScenario()
{
  this->_clock.Reset();
  this->execScenario();
}

void	Level::fillLevel()
{
  std::list< std::pair<Action *, float> > & myActions = this->_scenario.addActions();
  scenarioCreator(myActions);
}
