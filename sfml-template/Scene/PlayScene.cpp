#include "PlayScene.h"
#include <fstream>
#include "../FrameWork/stdafx.h"
#include "../FrameWork/InputMgr.h"
#include "SceneMgr.h"
#include "../FrameWork/Framework.h"
#include "../Manager/ResourceMgr.h"


void PlayScene::Update(float dt)
{
	world->Step(1 / 60.f, 8, 3);
	//////////////////////////////////////////////////////
	player->Move(dt);
	player->Update(dt);
	//cube->Update(dt);
	blue->Update(dt);
	orange->Update(dt);
//	player->SetGround(true);

	//GravityEffect(dt);
	worldView.setCenter(player->GetPos());

	//blue
	if (InputMgr::GetMouseButtonDown(Mouse::Left)) {
		blue->SetSize({ 10,10 });
		madeblue = false;
		blue->SetPos({ player->GetPos().x,player->GetPos().y - 20 });
		blue->SetDir(Utils::Normalize(ScreenToWorldPos((Vector2i)InputMgr::GetMousePos()) - player->GetPos()));

	}
	//orange

	if (InputMgr::GetMouseButtonDown(Mouse::Right)) {
		orange->SetSize({ 10,10 });
		madeorange = false;
		orange->SetPos({ player->GetPos().x,player->GetPos().y - 20 });
		orange->SetDir(Utils::Normalize(ScreenToWorldPos((Vector2i)InputMgr::GetMousePos()) - player->GetPos()));
	}

	MakePortal();
	MoveToPortal();

	/*if (InputMgr::GetKeyDown(Keyboard::E)) {
		if (!grabitem && player->GethitboxGlobalBounds().intersects(cube->GetGlobalBounds())) {
			grabitem = true;

			if (player->GetPos().x <= cube->GetPos().x)
			{
				cube->SetSide(true);
			}
			else if (player->GetPos().x > cube->GetPos().x) {
				cube->SetSide(false);
			}
			cube->SetGround(false);
		}
		else if (grabitem) {
			grabitem = false;
		}
	}

	if (grabitem) {
		if (cube->GetSide())
			cube->SetPos({ player->GetPos().x + 40,player->GetPos().y - 20 });
		else
			cube->SetPos({ player->GetPos().x - 40,player->GetPos().y - 20 });

	}*/


	if (InputMgr::GetKeyDown(Keyboard::Escape)) {
		SCENE_MGR->ChangeScene(Scenes::GAMESTART);
	}
}

void PlayScene::Draw(RenderWindow& window)
{
	DrawBackGroundView(window);

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

	//cube->Draw(window);

	if (madeorange) {
	orange->Draw(window);
	}

	if (madeblue) {
	blue->Draw(window);
	}

}

void PlayScene::MakeWall()
{
	Tile* temp = new Tile();

	wall.push_back(temp);
	wall.back()->SetOrigin(Origins::MC);
	wall.back()->SetPos(currgrid);

	wall.back()->SetSize({ GRIDSIZE ,GRIDSIZE });


	currgrid.x += GRIDSIZE;

}

void PlayScene::MakeCube()
{
	//Cube* temp = new Cube();

	/*cube.push_back(temp);
	cube.back()->SetOrigin(Origins::BC);
	cube.back()->SetPos({ currgrid.x,currgrid.y + GRIDSIZE / 2 });

	cube.back()->SetSize({ GRIDSIZE / 1.5 ,GRIDSIZE / 1.5 });*/

	/*cube = new Cube();
	cube->SetOrigin(Origins::BC);
	cube->SetPos({ currgrid.x,currgrid.y + GRIDSIZE / 2 });

	cube->SetSize({ GRIDSIZE / 1.5 ,GRIDSIZE / 1.5 });
	currgrid.x += GRIDSIZE;*/
	//////////////////////////////////////////////////////////////////////////////////
	Cube* newCube=new Cube(world.get(), Vector2f{ 0.0f,14.0f }, Vector2f({15.0f, 15.0f}));

	cube.push_back(newCube);
}

