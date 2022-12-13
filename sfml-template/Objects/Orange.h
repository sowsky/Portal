#pragma once
#include "SpriteObj.h"
#include <Candle/Candle.hpp>
#include "../Shader/Wave.h"

using namespace candle;

class Orange:public SpriteObj
{
public:
	Orange();
	virtual ~Orange();
	
	virtual void Update(float dt);
	virtual void Draw(RenderWindow& window);
	void SetPortalDir(int side) { dir = side; }
	int GetPortalDir() { return dir; }
	void SetLightDir(int side, bool texdir);

	void DrawPortalArray(RenderWindow& window);
	virtual void SetSize(Vector2f size);
protected:
	RectangleShape* hitbox;
	float projectilespeed = 2000.f;
	int dir;

	VertexArray portalArray;
	Texture* orangeTex;
	RectangleShape backFace;
	RectangleShape frontFace;
	RectangleShape light;
	bool texStand;
		
	RenderStates PortalState;
	Wave shader;

	const float widthVal = - 45.f;
	float heightVal = - 15.f;
};

