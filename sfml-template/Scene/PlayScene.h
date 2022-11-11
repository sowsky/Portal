#pragma once
#include "Scene.h"
#include "SFML/Graphics.hpp"
#include <vector>
#include "../FrameWork/Const.h"
#include "../FrameWork/ObjectHeaders.h"

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

	void PlayerMove(float dt);
	void GravityEffect(float dt);
private:

	//do all RectalgeShape change to Object class

	Player* player;
	vector<Tile*> wall;
	vector<Button*> button;
	vector<Cube*> cube;
		
	bool groundede = false;
	int jump = 100;
	Vector2f currgird = { 0,0 };
};

