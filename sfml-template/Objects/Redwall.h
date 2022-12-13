#pragma once
#include "SpriteObj.h"
#include "../Objects/Button.h"
#include "../Objects/Tile.h"

class Redwall : public WireableObject
{
public:
	Redwall();
	Redwall(Vector2f& position, vector<int> buttonlist, bool active, int dir);
	virtual ~Redwall();

	virtual void Update(float dt);
	virtual void Draw(RenderWindow& window);

	void SetButtonlist(vector<Button*>& button);
	virtual void SetButtonlist(vector<int> idList) { buttonid = idList; }
	virtual SpriteObj* NewThis();

	bool Gethitwall() { return hitwall; }
	void Sethitwall(bool a) { hitwall = a; }

	FloatRect GetredwallGlobalBound() { return redwall.getGlobalBounds(); }

	void Setwhohitwall(SpriteObj* wall) { whohitwall = wall; }

	FloatRect GetredwallHitboxGlobalBound() { return hitbox.getGlobalBounds(); }
	Vector2f GetStartPos() { return startpos; }

	Vector2f GetRedwallPos() { return redwall.getPosition(); }

	bool GetIspress() { return enable; };

	///////////////////

	void InitTexBox();	
	void DrawTexBox(RenderWindow& window);	
	bool GetRedActive() { return originactive; }
	void SetRedActive(bool a) { originactive = a; }

private:
	RectangleShape redwall;
	list<Button*> button;
	vector<int>buttonid;
	Vector2f startpos;
	bool enable;
	bool hitwall = false;
	const float thickness = 10;;
	int dir;
	bool originactive;

	RectangleShape hitbox;

	Vector2f pos;

	SpriteObj* whohitwall = nullptr;

	/////////////////////////
	RectangleShape onOfftexBox;
	Text onOffTex;
};

