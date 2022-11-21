#include "PlayScene.h"
#include <fstream>
#include "../FrameWork/stdafx.h"
#include "../FrameWork/InputMgr.h"
#include "SceneMgr.h"
#include "../FrameWork/Framework.h"
#include "../Manager/ResourceMgr.h"
#include "../Objects/Goal.h"

void PlayScene::Update(float dt)
{

	//////////////////////////////////////////////////////

	if (goal->GetGlobalBounds().intersects(player->GetGlobalBounds())) {
		if (goal->IsFinish()) {
			SCENE_MGR->ChangeScene(Scenes::GAMESTART);
			return;
		}
	}
	player->Update(dt);
	goal->Update(dt);

	for (auto c : cube) {
		c->Update(dt);
	}
	for (auto w : wall)
		w->Update(dt);

	blue->Update(dt);
	orange->Update(dt);

	if(!isMovingViewCenter)
		worldView.setCenter(player->GetPositions());

	//blue
	if (InputMgr::GetMouseButtonDown(Mouse::Left)) {
		blue->SetSize({ 20,20 });
		madeblue = false;
		blue->SetPos({ player->GetPositions().x,player->GetPositions().y - 25 });
		blue->SetDir(Utils::Normalize(ScreenToWorldPos((Vector2i)InputMgr::GetMousePos()) - player->GetPositions()));
	}

	//orange
	if (InputMgr::GetMouseButtonDown(Mouse::Right)) {
		orange->SetSize({ 20,20 });
		madeorange = false;
		orange->SetPos({ player->GetPositions().x,player->GetPositions().y - 25 });
		orange->SetDir(Utils::Normalize(ScreenToWorldPos((Vector2i)InputMgr::GetMousePos()) - player->GetPositions()));
	}

	MakePortal();
	MoveToPortal();


	if (grabitem) {
		if (grabbedcube->GetSide())
			grabbedcube->SetCubeBodyPos({ player->GetPositions().x + 40,player->GetPositions().y - 40 });
		else
			grabbedcube->SetCubeBodyPos({ player->GetPositions().x - 40,player->GetPositions().y - 40 });

		if (InputMgr::GetKeyDown(Keyboard::A)) {
			grabbedcube->SetSide(false);
		}
		else if (InputMgr::GetKeyDown(Keyboard::D)) {
			grabbedcube->SetSide(true);
		}

		if (InputMgr::GetKeyDown(Keyboard::E)) {
			cout << "drop" << endl;
			grabitem = false;
			grabbedcube->ChangeBodyTypeBetweenStaticAndDynamic(grabitem);
			grabbedcube = nullptr;
		}

	}
	else if (!grabitem) {
		for (auto c : cube) {
			if (c->GethitboxGlobalBounds().intersects(player->GetGlobalBounds()) && InputMgr::GetKeyDown(Keyboard::E)) {
				if (!grabitem) {
					cout << "pickup" << endl;

					grabitem = true;
					grabbedcube = c;
					float cposX = c->GetGlobalBounds().left + (c->GetGlobalBounds().width / 2);
					if (player->GetPositions().x <= cposX)
					{
						c->SetSide(true);
						c->ChangeBodyTypeBetweenStaticAndDynamic(grabitem);
					}
					else if (player->GetPositions().x > cposX) {
						c->SetSide(false);
						c->ChangeBodyTypeBetweenStaticAndDynamic(grabitem);
					}
					c->SetGround(false);
				}

			}
		}
	}

	Input();
}

void PlayScene::PhysicsUpdate(float dt)
{
	dtstack += dt;

	if (dtstack >= 1 / 60.f) {
		world->Step(1 / 60.f, 8, 3);
		for (auto w : wall) {
			w->PhysicsUpdate();
		}

		for (auto c : cube) {
			c->PhysicsUpdate();
		}

		player->PhysicsUpdate();

		dtstack -= 1 / 60.f;
	}

}

void PlayScene::Draw(RenderWindow& window)
{
	DrawBackGroundView(window);

	window.setView(worldView);

	for (auto v : wall) {
		v->Draw(window);
	}

	goal->Draw(window);

	if (player != nullptr)
		player->Draw(window);

	for (auto v : button) {
		v->Draw(window);
	}

	for (auto v : cube) {
		v->Draw(window);
	}

	//if (madeorange) {
	orange->Draw(window);
	//}

	//if (madeblue) {
	blue->Draw(window);
	//}

}

void PlayScene::MakeWall()
{
	Tile* temp = new Tile(world.get(), Vector2f{ currgrid }, Vector2f({ GRIDSIZE, GRIDSIZE }));
	temp->SetOrigin(Origins::MC);
	wall.push_back(temp);

	currgrid.x += GRIDSIZE;
}

