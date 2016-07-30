#include "Move.h"
#include "RClient.h"

Move::Move() : _movePtr()
{
  this->_movePtr['0'] = &Move::dontMove;
  this->_movePtr['U'] = &Move::moveUp;
  this->_movePtr['D'] = &Move::moveDown;
  this->_movePtr['L'] = &Move::moveLeft;
  this->_movePtr['R'] = &Move::moveRight;
  this->_movePtr['u'] = &Move::moveUpRight;
  this->_movePtr['r'] = &Move::moveDownRight;
  this->_movePtr['d'] = &Move::moveDownLeft;
  this->_movePtr['l'] = &Move::moveUpLeft;
}

Move::Move(Move const & rhs): _movePtr(rhs._movePtr)
{
}

Move &	Move::operator=(Move const & rhs)
{
  if (this != &rhs)
    {
      this->_movePtr = rhs._movePtr;
    }
  return (*this);
}

Move::~Move()
{
}

void	Move::dontMove(SpriteEntity* sprite, float)
{
  sprite->getSprite()->Move(0, 0);
  sprite->spriteLeft();
}

void	Move::moveUp(SpriteEntity* sprite, float elapsedTime)
{
  if (sprite->isPlayer())
    {
      if (sprite->getSprite()->GetPosition().y > 0)
	sprite->getSprite()->Move(0, -sprite->getSpeed() * elapsedTime);
    }
  else
    sprite->getSprite()->Move(0, -sprite->getSpeed() * elapsedTime);

  sprite->spriteUp();
}

void	Move::moveDown(SpriteEntity* sprite, float elapsedTime)
{
  if (sprite->isPlayer())
    {
      if (sprite->getSprite()->GetPosition().y + 40 < RClient::getInstance()->getApp()->GetHeight())
	sprite->getSprite()->Move(0, sprite->getSpeed() * elapsedTime);
    }
  else
    sprite->getSprite()->Move(0, sprite->getSpeed() * elapsedTime);
  sprite->spriteDown();
}

void	Move::moveLeft(SpriteEntity* sprite, float elapsedTime)
{
  if (sprite->isPlayer())
    {
      if (sprite->getSprite()->GetPosition().x > 0)
	sprite->getSprite()->Move(-sprite->getSpeed() * elapsedTime, 0);
    }
  else
    sprite->getSprite()->Move(-sprite->getSpeed() * elapsedTime, 0);
  sprite->spriteLeft();
}

void	Move::moveRight(SpriteEntity* sprite, float elapsedTime)
{
  if (sprite->isPlayer())
    {
      if (sprite->getSprite()->GetPosition().x + 70 < RClient::getInstance()->getApp()->GetWidth())
	sprite->getSprite()->Move(sprite->getSpeed() * elapsedTime, 0);
    }
  else
    sprite->getSprite()->Move(sprite->getSpeed() * elapsedTime, 0);
  sprite->spriteRight();
}

void	Move::moveUpLeft(SpriteEntity* sprite, float elapsedTime)
{
  this->moveUp(sprite, elapsedTime);
  this->moveLeft(sprite, elapsedTime);
  sprite->spriteUp();
}

void	Move::moveUpRight(SpriteEntity* sprite, float elapsedTime)
{
  this->moveUp(sprite, elapsedTime);
  this->moveRight(sprite, elapsedTime);
  sprite->spriteUp();
}

void	Move::moveDownLeft(SpriteEntity* sprite, float elapsedTime)
{
  this->moveDown(sprite, elapsedTime);
  this->moveLeft(sprite, elapsedTime);
  sprite->spriteDown();
}

void	Move::moveDownRight(SpriteEntity* sprite, float elapsedTime)
{
  this->moveDown(sprite, elapsedTime);
  this->moveRight(sprite, elapsedTime);
  sprite->spriteDown();
}

void	Move::execMove(SpriteEntity* sprite)
{
  float elapsedTime = RClient::getInstance()->getApp()->GetFrameTime();
  ptrMoveMethod f = 0;
  if (this->_movePtr.find(sprite->getDirection()) != this->_movePtr.end())
    {
      f = this->_movePtr[sprite->getDirection()];
      (this->*f)(sprite, elapsedTime);
    }
}
