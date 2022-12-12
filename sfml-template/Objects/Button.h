#pragma once

#include "WireableObject.h"
#include "SpriteObj.h"
#include "Goal.h"

class VertexArrayObj;
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

	/////////////////////////////
	virtual void Draw
	(RenderTexture& diffuse, Shader& nShader, RenderTexture& normal);

protected:
	bool isPress = false;
	static int buttonNum;
	int buttonId;
	static bool isEditMap;
	RectangleShape* hitbox;


	////////////////////////////////
	VertexArrayObj sideFaces;
	Sprite frontFace;
	Vector2f frontSize;
	Texture* normal;

	////////////////
	Sprite b_pivot;
	VertexArrayObj b_sideFaces;
	Sprite b_frontFace;
	Vector2f b_frontSize;
	Texture* b_normal;
};

