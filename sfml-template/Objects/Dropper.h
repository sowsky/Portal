#pragma once
#include "WireableObject.h"
#include "Button.h"
#include "Cube.h"

class Dropper : public WireableObject
{
public:
	Dropper();
	Dropper(Vector2f pos, vector<float> buttonlist,Cube* cube);

	virtual ~Dropper();

	virtual void Update(float dt);
	virtual void Draw(RenderWindow& window);
	virtual SpriteObj* NewThis();

	void InitTexBox();	
	void DrawTexBox(RenderWindow& window);	
	bool GetDropperTurnON() { return isTurnOn; }
	void SetDropperTurnON(bool a) { isTurnOn = a; }

	virtual void SetButtonlist(vector<Button*>& button);

protected:
	bool isTurnOn = false;
	list<Button*> button;

	RectangleShape dropper;

	Cube* cube;

	vector<float>buttonid;

	RectangleShape onOfftexBox;
	Text onOffTex;
	

};

