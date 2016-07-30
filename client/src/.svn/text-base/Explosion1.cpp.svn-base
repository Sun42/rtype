#include <sstream>
#include "Explosion1.h"
#include "RClient.h"

#ifdef _WIN32
SpriteEntity*	BuilderExplosion1(unsigned int idDecor, float timeOfCreation, float posXOnMap, float posYOnMap)
{
	return (new Explosion1(idDecor, timeOfCreation, posXOnMap, posYOnMap));
}
#else
extern "C"
{
typeDecor	GetType()
{
	return (EXPLOSION1);
}

SpriteEntity*	Builder(unsigned int idDecor, float timeOfCreation, float posXOnMap, float posYOnMap)
{
	return (new Explosion1(idDecor, timeOfCreation, posXOnMap, posYOnMap));
}

}
#endif

Explosion1::Explosion1(unsigned int idDecor, float timeOfCreation, 
					float posXOnMap, float posYOnMap):
  Decor(idDecor, 200, timeOfCreation, posXOnMap, posYOnMap, "./sprites/Explosion1.png", 2), 
	  _scenario(), _cptImg(0), _lastImgTime(RClient::getInstance()->getTime())
{
  this->setWidthHeight(34, 30);
  this->setPosOnSprite(0, 0);
  this->fillSprite();
  this->setDirection('L');
}

Explosion1::~Explosion1()
{

}

Explosion1::Explosion1(const Explosion1& rhs):
Decor(rhs), _scenario(rhs._scenario), _cptImg(rhs._cptImg), _lastImgTime(rhs._lastImgTime)
{
  this->setDirection('L');
}

Explosion1& Explosion1::operator=(const Explosion1& rhs)
{
	if (this != &rhs)
	{
		this->_scenario = rhs._scenario;
		this->_cptImg = rhs._cptImg;
		this->_lastImgTime = rhs._lastImgTime;
		this->setDirection('L');
	}
	return (*this);
}

void	Explosion1::insert_action(Action*,  float,
		      std::list< std::pair<Action *, float> >&)
{
}

void	Explosion1::pop_actions(unsigned int, float,
			     std::list< std::pair<Action *, float> >&)
{

}

//utilite de la fonction = ??
void	Explosion1::scenarioCreator(std::list< std::pair<Action *, float> >&)
{

}

void				Explosion1::fillSprite()
{

}


unsigned int		Explosion1::touched(float)
{
	return (0);
}

void		Explosion1::execActions(float)
{
}

void				Explosion1::spriteUp()
{
}

void				Explosion1::spriteDown()
{
}

void				Explosion1::spriteLeft()
{
	float			newTime = RClient::getInstance()->getTime();
	if (this->_cptImg < 7)
	{
			this->setPosOnSprite(this->_cptImg, 0);
		if ((newTime - this->_lastImgTime) > 0.05 && this->_cptImg < 7)
		{
			this->_lastImgTime = newTime;
			this->_cptImg += 1;
		}
	}
}

void				Explosion1::spriteRight()
{
}

