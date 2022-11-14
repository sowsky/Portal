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
public:
	void SetResourceTexture(String id);
	
	Sprite* GetSprite();

	void SetScale(Vector2f scale);
	virtual void SetSize(Vector2f size);
	Vector2f GetSize();

	void FitScale(float size);
	void SetRotation(int val);
	void SetRotation(float val) { sprite.setRotation(val); }
	void SetDir(Vector2f dir) { direction = dir; };
	char GetId();

	virtual SpriteObj* NewThis();

	FloatRect GetGlobalBounds();

	static void OnOffWiringState() { isWiring = !isWiring; }
	virtual bool GetWiringState() { return isWiring; }	

	void SetBoolInMapTool(bool isIn) { isInMapTool = isIn; }
protected:
	Sprite sprite;
	float speed=100.f;
	float velocity=0.f;
	Vector2f direction={0,0};

	char id;

	static bool isWiring;
	bool isInMapTool;
};

