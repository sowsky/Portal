#include "PlayScene.h"
#include <fstream>
#include "../FrameWork/stdafx.h"
#include "../FrameWork/InputMgr.h"
#include "SceneMgr.h"
#include "../FrameWork/Framework.h"
#include "../Manager/ResourceMgr.h"
#include "../Objects/Goal.h"
#include "../Objects/FileData.h"

#pragma warning(disable:4996)
using json = nlohmann::json;

void PlayScene::Update(float dt)
{
	crosshair.setPosition(InputMgr::GetMousePos());

	OpenStage(dt);

	ClearRenderBuffer();
	//////////////////////////////////////////////////////
	if (goal->GetGlobalBounds().intersects(player->GetGlobalBounds())) {
		if (goal->IsFinish()) {
			dark += dt * 200;
			ending.setFillColor(Color(0, 0, 0, dark));
		}
		if (dark >= 255) {
			SCENE_MGR->ChangeScene(Scenes::GAMESTART);
			return;
		}
	}
	else {
		if (dark > 0) {
			dark -= dt * 200;
			ending.setFillColor(Color(0, 0, 0, dark));
			if (dark < 0)
				dark = 0;

		}
	}
	player->Update(dt);
	goal->Update(dt);
	for (auto c : cube) {
		c->Update(dt);
	}
	for (auto w : wall)
		w->Update(dt);
	/*for (auto bw : blackwall)
		bw->Update(dt);*/
	for (auto t : tunnel) {
		t->Update(dt);
	}
	for (auto b : bridge) {
		b->Update(dt);
	}
	for (auto r : redwall) {
		r->Update(dt);
	}

	blue->Update(dt);
	orange->Update(dt);


	if (!isMovingViewCenter) {

		Vector2f currentcampos = worldView.getCenter();
		worldView.setCenter(Utils::Lerp(currentcampos.x, player->GetPos().x, dt * 4), Utils::Lerp(currentcampos.y, player->GetPos().y, dt * 4));

	}

	if (player->GetPos().y >= height + 200) {
		player->Respawn();
	}
	for (auto c : cube) {
		if (c->GetPos().y >= height + 200) {
			c->Respawn();
		}
	}

	MakePortal();
	MoveToPortal();
	PushButton();
	TunnelCheck();
	BridgeCheck();
	RedwallCheck();

	if (IsMadeTunnelFollowOrangePortal || IsMadeTunnelFollowBluePortal)
		CheckStillObjectalive();

	if (grabitem) {

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
						//	c->SetSide(true);
						c->ChangeBodyTypeBetweenStaticAndDynamic(grabitem);
					}
					else if (player->GetPos().x > cposX) {
						//c->SetSide(false);
						c->ChangeBodyTypeBetweenStaticAndDynamic(grabitem);
					}
					c->SetGround(false);
				}

			}
		}
	}

	if (particle.running())
		particle.update(dt);

	Input();

	//light.position.x = 0;
	//light.position.y = height;

	//light.position.x = GetMouseWorldPos().x;
	//light.position.y = height - GetMouseWorldPos().y;
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

		player->PhysicsUpdate(dt);

		dtstack -= 1 / 60.f;
	}

}

void PlayScene::Draw(RenderWindow& window)
{
	window.setView(worldView);

	window.draw(backtemp);

	for (auto v : wall) {
		v->Draw(window);
	}

	if (madeorange) {
		orange->Draw(window);
	}

	if (madeblue) {
		blue->Draw(window);
	}

	for (auto v : wall) {
		v->Draw(pass_diffuse, normals_shader, pass_normals);
	}

	for (auto v : blackwall) {
		v->Draw(window);
		v->Draw(pass_diffuse, normals_shader, pass_normals);
	}

	for (auto v : cube) {
		v->Draw(window);
		v->Draw(pass_diffuse, normals_shader, pass_normals);
	}

	for (auto v : bridge) {
		v->DrawBackSide(window);
	}

	if (goal != nullptr) {
		goal->Draw(window);
		//goal->Draw(pass_diffuse, normals_shader, pass_normals);
	}

	DrawRenderedBuffer(window);

	if (player != nullptr)
	{
		player->Draw(window);
	}


	/*for (auto v : wall) {
		v->DrawHitbox(window);
	}*/


	for (auto v : redwall) {
		v->Draw(window);
	}

	if (player != nullptr)
		player->Draw(window);

	for (auto v : button) {
		v->Draw(window);
	}

	for (auto v : tunnel) {
		v->Draw(window);
	}

	for (auto v : bridge) {
		v->Draw(window);
	}

	if (particle.running())
		window.draw(particle);

	if (showWire)
	{
		for (auto w : wires)
		{
			window.draw(w->wire,
				w->isOn ? orangeWire : blueWire);
		}
	}

	window.setView(uiView);
	window.draw(crosshair);

	window.setView(endingView);
	if (dark != 0)
		window.draw(ending);
}