void PlayScene::MakeCube()
{
	Cube* newCube = new Cube(world.get(), Vector2f{ currgrid }, Vector2f({ GRIDSIZE, GRIDSIZE }));

	cube.push_back(newCube);
}

void PlayScene::MakePlayer()
{

	player = new Player(world.get(), Vector2f{ currgrid }, Vector2f({ 20, 50 }));

	currgrid.x += GRIDSIZE;
}

void PlayScene::MakeButton(string dir, string id)
{
	for (auto b : dir) {
		if (b == ' ')
			continue;

		//seek id
		string idtemp;
		for (int i = 0; i < id.size(); i++) {
			if (id[i] == ' ') {
				id.erase(i, i);
				break;
			}
			idtemp.push_back(id[i]);
			id.erase(i, i);
		}

		Button* temp = new Button();

		/*	button.push_back(temp);
			button.back()->SetOrigin(Origins::BC);
			button.back()->SetButtonId(stoi(idtemp));
			button.back()->SetPos(currgrid);
			char temp = b;
			button.back()->SetRotation(b);*/

		if (b == '0') {			//top of gird
			button.back()->SetPos({ currgrid.x,currgrid.y - GRIDSIZE / 2 });
			button.back()->SetSize({ GRIDSIZE,GRIDSIZE / 4 });

		}
		else if (b == '1') {	//right of gird
			button.back()->SetPos({ currgrid.x + GRIDSIZE / 2,currgrid.y });
			button.back()->SetSize({ GRIDSIZE,GRIDSIZE / 4 });

		}
		else if (b == '2') {	//bottom of gird
			button.back()->SetPos({ currgrid.x,currgrid.y + GRIDSIZE / 2 });
			button.back()->SetSize({ GRIDSIZE,GRIDSIZE / 4 });

		}
		else if (b == '3') {	//left of gird
			button.back()->SetPos({ currgrid.x - GRIDSIZE / 2,currgrid.y });
			button.back()->SetSize({ GRIDSIZE ,GRIDSIZE / 4 });

		}
	}
	currgrid.x += GRIDSIZE;
}

