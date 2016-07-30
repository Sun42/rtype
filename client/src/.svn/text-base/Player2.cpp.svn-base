#include "Player2.h"

#ifdef _WIN32
SpriteEntity*	BuilderPlayer2(unsigned int id, float timeOfCreation, float posXOnMap, float posYOnMap)
{
	return (new Player2(id, timeOfCreation, posXOnMap, posYOnMap));
}
#else
extern "C"
{
typeShip	GetType()
{
	return (PLAYER2);
}

SpriteEntity*	Builder(unsigned int id, float timeOfCreation, float posXOnMap, float posYOnMap)
{
	return (new Player2(id, timeOfCreation, posXOnMap, posYOnMap));
}
}
#endif

Player2::Player2(unsigned int id, float timeOfCreation, float posXOnMap, float posYOnMap):
Ship(id,  200,timeOfCreation, posXOnMap, posYOnMap, "./sprites/r-typesheet42.png", 4), _scenario()
{
	this->setWidthHeight(33, 17);
	this->setPosOnSprite(2, 1);
}

Player2::~Player2()
{
	
}

Player2::Player2(const Player2& rhs):
Ship(rhs), _scenario(rhs._scenario)
{
}

Player2& Player2::operator=(const Player2&)
{
	return (*this);
}

void		Player2::spriteMove(unsigned int numCol, unsigned int numRow)
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

void		Player2::spriteUp()
{
	this->spriteMove(4, 1);
}

void		Player2::spriteDown()
{
	this->spriteMove(0, 1);
}

void		Player2::spriteLeft()
{
	this->spriteMove(2, 1);
}

void		Player2::spriteRight()
{
	this->spriteMove(2, 1);
}

void		Player2::execActions(float)
{

}