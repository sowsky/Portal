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
	void SetPlayerBodyLinearVelocityForce(b2Vec2 force);
	b2Vec2 GetPlayerBodyLinearVelocity() { return body->GetLinearVelocity(); }

	b2Body* GetBody() { return body; }

	Vector2f GetRecentSpeed() { return recentspeed; }
	void SetMaxSpeed(Vector2f vec) { recentspeed = vec; }

	bool GetIsMoving() { return IsMoving; }
protected:
	bool ground = false;
	bool IsMoving = false;
	float verticalspeed=0.f;
	float speedtX = 0.f;
	float speedtY = 0.f;

	float maximumspeed=18.f;

	Vector2f recentspeed;

	Vector2f dir={0,0};

	RectangleShape* hitbox;
	
	/////////////////////////////////////////////////////////
	b2Body* body = nullptr;
	b2Fixture* fixture = nullptr;

	Sprite p_head;
	Sprite p_body;
	Sprite p_arm;
	Sprite p_lleg;
	Sprite p_rleg;
};

