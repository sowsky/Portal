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
	virtual void Update(float dt);

	RectangleShape* GetHitbox() { return hitbox; }
	bool GetPressed() { return isPress; }
	bool& GetIsPressRef() { return isPress; }
	virtual void SetPressed();

	int GetButtonId() { return buttonId; }
	void SetButtonId(int a) { buttonId = a; }
	static void SetIsEditMap(bool edit) { isEditMap = edit; }
	virtual void SetSwitchActive() {};	

	/////////////////////////////

	virtual void Draw
	(RenderTexture& diffuse, Shader& nShader, RenderTexture& normal);	
	void SetUpButtonPos();
	void SetButtonRoation(int val);
	void UpdatePressureAnimation(float dt);
	void ChageTexOnoff(bool press);

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

	Sprite upPivot;
	VertexArrayObj upSideFaces;
	Sprite upFrontFace;
	Vector2f upFrontSize;
	Texture* upNormal;

	float buttonHeightFix;
	float limit = 1.f;
	const float move = 40.f;
	int rot;

	bool prevState;
};

