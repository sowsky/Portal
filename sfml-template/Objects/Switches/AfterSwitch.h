#pragma once
#include "../Switch.h"
class AfterSwitch : public Switch
{
public:
	AfterSwitch();
	virtual ~AfterSwitch() {}

	virtual SpriteObj* NewThis();
	float GetTime() { return time; }

	virtual void Draw(RenderWindow& window);
protected:
	RectangleShape box;
	Text num;

	CircleShape up;
	CircleShape down;
};

