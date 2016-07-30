#include <cstdlib>

#include "SpriteEntity.h"
#include "RClient.h"
#include "Move.h"

/*********************************************************************/

SpriteEntity::SpriteEntity(unsigned int id, int speed, float timeOfCreation, float posXOnMap, float posYOnMap, const char* imgPath, int deep):
  _timeOfCreation(timeOfCreation), _sprite(), _width(0), _height(0), _deepness(deep), _direction('0'), _id(id), _spriteImg(), _posXOnSprite(0), _posYOnSprite(0), _speed(speed), _isActioned(true)
{
  if (!this->_spriteImg.LoadFromFile(imgPath))
    {
      std::cerr << "Loading " << imgPath << " failed." << std::endl;
      exit (EXIT_FAILURE);
    }
  this->_sprite.SetImage(this->_spriteImg);
  this->_sprite.SetPosition(posXOnMap, posYOnMap);
  this->_sprite.SetScale(2, 2);
}

SpriteEntity::SpriteEntity(const SpriteEntity& rhs) :
  _timeOfCreation(rhs._timeOfCreation), _sprite(rhs._sprite), _deepness(rhs._deepness), _direction(rhs._direction), _id(rhs._id), _spriteImg(rhs._spriteImg),
  _posXOnSprite(rhs._posXOnSprite), _posYOnSprite(rhs._posYOnSprite), _speed(rhs._speed), _isActioned(_isActioned),
  _typeSpriteEntity(rhs._typeSpriteEntity)
{
}

SpriteEntity::~SpriteEntity()
{
}


SpriteEntity& SpriteEntity::operator=(const SpriteEntity& rhs)
{
  if (this != &rhs)
    {
      this->_sprite = rhs._sprite;
      this->_deepness = rhs._deepness;
      this->_direction = rhs._direction;
      this->_id = rhs._id;
      this->_spriteImg = rhs._spriteImg;
      this->_posXOnSprite = rhs._posXOnSprite;
      this->_posYOnSprite = rhs._posYOnSprite;
      this->_speed = rhs._speed;
      this->_isActioned = rhs._isActioned;
      this->_timeOfCreation = rhs._timeOfCreation;
      this->_typeSpriteEntity = rhs._typeSpriteEntity;
    }
  return (*this);
}

/*********************************************************************/

unsigned int 	SpriteEntity::getId() const
{
  return (this->_id);
}

void SpriteEntity::setDirection(const char direction)
{
  this->_direction = direction;
}

char SpriteEntity::getDirection() const
{
  return (this->_direction);
}

void SpriteEntity::setActioned(bool action)
{
  this->_isActioned = action;
}

int	SpriteEntity::getDeepness() const
{
  return (this->_deepness);
}

sf::Sprite *	SpriteEntity::getSprite()
{
  return (&this->_sprite);
}

void	SpriteEntity::setWidthHeight(float width, float height)
{
  this->_width = width;
  this->_height = height;
}

void	SpriteEntity::setPosOnSprite(float numX, float numY)
{
  float wPos = numX * this->_width;
  float hPos = numY * this->_height;

  sf::Rect<int> rect(static_cast<int>(wPos), static_cast<int>(hPos), static_cast<int>(this->_width + wPos), 
		     static_cast<int>(this->_height + hPos));
  this->_sprite.SetSubRect(rect);
}

void	SpriteEntity::setTypeSpriteEntity(typeSpriteEntity type)
{
  this->_typeSpriteEntity = type;
}


void	SpriteEntity::setPosition(float x, float y)
{
  this->_sprite.SetPosition(x, y);
}


/*********************************************************************/

bool SpriteEntity::isActioned() const
{
  return (this->_isActioned);
}


bool	SpriteEntity::isPlayer() const
{
  return (this->_id < 4);
}

/*********************************************************************/

typeSpriteEntity	SpriteEntity::getTypeSpriteEntity() const
{
  return (this->_typeSpriteEntity);
}


int		SpriteEntity::getSpeed() const
{
  return (this->_speed);
}

char	SpriteEntity::move()
{
  //L R U D l u r d
  Move	m;

  m.execMove(this);
  return (this->_direction);
}
