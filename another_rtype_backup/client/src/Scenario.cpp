#include "Scenario.h"

/*********************************************************************/

Scenario::Scenario()
{

}

Scenario::Scenario(const Scenario& )
{

}

Scenario::~Scenario()
{

}

Scenario& Scenario::operator=(const Scenario& )
{
  return (*this);
}

/*********************************************************************/

std::list< std::pair<Action *, float> >& Scenario::addActions()
{
  return (this->_actions);
}
