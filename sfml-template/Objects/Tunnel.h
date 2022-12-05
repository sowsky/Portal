#pragma once
#include <SFML/Graphics.hpp>
#include "WireableObject.h"
#include "Button.h"
#include "Tile.h"

class Tunnel : public WireableObject
{
public:
	Tunnel();
	Tunnel(const Vector2f& position, int dir, vector<int> buttonlist, bool Isblue, bool active,int connected);
	virtual ~Tunnel();

	virtual void Update(float dt);
	virtual void Draw(RenderWindow& window);

	void SetDir(bool b) { IsBlue = b; }  //true==blue,false=orange
	bool GetColor() { return IsBlue; }

	void ChangeDir();
	void ChangeColor();
	void TurnOn();

	bool GetHitwall() { return hitwall; }
	void SetHitwall(bool a) { hitwall = a; }
	FloatRect GetHitBoxGlobalbound() { return hitbox.getGlobalBounds(); }
	FloatRect GetDestinyGlobalbound() { return destiny.getGlobalBounds(); }
	FloatRect GetStartposGlobalbound() { return start.getGlobalBounds(); }

	void Setwhohitwall(SpriteObj& victim) { whohitwall = &victim; }

	virtual SpriteObj* NewThis() { return new Tunnel; }

	virtual void SetButtonlist(vector<Button*>& button);
	virtual void SetButtonlist(vector<int> idList) { buttonid = idList; }

	RectangleShape* GetHitbox() { return &hitbox; }

	int GetDir() { return dir; }
	Vector2f GetTunsPos() { return tuns.getPosition(); }
	int GetConnected() { return connected; }

	void AddParticle();
	void SetParticlePos();
	void TransParticles(float dt);

	vector<int> GetButtonid() { return buttonid; }
	Vector2f GetStartPos() { return startpos; }
private:
	list<Button*> button;
	vector<int>buttonid;

	SpriteObj* whohitwall;
	RectangleShape tuns;
	RectangleShape hitbox;
	RectangleShape destiny;
	RectangleShape start;
	Vector2f startpos;
	Vector2f endpos;
	bool IsBlue;
	bool active;
	bool hitwall = false;
	int dir = 0;
	int connected = 0; //0==none 1==follow blue 2==follow orange

	VertexArray particles;
	int particleNum = 20;
	Vector2f particleDir;
	bool isPtcSetted = false;

	Sprite emitter;
};

