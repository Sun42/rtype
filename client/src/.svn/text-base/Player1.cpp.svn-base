#include "Player1.h"

#ifdef _WIN32
SpriteEntity*	BuilderPlayer1(unsigned int id, float timeOfCreation, float posXOnMap, float posYOnMap)
{
	return (new Player1(id, timeOfCreation, posXOnMap, posYOnMap));
}
#else
extern "C"
{
typeShip	GetType()
{
	return (PLAYER1);
}

SpriteEntity*	Builder(unsigned int id, float timeOfCreation, float posXOnMap, float posYOnMap)
{
  return (new Player1(id, timeOfCreation, posXOnMap, posYOnMap));
}
}
#endif

Player1::Player1(unsigned int id, float timeOfCreation, float posXOnMap, float posYOnMap):
Ship(id, 200, timeOfCreation, posXOnMap, posYOnMap, "./sprites/r-typesheet42.png", 4), _scenario()
{
  this->setWidthHeight(33, 17);
  this->setPosOnSprite(2, 0);
}

Player1::~Player1()
{

}

Player1::Player1(const Player1& rhs):
Ship(rhs), _scenario(rhs._scenario)
{
}

Player1& Player1::operator=(const Player1&)
{
	return (*this);
}

void		Player1::spriteMove(unsigned int numCol, unsigned int numRow)
{
	float	currentTime = RClient::getInstance()->getTime();
	if ((currentTime - this->_lastTouchedTime) < 3)
	{
		this->getSprite()->SetColor(sf::Color(255, 255, 255, 125));
	}
	else
	{
		if ((currentTime - this->_lastTouchedTime) < 4)
			this->getSprite()->SetColor(sf::Color(255, 255, 255, 255));
	}
	this->setPosOnSprite(numCol, numRow);
}

void		Player1::spriteUp()
{
	this->spriteMove(4, 0);
}

void		Player1::spriteDown()
{
	this->spriteMove(0, 0);
}

void		Player1::spriteLeft()
{
	this->spriteMove(2, 0);
}

void		Player1::spriteRight()
{
	this->spriteMove(2, 0);
}

void		Player1::execActions(float)
{

}
