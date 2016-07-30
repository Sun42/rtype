#include "Player4.h"

#ifdef _WIN32
SpriteEntity*	BuilderPlayer4(unsigned int id, float timeOfCreation, float posXOnMap, float posYOnMap)
{
	return (new Player4(id, timeOfCreation, posXOnMap, posYOnMap));
}
#else
extern "C"
{
typeShip	GetType()
{
	return (PLAYER4);
}

SpriteEntity*	Builder(unsigned int id, float timeOfCreation, float posXOnMap, float posYOnMap)
{
	return (new Player4(id, timeOfCreation, posXOnMap, posYOnMap));
}
}
#endif

Player4::Player4(unsigned int id, float timeOfCreation, float posXOnMap, float posYOnMap):
Ship(id,  300,timeOfCreation, posXOnMap, posYOnMap, "./sprites/r-typesheet42.png", 4), _scenario()
{
	this->setWidthHeight(33, 17);
	this->setPosOnSprite(2, 3);
}

Player4::~Player4()
{
	
}

Player4::Player4(const Player4& rhs):
Ship(rhs), _scenario(rhs._scenario)
{
}

Player4& Player4::operator=(const Player4&)
{
	return (*this);
}

void		Player4::spriteMove(unsigned int numCol, unsigned int numRow)
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

void		Player4::spriteUp()
{
	this->spriteMove(4, 3);
}

void		Player4::spriteDown()
{
	this->spriteMove(0, 3);
}

void		Player4::spriteLeft()
{
	this->spriteMove(2, 3);
}

void		Player4::spriteRight()
{
	this->spriteMove(2, 3);
}

void		Player4::execActions(float)
{

}
