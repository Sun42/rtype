#include <sstream>

#include "KeyboardInput.h"

#include "RClient.h"
#include "Ship.h"

/*********************************************************************/

KeyboardInput::KeyboardInput() : _arrows()
{
}

KeyboardInput::KeyboardInput(const KeyboardInput& rhs)
{
  this->_arrows = rhs._arrows;
}
KeyboardInput::~KeyboardInput()
{}

KeyboardInput& KeyboardInput::operator=(const KeyboardInput& rhs)
{
  if (this != &rhs)
    this->_arrows = rhs._arrows;
  return (*this);
}

/*********************************************************************/

void	KeyboardInput::checkKeys(std::list<Action*>& actions)
{
  //Process events
  unsigned int shipid = RClient::getInstance()->getShipId();
  sf::Event Event;
  sf::RenderWindow* app = RClient::getInstance()->getApp();
  NetworkClient* network = RClient::getInstance()->getNetwork();
  while (app->GetEvent(Event))
  {
    this->_prevArrows = this->_arrows;
    this->_arrows.manageShoot(Event);
    this->_arrows.manageArrows(Event);
    if (this->_arrows.shoot)
      {
	SpriteEntity* spr = WindowManager::getInstance()->getShipInZone(shipid);
	Ship* myship= dynamic_cast<Ship*>(spr);
	if (myship)
	  myship->shoot(actions);
      }
    if (this->_prevArrows.getDirection() != this->_arrows.getDirection())
      {
	network->funcSendMove(this->_arrows.getDirection()[0]);
	actions.push_back(new Action(shipid, MOVE, TYPESHIP, Ship::getNumPlayer(shipid), this->_arrows.getDirection()));
      }
    if ((Event.Type == sf::Event::KeyPressed) && (Event.Key.Code == sf::Key::X))
      {
	SpriteEntity* spr = WindowManager::getInstance()->getShipInZone(shipid);
	Ship* myship= dynamic_cast<Ship*>(spr);
	if (myship)
	  myship->changeWeapon();
      }
    if (Event.Type == sf::Event::Closed)
      RClient::destroyInstance();
    if ((Event.Type == sf::Event::KeyPressed) && (Event.Key.Code == sf::Key::Escape))
	{
		RClient::getInstance()->exitEscape();
	}
  }
}

/*********************************************************************/

typeShip	getShipType(unsigned int shipid)
{
  typeShip	tab[]=
    {
      PLAYER1,
      PLAYER2,
      PLAYER3,
      PLAYER4
    };
  return (tab[shipid]);
}
