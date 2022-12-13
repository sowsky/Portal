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

	FloatRect GetHitboxGlobalbounds() { return hitbox.getGlobalBounds(); }

	int Getdir() { return dir + 4; }
	
protected:
	ConvexShape triangle;
	int dir;
	RectangleShape hitbox;
	Vector2f hitboxpos;
};

