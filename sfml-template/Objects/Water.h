#pragma once
#include "SpriteObj.h"
class Water : public SpriteObj
{
public:
	Water();
	virtual ~Water() {}

	virtual SpriteObj* NewThis();

	virtual void Update(float dt);
	virtual void Draw(RenderWindow& window);
protected:
	RectangleShape water;
};

