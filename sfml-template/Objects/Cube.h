#pragma once
#include "SpriteObj.h"
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
	
protected:
	bool ground = false;
	RectangleShape* hitbox;
	float verticalspeed = 0.f;
	float addspeed = 50;
	bool side=false; //false=left true=right


};

