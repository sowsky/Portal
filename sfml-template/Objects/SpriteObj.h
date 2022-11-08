#pragma once
#include "Object.h"
#include "../FrameWork/Utils.h"
#include <string>

class SpriteObj : public Object
{
public:
	SpriteObj();
	virtual ~SpriteObj();

	void SetOrigin(Origins origin);
	virtual void SetPos(const Vector2f& pos);

	virtual void Update(float dt);
	virtual void Draw(RenderWindow& window);

	void SetTexture(String id);
	Sprite* GetSprite();
protected:
	Sprite sprite;
	float speed;
};

