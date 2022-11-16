#pragma once
#include "SpriteObj.h"
class Player : public SpriteObj
{
public:
	Player();
	Player(b2World* world, const Vector2f& position, Vector2f dimensions);

	virtual ~Player();

	virtual SpriteObj* NewThis();

public:
	static int GetPlayerNum();
	virtual void Update(float dt);
	void PhysicsUpdate();
	virtual void Draw(RenderWindow& window);

	Vector2f GetPositions() { return sprite.getPosition(); }

	static int playerNum;

	bool GetGround() { return ground; }
	void SetGround(bool a) { ground = a; }
	

	FloatRect GethitboxGlobalBounds() { return hitbox->getGlobalBounds(); }
	void SetPlayerBodyPos(Vector2f pos);
	b2Vec2 GetPlayerBodyPos() { return body->GetPosition(); }
	void SetPlayerBodyForce(b2Vec2 force);
	b2Vec2 GetPlayerBodyForce() { return body->GetLinearVelocity(); }

protected:
	bool ground = false;
	float verticalspeed=0.f;
	float addspeed = 50;
	float maxspeed = 80;

	Vector2f dir={0,0};

	RectangleShape* hitbox;
	
	/////////////////////////////////////////////////////////
	b2Body* body = nullptr;
	b2Fixture* fixture = nullptr;

};

