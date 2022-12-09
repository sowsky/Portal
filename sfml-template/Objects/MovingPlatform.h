#pragma once
#include "WireableObject.h"

class MovingPlatform :  public WireableObject
{
public:
	MovingPlatform();
	virtual ~MovingPlatform() {}

	virtual SpriteObj* NewThis();

	virtual void Update(float dt);
	virtual void Draw(RenderWindow& window);

	void DrawUi(RenderWindow& window);

	int GetRange() { return range; }
	void SetRange(int r) { range = r; }
protected:
	int range = 1;

	CircleShape up;
	CircleShape down;

	array<Sprite, 20> arrows;
};

