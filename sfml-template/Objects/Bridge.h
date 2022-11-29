#pragma once
#include "SpriteObj.h"
#include "Button.h"

class Bridge : public SpriteObj
{
public:
	Bridge();
	Bridge(b2World* world, const Vector2f& position, Vector2f dimensions, int dir);
	virtual ~Bridge();
	virtual void Update(float dt);
	virtual void Draw(RenderWindow& window);
protected:
	list<Button*> button;
	vector<int>buttonid;
	bool on;

	RectangleShape bridge;
	RectangleShape hitbox;

	int dir = 0;
	b2Body* body = nullptr;
	b2Fixture* fixture = nullptr;
};

