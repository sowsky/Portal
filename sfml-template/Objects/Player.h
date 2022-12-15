#pragma once
#include "SpriteObj.h"
#include <SFML/Audio.hpp>
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
	virtual void Draw
	(RenderTexture& diffuse, Shader& nShader, RenderTexture& normal);

	Vector2f GetPositions() { return sprite.getPosition(); }

	bool GetGround() { return ground; }
	void SetGround(bool a) { ground = a; }
	
	void BodySetDoubleScale();

	FloatRect GetIndicatorGlobalBounds() { return indicator.getGlobalBounds(); }

	FloatRect GethitboxGlobalBounds() { return hitbox->getGlobalBounds(); }
	void SetPlayerBodyPos(Vector2f pos);
	b2Vec2 GetPlayerBodyPos() { return body->GetPosition(); }
	void SetPlayerBodyLinearVelocityForce(b2Vec2 force);
	b2Vec2 GetPlayerBodyLinearVelocity() { return body->GetLinearVelocity(); }

	b2Body* GetBody() { return body; }

	Vector2f GetRecentSpeed() { return recentspeed; }
	void SetMaxSpeed(Vector2f vec) { recentspeed = vec; }

	bool GetIsMoving() { return IsMoving; }

	void UpdatePlayerPos(float dt);
	void WalkAnimaton(float dt);
	void StruggelAnimation(float dt);
	void RotateAnimation(RenderWindow& window);
	void ShowBornForDev(RenderWindow& window);
	void ShowIndicator(RenderWindow& window);
	void Respawn();

	void SetFlying(bool a) { isFlying = a; }

	Vector2f GetClaviclePos();
	Vector2f GetIndicator();
	bool IsMouseRight();
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

	Vector2f checkpointpos;
	
	/////////////////////////////////////////////////////////
	b2Body* body = nullptr;
	b2Fixture* fixture = nullptr;

	Sprite p_head;
	Sprite p_body;
	RectangleShape p_arm;	
	RectangleShape p_spare_arm;
	Sprite p_lleg;
	Sprite p_rleg;
	Sprite portalGun;

	Texture* head_normal;
	Texture* body_normal;
	Texture* arm_normal;
	Texture* leg_normal;

	RectangleShape spine1;
	RectangleShape spine2;
	RectangleShape pelvis;
	RectangleShape clavicle;
	RectangleShape armBorn;
	RectangleShape indicator;
	RectangleShape jump;

	float jumpcooltime = 0;
	bool startMove;
	bool isFlying;
	float legdir = 1.f;
	float groundTime = 0.25f;
	float groundTimeMax = 0.0f;

	//bool devMod = false;
	bool right;
	bool isJumping = false;

	float pressdt = 0.0f;

	float addt = 0.0f;
};

