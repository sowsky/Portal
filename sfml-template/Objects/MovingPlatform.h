#pragma once
#include "WireableObject.h"
#include "Button.h"

class MovingPlatform :  public WireableObject
{
public:
	MovingPlatform();
	MovingPlatform(b2World* world, Vector2f& position,bool on,float destX,float destY,vector<int> buttonlist);
	virtual ~MovingPlatform() {};

	virtual SpriteObj* NewThis();

	virtual void Update(float dt);
	virtual void Draw(RenderWindow& window);
protected:
	CircleShape up;
	CircleShape down;
	
	RectangleShape platform;
	RectangleShape Pillar;

	Vector2f destiny;
	Vector2f endpos;

	bool enable;
	list<Button*> button;
	vector<int>buttonid;

	int dir;

	b2World* world = nullptr;

	b2Body* pillarbody = nullptr;
	b2Fixture* pillarfixture = nullptr;

	b2Body* platformbody = nullptr;
	b2Fixture* platformfixture = nullptr;
};

