#pragma once
#include "WireableObject.h"

class MovingPlatform :  public WireableObject
{
public:
	MovingPlatform();
	virtual ~MovingPlatform() {}

	virtual SpriteObj* NewThis();

	virtual void Update(float dt);
	virtual void Draw(RenderWindow& window);

	void DrawUi(RenderWindow& window);

	int GetRange() { return range; }
	void SetRange(int r) { range = r; }

	void InitTexBox();	
	void DrawTexBox(RenderWindow& window);	
	bool GetPlatformOn() { return isTurnedOn; }
	void SetPlatformOn(bool a) { isTurnedOn = a; }
protected:
	int range = 1;
	bool isTurnedOn;

	CircleShape up;
	CircleShape down;

	array<Sprite, 20> arrows;

	RectangleShape onOfftexBox;
	Text onOffTex;
};

