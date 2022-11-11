#include "PlayScene.h"
#include <fstream>
#include "../FrameWork/stdafx.h"
#include "../FrameWork/InputMgr.h"
#include "SceneMgr.h"
#include "../FrameWork/Framework.h"

void PlayScene::Update(float dt)
{

	PlayerMove(dt);
	GravityEffect(dt);
	worldView.setCenter(player->GetPos());

	if (InputMgr::GetKeyDown(Keyboard::Escape)) {
		SCENE_MGR->ChangeScene(Scenes::GAMESTART);
	}
}

void PlayScene::Draw(RenderWindow& window)
{
	window.setView(worldView);

	if (player != nullptr)
		player->Draw(window);

	for (auto v : wall) {
		v->Draw(window);
	}

	for (auto v : button) {
		v->Draw(window);
	}

	for (auto v : cube) {
		v->Draw(window);
	}
}

void PlayScene::MakeWall()
{
	Tile* temp = new Tile();


	wall.push_back(temp);
	wall.back()->SetPos(currgird);

	wall.back()->SetSize({ GRIDSIZE ,GRIDSIZE });


	currgird.x += GRIDSIZE;

}

void PlayScene::MakeCube()
{
	Cube* temp = new Cube();

	cube.push_back(temp);
	cube.back()->SetPos(currgird);

	cube.back()->SetSize({ GRIDSIZE ,GRIDSIZE });
	currgird.x += GRIDSIZE;

}

void PlayScene::MakePlayer()
{
	player = new Player();


	player->SetPos(currgird);

	player->SetSize({ 20,50 });
	player->SetOrigin(Origins::MC);
	currgird.x += GRIDSIZE;
}

void PlayScene::MakeButton(int dir)
{
	//Button* temp = new Button();

	//button.push_back(temp);

	////top of gird
	//if (dir == 0) {
	//	button.back()->SetRotation(dir);
	//	button.back()->SetPos();

	//}
	//button.back()->SetSize({ GRIDSIZE ,GRIDSIZE });
	//currgird.x += GRIDSIZE;
}

void PlayScene::PlayerMove(float dt)
{
	if (InputMgr::GetKey(Keyboard::A)) {
		player->SetPos({ player->GetPos().x - 100 * dt
			, player->GetPos().y });
	}
	else if (InputMgr::GetKey(Keyboard::D)) {
		player->SetPos({ player->GetPos().x + 100 * dt
			, player->GetPos().y });
	}
	if (InputMgr::GetKeyDown(Keyboard::Space) && groundede) {
		jump = -100;
		groundede = false;
		player->SetPos({ player->GetPos().x, player->GetPos().y - 10 });

	}

}

void PlayScene::GravityEffect(float dt)
{
	for (auto v : wall) {
		if (v->GetGlobalBounds().intersects(player->GetGlobalBounds())) {
			groundede = true;
		}
		for (auto w : cube) {
			if (!v->GetGlobalBounds().intersects(w->GetGlobalBounds())) {
				w->SetPos({ w->GetPos().x, w->GetPos().y + dt * 10 });
			}
		}
	}
	if (groundede)
		player->SetPos({ player->GetPos().x, player->GetPos().y });
	else
		player->SetPos({ player->GetPos().x, player->GetPos().y + dt * jump });
	jump += 1000 * dt;
	if (jump >= 100) {
		jump = 100;
	}

}

PlayScene::PlayScene(string path)
{
	ifstream fin;
	fin.open(path);

	string str;
	//each line
	while (getline(fin, str)) {
		//verifying each character
		for (int i = 0; i < str.size() + 1; i++) {

			int type;
			if (str[i] == 'b' || str[i] == 'B') {
				type = (int)str[i + 1] - 48;
			}

			switch (str[i]) {
			case '1':
				MakeWall();
				break;
			case 'p':
			case 'P':
				MakePlayer();
				break;
			case 'C':
			case 'c':
				MakeCube();
				break;

			case 'b':
			case 'B':
				MakeButton(type);
				i++;
				break;
			default:
				currgird.x += GRIDSIZE;
			}
		}
		currgird = { 0,currgird.y + GRIDSIZE };

	}

	fin.close();
}

PlayScene::~PlayScene()
{
	Release();
}

void PlayScene::Init()
{
}

void PlayScene::Release()
{
	FRAMEWORK->GetWindow().setView(FRAMEWORK->GetWindow().getDefaultView());
	delete player;

	for (auto v : wall) {
		delete v;
	}
	wall.clear();

	for (auto v : button) {
		delete v;
	}
	button.clear();

	for (auto v : cube) {
		delete v;
	}
	cube.clear();
}

void PlayScene::Enter()
{
	auto size = (Vector2f)FRAMEWORK->GetWindowSize();
	worldView.setSize(size);
	worldView.setCenter(size / 2.f);
	FRAMEWORK->GetWindow().setView(worldView);
}

void PlayScene::Exit()
{

}
