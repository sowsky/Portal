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

	void DrawUi(RenderWindow& window);

	int GetRange() { return range; }
	void SetRange(int r) { range = r; }

	void InitTexBox();	
	void DrawTexBox(RenderWindow& window);	
	bool GetPlatformOn() { return isTurnedOn; }
	void SetPlatformOn(bool a) { isTurnedOn = a; }
protected:
	int range = 1;
	bool isTurnedOn;

	CircleShape up;
	CircleShape down;
	
	RectangleShape platform;
	RectangleShape pillar;


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

	array<Sprite, 20> arrows;


	RectangleShape onOfftexBox;
	Text onOffTex;

};

