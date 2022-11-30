#pragma once
#include <SFML/Graphics.hpp>
#include "WireableObject.h"
#include "Button.h"
#include "Tile.h"
#include "../Particle/Particle.h"

struct Particles
{
	vector<Particle> m_Particles;
	VertexArray m_Vertices;
	float m_Duration;
	bool m_IsRunning = false;
};

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
	
	void Setwhohitwall(Tile& victim) { whohitwall = &victim; }
	virtual SpriteObj* NewThis() { return new Tunnel; }

	virtual void SetButtonlist(vector<Button*>& button);
	virtual void SetButtonlist(vector<int> idList) { buttonid = idList; }

	FloatRect GetHitbox() { return hitbox.getGlobalBounds(); }

	int GetDir() { return dir; }
	Vector2f GetTunsPos() { return tuns.getPosition(); }
	int GetConnected() { return connected; }

	void InitParticle(int num);

private:
	list<Button*> button;
	vector<int>buttonid;

	Tile* whohitwall = nullptr;
	RectangleShape tuns;
	RectangleShape hitbox;
	Vector2f startpos;
	bool IsBlue;
	bool active;
	bool hitwall = false;
	int dir = 0;
	int connected = 0; //0==none 1==follow blue 2==follow orange

	Particles particles;
};

