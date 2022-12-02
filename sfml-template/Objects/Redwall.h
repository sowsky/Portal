#pragma once
#include "SpriteObj.h"
#include "../Objects/Button.h"
#include "../Objects/Tile.h"

class Redwall : public SpriteObj
{
public:
	Redwall(Vector2f& position, vector<int> buttonlist, bool active, int dir);
	virtual ~Redwall();

	virtual void Update(float dt);
	virtual void Draw(RenderWindow& window);

	void SetButtonlist(vector<Button*>& button);
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

