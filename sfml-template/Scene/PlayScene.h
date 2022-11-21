#pragma once
#include "Scene.h"
#include "SFML/Graphics.hpp"
#include <vector>
#include "../FrameWork/Const.h"
#include "../FrameWork/ObjectHeaders.h"
#include "../Objects/Goal.h"
#include <box2d/box2d.h>

class PlayScene : public Scene
{
public:
	PlayScene() {};
	PlayScene(string path);
	virtual ~PlayScene();

	virtual void Init();	// ����
	virtual void Release();		// ����

	virtual void Enter();
	virtual void Exit();

	virtual void Update(float dt);
	virtual void PhysicsUpdate(float dt);

	virtual void Draw(RenderWindow& window);

	void MakeWall();
	void MakeCube();
	void MakePlayer();
	void MakeButton(string dir, string id);
	void MakePortal();
	void MakeGoal(string list);

	void MoveToPortal();
public:
	void DrawBackGroundView(RenderWindow& window);
	void Input();
private:

	//do all RectalgeShape change to Object class

	Player* player;
	Goal* goal;
	vector<Tile*> wall;
	vector<Button*> button;
	vector<Cube*> cube;

	Cube* grabbedcube = nullptr;
	Vector2f currgrid = { GRIDSIZE / 2,GRIDSIZE / 2 };

	View backgroundView;
	Sprite background;

	Blue* blue;
	Orange* orange;
	bool madeblue = false;
	bool madeorange = false;

	bool grabitem = false;

	////////////////////////////////////////////////////
	unique_ptr<b2World> world;

	float dtstack = 0.f;

	int zoomCount;
	bool isMovingViewCenter;

	vector<SpriteObj*> tempContainer;
	vector<vector<SpriteObj*>> objInfos;
};