void PlayScene::MakePortal()
{
	int bluecollidercount = 0;
	//wall=mc blue=mc

	float sety;
	float setx;

	bool intersect = false;
	RectangleShape blueTL;
	RectangleShape blueTR;
	RectangleShape blueBL;
	RectangleShape blueBR;

	Vector2f bluetlpos, bluetrpos, blueblpos, bluebrpos;
	bool bluetlhit = false;
	bool bluetrhit = false;
	bool blueblhit = false;
	bool bluebrhit = false;

	for (auto w : wall) {
		if (!madeblue && w->GetGlobalBounds().intersects(blue->GetGlobalBounds())) {
			blue->SetSize({ 50,50 });
			blue->SetDir({ 0,0 });


			bluetlpos = { blue->GetGlobalBounds().left,blue->GetGlobalBounds().top };
			blueTL.setSize({ 0.1f,0.1f });

			bluetrpos = { blue->GetGlobalBounds().left + blue->GetGlobalBounds().width,blue->GetGlobalBounds().top };
			blueTR.setSize({ 0.1f,0.1f });

			blueblpos = { blue->GetGlobalBounds().left ,blue->GetGlobalBounds().top + blue->GetGlobalBounds().height };
			blueBL.setSize({ 0.1f,0.1f });

			bluebrpos = { blue->GetGlobalBounds().left + blue->GetGlobalBounds().width,blue->GetGlobalBounds().top + blue->GetGlobalBounds().height };
			blueBR.setSize({ 0.1f,0.1f });

			blueBR.setPosition(bluebrpos);
			blueBL.setPosition(blueblpos);
			blueTR.setPosition(bluetrpos);
			blueTL.setPosition(bluetlpos);

			intersect = true;
			break;
		}
	}

	if (intersect)
	{
		for (auto w : wall) {
			if (!madeblue && w->GetGlobalBounds().contains(blueBL.getPosition())) {
				setx = w->GetGlobalBounds().left + w->GetGlobalBounds().width;
				sety = w->GetGlobalBounds().top;

				bluecollidercount++;
				blueblhit = true;

			}

			if (!madeblue && w->GetGlobalBounds().contains(blueBR.getPosition())) {

				setx = w->GetGlobalBounds().left;
				sety = w->GetGlobalBounds().top;
				bluecollidercount++;
				bluebrhit = true;

			}
			if (!madeblue && w->GetGlobalBounds().contains(blueTL.getPosition())) {

				setx = w->GetGlobalBounds().left + w->GetGlobalBounds().width;
				sety = w->GetGlobalBounds().top + w->GetGlobalBounds().height;
				bluecollidercount++;
				bluetlhit = true;

			}
			if (!madeblue && w->GetGlobalBounds().contains(blueTR.getPosition())) {

				setx = w->GetGlobalBounds().left;
				sety = w->GetGlobalBounds().top + w->GetGlobalBounds().height;
				bluecollidercount++;
				bluetrhit = true;

			}
		}

	}

	if (bluecollidercount == 2) {

		//bottom
		if (bluetlhit && bluetrhit) {
			blue->SetSize({ 50,20 });
			blue->SetPos({ blue->GetPos().x,sety });
			blue->SetPortalDir(2);
			cout << "low" << endl;
		}
		//left
		else if (bluetrhit && bluebrhit) {
			blue->SetSize({ 20,50 });
			blue->SetPos({ setx,blue->GetPos().y });
			blue->SetPortalDir(3);
			cout << "left" << endl;
		}
		//top
		else if (blueblhit && bluebrhit) {
			blue->SetSize({ 50,20 });
			blue->SetPos({ blue->GetPos().x,sety });
			blue->SetPortalDir(0);
			cout << "top" << endl;

		}
		//right
		else if (bluetlhit && blueblhit) {
			blue->SetSize({ 20,50 });
			blue->SetPos({ blue->GetPos().x,sety });
			blue->SetPortalDir(1);
			cout << "right" << endl;
		}
		madeblue = true;
		blue->SetDir({ 0,0 });
	}
	else if (bluecollidercount != 0) {
		blue->SetPos({ -1000,-1000 });
	}


	int orangecollidercount = 0;
	//wall=mc orange=mc

	float orangesety;
	float orangesetx;
	bool orangeintersect = false;
	RectangleShape orangeTL;
	RectangleShape orangeTR;
	RectangleShape orangeBL;
	RectangleShape orangeBR;

	Vector2f orangetlpos, orangetrpos, orangeblpos, orangebrpos;
	bool orangetlhit = false;
	bool orangetrhit = false;
	bool orangeblhit = false;
	bool orangebrhit = false;

	for (auto w : wall) {
		if (!madeorange && w->GetGlobalBounds().intersects(orange->GetGlobalBounds())) {
			orange->SetSize({ 50,50 });
			orange->SetDir({ 0,0 });


			orangetlpos = { orange->GetGlobalBounds().left,orange->GetGlobalBounds().top };
			orangeTL.setSize({ 0.1f,0.1f });

			orangetrpos = { orange->GetGlobalBounds().left + orange->GetGlobalBounds().width,orange->GetGlobalBounds().top };
			orangeTR.setSize({ 0.1f,0.1f });

			orangeblpos = { orange->GetGlobalBounds().left ,orange->GetGlobalBounds().top + orange->GetGlobalBounds().height };
			orangeBL.setSize({ 0.1f,0.1f });

			orangebrpos = { orange->GetGlobalBounds().left + orange->GetGlobalBounds().width,orange->GetGlobalBounds().top + orange->GetGlobalBounds().height };
			orangeBR.setSize({ 0.1f,0.1f });

			orangeBR.setPosition(orangebrpos);
			orangeBL.setPosition(orangeblpos);
			orangeTR.setPosition(orangetrpos);
			orangeTL.setPosition(orangetlpos);

			orangeintersect = true;
			break;
		}
	}

	if (orangeintersect)
	{
		for (auto w : wall) {
			if (!madeorange && w->GetGlobalBounds().contains(orangeBL.getPosition())) {
				orangesetx = w->GetGlobalBounds().left + w->GetGlobalBounds().width;
				orangesety = w->GetGlobalBounds().top;

				orangecollidercount++;
				orangeblhit = true;

			}

			if (!madeorange && w->GetGlobalBounds().contains(orangeBR.getPosition())) {

				orangesetx = w->GetGlobalBounds().left;
				orangesety = w->GetGlobalBounds().top;
				orangecollidercount++;
				orangebrhit = true;

			}
			if (!madeorange && w->GetGlobalBounds().contains(orangeTL.getPosition())) {

				orangesetx = w->GetGlobalBounds().left + w->GetGlobalBounds().width;
				orangesety = w->GetGlobalBounds().top + w->GetGlobalBounds().height;
				orangecollidercount++;
				orangetlhit = true;

			}
			if (!madeorange && w->GetGlobalBounds().contains(orangeTR.getPosition())) {

				orangesetx = w->GetGlobalBounds().left;
				orangesety = w->GetGlobalBounds().top + w->GetGlobalBounds().height;
				orangecollidercount++;
				orangetrhit = true;

			}
		}

	}

	if (orangecollidercount == 2) {

		//bottom
		if (orangetlhit && orangetrhit) {
			orange->SetSize({ 50,20 });
			orange->SetPos({ orange->GetPos().x,orangesety });
			orange->SetPortalDir(2);
			cout << "low" << endl;
		}
		//left
		else if (orangetrhit && orangebrhit) {
			orange->SetSize({ 20,50 });
			orange->SetPos({ orangesetx,orange->GetPos().y });
			orange->SetPortalDir(3);
			cout << "left" << endl;
		}
		//top
		else if (orangeblhit && orangebrhit) {
			orange->SetSize({ 50,20 });
			orange->SetPos({ orange->GetPos().x,orangesety });
			orange->SetPortalDir(0);
			cout << "top" << endl;

		}
		//right
		else if (orangetlhit && orangeblhit) {
			orange->SetSize({ 20,50 });
			orange->SetPos({ orange->GetPos().x,orangesety });
			orange->SetPortalDir(1);
			cout << "right" << endl;
		}
		madeorange = true;
		orange->SetDir({ 0,0 });
	}
	else if (orangecollidercount != 0) {
		orange->SetPos({ -1000,-1000 });
	}

}