PlayScene::PlayScene(string path)
	:light(sf::Vector3f(255 / 255.0, 214 / 255.0, 170 / 255.0),
		sf::Vector3f(0, 0, 0.08),
		sf::Vector3f(0.5, 0.5, 0.5)),
	falloff(0.5, 0.5, 0.5)
	//light(sf::Vector3f(255 / 255.0, 214 / 255.0, 170 / 255.0),
	//	sf::Vector3f(0, 0, 0),
	//	sf::Vector3f(0.5, 0.5, 0.5)),
	//falloff(4, 4, 4)
{

	b2Vec2 g(0.0f, -10);
	world = make_unique<b2World>(g);

	/////////////////////////////////////////////////////////////////////////////
	blue = new Blue;
	orange = new Orange;

	blue->SetSize({ 10,10 });
	orange->SetSize({ 10,10 });

	ifstream ifs(path);
	Data_struct loadObjInfo = json::parse(ifs);
	const int rowNum = loadObjInfo.map_size.row;
	const int colNum = loadObjInfo.map_size.col;

	vector<vector<list<Object_struct*>>> loadedArray;

	loadedArray.resize(colNum);
	for (int i = 0; i < colNum; i++)
	{
		loadedArray[i].resize(rowNum);
	}

	loadedArray[loadObjInfo.player.posY][loadObjInfo.player.posX].push_back(&loadObjInfo.player);
	loadedArray[loadObjInfo.goal.posY][loadObjInfo.goal.posX].push_back(&loadObjInfo.goal);

	for (auto& p : loadObjInfo.buttons)
	{
		loadedArray[p.posY][p.posX].push_back(&p);
	}
	for (auto& p : loadObjInfo.cubes)
	{
		loadedArray[p.posY][p.posX].push_back(&p);
	}
	for (auto& p : loadObjInfo.tiles)
	{
		loadedArray[p.posY][p.posX].push_back(&p);
	}
	for (auto& p : loadObjInfo.tunnels)
	{
		loadedArray[p.posY][p.posX].push_back(&p);
	}
	for (auto& p : loadObjInfo.bridges)
	{
		loadedArray[p.posY][p.posX].push_back(&p);
	}

	for (auto& p : loadObjInfo.blacktile)
	{
		loadedArray[p.posY][p.posX].push_back(&p);
	}

	for (auto& p : loadObjInfo.redwalls)
	{
		loadedArray[p.posY][p.posX].push_back(&p);
	}

	for (int i = 0; i < colNum; i++)
	{
		for (int j = 0; j < rowNum; j++)
		{

			if (loadedArray[i][j].empty())
			{
				currgrid.x += GRIDSIZE;
				box2dposition.x = currgrid.x;
			}
			else {
				for (auto obj : loadedArray[i][j])  //load all object on 1grid
				{

					switch (obj->id)
					{
					case '1':
					{
						if (j + 1 < rowNum &&
							!loadedArray[i][j + 1].empty() &&
							(loadedArray[i][j + 1].front()->id == '1' || loadedArray[i][j + 1].front()->id == '2'))
						{
							MakeWall(false);
							wallbunchwidth += GRIDSIZE;

						}
						else
						{
							MakeWall(true);
							box2dposition.x = currgrid.x;
							wallbunchwidth = GRIDSIZE;

						}
						Tile_struct* t = (Tile_struct*)loadedArray[i][j].front();
						wall.back()->SetActiveSideTiles(t->sideBool);
						break;
					}
					case '2':
					{
						if (j + 1 < rowNum &&
							!loadedArray[i][j + 1].empty() &&
							(loadedArray[i][j + 1].front()->id == '1' || loadedArray[i][j + 1].front()->id == '2'))
						{
							MakeBlackWall(false);
							wallbunchwidth += GRIDSIZE;
						}
						else
						{
							MakeBlackWall(true);
							box2dposition.x = currgrid.x;
							wallbunchwidth = GRIDSIZE;


						}
						Black_Tile_struct* t = (Black_Tile_struct*)loadedArray[i][j].front();
						blackwall.back()->SetActiveSideTiles(t->sideBool);
						break;
					}
					case 'p':
					case 'P':
						MakePlayer();
						box2dposition.x = currgrid.x;

						break;
					case 'C':
					case 'c':
						MakeCube();
						box2dposition.x = currgrid.x;

						break;
					case 'b':
					case 'B':
					{
						Button_sturct* tempB = (Button_sturct*)obj;
						MakeButton(obj->rotation, tempB->buttonId);
						box2dposition.x += GRIDSIZE;
						break;
					}
					case'@':
					{
						Goal_struct* tempG = (Goal_struct*)obj;
						MakeGoal(tempG->buttonList);
						box2dposition.x += GRIDSIZE;
						//if (m.find("Alice") != m.end())
						for (auto b : tempG->buttonList)
						{
							if (wireList.find(b) == wireList.end())
							{
								list<Vector2f> templ;
								templ.clear();
								wireList.insert({ b, templ });
							}
							wireList[b].push_back(goal->GetSpritePos());
						}
						break;
					}
					case 't':
					case 'T':
					{
						Tunnel_sturct* tempT = (Tunnel_sturct*)obj;
						tunnel.push_back(new Tunnel({ currgrid.x,currgrid.y }, tempT->rotation, tempT->buttonList, 1, false, 0));
						currgrid.x += GRIDSIZE;
						box2dposition.x += GRIDSIZE;

						for (auto b : tempT->buttonList)
						{
							if (wireList.find(b) == wireList.end())
							{
								list<Vector2f> templ;
								templ.clear();
								wireList.insert({ b, templ });
							}
							wireList[b].push_back(tunnel.back()->GetStartPos());
						}

						break;
					}
					case 'l':
					case 'L': {
						Bridge_sturct* tempB = (Bridge_sturct*)obj;
						bridge.push_back(new Bridge(world.get(), currgrid, tempB->buttonList, true, tempB->rotation, 0));
						currgrid.x += GRIDSIZE;
						box2dposition.x += GRIDSIZE;

						for (auto b : tempB->buttonList)
						{
							if (wireList.find(b) == wireList.end())
							{
								list<Vector2f> templ;
								templ.clear();
								wireList.insert({ b, templ });
							}
							wireList[b].push_back(bridge.back()->GetStartPos());
						}
						break;
					}
					case 'r':
					case 'R':
					{
						Redwall_struct* tempR = (Redwall_struct*)obj;
						redwall.push_back(new Redwall(currgrid, tempR->buttonList, tempR->on, tempR->rotation));
						currgrid.x += GRIDSIZE;
						box2dposition.x += GRIDSIZE;

						for (auto b : tempR->buttonList)
						{
							if (wireList.find(b) == wireList.end())
							{
								list<Vector2f> templ;
								templ.clear();
								wireList.insert({ b, templ });
							}
							wireList[b].push_back(redwall.back()->GetStartPos());
						}
						break;
					}
					}
				}
			}
		}
		currgrid = { GRIDSIZE / 2, currgrid.y + GRIDSIZE };
		box2dposition = { GRIDSIZE / 2, currgrid.y + GRIDSIZE };
		wallbunchwidth = GRIDSIZE;
	}

	height = colNum * GRIDSIZE;
	width = rowNum * GRIDSIZE;

	bgNormal = RESOURCEMGR->GetTexture("Graphics/bg.png");
	SetTex(crosshair, "Graphics/crosshair/alloff.png");
	crosshair.setScale(0.3f, 0.3f);
	Utils::SetOrigin(crosshair, Origins::MC);

	goal->SetButtonlist(button);

	if (!tunnel.empty()) {
		for (auto t : tunnel) {
			t->SetButtonlist(button);
		}
	}
	if (!bridge.empty()) {
		for (auto t : bridge) {
			t->SetButtonlist(button);
		}
	}
	if (!redwall.empty()) {
		for (auto t : redwall) {
			t->SetButtonlist(button);
		}
	}

	particle.init(500);

	//////////////
	if (!button.empty())
	{
		for (auto b : button)
		{
			for (auto w : wireList[b->GetButtonId()])
			{
				wires.push_back(new PsceneWire(b->GetIsPressRef()));
				wires.back()->wire[0].position = b->GetSpritePos();
				wires.back()->wire[1].position = w;
			}
		}
	}

	orangeWire = RESOURCEMGR->GetTexture("Graphics/orange.png");
	blueWire = RESOURCEMGR->GetTexture("Graphics/blue.png");

	fireBlueBuffer.loadFromFile("Sound/fireblue.wav");
	fireOrangeBuffer.loadFromFile("Sound/fireorange.wav");

	fireBlue.setBuffer(fireBlueBuffer);
	fireOrange.setBuffer(fireOrangeBuffer);

	backtemp.setTexture(*RESOURCEMGR->GetTexture("Graphics/tempback.png"));
	backtemp.setPosition(200.f, 200.f);

}

void PlayScene::MakeWall(bool isEnd)
{
	Tile* temp = new Tile(world.get(), currgrid, Vector2f({ wallbunchwidth, GRIDSIZE }), box2dposition, isEnd);
	temp->SetOrigin(Origins::MC);
	wall.push_back(temp);

	currgrid.x += GRIDSIZE;
}

void PlayScene::MakeBlackWall(bool isEnd)
{
	BlackTile* temp = new BlackTile(world.get(), currgrid, Vector2f({ wallbunchwidth, GRIDSIZE }), box2dposition, isEnd);
	temp->SetOrigin(Origins::MC);
	blackwall.push_back(temp);

	currgrid.x += GRIDSIZE;
}

