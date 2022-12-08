#pragma once

#include "WireableObject.h"
#include "SpriteObj.h"
#include "Goal.h"

class Button : public WireableObject {
public:
	Button();	
	virtual ~Button();

	virtual SpriteObj* NewThis();
public:
	virtual void Draw(RenderWindow& window);

	RectangleShape* GetHitbox() { return hitbox; }
	bool GetPressed() { return isPress; }
	bool& GetIsPressRef() { return isPress; }
	virtual void SetPressed() { isPress = !isPress; }

	int GetButtonId() { return buttonId; }
	void SetButtonId(int a) { buttonId = a; }
	static void SetIsEditMap(bool edit) { isEditMap = edit; }
	virtual void SetSwitchActive() {};
protected:
	bool isPress = false;
	static int buttonNum;
	int buttonId;
	static bool isEditMap;
	RectangleShape* hitbox;

};

