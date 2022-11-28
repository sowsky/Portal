#pragma once
#include <SFML/Graphics.hpp>
#include "SpriteObj.h"
#include "Button.h"

class Tunnel :public SpriteObj
{
public:
	Tunnel();
	Tunnel(const Vector2f& position, bool Horizon,int d, string buttonlist);
	virtual ~Tunnel();

	virtual void Update(float dt);
	virtual void Draw(RenderWindow& window);

	void SetDir(bool b) { IsBlue = b; }  //true==blue,false=orange
	bool GetDir() { return IsBlue; }

	bool GetHitwall() { return hitwall; }
	void SetHitwall(bool a) { hitwall = a; }
	FloatRect GetHitBoxGlobalbound() { return hitbox.getGlobalBounds(); }

	virtual SpriteObj* NewThis() { return new Tunnel; }
	void SetButtonlist(vector<Button*>& button);
private:
	list<Button*> button;
	vector<int>buttonid;

	RectangleShape tuns;
	RectangleShape hitbox;
	bool IsBlue = true;
	bool active = false;
	bool hitwall = false;
	int dir = 0;

};

