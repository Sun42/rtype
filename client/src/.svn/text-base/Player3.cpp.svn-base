#include "Player3.h"

#ifdef _WIN32
SpriteEntity*	BuilderPlayer3(unsigned int id, float timeOfCreation, float posXOnMap, float posYOnMap)
{
	return (new Player3(id, timeOfCreation, posXOnMap, posYOnMap));
}
#else
extern "C"
{
typeShip	GetType()
{
	return (PLAYER3);
}

SpriteEntity*	Builder(unsigned int id, float timeOfCreation, float posXOnMap, float posYOnMap)
{
	return (new Player3(id, timeOfCreation, posXOnMap, posYOnMap));
}
}
#endif

Player3::Player3(unsigned int id, float timeOfCreation, float posXOnMap, float posYOnMap):
Ship(id,  200,timeOfCreation, posXOnMap, posYOnMap, "./sprites/r-typesheet42.png", 4), _scenario()
{
	this->setWidthHeight(33, 17);
	this->setPosOnSprite(2, 2);
}

Player3::~Player3()
{
	
}

Player3::Player3(const Player3& rhs):
Ship(rhs), _scenario(rhs._scenario)
{
}

Player3& Player3::operator=(const Player3&)
{
	return (*this);
}

void		Player3::spriteMove(unsigned int numCol, unsigned int numRow)
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


void		Player3::spriteUp()
{
	this->spriteMove(4, 2);
}

void		Player3::spriteDown()
{
	this->spriteMove(0, 2);
}

void		Player3::spriteLeft()
{
	this->spriteMove(2, 2);
}

void		Player3::spriteRight()
{
	this->spriteMove(2, 2);
}

void		Player3::execActions(float)
{

}