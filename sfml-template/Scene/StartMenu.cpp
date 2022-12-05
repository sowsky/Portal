#include "StartMenu.h"
#include "../FrameWork/InputMgr.h"
#include "../FrameWork/stdafx.h"
#include "../Scene/SceneMgr.h"
#include "../FrameWork/Framework.h"
#include "../Manager/ResourceMgr.h"

StartMenu::StartMenu()
{
	Init();
}

StartMenu::~StartMenu()
{
	Release();
}

void StartMenu::Init()
{
	SetUiView();

	b2Vec2 g(0.0f, -10);
	world = make_unique<b2World>(g);

	start.setFont(*RESOURCEMGR->GetFont("Fonts/NanumGothic.otf"));
	edit.setFont(*RESOURCEMGR->GetFont("Fonts/NanumGothic.otf"));

	mousePos = new RectangleShape();
	Utils::SetOrigin(*mousePos, Origins::MC);
	mousePos->setSize({ 100, 50 });
	mousePos->setFillColor(Color::Blue);
	mousePos->setPosition(InputMgr::GetMousePos());


	startbox = new RectangleShape();
	Utils::SetOrigin(*startbox, Origins::TL);
	startbox->setSize({ 100, 50 });
	startbox->setFillColor(Color(128, 128, 128,100));
	startbox->setPosition(100, FRAMEWORK->GetWindowSize().y  - 300);
	start.setPosition(startbox->getPosition());
	start.setString("START");
	start.setFont(*RESOURCEMGR->GetFont("Fonts/D-DINCondensed-Bold.otf"));
	start.setFillColor(Color::White);
	start.setCharacterSize(40);

	editbox = new RectangleShape();
	Utils::SetOrigin(*editbox, Origins::TL);
	editbox->setSize({ 100, 50 });
	editbox->setFillColor(Color(128,128,128,100));
	editbox->setPosition(100, startbox->getPosition().y + 100);
	edit.setPosition(editbox->getPosition());
	edit.setCharacterSize(40);
	edit.setString("EDIT");
	edit.setFont(*RESOURCEMGR->GetFont("Fonts/D-DINCondensed-Bold.otf"));
	edit.setFillColor(Color::White);

	title.SetResourceTexture("Graphics/title.png");
	title.SetPos({ title.GetPos().x+100,title.GetPos().y + 140 });
	player = new Player(world.get(), Vector2f{ FRAMEWORK->GetWindowSize().x-450.f,FRAMEWORK->GetWindowSize().y-280.f}, Vector2f({20, 50}));

	player->GetBody()->SetType(b2_staticBody);
	
}

void StartMenu::Release()
{
	delete editbox;
	delete startbox;
	delete player;
}

void StartMenu::Enter()
{

	Scene::SetWorldView();
	SetUiView();
	uiView.zoom(0.44f);
}

void StartMenu::Update(float dt)
{

	Utils::SetOrigin(*startbox, Origins::TL);
	Utils::SetOrigin(*editbox, Origins::TL);
	Utils::SetOrigin(edit, Origins::TL);
	Utils::SetOrigin(start, Origins::TL);

	mousePos->setPosition(InputMgr::GetMousePos());

	if (mousePos->getGlobalBounds().intersects(startbox->getGlobalBounds()) && InputMgr::GetMouseButtonDown(Mouse::Left)) {
		SCENE_MGR->ChangeScene(Scenes::MAPLIST);
	}
	else if (mousePos->getGlobalBounds().intersects(editbox->getGlobalBounds()) && InputMgr::GetMouseButtonDown(Mouse::Left)) {
		SCENE_MGR->ChangeScene(Scenes::MAPEDITER);
	}

	player->Update(dt);
}

void StartMenu::Exit()
{
	SetUiView();
	FRAMEWORK->GetWindow().setView(worldView);
}

void StartMenu::Draw(RenderWindow& window)
{
	window.setView(worldView);
	title.Draw(window);
	if (editbox != nullptr) {
		window.draw(*editbox);
		window.draw(edit);
	}

	if (startbox != nullptr) {
		window.draw(*startbox);
		window.draw(start);
	}
	window.setView(uiView);
	player->Draw(window);
}

