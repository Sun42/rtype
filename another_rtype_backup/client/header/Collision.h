#ifndef _COLLISION_H
#define	_COLLISION_H


#ifndef PI
# define PI (3.14159265358979323846)
#endif
# define RADIANS_PER_DEGREE (PI/180.0)


class	Collision
{
 public:
  virtual ~Collision();
  static bool		PixelPerfectTest(const sf::Sprite& Object1 ,const sf::Sprite& Object2, sf::Uint8 AlphaLimit = 127);
  static bool		CircleTest(const sf::Sprite& Object1, const sf::Sprite& Object2);
  static bool		BoundingBoxTest(const sf::Sprite& Object1, const sf::Sprite& Object2);
  static sf::IntRect	GetAABB(const sf::Sprite& Object);

  static sf::Vector2f	RotatePoint(const sf::Vector2f& Point, float Angle);
  static float		MinValue(float a, float b, float c, float d);
  static float		MaxValue(float a, float b, float c, float d);

 private:
  Collision();
};

#endif	/* _COLLISION_H */
