#pragma once
#include "WireableObject.h"
#include "Button.h"

class MovingPlatform :  public WireableObject
{
public:
	MovingPlatform();
	MovingPlatform(b2World* world, Vector2f& position,bool on,float rot,float destY,vector<float> buttonlist);
	virtual ~MovingPlatform() {};

	virtual SpriteObj* NewThis();

	virtual void Update(float dt);
	virtual void Draw(RenderWindow& window);
	virtual void Draw
	(RenderTexture& diffuse, Shader& nShader, RenderTexture& normal);
	virtual void DrawPillar
	(RenderTexture& diffuse, Shader& nShader, RenderTexture& normal);

	void DrawUi(RenderWindow& window);

	int GetRange() { return range; }
	void SetRange(int r) { range = r; }

	void InitTexBox();	
	void DrawTexBox(RenderWindow& window);	
	bool GetPlatformOn() { return isTurnedOn; }
	void SetPlatformOn(bool a) { isTurnedOn = a; }
	void SetButtonlist(vector<Button*>& button);

	bool Getenable() { return enable; }
	
	FloatRect GetplatformGlobalBounds() { return platform.getGlobalBounds(); }
	FloatRect GetpillarGlobalBounds() { return pillar.getGlobalBounds(); }
protected:
	int range = 1;
	bool isTurnedOn;
	bool originactive;

	CircleShape up;
	CircleShape down;
	
	RectangleShape platform;
	RectangleShape pillar;
	RectangleShape test;

	Vector2f destiny;
	Vector2f originpos;

	float y;
	float x;
	bool enable;
	list<Button*> button;
	vector<float>buttonid;

	int dir;

	b2World* world = nullptr;

	b2Body* pillarbody = nullptr;
	b2Fixture* pillarfixture = nullptr;

	b2Body* platformbody = nullptr;
	b2Fixture* platformfixture = nullptr;

	array<Sprite, 20> arrows;


	RectangleShape onOfftexBox;
	Text onOffTex;

	////////////////////////////

	VertexArrayObj sideFaces;
	Sprite frontFace;
	Vector2f frontSize;
	Texture* normal;

	RectangleShape pillar_diffuse;
	Texture* pillar_n;

	const float platFormHeightHalf = 3.9f;
};

