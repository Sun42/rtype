#include <iostream> 
#include "WindowManager.h"

WindowManager* WindowManager::_instance = 0;

WindowManager*	WindowManager::getInstance()
{
  if (WindowManager::_instance == 0)
    {
      WindowManager::_instance = new WindowManager();
    }
  return (WindowManager::_instance);
}

void	WindowManager::destroyInstance()
{
  if (WindowManager::_instance == 0)
    {
      delete WindowManager::_instance;
      WindowManager::_instance = 0;
    }
}

WindowManager::WindowManager() :
  _windowZoneSize(320), _windowZones()
{
  this->_windowZones.push_back(new WindowZone());
  this->_windowZones.push_back(new WindowZone());
  this->_windowZones.push_back(new WindowZone());
  this->_windowZones.push_back(new WindowZone());
  this->_windowZones.push_back(new WindowZone());
  this->_windowZones.push_back(new WindowZone());
}

WindowManager::WindowManager(const WindowManager& rhs) :
  _windowZoneSize(rhs._windowZoneSize), _windowZones(rhs._windowZones)
{
}

WindowManager::~WindowManager()
{
  unsigned int	i = 0;
  while (i < this->_windowZones.size())
    {
      delete this->_windowZones[i++];
    }
}

WindowManager& WindowManager::operator=(const WindowManager& )
{
  return (*this);
}

void	WindowManager::addSpriteInZone(SpriteEntity* sprite)
{
  unsigned ibegin = static_cast<unsigned int>((sprite->getSprite()->GetPosition().x / 320) + 1);
  unsigned iend = static_cast<unsigned int>(((sprite->getSprite()->GetPosition().x + sprite->getSprite()->GetSize().x)/ 320) + 1);
  while (ibegin <= iend/* && ibegin < 6*/)
    {
		this->_windowZones[ibegin++]->addSpriteEntity(sprite);
    }
}

void	WindowManager::updateSpriteInZone(SpriteEntity* sprite)
{
  unsigned int i = 0;
  while (i < 6)
    {
      this->_windowZones[i++]->delSpriteEntity(sprite);
    }
  this->addSpriteInZone(sprite);
}

void	WindowManager::delSpriteInZones(SpriteEntity* sprite)
{
  unsigned int i = 0;
  while (i < 6)
    {
      this->_windowZones[i++]->delSpriteEntity(sprite);
    }
}

//print les sprites des 5 zones visibles
void		WindowManager::printMap() const
{
  unsigned int i = 1;
  while (i < 5)
    {
      this->_windowZones[i++]->printSprites();
    }
}

SpriteEntity*	WindowManager::getShipInZone(unsigned int spriteid)
{
  unsigned int i = 0;
  SpriteEntity*	tmpvar = 0;
  while (i < 6)
    {
      if ((tmpvar = this->_windowZones[i]->getShipSprite(spriteid)) != 0)
	return (tmpvar);
      i++;
    }
  return (tmpvar);
}


SpriteEntity*	WindowManager::getWeaponInZone(unsigned int weaponId, unsigned int ownerId)
{
  unsigned int i = 0;
  SpriteEntity*	tmpvar = 0;
  while (i < 6)
    {
      if ((tmpvar = this->_windowZones[i]->getWeaponSprite(weaponId, ownerId)) != 0)
	return (tmpvar);
      i++;
    }
  return (tmpvar);
}

void	WindowManager::execNonActioned() const
{
  unsigned int i = 0;
  while (i < 6)
    {
      this->_windowZones[i++]->execNonActioned();
    }
}

void	WindowManager::checkCollision()
{
  unsigned int i = 1;
  while (i < 5)
    {
      this->_windowZones[i++]->checkCollision();
    }
}

void	WindowManager::flushDestroyZones()
{
  this->_windowZones[0]->flushDestroyZone();
}
