#include "PlayScene.h"
#include <fstream>
#include "../FrameWork/stdafx.h"
#include "../FrameWork/InputMgr.h"
#include "SceneMgr.h"
#include "../FrameWork/Framework.h"

void PlayScene::Update(float dt)
{

	PlayerMove(dt);
	//GravityEffect(dt);
	worldView.setCenter(player->getPosition());

	if (InputMgr::GetKeyDown(Keyboard::Escape)) {
		SCENE_MGR->ChangeScene(Scenes::GAMESTART);
	}
}

void PlayScene::Draw(RenderWindow& window)
{
	window.setView(worldView);

	if (player != nullptr)
		window.draw(*player);

	for (auto v : wall) {
		window.draw(*v);
	}

	for (auto v : button) {
		window.draw(*v);
	}

	for (auto v : cube) {
		window.draw(*v);
	}
}

void PlayScene::MakeWall(bool vertical)
{
	RectangleShape* temp = new RectangleShape();

	if (!vertical) {
		wall.push_back(temp);
		wall.back()->setPosition(currgird);

		wall.back()->setSize({ GRIDSIZE ,GRIDSIZE});
	}
	else if (vertical) {

	}
	currgird.x += GRIDSIZE;
	wall.back()->setFillColor(Color::Black);

}

void PlayScene::MakeCube()
{
	RectangleShape* temp = new RectangleShape();

	cube.push_back(temp);
	cube.back()->setPosition(currgird);

	cube.back()->setSize({ GRIDSIZE / 4,GRIDSIZE / 4 });
	currgird.x += GRIDSIZE;
	cube.back()->setFillColor(Color::Green);

}

void PlayScene::MakePlayer()
{
	player = new RectangleShape();


	player->setPosition(currgird);

	player->setSize({ 20,50 });
	currgird.x += GRIDSIZE;
	player->setFillColor(Color::Blue);
}

void PlayScene::MakeButton()
{
}

void PlayScene::PlayerMove(float dt)
{
	if (InputMgr::GetKey(Keyboard::A)) {
		player->setPosition(player->getPosition().x - 100 * dt
			, player->getPosition().y);
	}
	else if (InputMgr::GetKey(Keyboard::D)) {
		player->setPosition(player->getPosition().x + 100 * dt
			, player->getPosition().y);
	}
	if (InputMgr::GetKeyDown(Keyboard::Space) && groundede) {
		jump = -100;
		groundede = false;
		player->setPosition(player->getPosition().x, player->getPosition().y - 10);

	}

}

void PlayScene::GravityEffect(float dt)
{
	for (auto v : wall) {
		if (v->getGlobalBounds().intersects(player->getGlobalBounds())) {
			groundede = true;
		}
		for (auto w : cube) {
			if (!v->getGlobalBounds().intersects(w->getGlobalBounds())) {
				w->setPosition(w->getPosition().x, w->getPosition().y + dt * 10);
			}
		}
	}
	if (groundede)
		player->setPosition(player->getPosition().x, player->getPosition().y);
	else
		player->setPosition(player->getPosition().x, player->getPosition().y + dt * jump);
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
			switch (str[i]) {
			case '1':
				MakeWall(false);
				break;
			case '2':
				MakeWall(true);
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
				MakeButton();
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
