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

	for (auto v : checkcurrgrid) {
		window.draw(*v);
	}
}

void PlayScene::MakeWall()
{
	SmallTile* temp = new SmallTile();

	wall.push_back(temp);
	wall.back()->SetOrigin(Origins::MC);
	wall.back()->SetPos(currgrid);

	wall.back()->SetSize({ GRIDSIZE ,GRIDSIZE });


	currgrid.x += GRIDSIZE;

}

void PlayScene::MakeCube()
{
	Cube* temp = new Cube();


	cube.push_back(temp);
	cube.back()->SetOrigin(Origins::BC);
	cube.back()->SetPos({ currgrid.x,currgrid.y+GRIDSIZE/2 });

	cube.back()->SetSize({ GRIDSIZE/1.5 ,GRIDSIZE/1.5 });
	currgrid.x += GRIDSIZE;

}

void PlayScene::MakePlayer()
{
	player = new Player();

	player->SetSize({ 20,50 });
	player->SetOrigin(Origins::BC);
	player->SetPos({ currgrid.x,currgrid.y+GRIDSIZE/2 });

	currgrid.x += GRIDSIZE;
}

void PlayScene::MakeButton(int dir)
{
	Button* temp = new Button();

	button.push_back(temp);
	button.back()->SetOrigin(Origins::BC);

	button.back()->SetPos(currgrid);
	button.back()->SetRotation(dir);
	//button.back()->FitScale(TILE_SIZE);
	
	if (dir == 0) {			//top of gird
		button.back()->SetPos({ currgrid.x,currgrid.y - GRIDSIZE / 2 });
		button.back()->SetSize({ GRIDSIZE,GRIDSIZE/4 });

	}
	else if (dir == 1) {	//right of gird
		button.back()->SetPos({ currgrid.x + GRIDSIZE / 2,currgrid.y });
		button.back()->SetSize({ GRIDSIZE,GRIDSIZE / 4 });

	}
	else if (dir == 2) {	//bottom of gird
		button.back()->SetPos({ currgrid.x,currgrid.y + GRIDSIZE / 2 });
		button.back()->SetSize({ GRIDSIZE,GRIDSIZE / 4 });

	}
	else if (dir == 3) {	//left of gird
		button.back()->SetPos({ currgrid.x - GRIDSIZE / 2,currgrid.y });
		button.back()->SetSize({ GRIDSIZE ,GRIDSIZE / 4 });

	}
	currgrid.x += GRIDSIZE;
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
			checkcurrgrid.push_back( new RectangleShape());
			Utils::SetOrigin(*checkcurrgrid.back(), Origins::MC);
			checkcurrgrid.back()->setSize({ 10,10 });
			checkcurrgrid.back()->setFillColor(Color::Black);
			checkcurrgrid.back()->setPosition(currgrid);

			///////////get button side///////
			int type;
			if (str[i] == 'b' || str[i] == 'B') {
				type = (int)str[i + 1] - 48;
			}
			/////////////////////////////

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
				currgrid.x += GRIDSIZE;
			}

		}
		currgrid = { GRIDSIZE/2,currgrid.y + GRIDSIZE };

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

	for (auto v : checkcurrgrid) {
		delete v;
	}
	checkcurrgrid.clear();
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
