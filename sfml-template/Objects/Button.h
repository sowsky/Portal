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
	virtual void Draw(RenderWindow& window);

	RectangleShape* GetHitbox() { return hitbox; }
	bool GetPressed() { return isPress; }
	void SetPressed(bool a) { isPress = a; }

	int GetButtonId() { return buttonId; }
	void SetButtonId(int a) { buttonId = a; }
	static void SetIsEditMap(bool edit) { isEditMap = edit; }

protected:
	bool isPress = false;
	int buttonId;	
	static bool isEditMap;
	RectangleShape* hitbox;

};

