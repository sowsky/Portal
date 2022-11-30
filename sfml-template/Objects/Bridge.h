#pragma once
#include "WireableObject.h"
#include "Button.h"
#include "Tile.h"

class Bridge : public WireableObject
{
public:
	Bridge();
	Bridge(b2World* world, const Vector2f& position, Vector2f dimensions, vector<int> buttonlist, bool active, int dir, int connected);
	virtual ~Bridge();
	virtual void Update(float dt);
	virtual void Draw(RenderWindow& window);

	bool GetHitwall() { return hitwall; }
	void SetHitwall(bool a) { hitwall = a; }
	void Setwhohitwall(Tile& victim) { whohitwall = &victim; }
	FloatRect GetHitBoxGlobalbound() { return hitbox.getGlobalBounds(); }

	virtual SpriteObj* NewThis() { return new Bridge; }
protected:
	list<Button*> button;
	vector<int>buttonid;
	Tile* whohitwall = nullptr;

	bool active;
	bool hitwall;
	int connected = 0; //0==none 1==follow blue 2==follow orange

	RectangleShape bridge;
	RectangleShape hitbox;

	Vector2f startpos;

	int dir = 0;
	b2Body* body = nullptr;
	b2Fixture* fixture = nullptr;
};

