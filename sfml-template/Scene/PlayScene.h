#pragma once
#include "Scene.h"
#include "SFML/Graphics.hpp"
#include <vector>
#include "../FrameWork/Const.h"
#include "../FrameWork/ObjectHeaders.h"
#include "box2d/box2d.h"

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
	virtual void Draw(RenderWindow& window);

	void MakeWall();
	void MakeCube();
	void MakePlayer();
	void MakeButton(int dir);
	void MakePortal();

	void MoveToPortal();

	void GravityEffect(float dt);
public:
	void DrawBackGroundView(RenderWindow& window);
private:

	//do all RectalgeShape change to Object class

	Player* player;
	vector<Tile*> wall;
	vector<Button*> button;
	//vector<Cube*> cube;
	vector<Cube*> cube;
	Vector2f currgrid = { GRIDSIZE/2,GRIDSIZE/2 };

	View backgroundView;
	Sprite background;

	Blue* blue;
	Orange* orange;
	bool madeblue=false;
	bool madeorange=false;

	bool grabitem = false;

	////////////////////////////////////////////////////
	unique_ptr<b2World> world;

};

