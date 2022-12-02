#pragma once
#include "WireableObject.h"
#include "Button.h"
#include "Tile.h"

class Bridge : public WireableObject
{
public:
	Bridge();
	Bridge(b2World* world, Vector2f& position,vector<int> buttonlist, bool active, int dir, int connected);
	virtual ~Bridge();
	virtual void Update(float dt);
	virtual void Draw(RenderWindow& window);

	bool GetHitwall() { return hitwall; }
	void SetHitwall(bool a) { hitwall = a; }
	void Setwhohitwall(Tile& victim) { whohitwall = &victim; }
	FloatRect GetHitBoxGlobalbound() { return hitbox.getGlobalBounds(); }

	virtual void SetButtonlist(vector<int> idList) { buttonid = idList; }

	FloatRect GetBridgeGlobalBound() { return bridge.getGlobalBounds(); }
	FloatRect GetDestinyGlobalbound() { return destiny.getGlobalBounds(); }
	FloatRect GetStartposGlobalbound() { return start.getGlobalBounds(); }

	virtual SpriteObj* NewThis() { return new Bridge; }

	Vector2f Gethitboxpos() { return hitbox.getPosition(); }
	virtual void SetButtonlist(vector<Button*>& button);

	int GetConnected() { return connected; }

	void UpdateBridgeDraw(RenderWindow& window);
	void DrawBackEmmiter(RenderWindow& window);
protected:
	list<Button*> button;
	vector<int>buttonid;
	Tile* whohitwall = nullptr;

	bool active;
	bool hitwall;
	bool setedpos;
	int connected = 0; //0==none 1==follow blue 2==follow orange

	RectangleShape bridge;

	RectangleShape hitbox;
	RectangleShape destiny;
	RectangleShape start;

	Vector2f startpos;
	Vector2f endpos;

	int dir = 0;
	b2Body* body = nullptr;
	b2World* world = nullptr;
	b2Fixture* fixture = nullptr;	

	//////////////////

	Vector2f front_des_pos;
	Vector2f back_des_pos;

	Sprite frontEmitter;
	Sprite backEmitter;	
	
	VertexArray bridge_rect;

	Texture* bridge_color;

	float backDp;
};

