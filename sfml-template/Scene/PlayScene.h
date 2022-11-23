#pragma once
#include "Scene.h"
#include "SFML/Graphics.hpp"
#include <vector>
#include "../FrameWork/Const.h"
#include "../FrameWork/ObjectHeaders.h"
#include "../Objects/Goal.h"
#include <box2d/box2d.h>
#include "../Particle/ParticleSystem.h"

//////////////////////////
#include <Candle/Candle.hpp>
using namespace candle;
/////////////////////////

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

	void MakeWall(bool isEnd);
	void MakeCube();
	void MakePlayer();
	void MakeButton(string dir, string id);
	void MakePortal();
	void MakeGoal(string list);
	void PushButton();
	Vector2f CameraMove(Vector2f currpos, Vector2f playerpos, float dt);

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
	float wallbunchwidth = 50;
	Vector2f box2dposition={ GRIDSIZE / 2,GRIDSIZE / 2 };

	View backgroundView;
	View endingView;
	Sprite background;

	Blue* blue;
	Orange* orange;
	bool madeblue = false;
	bool madeorange = false;

	bool grabitem = false;

	RectangleShape ending;


	////////////////////////////////////////////////////
	unique_ptr<b2World> world;

	float dtstack = 0.f;
	int dark = 0;
	int zoomCount;
	bool isMovingViewCenter;

	vector<SpriteObj*> tempContainer;
	vector<vector<SpriteObj*>> objInfos;

	ParticleSystem particle;

};

