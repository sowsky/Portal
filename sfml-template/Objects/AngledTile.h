#pragma once
#include "SpriteObj.h"
class AngledTile : public SpriteObj
{
public:
	AngledTile();
	AngledTile(b2World* world, Vector2f position, int angle);
	virtual ~AngledTile();	

	virtual SpriteObj* NewThis();

	virtual void Update(float dt);
	virtual void Draw(RenderWindow& window);
protected:
	ConvexShape triangle;
	int dir;
	RectangleShape hitbox;
};

