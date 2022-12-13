#pragma once
#include "SpriteObj.h"
#include "../Shader/Wave.h"

enum class AngleState
{
	None = -1,
	Noraml,
	Blue,
	Orange,
};


class AngledTile : public SpriteObj
{
public:
	AngledTile();
	AngledTile(b2World* world, Vector2f position, int angle);
	virtual ~AngledTile();	

	virtual SpriteObj* NewThis();

	virtual void Update(float dt);
	virtual void Draw(RenderWindow& window);

	FloatRect GetHitboxGlobalbounds() { return hitbox.getGlobalBounds(); }

	int Getdir() { return dir + 4; }

	Vector2f Gethitboxpos() { return hitboxpos; }

	void DrawFaces(RenderWindow& window);
	void DrawBackFace(RenderWindow& window);
	void SetTransparent(int t);
	void ChangeTex();
	void SetAngleState(AngleState st) { state = st; }

	static bool GetIsBLueOn() { return isBlueOn; }
	static void SetIsBlueOn(bool b) { isBlueOn = b; }
	static bool GetIsOrangeOn() { return isOrangeOn; }
	static void SetIsOrangeOn(bool o) { isOrangeOn = o; }
protected:
	ConvexShape triangle;
	int dir;
	RectangleShape hitbox;
	Vector2f hitboxpos;

	VertexArray topSide;
	Texture* upTex;
	Texture* blue;
	Texture* orange;
	Sprite front;
	RectangleShape back;

	AngleState state;
	AngleState prevState;

	RenderStates render;
	Wave wave;

	static bool isBlueOn;
	static bool isOrangeOn;

	RectangleShape light;
	RenderStates lightRender;
	Texture* blueLight;
	Texture* orangeLight;
};

