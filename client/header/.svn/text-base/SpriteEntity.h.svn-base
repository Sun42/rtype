#ifndef SPRITE_ENTITY_H_
#define SPRITE_ENTITY_H_

#include <SFML/Graphics.hpp>

enum typeShip	{PLAYER1, PLAYER2, PLAYER3, PLAYER4, MONSTER1, MONSTER2, BOSS1, BOSS2};
enum typeWeapon	{WEAPON1, WEAPON2, WEAPON3};
enum typeDecor	{EXPLOSION1, DECOR1, DECOR2, DECOR3};
enum typeSpriteEntity {TYPESHIP, TYPEWEAPON, TYPEDECOR};

class	SpriteEntity
{
 public:
  SpriteEntity(unsigned int id, int speed, float timeOfCreation, float posXOnMap, float posYOnMap, const char* imgPath, int deep);
  SpriteEntity(const SpriteEntity& r);
  virtual ~SpriteEntity();
  SpriteEntity&			operator=(const SpriteEntity& r);

  unsigned int		 	getId() const;
  sf::Sprite *			getSprite();
  void				setDirection(const char direction);
  char				getDirection() const;
  void				setActioned(bool action);
  int				getDeepness() const;
  void				setWidthHeight(float width, float height);
  void				setPosOnSprite(float wPos, float hPos);
  void				setTypeSpriteEntity(typeSpriteEntity type);
  void				setPosition(float x, float y);
  typeSpriteEntity		getTypeSpriteEntity() const;
  int				getSpeed() const;

  bool				isActioned() const;
  bool				isPlayer() const;

  char				move();

  virtual unsigned int		touched(float currentTime) = 0;
  virtual void			execActions(float currentTime) = 0;
  virtual void			spriteUp() = 0;
  virtual void			spriteDown() = 0;
  virtual void			spriteLeft() = 0;
  virtual void			spriteRight() = 0;

 protected:
  float			_timeOfCreation;
  sf::Sprite		_sprite;

 private:
  float			_width;
  float			_height;
  int			_deepness;
  char			_direction;
  unsigned int		_id;
  sf::Image		_spriteImg;
  float			_posXOnSprite;
  float			_posYOnSprite;
  int			_speed;
  bool			_isActioned;
  typeSpriteEntity	_typeSpriteEntity;
};

#endif //! SPRITE_ENTITY_H_

