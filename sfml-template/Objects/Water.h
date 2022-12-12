#pragma once
#include "SpriteObj.h"

class VertexArrayObj;
class Water : public SpriteObj
{
public:
	Water(bool top);
	Water(Vector2f position);
	virtual ~Water() {}

	virtual SpriteObj* NewThis();

	FloatRect GetWaterGlobalBounds() { return water.getGlobalBounds(); }

	virtual void Update(float dt);
	virtual void Draw(RenderWindow& window);
	void InitSetting();

	bool GetIsTop() { return isTop; }
	void SetIsTop(bool top) { isTop = top; }
protected:
	RectangleShape water;

	Vector2f pos;

	Vector2f frontSize;

	Sprite frontFace;
	VertexArrayObj sideFaces;

	bool isTop;
};

