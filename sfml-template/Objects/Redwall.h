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
private:
	RectangleShape redwall;
	list<Button*> button;
	vector<int>buttonid;
	Vector2f startpos;
	bool active;
	bool hitwall = false;
	const float thickness = 10;;
	int dir;

	Tile* whohitwall = nullptr;

};

