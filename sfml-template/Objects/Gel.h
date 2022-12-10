#pragma once
#include "WireableObject.h"

#include <iostream>
using namespace std;

class Gel : public WireableObject
{
public:
	Gel();
	virtual ~Gel();

	virtual void Update(float dt);
	virtual void Draw(RenderWindow& window);
	virtual SpriteObj* NewThis();

	void InitTexBox();
	void InitColorBox();
	void DrawTexBox(RenderWindow& window);
	void DrawColorBox(RenderWindow& window);
	bool GetGelTurnON() { return isTurnOn; }
	void SetGelTurnON(bool a) { isTurnOn = a; }

	bool GetIsBlue() { return isBlue; }
	void SetIsBlue(bool b) { isBlue = b; }
protected:
	bool isTurnOn =false;
	bool isBlue = true;
	bool isDropper;

	RectangleShape onOfftexBox;
	Text onOffTex;

	RectangleShape colorBox;
};