void PlayScene::MakeCube()
{
	Cube* newCube = new Cube(world.get(), Vector2f{ currgrid }, Vector2f({ GRIDSIZE, GRIDSIZE }));

	cube.push_back(newCube);

	currgrid.x += GRIDSIZE;
}

void PlayScene::MakePlayer()
{
	player = new Player(world.get(), Vector2f{ currgrid }, Vector2f({ 20, 50 }));

	currgrid.x += GRIDSIZE;
}

void PlayScene::MakeButton(int rotaion, int id)
{
	Button* temp = new Button();

	button.push_back(temp);
	button.back()->SetOrigin(Origins::BC);
	button.back()->SetButtonId(id);
	button.back()->SetPos(currgrid);
	button.back()->SetRotation(rotaion);

	if (rotaion == 0) {			//top of gird
		button.back()->SetPos({ currgrid.x,currgrid.y - GRIDSIZE / 2 });
		button.back()->SetSize({ GRIDSIZE,GRIDSIZE / 4 });

	}
	else if (rotaion == 1) {	//right of gird
		button.back()->SetPos({ currgrid.x + GRIDSIZE / 2,currgrid.y });
		button.back()->SetSize({ GRIDSIZE,GRIDSIZE / 4 });

	}
	else if (rotaion == 2) {	//bottom of gird
		button.back()->SetPos({ currgrid.x,currgrid.y + GRIDSIZE / 2 });
		button.back()->SetSize({ GRIDSIZE,GRIDSIZE / 4 });

	}
	else if (rotaion == 3) {	//left of gird
		button.back()->SetPos({ currgrid.x - GRIDSIZE / 2,currgrid.y });
		button.back()->SetSize({ GRIDSIZE ,GRIDSIZE / 4 });

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
	float bluey;
	float bluex;

	for (auto w : blackwall) {
		if (w->GetGlobalBounds().intersects(blue->GetGlobalBounds())) {
			particle.emitParticles(blue->GetPos(), false);
			blue->SetPos({ -1000,-1000 });
			blue->SetDir({ 0,0 });
			madeblue = false;
		}
		if (w->GetGlobalBounds().intersects(orange->GetGlobalBounds())) {
			particle.emitParticles(orange->GetPos(), false);
			orange->SetPos({ -1000,-1000 });
			blue->SetDir({ 0,0 });
			madeorange = false;

		}
	}

	for (auto b : bridge)
	{
		if (b->GetStartposGlobalbound().intersects(blue->GetGlobalBounds())) {
			particle.emitParticles(blue->GetPos(), false);
			blue->SetPos({ -1000,-1000 });
			blue->SetDir({ 0,0 });
			madeblue = false;

		}
		if (b->GetStartposGlobalbound().intersects(orange->GetGlobalBounds())) {
			particle.emitParticles(orange->GetPos(), false);
			orange->SetPos({ -1000,-1000 });
			blue->SetDir({ 0,0 });
			madeorange = false;

		}
	}

	for (auto b : redwall)
	{
		if (b->GetredwallGlobalBound().intersects(blue->GetGlobalBounds())) {
			particle.emitParticles(blue->GetPos(), false);
			blue->SetPos({ -1000,-1000 });
			blue->SetDir({ 0,0 });
			madeblue = false;

		}
		if (b->GetredwallGlobalBound().intersects(orange->GetGlobalBounds())) {
			particle.emitParticles(orange->GetPos(), false);
			orange->SetPos({ -1000,-1000 });
			blue->SetDir({ 0,0 });
			madeorange = false;

		}
	}

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

			bluey = blue->GetPos().y;
			bluex = blue->GetPos().x;
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

	if (madeorange && orange->GetGlobalBounds().intersects(blue->GetGlobalBounds())) {
		particle.emitParticles(blue->GetPos(), false);
		blue->SetPos({ -1000,-1000 });
	}
	else if (bluecollidercount == 2) {
		//bottom
		if (bluetlhit && bluetrhit) {
			blue->SetLightDir(90, false);
			blue->SetSize({ 50,20 });
			blue->SetPos({ blue->GetPos().x,sety });
			blue->SetPortalDir(2);
			cout << "low" << endl;
		}
		//left
		else if (bluetrhit && bluebrhit) {
			blue->SetLightDir(180, true);
			blue->SetSize({ 20,50 });
			blue->SetPos({ setx,blue->GetPos().y });
			blue->SetPortalDir(3);
			cout << "left" << endl;
		}
		//top
		else if (blueblhit && bluebrhit) {
			blue->SetLightDir(270, false);
			blue->SetSize({ 50,20 });
			blue->SetPos({ blue->GetPos().x,sety });
			blue->SetPortalDir(0);
			cout << "top" << endl;

		}
		//right
		else if (bluetlhit && blueblhit) {
			blue->SetLightDir(0, true);
			blue->SetSize({ 20,50 });
			blue->SetPos({ setx,bluey });
			blue->SetPortalDir(1);
			cout << "right" << endl;
		}
		madeblue = true;

		blue->SetDir({ 0,0 });
	}
	else if (bluecollidercount != 0 || (blue->GetSize().x == 50 && blue->GetSize().y == 50)) {
		particle.emitParticles(blue->GetPos(), false);
		blue->SetPos({ -1000,-1000 });
	}

	for (auto t : tunnel) {
		if (t->GetStartposGlobalbound().intersects(blue->GetGlobalBounds())) {
			particle.emitParticles(blue->GetPos(), false);
			blue->SetPos({ -1000,-1000 });
		}
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
	float orangey;
	float orangex;

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
			orangex = orange->GetPos().x;
			orangey = orange->GetPos().y;
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

	if (madeblue && blue->GetGlobalBounds().intersects(orange->GetGlobalBounds())) {
		particle.emitParticles(orange->GetPos(), false);
		orange->SetPos({ -1000,-1000 });
	}
	else if (orangecollidercount == 2) {
		//bottom
		if (orangetlhit && orangetrhit) {
			orange->SetLightDir(90, false);
			orange->SetSize({ 50,20 });
			orange->SetPos({ orange->GetPos().x,orangesety });
			orange->SetPortalDir(2);
			cout << "low" << endl;
		}
		//left
		else if (orangetrhit && orangebrhit) {
			orange->SetLightDir(180, true);
			orange->SetSize({ 20,50 });
			orange->SetPos({ orangesetx,orange->GetPos().y });
			orange->SetPortalDir(3);
			cout << "left" << endl;
		}
		//top
		else if (orangeblhit && orangebrhit) {
			orange->SetLightDir(270, false);
			orange->SetSize({ 50,20 });
			orange->SetPos({ orange->GetPos().x,orangesety });
			orange->SetPortalDir(0);
			cout << "top" << endl;

		}
		//right
		else if (orangetlhit && orangeblhit) {
			orange->SetLightDir(0, true);
			orange->SetSize({ 20,50 });
			orange->SetPos({ orangesetx,orangey });

			orange->SetPortalDir(1);
			cout << "right" << endl;
		}
		madeorange = true;
		orange->SetDir({ 0,0 });
	}
	else if (orangecollidercount != 0 || (orange->GetSize().x == 50 && orange->GetSize().y == 50)) {
		particle.emitParticles(orange->GetPos(), true);
		orange->SetPos({ -1000,-1000 });
	}

	for (auto t : tunnel) {
		if (t->GetStartposGlobalbound().intersects(orange->GetGlobalBounds())) {
			particle.emitParticles(orange->GetPos(), false);
			orange->SetPos({ -1000,-1000 });
		}
	}

	if (madeblue && madeorange)
	{
		SetTex(crosshair, "Graphics/crosshair/allon.png");
	}
	if (!madeblue && madeorange)
	{
		SetTex(crosshair, "Graphics/crosshair/orgon.png");
	}
	if (madeblue && !madeorange)
	{
		SetTex(crosshair, "Graphics/crosshair/blueon.png");
	}
	if (!madeblue && !madeorange)
	{
		SetTex(crosshair, "Graphics/crosshair/alloff.png");
	}


}

void PlayScene::MakeGoal(vector<int> list)
{
	goal = new Goal(currgrid, GRIDSIZE, list);

	currgrid.x += GRIDSIZE;
}

void PlayScene::MakeTunnel(string dir, string id)
{
	bool d;
	if (dir == '0' || dir == '2')
		d = false;
	else
		d = true;
	//tunnel.push_back(new Tunnel(currgrid, d, dir));
}

void PlayScene::PushButton()
{
	//for (auto b : button) {
	//	if (b->GetPressed())
	//		continue;

	//	if (b->GetGlobalBounds().intersects(player->GethitboxGlobalBounds())) {
	//		b->SetPressed(true);
	//		break;
	//	}

	//}

	//for (auto b : button) {
	//	if (!b->GetPressed())
	//		continue;
	//	if (b->GetGlobalBounds().intersects(player->GethitboxGlobalBounds())) {
	//		b->SetPressed(false);
	//	}
	//}

	for (auto b : button) {
		if (b->GetPressed())
			continue;
		for (auto c : cube) {
			if (c->GetGlobalBounds().intersects(b->GetHitbox()->getGlobalBounds())) {
				b->SetPressed(true);
				break;
			}
		}
	}

	for (auto b : button) {
		if (!b->GetPressed())
			continue;

		bool off = false;
		for (auto c : cube) {
			if (c->GetGlobalBounds().intersects(b->GetHitbox()->getGlobalBounds())) {
				off = false;
				break;
			}
			off = true;
		}
		if (off)
			b->SetPressed(false);

	}


}

void PlayScene::TunnelCheck()
{
	///////////////////////wall check//////////////////////////
	for (auto w : wall) {
		for (auto t : tunnel) {
			if (w->GetGlobalBounds().intersects(t->GetHitBoxGlobalbound())) {
				t->SetHitwall(true);
				t->Setwhohitwall(*w);
			}
		}
	}

	for (auto w : blackwall) {
		for (auto t : tunnel) {
			if (w->GetGlobalBounds().intersects(t->GetHitBoxGlobalbound())) {
				t->SetHitwall(true);
				t->Setwhohitwall(*w);
			}
		}
	}

	for (auto t : tunnel) {
		//////////////////////player check//////////////////////////
		if (t->GetHitBoxGlobalbound().intersects(player->GetGlobalBounds())) {
			if (t->GetDir() == 0) {
				if (!player->GetIsMoving()) {
					float x = player->GetPos().x - t->GetTunsPos().x;
					player->GetBody()->SetLinearVelocity({ x * -1 ,-2 });
				}
				else
				{
					if ((int)player->GetBody()->GetLinearVelocity().y == 0) {
						player->GetBody()->SetLinearVelocity({ player->GetBody()->GetLinearVelocity().x,0.2f });
					}
					else
						player->GetBody()->SetLinearVelocity({ player->GetBody()->GetLinearVelocity().x,-2 });

				}
				if (!t->GetColor()) {
					float x = player->GetPlayerBodyLinearVelocity().x;
					float y = player->GetPlayerBodyLinearVelocity().y;
					player->GetBody()->SetLinearVelocity({ x,y * -1 });
				}
			}
			if (t->GetDir() == 2) {
				if (!player->GetIsMoving()) {
					float x = player->GetPos().x - t->GetTunsPos().x;
					player->GetBody()->SetLinearVelocity({ x * -1 / 10,2 });
				}
				else
				{
					if ((int)player->GetBody()->GetLinearVelocity().y == 0) {
						player->GetBody()->SetLinearVelocity({ player->GetBody()->GetLinearVelocity().x,0.2f });
					}
					else
						player->GetBody()->SetLinearVelocity({ player->GetBody()->GetLinearVelocity().x,2 });

				}
				if (!t->GetColor()) {
					float x = player->GetPlayerBodyLinearVelocity().x;
					float y = player->GetPlayerBodyLinearVelocity().y;
					player->GetBody()->SetLinearVelocity({ x,y * -1 });
				}
			}
			if (t->GetDir() == 1) {
				if (!player->GetIsMoving()) {
					float y = player->GetPos().y - player->GetSize().y / 2 - t->GetTunsPos().y;
					player->GetBody()->SetLinearVelocity({ -2,y });
				}
				else
				{
					if ((int)player->GetBody()->GetLinearVelocity().y == 0) {
						player->GetBody()->SetLinearVelocity({ -0.2f,player->GetBody()->GetLinearVelocity().y });
					}
					else
						player->GetBody()->SetLinearVelocity({ -0.2f,player->GetBody()->GetLinearVelocity().y });
				}
			}
			if (t->GetDir() == 3) {
				if (!player->GetIsMoving()) {
					float y = player->GetPos().y - player->GetSize().y / 2 - t->GetTunsPos().y;
					player->GetBody()->SetLinearVelocity({ 2,y });
				}
				else
				{
					if ((int)player->GetBody()->GetLinearVelocity().y == 0) {
						player->GetBody()->SetLinearVelocity({ 0.2f,player->GetBody()->GetLinearVelocity().y });
					}
					else
						player->GetBody()->SetLinearVelocity({ 0.2f,player->GetBody()->GetLinearVelocity().y });

				}
			}
		}

		//////////////////cube check/////////////////////////
		for (auto c : cube) {
			if (t->GetHitBoxGlobalbound().intersects(c->GetGlobalBounds())) {
				if (t->GetDir() == 0) {
					float x = c->GetPos().x - t->GetTunsPos().x;
					c->GetBody()->SetLinearVelocity({ x * -1 / 10,-2.f });
				}
				if (t->GetDir() == 2) {
					float x = c->GetPos().x - t->GetTunsPos().x;
					c->GetBody()->SetLinearVelocity({ x * -1 / 10,2.f });
				}
				if (t->GetDir() == 1) {
					float y = c->GetPos().y - t->GetTunsPos().y;
					c->GetBody()->SetLinearVelocity({ -2.f,y });
				}
				if (t->GetDir() == 3) {
					float y = c->GetPos().y - t->GetTunsPos().y;
					c->GetBody()->SetLinearVelocity({ 2.f,y });
				}
			}
		}

	}

}

void PlayScene::BridgeCheck()
{
	for (auto w : wall) {
		for (auto v : bridge) {
			if (w->GetGlobalBounds().intersects(v->GetHitBoxGlobalbound())) {
				v->SetHitwall(true);
				v->Setwhohitwall(*w);

			}
		}
	}


	for (auto w : blackwall) {
		for (auto v : bridge) {
			if (w->GetGlobalBounds().intersects(v->GetHitBoxGlobalbound())) {
				v->SetHitwall(true);
				v->Setwhohitwall(*w);

			}
		}
	}


	if (!madeorange || !madeblue) {

		auto ite = bridge.begin();
		while (ite != bridge.end())
		{
			if ((*ite)->GetConnected() == 2)
			{
				auto ptr = (*ite);
				ite = bridge.erase(ite);
				delete ptr;
				break;
			}
			else {
				++ite;
			}
		}
		IsMadeBridgeFollowOrangePortal = false;
	}

	if (!madeblue || !madeorange) {

		auto ite = bridge.begin();
		while (ite != bridge.end())
		{
			if ((*ite)->GetConnected() == 1)
			{
				auto ptr = (*ite);
				ite = bridge.erase(ite);
				delete ptr;
				break;
			}
			else {
				++ite;
			}
		}
		IsMadeBridgeFollowBluePortal = false;
	}

}

void PlayScene::RedwallCheck()
{
	for (auto r : redwall) {
		if (!r->Gethitwall()) {
			for (auto w : wall) {
				if (w->GetGlobalBounds().intersects(r->GetredwallGlobalBound())) {
					r->Sethitwall(true);
					r->Setwhohitwall(w);
				}
			}

			for (auto w : blackwall) {
				if (w->GetGlobalBounds().intersects(r->GetredwallGlobalBound())) {
					r->Sethitwall(true);
					r->Setwhohitwall(w);
				}
			}
		}


		if (r->GetredwallGlobalBound().intersects(player->GethitboxGlobalBounds())) {
			madeblue = false;
			madeorange = false;
			blue->SetPos({ -1000,-1000 });
			orange->SetPos({ -1000,-1000 });
			blue->SetDir({ 0,0 });
			orange->SetDir({ 0,0 });
		}
		for (auto c : cube) {
			if (r->GetredwallGlobalBound().intersects(c->GethitboxGlobalBounds())) {
				if (grabitem) {

					grabbedcube->ChangeBodyTypeBetweenStaticAndDynamic(false);

					grabbedcube = nullptr;
					grabitem = false;
				}
				c->MovetoStartpos();
			}
		}
	}
}

void PlayScene::CheckStillObjectalive()
{
	if (!IsMadeTunnelFollowOrangePortal) {
		//check blue hit
		for (auto b : bridge) {
			if (b->GetDestinyGlobalbound().intersects(blue->GetGlobalBounds())) {

			}
		}
	}

	////////////////////////////////////////////////////////////////////
	if (IsMadeTunnelFollowOrangePortal) {
		bool on = false;
		for (auto t : tunnel)
		{
			if (t->GetDestinyGlobalbound().intersects(blue->GetGlobalBounds())) {
				on = true;
			}
		}
		if (!on)
		{
			auto ite = tunnel.begin();
			while (ite != tunnel.end())
			{
				if ((*ite)->GetConnected() == 2)
				{
					auto ptr = (*ite);
					ite = tunnel.erase(ite);
					delete ptr;
					break;
				}
				else {
					++ite;
				}
			}
			IsMadeTunnelFollowOrangePortal = false;
		}
	}

	if (IsMadeTunnelFollowBluePortal) {
		bool on = false;
		for (auto t : tunnel)
		{
			if (t->GetDestinyGlobalbound().intersects(orange->GetGlobalBounds())) {
				on = true;
			}
		}
		if (!on)
		{
			auto ite = tunnel.begin();
			while (ite != tunnel.end())
			{
				if ((*ite)->GetConnected() == 1)
				{
					auto ptr = (*ite);
					ite = tunnel.erase(ite);
					delete ptr;
					break;
				}
				else {
					++ite;
				}
			}
			IsMadeTunnelFollowBluePortal = false;
		}
	}


	if (IsMadeBridgeFollowOrangePortal) {
		bool on = false;
		for (auto t : bridge)
		{
			if (t->GetDestinyGlobalbound().intersects(blue->GetGlobalBounds())) {
				on = true;
			}
		}
		if (!on)
		{
			auto ite = tunnel.begin();
			while (ite != tunnel.end())
			{
				if ((*ite)->GetConnected() == 2)
				{
					auto ptr = (*ite);
					ite = tunnel.erase(ite);
					delete ptr;
					break;
				}
				else {
					++ite;
				}
			}
			IsMadeBridgeFollowOrangePortal = false;
		}
	}

	if (IsMadeBridgeFollowBluePortal) {
		bool on = false;
		for (auto t : bridge)
		{
			if (t->GetDestinyGlobalbound().intersects(orange->GetGlobalBounds())) {
				on = true;
			}
		}
		if (!on)
		{
			auto ite = tunnel.begin();
			while (ite != tunnel.end())
			{
				if ((*ite)->GetConnected() == 1)
				{
					auto ptr = (*ite);
					ite = tunnel.erase(ite);
					delete ptr;
					break;
				}
				else {
					++ite;
				}
			}
			IsMadeBridgeFollowBluePortal = false;
		}
	}


}

void PlayScene::DrawBackGroundView(RenderWindow& window)
{
	window.setView(backgroundView);
}

void PlayScene::DrawRenderedBuffer(RenderWindow& window)
{
	pass_diffuse.display();
	pass_normals.display();

	lights_shader.setParameter("resolution", sf::Vector2f(width, height));
	lights_shader.setParameter("sampler_normal", pass_normals.getTexture());
	lights_shader.setParameter("ambient_intensity", ambient_intensity);
	lights_shader.setParameter("falloff", falloff);

	lights_shader.setParameter("sampler_light", front->getTexture());
	lights_shader.setParameter("light_pos", light.position);
	lights_shader.setParameter("light_color", light.color);
	back->draw(sf::Sprite(pass_diffuse.getTexture()), &lights_shader);
	back->display();
	std::swap(back, front);

	// Draw diffuse color
	window.draw(sf::Sprite(pass_diffuse.getTexture()));
	// Blend lighting over
	window.draw(sf::Sprite(front->getTexture()), sf::BlendMultiply);
}

void PlayScene::Input()
{
	LightTestInputForDev();

	if (InputMgr::GetMouseWheelState() == 1)
	{
		if (worldView.getSize().x < 60.f || openingTime > 0.f)
			return;

		worldView.zoom(0.8f);
	}
	if (InputMgr::GetMouseWheelState() == -1)
	{
		if (worldView.getSize().x > 2800.f || openingTime > 0.f)
			return;

		worldView.zoom(1.12f);
	}

	if (InputMgr::GetMouseButton(Mouse::Middle))
	{
		if (openingTime > 0.f)
			return;

		isMovingViewCenter = true;
		Vector2f pos = InputMgr::GetMousePosDisplacement();
		worldView.setCenter(worldView.getCenter() + pos);
	}

	if (InputMgr::GetMouseButtonUp(Mouse::Middle))
	{
		isMovingViewCenter = false;
	}

	if (InputMgr::GetKeyDown(Keyboard::Num8))
	{
		SpriteObj::OnOffWiringState();
	}

	//blue
	if (InputMgr::GetMouseButtonDown(Mouse::Left) && !grabitem) {
		auto it = tunnel.begin();
		if (IsMadeTunnelFollowBluePortal) {
			while (it != tunnel.end())
			{
				if ((*it)->GetConnected() == 1)
				{
					it = tunnel.erase(it);
					break;
				}
				else {
					++it;
				}
			}
			IsMadeTunnelFollowBluePortal = false;
		}
		it = tunnel.begin();
		if (IsMadeTunnelFollowOrangePortal) {
			while (it != tunnel.end())
			{
				if ((*it)->GetConnected() == 2)
				{
					it = tunnel.erase(it);
					break;
				}
				else {
					++it;
				}
			}
			IsMadeTunnelFollowOrangePortal = false;
		}

		auto ite = bridge.begin();
		if (IsMadeBridgeFollowOrangePortal) {
			while (ite != bridge.end())
			{
				if ((*ite)->GetConnected() == 2)
				{
					auto ptr = (*ite);
					ite = bridge.erase(ite);
					delete ptr;
					break;
				}
				else {
					++ite;
				}
			}
			IsMadeBridgeFollowOrangePortal = false;
		}
		ite = bridge.begin();
		if (IsMadeBridgeFollowBluePortal) {
			while (ite != bridge.end())
			{
				if ((*ite)->GetConnected() == 1)
				{
					auto ptr = (*ite);
					ite = bridge.erase(ite);
					delete ptr;
					break;
				}
				else {
					++ite;
				}
			}
			IsMadeBridgeFollowBluePortal = false;
		}

		blue->SetSize({ 20,20 });
		madeblue = false;
		blue->SetPos(player->GetClaviclePos());
		blue->SetDir(Utils::Normalize(ScreenToWorldPos((Vector2i)InputMgr::GetMousePos()) - player->GetPositions()));
		////////////////////
		fireBlue.play();
	}


	//orange
	if (InputMgr::GetMouseButtonDown(Mouse::Right) && !grabitem) {
		auto it = tunnel.begin();
		if (IsMadeTunnelFollowBluePortal) {
			while (it != tunnel.end())
			{
				if ((*it)->GetConnected() == 1)
				{
					it = tunnel.erase(it);
					break;
				}
				else {
					++it;
				}
			}
			IsMadeTunnelFollowBluePortal = false;
		}

		if (IsMadeTunnelFollowOrangePortal) {
			while (it != tunnel.end())
			{
				if ((*it)->GetConnected() == 2)
				{
					it = tunnel.erase(it);
					break;
				}
				else {
					++it;
				}
			}
			IsMadeTunnelFollowOrangePortal = false;
		}
		auto ite = bridge.begin();
		if (IsMadeBridgeFollowOrangePortal) {
			while (ite != bridge.end())
			{
				if ((*ite)->GetConnected() == 2)
				{
					auto ptr = (*ite);
					ite = bridge.erase(ite);
					delete ptr;
					break;
				}
				else {
					++ite;
				}
			}
			IsMadeBridgeFollowOrangePortal = false;
		}

		if (IsMadeBridgeFollowBluePortal) {
			while (ite != bridge.end())
			{
				if ((*ite)->GetConnected() == 2)
				{
					auto ptr = (*ite);
					ite = bridge.erase(ite);
					delete ptr;
					break;
				}
				else {
					++ite;
				}
			}
			IsMadeBridgeFollowBluePortal = false;
		}

		orange->SetSize({ 20,20 });
		madeorange = false;
		orange->SetPos(player->GetClaviclePos());
		orange->SetDir(Utils::Normalize(ScreenToWorldPos((Vector2i)InputMgr::GetMousePos()) - player->GetPositions()));
		/////////////////////
		fireOrange.play();
	}

	if (grabitem) {
		Vector2f dir = Utils::Normalize(ScreenToWorldPos((Vector2i)InputMgr::GetMousePos()) - grabbedcube->GetPos());
		dir.x *= 50;
		dir.y *= 50;
		if (player->IsMouseRight())
			dir.x = 50;
		if (!player->IsMouseRight())
			dir.x = -50;
		float x = Utils::Lerp(grabbedcube->GetPos().x, dir.x + player->GetPos().x, 0.5f);

		Vector2f real(dir.x + player->GetPos().x, player->GetPos().y - 25);
		grabbedcube->GetBody()->SetTransform({ real.x / SCALE,real.y / SCALE * -1 }, grabbedcube->GetBody()->GetAngle());
		//grabbedcube->GetBody()->ApplyForce({ x / SCALE,0 }, grabbedcube->GetBody()->GetWorldCenter(), 1);
	}

	///////////////////////

	if (InputMgr::GetKeyDown(Keyboard::T))
	{
		showWire = !showWire;
	}

	if (InputMgr::GetKeyDown(Keyboard::Escape)) {
		if (SCENE_MGR->GetPrevKey() == Scenes::MAPEDITER)
		{
			SCENE_MGR->ChangeScene(Scenes::MAPEDITER);
		}
		else
			SCENE_MGR->ChangeScene(Scenes::GAMESTART);
		return;
	}


	if (InputMgr::GetKeyDown(Keyboard::R))
	{
		player->Respawn();
		madeblue = false;
		madeorange = false;
		blue->SetPos({ -100,-100 });
		orange->SetPos({ -100,-100 });
		for (auto c : cube) {
			c->Respawn();
		}
		if (grabitem) {
			grabbedcube->ChangeBodyTypeBetweenStaticAndDynamic(false);
			grabbedcube = nullptr;
			grabitem = false;

		}
	}

}

void PlayScene::LightTestInputForDev()
{
	if (InputMgr::GetKeyDown(Keyboard::Numpad8))
	{
		light.position.z += 0.01f;
		cout << "light.position.z : " << light.position.z << endl;
	}
	if (InputMgr::GetKeyDown(Keyboard::Numpad2))
	{
		light.position.z -= 0.01f;
		cout << "light.position.z : " << light.position.z << endl;
	}
	if (InputMgr::GetKeyDown(Keyboard::Add))
	{
		ambient_intensity += 0.05f;
		cout << "ambient_intensity : " << ambient_intensity << endl;
	}
	if (InputMgr::GetKeyDown(Keyboard::Subtract))
	{
		ambient_intensity -= 0.05f;
		cout << "ambient_intensity : " << ambient_intensity << endl;
	}
	if (InputMgr::GetKeyDown(Keyboard::Numpad4))
	{
		falloff /= 0.5f;
		cout
			<< "falloff : "
			<< falloff.x << ','
			<< falloff.y << ','
			<< falloff.z << ','
			<< endl;
	}
	if (InputMgr::GetKeyDown(Keyboard::Numpad6))
	{
		falloff *= 0.5f;
		cout
			<< "falloff : "
			<< falloff.x << ','
			<< falloff.y << ','
			<< falloff.z << ','
			<< endl;
	}
}

void PlayScene::ClearRenderBuffer()
{
	back->clear();
	front->clear();
	//pass_diffuse.clear(Color::White);
	pass_diffuse.clear(Color::Transparent);
	// Set normals buffer to neutral color
	//pass_normals.clear(Color::White);
	pass_normals.clear(Color(128, 128, 255));
}

void PlayScene::OpenStage(float dt)
{
	if (openingTime < 0.f)
		return;
	openingTime -= dt;
	worldView.zoom(0.995f);
}


void PlayScene::MoveToPortal()
{
	if (!madeblue || !madeorange) {
		return;
	}
	if (madeblue && blue->GetGlobalBounds().intersects(player->GetGlobalBounds())) {
		cout << player->GetRecentSpeed().y << endl;
		float recent = player->GetPlayerBodyLinearVelocity().y*-1;
		if ((int)recent <= 2)
			recent = 1;

		if (orange->GetPortalDir() == 0) {
			player->SetPlayerBodyPos({ orange->GetPos().x,orange->GetPos().y - player->GetGlobalBounds().height });
			player->GetBody()->SetLinearVelocity({ 0,0 });
			player->GetBody()->SetLinearVelocity({ player->GetRecentSpeed().x ,recent });
			cout << player->GetRecentSpeed().y * -1 << endl;

		}
		else if (orange->GetPortalDir() == 1) {
			player->SetPlayerBodyPos({ orange->GetPos().x + 30,orange->GetPos().y });
			float force = (abs(player->GetRecentSpeed().y)) + (abs(player->GetRecentSpeed().x));
			player->GetBody()->SetLinearVelocity({ force ,1 });
		}
		else if (orange->GetPortalDir() == 2) {
			player->SetPlayerBodyPos({ orange->GetPos().x ,orange->GetPos().y + player->GetGlobalBounds().height });
			//	player->GetBody()->SetLinearVelocity({ 0,player->GetRecentSpeed().y });
			player->GetBody()->SetLinearVelocity({ player->GetPlayerBodyLinearVelocity().x,player->GetRecentSpeed().y - 1 });
		}
		else if (orange->GetPortalDir() == 3) {
			player->SetPlayerBodyPos({ orange->GetPos().x - 30 ,orange->GetPos().y });
			float force = (abs(player->GetRecentSpeed().y)) + (abs(player->GetRecentSpeed().x));
			player->GetBody()->SetLinearVelocity({ force * -1,1 });
		}
	}

	//////////////////////////////move to blue//////////////////////////////////////
	if (madeorange && orange->GetGlobalBounds().intersects(player->GetGlobalBounds())) {
		cout << player->GetRecentSpeed().y << endl;

		float recent = player->GetRecentSpeed().y * -1;
		if ((int)recent <= 2)
			recent = 1;

		if (blue->GetPortalDir() == 0) {
			player->SetPlayerBodyPos({ blue->GetPos().x,blue->GetPos().y - player->GetGlobalBounds().height });
			player->GetBody()->SetLinearVelocity({ 0,0 });
			player->GetBody()->SetLinearVelocity({ player->GetRecentSpeed().x ,recent });
			cout << player->GetRecentSpeed().y * -1 << endl;

		}
		else if (blue->GetPortalDir() == 1) {
			player->SetPlayerBodyPos({ blue->GetPos().x + 30,blue->GetPos().y });
			float force = (abs(player->GetRecentSpeed().y)) + (abs(player->GetRecentSpeed().x));
			player->GetBody()->SetLinearVelocity({ force ,1 });
		}
		else if (blue->GetPortalDir() == 2) {
			player->SetPlayerBodyPos({ blue->GetPos().x ,blue->GetPos().y + player->GetGlobalBounds().height });
			player->GetBody()->SetLinearVelocity({ player->GetPlayerBodyLinearVelocity().x,player->GetRecentSpeed().y - 1 });

		}
		else if (blue->GetPortalDir() == 3) {
			player->SetPlayerBodyPos({ blue->GetPos().x - 30 ,blue->GetPos().y });
			float force = (abs(player->GetRecentSpeed().y)) + (abs(player->GetRecentSpeed().x));
			player->GetBody()->SetLinearVelocity({ force * -1 ,1 });
		}
	}


	///////////////////////////////////////CUBE////////////////////////////////////////////////////
	for (auto c : cube) {
		if (madeblue && blue->GetGlobalBounds().intersects(c->GetGlobalBounds())) {
			if (orange->GetPortalDir() == 0) {
				c->SetCubeBodyPos({ orange->GetPos().x,orange->GetPos().y - c->GetGlobalBounds().height });
				if (abs(c->GetCubeBodyForce().y) <= 0.5f) {
					c->GetBody()->SetLinearVelocity({ c->GetRecentSpeed().x ,1.f });
				}
				else {
					c->GetBody()->SetLinearVelocity({ 0,0 });
					c->GetBody()->SetLinearVelocity({ c->GetRecentSpeed().x ,c->GetRecentSpeed().y * -1 });
				}

			}
			else if (orange->GetPortalDir() == 1) {
				c->SetCubeBodyPos({ orange->GetPos().x + c->GetGlobalBounds().width,orange->GetPos().y });
				float force = (abs(c->GetRecentSpeed().y)) + (abs(c->GetRecentSpeed().x));
				c->GetBody()->SetLinearVelocity({ force ,1 });
			}
			else if (orange->GetPortalDir() == 2) {
				c->SetCubeBodyPos({ orange->GetPos().x ,orange->GetPos().y + c->GetGlobalBounds().height });
				c->GetBody()->SetLinearVelocity({ c->GetCubeBodyForce().x,c->GetRecentSpeed().y - 1 });


			}
			else if (orange->GetPortalDir() == 3) {
				c->SetCubeBodyPos({ orange->GetPos().x - c->GetGlobalBounds().width ,orange->GetPos().y });
				float force = (abs(c->GetRecentSpeed().y)) + (abs(c->GetRecentSpeed().x));
				c->GetBody()->SetLinearVelocity({ force * -1  ,1 });
			}
		}


		if (madeorange && orange->GetGlobalBounds().intersects(c->GetGlobalBounds())) {
			if (blue->GetPortalDir() == 0) {
				c->SetCubeBodyPos({ blue->GetPos().x,blue->GetPos().y - c->GetGlobalBounds().height });
				if (abs(c->GetCubeBodyForce().y) <= 0.5f) {
					c->GetBody()->SetLinearVelocity({ c->GetRecentSpeed().x ,1.f });
				}
				else {
					c->GetBody()->SetLinearVelocity({ 0,0 });
					c->GetBody()->SetLinearVelocity({ c->GetRecentSpeed().x ,c->GetRecentSpeed().y * -1 });
				}
			}
			else if (blue->GetPortalDir() == 1) {
				c->SetCubeBodyPos({ blue->GetPos().x + c->GetGlobalBounds().width,blue->GetPos().y });
				float force = (abs(c->GetRecentSpeed().y)) + (abs(c->GetRecentSpeed().x));
				c->GetBody()->SetLinearVelocity({ force  ,1 });

			}
			else if (blue->GetPortalDir() == 2) {
				c->SetCubeBodyPos({ blue->GetPos().x ,blue->GetPos().y + c->GetGlobalBounds().height });
				c->GetBody()->SetLinearVelocity({ c->GetCubeBodyForce().x,c->GetRecentSpeed().y - 1 });
			}
			else if (blue->GetPortalDir() == 3) {
				c->SetCubeBodyPos({ blue->GetPos().x - c->GetGlobalBounds().width ,blue->GetPos().y });
				float force = (abs(c->GetRecentSpeed().y)) + (abs(c->GetRecentSpeed().x));
				c->GetBody()->SetLinearVelocity({ force * -1 ,1 });
			}
		}
	}

	//////////////////////////////////////////////////////tunnel//////////////////////////////////

	for (int i = 0; i < (int)tunnel.size(); i++)
	{
		if ((IsMadeTunnelFollowOrangePortal || IsMadeBridgeFollowBluePortal) && i == tunnel.size())
			break;
		//hit blue
		if (tunnel[i]->GetDestinyGlobalbound().intersects(blue->GetGlobalBounds()) && !IsMadeTunnelFollowOrangePortal) {
			vector<int> temp;
			Vector2f pos;
			int dir = 0;
			if (orange->GetPortalDir() == 0) {
				pos = { orange->GetPos().x,orange->GetPos().y - orange->GetGlobalBounds().height - 30 };
				dir = 2;
			}
			else if (orange->GetPortalDir() == 1) {
				pos = { orange->GetPos().x + 50,orange->GetPos().y };
				dir = 3;
			}
			else if (orange->GetPortalDir() == 2) {
				pos = { orange->GetPos().x,orange->GetPos().y + orange->GetGlobalBounds().height + 30 };
				dir = 0;
			}
			else if (orange->GetPortalDir() == 3) {
				pos = { orange->GetPos().x - 50,orange->GetPos().y };
				dir = 1;

			}


			tunnel.push_back(new Tunnel(pos, dir, temp, tunnel[i]->GetColor(), true, 2));
			IsMadeTunnelFollowOrangePortal = true;

			if (tunnel[i]->GetDir() == 0 || tunnel[i]->GetDir() == 2)
				blue->SetPos({ tunnel[i]->GetHitbox()->getPosition().x,blue->GetPos().y });
			else if (tunnel[i]->GetDir() == 1 || tunnel[i]->GetDir() == 3)
				blue->SetPos({ blue->GetPos().x,tunnel[i]->GetHitbox()->getPosition().y });
		}

		//hit orange
		if (tunnel[i]->GetDestinyGlobalbound().intersects(orange->GetGlobalBounds()) && !IsMadeTunnelFollowBluePortal) {

			vector<int> temp;
			Vector2f pos;
			int dir = 0;
			if (blue->GetPortalDir() == 0) {
				pos = { blue->GetPos().x,orange->GetPos().y - blue->GetGlobalBounds().height - 30 };
				dir = 2;
			}
			else if (blue->GetPortalDir() == 1) {
				pos = { blue->GetPos().x + 50,blue->GetPos().y };
				dir = 3;
			}
			else if (blue->GetPortalDir() == 2) {
				pos = { blue->GetPos().x,blue->GetPos().y + blue->GetGlobalBounds().height + 30 };
				dir = 0;
			}
			else if (blue->GetPortalDir() == 3) {
				pos = { blue->GetPos().x - 50,blue->GetPos().y };
				dir = 1;

			}

			tunnel.push_back(new Tunnel(pos, dir, temp, tunnel[i]->GetColor(), true, 1));
			IsMadeTunnelFollowBluePortal = true;
			if (tunnel[i]->GetDir() == 0 || tunnel[i]->GetDir() == 2)
				orange->SetPos({ tunnel[i]->GetHitbox()->getPosition().x,orange->GetPos().y });
			else if (tunnel[i]->GetDir() == 1 || tunnel[i]->GetDir() == 3)
				orange->SetPos({ orange->GetPos().x,tunnel[i]->GetHitbox()->getPosition().y });


		}
	}

	////////////////////////////bridge////////////////////////
	for (int i = 0; i < (int)bridge.size(); i++) {

		//hit blue
		if (bridge[i]->GetHitBoxGlobalbound().intersects(blue->GetGlobalBounds()) && !IsMadeBridgeFollowOrangePortal) {
			vector<int> temp;
			Vector2f pos;
			int dir = 0;
			if (orange->GetPortalDir() == 0) {
				pos = { orange->GetPos().x,orange->GetPos().y - orange->GetGlobalBounds().height - 25 };
				dir = 2;
			}
			else if (orange->GetPortalDir() == 1) {
				pos = { orange->GetPos().x + 50,orange->GetPos().y };
				dir = 3;
			}
			else if (orange->GetPortalDir() == 2) {
				pos = { orange->GetPos().x,orange->GetPos().y + orange->GetGlobalBounds().height + 25 };
				dir = 0;
			}
			else if (orange->GetPortalDir() == 3) {
				pos = { orange->GetPos().x - 50,orange->GetPos().y };
				dir = 1;

			}

			bridge.push_back(new Bridge(world.get(), pos, temp, true, dir, 2));

			IsMadeBridgeFollowOrangePortal = true;
		}

		//hit orange
		if (bridge[i]->GetHitBoxGlobalbound().intersects(orange->GetGlobalBounds()) && !IsMadeBridgeFollowBluePortal) {
			vector<int> temp;
			Vector2f pos;
			int dir = 0;
			if (blue->GetPortalDir() == 0) {
				pos = { blue->GetPos().x,blue->GetPos().y - blue->GetGlobalBounds().height - 25 };
				dir = 2;
			}
			else if (blue->GetPortalDir() == 1) {
				pos = { blue->GetPos().x + 50,blue->GetPos().y };
				dir = 3;
			}
			else if (blue->GetPortalDir() == 2) {
				pos = { blue->GetPos().x,blue->GetPos().y + blue->GetGlobalBounds().height + 25 };
				dir = 0;
			}
			else if (blue->GetPortalDir() == 3) {
				pos = { blue->GetPos().x - 50,blue->GetPos().y };
				dir = 1;

			}
			bridge.push_back(new Bridge(world.get(), pos, temp, true, dir, 1));

			IsMadeBridgeFollowBluePortal = true;
		}
	}
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
	player = nullptr;

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


	for (auto v : tunnel) {
		delete v;
	}
	tunnel.clear();

	if (orange != nullptr)
		delete orange;
	if (blue != nullptr)
		delete blue;
	if (goal != nullptr)
		delete goal;

	/*if (grabbedcube != nullptr)
		delete grabbedcube;*/

	for (auto v : wires)
	{
		delete v;
	}
	wires.clear();
}

void PlayScene::Enter()
{
	FRAMEWORK->GetWindow().setMouseCursorVisible(false);

	auto size = (Vector2f)FRAMEWORK->GetWindowSize();
	worldView.setSize(size);
	worldView.setCenter(size / 2.f);
	FRAMEWORK->GetWindow().setView(worldView);

	SetUiView();

	backgroundView.setSize(size);
	backgroundView.setCenter(size / 2.f);
	ending.setSize(size);
	ending.setFillColor(Color(0, 0, 0, 0));

	endingView.setSize(size);
	endingView.setCenter(size / 2.f);

	SpriteObj::SetIsPlayingGame(true);
	isMovingViewCenter = false;
	showWire = false;

	front = unique_ptr<RenderTexture>(new RenderTexture());
	back = unique_ptr<RenderTexture>(new RenderTexture());

	front->create(width, height);
	back->create(width, height);

	pass_normals.create(width, height);
	pass_diffuse.create(width, height);

	lights_shader.loadFromFile("Shader/light.frag", Shader::Fragment);
	normals_shader.loadFromFile("Shader/normals.frag", Shader::Fragment);
}

void PlayScene::Exit()
{
	FRAMEWORK->GetWindow().setMouseCursorVisible(true);
	SpriteObj::SetIsPlayingGame(false);
}
