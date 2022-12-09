#pragma once
#include "WireableObject.h"

class MovingPlatform :  public WireableObject
{
public:
	MovingPlatform();
	virtual ~MovingPlatform();

	virtual SpriteObj* NewThis();

	virtual void Update(float dt);
	virtual void Draw(RenderWindow& window);
protected:
	CircleShape up;
	CircleShape down;


};

