#pragma once
#include "SpriteObj.h"
#include "box2d/box2d.h"

class Cube : public SpriteObj
{
public:
	Cube();
	virtual ~Cube();

	virtual SpriteObj* NewThis();
	bool GetGround() { return ground; }
	void SetGround(bool a) { ground = a; }
	FloatRect GethitboxGlobalBounds() { return hitbox->getGlobalBounds(); }

	virtual void Update(float dt);
	virtual void Draw(RenderWindow& window);
	void SetSide(bool s) { side = s; }
	bool GetSide() { return side; }

	/////////////////////////////////////////////////////////////////////////
	Cube(b2World* world, const Vector2f& position, Vector2f dimensions);
	b2Body* GetBody() { return body; }
	b2Fixture* GetFixture() { return fixture; }	
protected:
	bool ground = false;
	RectangleShape* hitbox;
	float verticalspeed = 0.f;
	float addspeed = 50;
	bool side=false; //false=left true=right

	///////////////////////////////////////////////////////////////////////
	b2Body* body = nullptr;
	b2Fixture* fixture = nullptr;


};

