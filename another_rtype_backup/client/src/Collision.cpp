#include <SFML/Graphics.hpp>
#include "Collision.h"

Collision::Collision()
{
}

Collision::~Collision()
{
}

sf::IntRect	Collision::GetAABB(const sf::Sprite& Object)
{
  sf::Vector2f	pos = Object.TransformToGlobal(sf::Vector2f(0, 0));
  sf::Vector2f	size = Object.GetSize();
  float	Angle = Object.GetRotation();

  if (Angle == 0.0f)
    {
      return sf::IntRect(static_cast<int> (pos.x),
			 static_cast<int> (pos.y),
			 static_cast<int> (pos.x + size.x),
			 static_cast<int> (pos.y + size.y));
    }
  sf::Vector2f B(size.x, 0);
  sf::Vector2f C(size.x, size.y);
  sf::Vector2f D(0, size.y);

  B = RotatePoint(B, Angle);
  C = RotatePoint(C, Angle);
  D = RotatePoint(D, Angle);

  int Left = static_cast<int> (MinValue(0.0f, B.x, C.x, D.x));
  int Top = static_cast<int> (MinValue(0.0f, B.y, C.y, D.y));
  int Right = static_cast<int> (MaxValue(0.0f, B.x, C.x, D.x));
  int Bottom = static_cast<int> (MaxValue(0.0f, B.y, C.y, D.y));

  sf::IntRect AABB = sf::IntRect(Left, Top, Right, Bottom);
  AABB.Offset(static_cast<int> (pos.x), static_cast<int> (pos.y));
  return AABB;
}

float	Collision::MinValue(float a, float b, float c, float d)
{
  float min = a;

  min = (b < min ? b : min);
  min = (c < min ? c : min);
  min = (d < min ? d : min);

  return min;
}

float	Collision::MaxValue(float a, float b, float c, float d)
{
  float max = a;

  max = (b > max ? b : max);
  max = (c > max ? c : max);
  max = (d > max ? d : max);

  return max;
}

sf::Vector2f	Collision::RotatePoint(const sf::Vector2f& Point, float Angle)
{
  Angle = static_cast<float>(Angle * RADIANS_PER_DEGREE);
  sf::Vector2f RotatedPoint;
  RotatedPoint.x = Point.x * cos(Angle) + Point.y * sin(Angle);
  RotatedPoint.y = -Point.x * sin(Angle) + Point.y * cos(Angle);
  return RotatedPoint;
}

bool	Collision::PixelPerfectTest(const sf::Sprite& Object1, const sf::Sprite& Object2, sf::Uint8 AlphaLimit)
{
  sf::IntRect Object1AABB = GetAABB(Object1);
  sf::IntRect Object2AABB = GetAABB(Object2);
  sf::IntRect Intersection;

  if (Object1AABB.Intersects(Object2AABB, &Intersection))
    {
      if (AlphaLimit == 0)
	return (true);
      sf::IntRect O1SubRect = Object1.GetSubRect();
      sf::IntRect O2SubRect = Object2.GetSubRect();

      sf::Vector2i O1SubRectSize(O1SubRect.GetWidth(), O1SubRect.GetHeight());
      sf::Vector2i O2SubRectSize(O2SubRect.GetWidth(), O2SubRect.GetHeight());

      sf::Vector2f o1v;
      sf::Vector2f o2v;

      for (int i = Intersection.Left; i < Intersection.Right; i++) {
	for (int j = Intersection.Top; j < Intersection.Bottom; j++) {

	  o1v = Object1.TransformToLocal(sf::Vector2f(static_cast<float>(i), static_cast<float>(j)));
	  o2v = Object2.TransformToLocal(sf::Vector2f(static_cast<float>(i), static_cast<float>(j)));

	  if (o1v.x > 0 && o1v.y > 0 && o2v.x > 0 && o2v.y > 0 &&
	      o1v.x < O1SubRectSize.x && o1v.y < O1SubRectSize.y &&
	      o2v.x < O2SubRectSize.x && o2v.y < O2SubRectSize.y) {

	    if ((Object1.GetPixel(static_cast<int> (o1v.x), static_cast<int> (o1v.y)).a > AlphaLimit) &&
		(Object2.GetPixel(static_cast<int> (o2v.x), static_cast<int> (o2v.y)).a > AlphaLimit)) {
	      return true;
	    }
	  }
	}
      }
      return false;
    }
  return false;
}