void PlayScene::MakeGoal(string list)
{
	goal = new Goal(currgrid, GRIDSIZE, list);

	currgrid.x += GRIDSIZE;

}


void PlayScene::DrawBackGroundView(RenderWindow& window)
{
	window.setView(backgroundView);
	window.draw(background);
}

void PlayScene::Input()
{
	if (InputMgr::GetKeyDown(Keyboard::Escape)) {
		SCENE_MGR->ChangeScene(Scenes::GAMESTART);
	}

	if (InputMgr::GetMouseWheelState() == 1)
	{
		if (zoomCount > 20)
			return;
		zoomCount++;
		worldView.zoom(0.94f);
	}
	if (InputMgr::GetMouseWheelState() == -1)
	{
		if (zoomCount < -3)
			return;
		zoomCount--;
		worldView.zoom(1.06f);
	}

	if (InputMgr::GetMouseButton(Mouse::Middle))
	{
		isMovingViewCenter = true;
		Vector2f pos = InputMgr::GetMousePosDisplacement();
		worldView.setCenter(worldView.getCenter() + pos);
	}

	if (InputMgr::GetMouseButtonUp(Mouse::Middle))
	{
		isMovingViewCenter = false;
	}
}


void PlayScene::MoveToPortal()
{

	if (madeblue && blue->GetGlobalBounds().intersects(player->GetGlobalBounds())) {
		if (orange->GetPortalDir() == 0) {
			player->SetPlayerBodyPos({ orange->GetPos().x,orange->GetPos().y - player->GetGlobalBounds().height });
			player->SetPlayerBodyForce({ player->GetPlayerBodyForce().x,10000000 });

		}
		else if (orange->GetPortalDir() == 1) {
			player->SetPlayerBodyPos({ orange->GetPos().x + 30,orange->GetPos().y });
			player->SetPlayerBodyForce({ 10000 * 333,0 });
		}
		else if (orange->GetPortalDir() == 2) {
			player->SetPlayerBodyPos({ orange->GetPos().x ,orange->GetPos().y + player->GetGlobalBounds().height });
			player->SetPlayerBodyForce({ player->GetPlayerBodyForce().x,-10000000 });
		}
		else if (orange->GetPortalDir() == 3) {
			player->SetPlayerBodyPos({ orange->GetPos().x - 30 ,orange->GetPos().y });
			player->SetPlayerBodyForce({ 10000 * -333,0 });

		}

	}

	if (madeorange && orange->GetGlobalBounds().intersects(player->GetGlobalBounds())) {
		if (blue->GetPortalDir() == 0) {
			player->SetPlayerBodyPos({ blue->GetPos().x,blue->GetPos().y - player->GetGlobalBounds().height });
			player->SetPlayerBodyForce({ player->GetPlayerBodyForce().x,10000000 });
		}
		else if (blue->GetPortalDir() == 1) {
			player->SetPlayerBodyPos({ blue->GetPos().x + 30,blue->GetPos().y });
			player->SetPlayerBodyForce({ 10000 * 333,0 });

		}
		else if (blue->GetPortalDir() == 2) {
			player->SetPlayerBodyPos({ blue->GetPos().x ,blue->GetPos().y + player->GetGlobalBounds().height });
			player->SetPlayerBodyForce({ player->GetPlayerBodyForce().x,-10000000 });
		}
		else if (blue->GetPortalDir() == 3) {
			player->SetPlayerBodyPos({ blue->GetPos().x - 30 ,blue->GetPos().y });
			player->SetPlayerBodyForce({ 10000 * -333,0 });
		}
	}


	///////////////////////////////////////CUBE////////////////////////////////////////////////////
	for (auto c : cube) {
		if (madeblue && blue->GetGlobalBounds().intersects(c->GetGlobalBounds())) {
			if (orange->GetPortalDir() == 0) {
				c->SetCubeBodyPos({ orange->GetPos().x,orange->GetPos().y - c->GetGlobalBounds().height });
				c->SetCubeBodyForce({ c->GetCubeBodyForce().x,10000000 });

			}
			else if (orange->GetPortalDir() == 1) {
				c->SetCubeBodyPos({ orange->GetPos().x + c->GetGlobalBounds().width,orange->GetPos().y });
				c->SetCubeBodyForce({ 10000 * 333,0 });
			}
			else if (orange->GetPortalDir() == 2) {
				c->SetCubeBodyPos({ orange->GetPos().x ,orange->GetPos().y + c->GetGlobalBounds().height });
				c->SetCubeBodyForce({ c->GetCubeBodyForce().x,-10000000 });
			}
			else if (orange->GetPortalDir() == 3) {
				c->SetCubeBodyPos({ orange->GetPos().x - c->GetGlobalBounds().width ,orange->GetPos().y });
				c->SetCubeBodyForce({ 10000 * -333,0 });
			}
		}

		if (madeorange && orange->GetGlobalBounds().intersects(c->GetGlobalBounds())) {
			if (blue->GetPortalDir() == 0) {
				c->SetCubeBodyPos({ blue->GetPos().x,blue->GetPos().y - c->GetGlobalBounds().height });
				c->SetCubeBodyForce({ c->GetCubeBodyForce().x,10000000 });
			}
			else if (blue->GetPortalDir() == 1) {
				c->SetCubeBodyPos({ blue->GetPos().x + c->GetGlobalBounds().width,blue->GetPos().y });
				c->SetCubeBodyForce({ 10000 * 333,0 });

			}
			else if (blue->GetPortalDir() == 2) {
				c->SetCubeBodyPos({ blue->GetPos().x ,blue->GetPos().y + c->GetGlobalBounds().height });
				c->SetCubeBodyForce({ c->GetCubeBodyForce().x,-10000000 });
			}
			else if (blue->GetPortalDir() == 3) {
				c->SetCubeBodyPos({ blue->GetPos().x - c->GetGlobalBounds().width ,blue->GetPos().y });
				c->SetCubeBodyForce({ 10000 * -333,0 });
			}
		}
	}

}


