#pragma once
#include "WireableObject.h"
class Dropper : public WireableObject
{
public:
	Dropper();
	virtual ~Dropper();

	virtual void Update(float dt);
	virtual void Draw(RenderWindow& window);
	virtual SpriteObj* NewThis();

	void InitTexBox();	
	void DrawTexBox(RenderWindow& window);	
	bool GetDropperTurnON() { return isTurnOn; }
	void SetDropperTurnON(bool a) { isTurnOn = a; }
protected:
	bool isTurnOn = false;

	RectangleShape onOfftexBox;
	Text onOffTex;
};

