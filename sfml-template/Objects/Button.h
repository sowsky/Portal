#pragma once

#include "WireableObject.h"
#include "SpriteObj.h"
#include "Goal.h"

class Button : public WireableObject{
public:
	Button();
	virtual ~Button();	

	virtual SpriteObj* NewThis();
public:
	static int GetButtonNum() { return buttonNum; }
	static void SetButtonNum(int num) { buttonNum = num; }

	bool GetPressed() { return isPress; }
	void SetPressed(bool a) { isPress = a; }

	int GetButtonId() { return buttonId; }
	void SetButtonId(int a) { buttonId = a; }
protected:
	bool isPress = false;
	int buttonId;
	static int buttonNum;

};

