#pragma once
#include "SpriteObj.h"
class Water : public SpriteObj
{
public:
	Water();
	Water(Vector2f position);
	virtual ~Water() {}

	virtual SpriteObj* NewThis();

	FloatRect GetWaterGlobalBounds() { return water.getGlobalBounds(); }

	virtual void Update(float dt);
	virtual void Draw(RenderWindow& window);
protected:
	RectangleShape water;

	Vector2f pos;
};

