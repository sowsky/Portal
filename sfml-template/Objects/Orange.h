#pragma once
#include "SpriteObj.h"
class Orange:public SpriteObj
{
public:
	Orange();
	virtual ~Orange();
	
	virtual void Update(float dt);
	virtual void Draw(RenderWindow& window);
	void SetPortalDir(int side) { dir = side; }
	int GetPortalDir() { return dir; }
protected:
	RectangleShape* hitbox;
	float projectilespeed = 1000.f;
	int dir;
};

