#include "StartMenu.h"
#include "../FrameWork/InputMgr.h"
#include "../FrameWork/stdafx.h"
#include "../Scene/SceneMgr.h"
#include "../FrameWork/Framework.h"

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
	mousePos = new RectangleShape();
	Utils::SetOrigin(*mousePos, Origins::MC);
	mousePos->setSize({ 100, 20 });
	mousePos->setFillColor(Color::Blue);
	mousePos->setPosition(InputMgr::GetMousePos());

	editbox = new RectangleShape();
	Utils::SetOrigin(*editbox, Origins::MC);
	editbox->setSize({ 100, 20 });
	editbox->setFillColor(Color::Blue);
	editbox->setPosition(FRAMEWORK->GetWindowSize().x / 2, FRAMEWORK->GetWindowSize().y / 2);

	startbox = new RectangleShape();
	Utils::SetOrigin(*startbox, Origins::MC);
	startbox->setSize({ 100, 20 });
	startbox->setFillColor(Color::Blue);
	startbox->setPosition(editbox->getPosition().x, editbox->getPosition().y+50);
}

void StartMenu::Release()
{
	delete editbox;
	delete startbox;
}

void StartMenu::Enter()
{
}

void StartMenu::Update(float dt)
{
	mousePos->setPosition(InputMgr::GetMousePos());
	cout << "this is start menu" << endl;

	if (mousePos->getGlobalBounds().intersects(editbox->getGlobalBounds()) && InputMgr::GetMouseButtonDown(Mouse::Left)) {
		SCENE_MGR->ChangeScene(Scenes::MAPLIST);
	}
	else if (mousePos->getGlobalBounds().intersects(startbox->getGlobalBounds()) && InputMgr::GetMouseButtonDown(Mouse::Left)) {
		SCENE_MGR->ChangeScene(Scenes::MAPEDITER);
	}
}

void StartMenu::Exit()
{
	
}

void StartMenu::Draw(RenderWindow& window)
{
	if (editbox != nullptr)
		window.draw(*editbox);

	if (startbox != nullptr)
		window.draw(*startbox);
}
