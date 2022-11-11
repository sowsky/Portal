#pragma once
#include "SpriteObj.h"
class Player : public SpriteObj
{
public:
	Player();
	virtual ~Player();

	virtual SpriteObj* NewThis();

public:
	static int GetPlayerNum();
	virtual void Update(float dt);
	virtual void Draw(RenderWindow& window);
	void Move(float dt);

	static int playerNum;

	bool GetGround() { return ground; }
	void SetGround(bool a) { ground = a; }
	

	FloatRect GethitboxGlobalBounds() { return hitbox->getGlobalBounds(); }

protected:
	bool ground = false;
	float verticalspeed=0.f;
	float addspeed = 50;
	float maxspeed = 80;

	Vector2f dir={0,0};

	RectangleShape* hitbox;

};