void PlayScene::MakePlayer()
{
	player = new Player();

	player->SetSize({ 20,50 });
	player->SetOrigin(Origins::BC);
	player->SetPos({ currgrid.x,currgrid.y + GRIDSIZE / 2 });
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
		button.back()->SetSize({ GRIDSIZE,GRIDSIZE / 4 });

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

void PlayScene::MakePortal()
{
	//wall=mc blue=mc

	for (auto w : wall) {
		//blue
		//if hit side
		if (!madeblue && w->GetGlobalBounds().intersects(blue->GetGlobalBounds())) {
			blue->SetPos({ blue->GetPos().x,blue->GetPos().y });
			if (blue->GetPos().x > w->GetPos().x + (Utils::GetSpriteSize(*w->GetSprite()).x / 2) ||
				blue->GetPos().x < w->GetPos().x - (Utils::GetSpriteSize(*w->GetSprite()).x / 2)) {
				blue->SetSize({ 50,20 });
				blue->SetRotation(90.f);
				if (blue->GetPos().x > w->GetPos().x + (Utils::GetSpriteSize(*w->GetSprite()).x / 2)) {
					blue->SetPortalDir(1);
				}
				else
					blue->SetPortalDir(3);
			}
			else {
				blue->SetSize({ 50,20 });
				blue->SetRotation(180.f);

				if (blue->GetPos().y > w->GetPos().y - (Utils::GetSpriteSize(*w->GetSprite()).y / 2)) {
					blue->SetPortalDir(0);
				}
				else
					blue->SetPortalDir(2);
			}
			blue->SetDir({ 0,0 });
			madeblue = true;
		}

		//orange
		if (!madeorange && w->GetGlobalBounds().intersects(orange->GetGlobalBounds())) {
			orange->SetPos({ orange->GetPos().x,orange->GetPos().y });

			//side
			if (orange->GetPos().x > w->GetPos().x + (Utils::GetSpriteSize(*w->GetSprite()).x / 2) ||
				orange->GetPos().x < w->GetPos().x - (Utils::GetSpriteSize(*w->GetSprite()).x / 2)) {
				orange->SetSize({ 50,20 });
				orange->SetRotation(90.f);
				if (orange->GetPos().x > w->GetPos().x + (Utils::GetSpriteSize(*w->GetSprite()).x / 2)) {
					orange->SetPortalDir(1);
				}
				else
					orange->SetPortalDir(3);
			}
			else {//top bottom
				orange->SetSize({ 50,20 });
				orange->SetRotation(180.f);

				if (orange->GetPos().y > w->GetPos().y - (Utils::GetSpriteSize(*w->GetSprite()).y / 2)) {
					orange->SetPortalDir(0);
				}
				else
					orange->SetPortalDir(2);
			}
			orange->SetDir({ 0,0 });
			madeorange = true;
		}
	}

}


void PlayScene::DrawBackGroundView(RenderWindow& window)
{	
	window.setView(backgroundView);
	window.draw(background);
}


void PlayScene::MoveToPortal()
{

	if(madeblue&&blue->GetGlobalBounds().intersects(player->GetGlobalBounds())) {
		if (orange->GetPortalDir() == 0) {
			player->SetPos({ orange->GetPos().x,orange->GetPos().y-Utils::GetSpriteSize(*orange->GetSprite()).y/2});
		}
		else if (orange->GetPortalDir() == 1) {
			player->SetPos({ orange->GetPos().x+20,orange->GetPos().y});

		}
		else if (orange->GetPortalDir() == 2) {
			player->SetPos({ orange->GetPos().x ,orange->GetPos().y+20 });

		}
		else if (orange->GetPortalDir() == 3) {
			player->SetPos({ orange->GetPos().x-20 ,orange->GetPos().y });

		}
		
	}

	if (madeorange && orange->GetGlobalBounds().intersects(player->GetGlobalBounds())) {
		if (blue->GetPortalDir() == 0) {
			player->SetPos({ blue->GetPos().x,blue->GetPos().y - 50 });
		}
		else if (blue->GetPortalDir() == 1) {
			player->SetPos({ blue->GetPos().x + 20,blue->GetPos().y });

		}
		else if (blue->GetPortalDir() == 2) {
			player->SetPos({ blue->GetPos().x ,blue->GetPos().y + 50 });

		}
		else if (blue->GetPortalDir() == 3) {
			player->SetPos({ blue->GetPos().x - 20 ,blue->GetPos().y });

		}
	}
}



void PlayScene::GravityEffect(float dt)
{

	for (auto w : wall) {
		if (w->GetGlobalBounds().intersects(player->GethitboxGlobalBounds())) {
			player->SetGround(true);
			player->SetPos({ player->GetPos().x,w->GetGlobalBounds().top - 0.1f });
		}

		/*if (w->GetGlobalBounds().intersects(cube->GethitboxGlobalBounds())) {
			cube->SetGround(true);
			cube->SetPos({ cube->GetPos().x,w->GetGlobalBounds().top - 0.1f });
		}*/

	}
}


PlayScene::PlayScene(string path)
{

	b2Vec2 g(0.0f, -10);
	world = make_unique<b2World>(g);
	
	b2BodyDef groundBodyDef;
	groundBodyDef.position.Set(0.0f, -10.0f);
	b2Body* groundBody = world->CreateBody(&groundBodyDef);
	b2PolygonShape groundBox;
	groundBox.SetAsBox(50.0f,10.0f);
	groundBody->CreateFixture(&groundBox, 0.0f);

	/////////////////////////////////////////////////////////////////////////////
	blue = new Blue;
	orange = new Orange;


	blue->SetSize({ 10,10 });
	orange->SetSize({ 10,10 });

	ifstream fin;
	fin.open(path);

	string str;
	//each line
	while (getline(fin, str)) {
		//verifying each character
		for (int i = 0; i < str.size() + 1; i++) {


			///////////get button side///////
			int side;
			if (str[i] == 'b' || str[i] == 'B') {
				side = (int)str[i + 1] - 48;
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
				MakeButton(side);
				i++;
				break;
			default:
				currgrid.x += GRIDSIZE;
			}

		}
		currgrid = { GRIDSIZE / 2,currgrid.y + GRIDSIZE };

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

	delete orange;
	delete blue;
	//delete cube;
	

}

void PlayScene::Enter()
{	
	background.setTexture(*RESOURCEMGR->GetTexture("Graphics/backgrounds/ruin2.png"));
	Utils::SetSpriteSize(background, {WINDOW_WIDTH,WINDOW_HEIGHT});	
	auto size = (Vector2f)FRAMEWORK->GetWindowSize();
	worldView.setSize(size);
	worldView.setCenter(size / 2.f);
	FRAMEWORK->GetWindow().setView(worldView);

	backgroundView.setSize(size);
	backgroundView.setCenter(size / 2.f);
}

void PlayScene::Exit()
{

}
