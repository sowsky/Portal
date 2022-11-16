#pragma once
#include "WireableObject.h"

class Button : public WireableObject
{
public:
	Button();
	virtual ~Button();	

	virtual SpriteObj* NewThis();
public:
	static int GetButtonNum() { return buttonNum; }
	static void SetButtonNum(int num) { buttonNum = num; }
protected:	
	bool isPressed = false;
	int buttonId;

	static int buttonNum;
};