PlayScene::PlayScene(string path)
{

	b2Vec2 g(0.0f, -900);
	world = make_unique<b2World>(g);

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
				//b"2 4 4 "(1)
			{
				i += 2;//index of gridposition number 
				string poslist;
				int posnum = str.find('"', i);
				poslist = str.substr(i, posnum - i);

				i += 3; //index of buttonId
				string idlist;
				int idnum = str.find(')', i);
				idlist = str.substr(i, idnum - i);
				//	MakeButton(poslist, idlist);
				i++;
			}
			case'@':
			{
				string list;
				int num = str.find(')', i);
				list = str.substr(i + 2, num - i - 2);
				MakeGoal(list);
				i = num;
			}
			default:
				currgrid.x += GRIDSIZE;
			}

		}
		currgrid = { GRIDSIZE / 2,currgrid.y + GRIDSIZE };

	}

	goal->SetButtonlist(button);

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
	delete goal;

}

void PlayScene::Enter()
{
	background.setTexture(*RESOURCEMGR->GetTexture("Graphics/backgrounds/ruin2.png"));
	Utils::SetSpriteSize(background, { WINDOW_WIDTH,WINDOW_HEIGHT });
	auto size = (Vector2f)FRAMEWORK->GetWindowSize();
	worldView.setSize(size);
	worldView.setCenter(size / 2.f);
	FRAMEWORK->GetWindow().setView(worldView);

	backgroundView.setSize(size);
	backgroundView.setCenter(size / 2.f);

	Tile::SetIsPlayingGame(true);
	zoomCount = 0;
	isMovingViewCenter = false;
}

void PlayScene::Exit()
{
	Tile::SetIsPlayingGame(false);
	zoomCount = 0;
}
