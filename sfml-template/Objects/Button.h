#pragma once
#include "SpriteObj.h"
#include "Goal.h"

class Button : public SpriteObj
{
public:
	Button();
	virtual ~Button();

	virtual SpriteObj* NewThis();

	bool GetPressed() { return isPress; }
	void SetPressed(bool a) { isPress = a; }

	int GetButtonId() { return buttonId; }
	void SetButtonId(int a) { buttonId = a; }
protected:
	bool isPress = false;
	int buttonId;
	
};

