#include "Input.h"
#include "RClient.h"

/*********************************************************************/

Input::Input() :
  _keyInput(KeyboardInput::KeyboardInput()), _inputActions()
{
}

Input::Input(const Input& rhs) :
  _keyInput(rhs._keyInput), _inputActions(rhs._inputActions)
{
}

Input::~Input()
{}

Input& Input::operator=(const Input& )
{
  return *this;
}

/*********************************************************************/

void	Input::fillActions()
{
  this->_keyInput.checkKeys(this->_inputActions);
  RClient::getInstance()->getNetwork()->checkNetwork(this->_inputActions);
}

void	Input::execActions()
{
  std::list<Action *>::iterator it = this->_inputActions.begin();
  std::list<Action *>::iterator itend = this->_inputActions.end();

  for (;it != itend; ++it)
    (*it)->execAction();
  this->_inputActions.clear();
}
