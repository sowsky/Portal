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
	virtual void Update(float dt);
	virtual void PhysicsUpdate(float dt);
	virtual void Draw(RenderWindow& window);

	Vector2f GetPositions() { return sprite.getPosition(); }	

	bool GetGround() { return ground; }
	void SetGround(bool a) { ground = a; }
	

	FloatRect GethitboxGlobalBounds() { return hitbox->getGlobalBounds(); }
	void SetPlayerBodyPos(Vector2f pos);
	b2Vec2 GetPlayerBodyPos() { return body->GetPosition(); }
	void SetPlayerBodyForce(b2Vec2 force);
	b2Vec2 GetPlayerBodyForce() { return body->GetLinearVelocity(); }

	b2Body* GetBody() { return body; }
protected:
	bool ground = false;
	float verticalspeed=0.f;
	float speed = 50;
	float maxspeed = 80;

	Vector2f dir={0,0};

	RectangleShape* hitbox;
	
	/////////////////////////////////////////////////////////
	b2Body* body = nullptr;
	b2Fixture* fixture = nullptr;

};

