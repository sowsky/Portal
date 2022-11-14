#pragma once
#include "SpriteObj.h"
#include <box2d/box2d.h>

class Tile : public SpriteObj
{
public:
	Tile();
	// Tile(b2World* world, const Vector2f& position, Vector2f dimensions);
	virtual ~Tile();

	virtual SpriteObj* NewThis();

	virtual void Update(float dt);
	virtual void Draw(RenderWindow& window);
	void PhysicsUpdate();

	////////////////////////////////////////////////////////////////////////////
	Tile(b2World* world, const Vector2f& position, Vector2f dimensions);
	b2Body* GetBody() { return body; }
	b2Fixture* GetFixture() { return fixture; }
protected:
	b2Body* body = nullptr;
	b2Fixture* fixture = nullptr;
	
	RectangleShape* hitbox;


};