bool	Collision::CircleTest(const sf::Sprite& Object1, const sf::Sprite& Object2)
{
  float Radius1 = (Object1.GetSize().x + Object1.GetSize().y) / 4;
  float Radius2 = (Object2.GetSize().x + Object2.GetSize().y) / 4;
  float xd = Object1.GetPosition().x - Object2.GetPosition().x;
  float yd = Object1.GetPosition().y - Object2.GetPosition().y;

  return sqrt(xd * xd + yd * yd) <= Radius1 + Radius2;
}

bool Collision::BoundingBoxTest(const sf::Sprite& Object1, const sf::Sprite& Object2)
{
  sf::Vector2f A, B, C, BL, TR;
  sf::Vector2f HalfSize1 = Object1.GetSize();
  sf::Vector2f HalfSize2 = Object2.GetSize();

  HalfSize1.x /= 2;
  HalfSize1.y /= 2;
  HalfSize2.x /= 2;
  HalfSize2.y /= 2;

  float Angle = Object1.GetRotation() - Object2.GetRotation();
  float CosA = static_cast<float>(cos(Angle * RADIANS_PER_DEGREE));
  float SinA = static_cast<float>(sin(Angle * RADIANS_PER_DEGREE));

  float t, x, a, dx, ext1, ext2;

  C = Object2.GetPosition();

  C -= Object1.GetPosition();

  C = RotatePoint(C, Object2.GetRotation());

  BL = TR = C;
  BL -= HalfSize2;
  TR += HalfSize2;

  A.x = -HalfSize1.y*SinA;
  B.x = A.x;
  t = HalfSize1.x*CosA;
  A.x += t;
  B.x -= t;

  A.y = HalfSize1.y*CosA;
  B.y = A.y;
  t = HalfSize1.x*SinA;
  A.y += t;
  B.y -= t;

  t = SinA * CosA;

  if (t < 0)
    {
      t = A.x;
      A.x = B.x;
      B.x = t;
      t = A.y;
      A.y = B.y;
      B.y = t;
    }

  if (SinA < 0)
    {
      B.x = -B.x;
      B.y = -B.y;
    }

  if (B.x > TR.x || B.x > -BL.x)
    return (false);

  if (t == 0)
    {
      ext1 = A.y;
      ext2 = -ext1;
    }
  else
    {
      x = BL.x - A.x;
      a = TR.x - A.x;
      ext1 = A.y;
      if (a * x > 0)
	{
	  dx = A.x;
	  if (x < 0)
	    {
	      dx -= B.x;
	      ext1 -= B.y;
	      x = a;
            } else
	    {
	      dx += B.x;
	      ext1 += B.y;
            }
	  ext1 *= x;
	  ext1 /= dx;
	  ext1 += A.y;
        }

      x = BL.x + A.x;
      a = TR.x + A.x;
      ext2 = -A.y;
      if (a * x > 0)
	{
	  dx = -A.x;
	  if (x < 0)
	    {
	      dx -= B.x;
	      ext2 -= B.y;
	      x = a;
	    }
	  else
	    {
	      dx += B.x;
	      ext2 += B.y;
	    }
	  ext2 *= x;
	  ext2 /= dx;
	  ext2 -= A.y;
        }
    }
  return !((ext1 < BL.y && ext2 < BL.y) ||
	   (ext1 > TR.y && ext2 > TR.y));
}
