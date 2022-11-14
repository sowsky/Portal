#pragma once
#include <random>
#include <SFML/Graphics.hpp>
#include "box2d/box2d.h"
#include "../FrameWork/Const.h"

using namespace sf;
using namespace std;

enum class Origins
{
	TL,	// 0
	TC,
	TR,
	ML,
	MC,
	MR,
	BL,
	BC,
	BR,	// 8
};

class Utils
{
private:
	static random_device rd;
	static mt19937 gen;

public:
	static void SetOrigin(Text& obj, Origins origin);
	static void SetOrigin(Sprite& obj, Origins origin);
	static void SetOrigin(Shape& obj, Origins origin);
	static void SetOrigin(Transformable& obj, Origins origin, FloatRect rect);
	
	static float Clamp(float v, float min, float max);

	static int RandomRange(int min, int maxExclude);
	static float RandomRange(float min, float max);

	static float SqrMagnitude(const Vector2f& vec);
	static float Magnitude(const Vector2f& vec);
	static Vector2f Normalize(const Vector2f& vec);
	static float Distance(const Vector2f& vec1, const Vector2f& vec2);
	static float Dot(const Vector2f& a, const Vector2f& b);
	static Vector2f GetNormal(const Vector2f& vec);

	static float Angle(const Vector2f& start, const Vector2f& end);
	static float Angle(const Vector2f& dir);

	static float RandomZeroToOne();
	static Vector2f RandomInCirclePoint();
	static Vector2f RandomOutCirclePoint();

	static void SetSpriteSize(Sprite& sprite, Vector2f size);

	static Vector2f GetSpriteSize(Sprite& sprite);	
	
	static void ChangeCoordSFMLToBox2d(Sprite& sprite,b2Body& body);
	static void ChangeBCSpriteSFMLPosToBox2dPos(Sprite& sprite, b2Body& body);

	static void ChangePPM(b2Vec2 vec);
};

