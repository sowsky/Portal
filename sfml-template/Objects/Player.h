#pragma once
#include "SpriteObj.h"
class Player : public SpriteObj
{
public:
	Player();
	virtual ~Player();

	virtual SpriteObj* NewThis();
	bool GetGround() { return ground; }
	void SetGround(bool a) { ground = a; }
	void Move(float dt);
	virtual void Update(float dt);
	virtual void Draw(RenderWindow& window);

	FloatRect GethitboxGlobalBounds() { return hitbox->getGlobalBounds(); }

protected:
	bool ground = false;
	float verticalspeed=0.f;
	float addspeed = 50;
	float maxspeed = 80;

	Vector2f dir={0,0};

	RectangleShape* hitbox;
};

