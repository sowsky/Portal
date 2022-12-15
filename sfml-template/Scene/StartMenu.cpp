#include "StartMenu.h"
#include "../FrameWork/InputMgr.h"
#include "../FrameWork/stdafx.h"
#include "../Scene/SceneMgr.h"
#include "../FrameWork/Framework.h"
#include "../Manager/ResourceMgr.h"
#include <filesystem>

namespace fs = std::filesystem;

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
	Vector2f size;
	size.x = FRAMEWORK->GetWindowSize().x;
	size.y = FRAMEWORK->GetWindowSize().y;

	back.setTexture(*RESOURCEMGR->GetTexture("Graphics/backgrounds/main.png"));
	Utils::SetSpriteSize(back, { size.x, size.y });
	Utils::SetOrigin(back, Origins::MC);
	back.setPosition({ size.x / 2, size.y / 2 });

	stagespace.setTexture(*RESOURCEMGR->GetTexture("Graphics/Ui/stagespace.png"));
	Utils::SetSpriteSize(stagespace, { size.x * 0.6f, size.y * 0.9f });
	Utils::SetOrigin(stagespace, Origins::MC);
	stagespace.setPosition({ size.x / 2 + (size.x * 0.1f), size.y / 2 });

	play.setTexture(*RESOURCEMGR->GetTexture("Graphics/Ui/playbutton.png"));
	Utils::SetSpriteSize(play, { size.x * 0.25f, size.y * 0.2f });
	Utils::SetOrigin(play, Origins::ML);
	play.setPosition({ 10, size.y * 0.15f });

	option.setTexture(*RESOURCEMGR->GetTexture("Graphics/Ui/option.png"));
	Utils::SetSpriteSize(option, { size.x * 0.25f, size.y * 0.2f });
	Utils::SetOrigin(option, Origins::ML);
	option.setPosition({ 10, play.getPosition().y + 100 });

	exit.setTexture(*RESOURCEMGR->GetTexture("Graphics/Ui/exit.png"));
	Utils::SetSpriteSize(exit, { size.x * 0.25f, size.y * 0.2f });
	Utils::SetOrigin(exit, Origins::ML);
	exit.setPosition({ 10,  option.getPosition().y + 100 });
}

void StartMenu::Release()
{
	for (auto v : stagelist) {
		delete v;
	}
	stagelist.clear();
}

void StartMenu::Enter()
{
	Scene::SetWorldView();
	SetUiView();
}

void StartMenu::Update(float dt)
{
	//Utils::SetOrigin(*startbox, Origins::TL);
	//Utils::SetOrigin(*editbox, Origins::TL);
	//Utils::SetOrigin(edit, Origins::TL);
	//Utils::SetOrigin(start, Origins::TL);

	//mousePos->setPosition(InputMgr::GetMousePos());

	//if (mousePos->getGlobalBounds().intersects(startbox->getGlobalBounds()) && InputMgr::GetMouseButtonDown(Mouse::Left)) {
	//	SCENE_MGR->ChangeScene(Scenes::MAPLIST);
	//}
	//else if (mousePos->getGlobalBounds().intersects(editbox->getGlobalBounds()) && InputMgr::GetMouseButtonDown(Mouse::Left)) {
	//	SCENE_MGR->ChangeScene(Scenes::MAPEDITER);
	//}

	//player->Update(dt);

	if (InputMgr::GetKeyDown(Keyboard::F1)) {
		SCENE_MGR->ChangeScene(Scenes::MAPEDITER);
	}

	Vector2f mospos = InputMgr::GetMousePos();
	if (play.getGlobalBounds().contains(mospos)) {
		play.setTexture(*RESOURCEMGR->GetTexture("Graphics/Ui/playbuttonblack.png"));
		if (InputMgr::GetMouseButtonDown(Mouse::Left)) {
			playon = true;
			optionon = false;
			LoadFile();
		}
	}
	else
		play.setTexture(*RESOURCEMGR->GetTexture("Graphics/Ui/playbutton.png"));

	if (option.getGlobalBounds().contains(mospos)) {
		option.setTexture(*RESOURCEMGR->GetTexture("Graphics/Ui/optionblack.png"));
		if (InputMgr::GetMouseButtonDown(Mouse::Left)) {
			playon = false;
			optionon = true;
			for (auto v : stagelist) {
				delete v;
			}
			stagelist.clear();
		}
	}
	else
		option.setTexture(*RESOURCEMGR->GetTexture("Graphics/Ui/option.png"));

	if (exit.getGlobalBounds().contains(mospos)) {
		exit.setTexture(*RESOURCEMGR->GetTexture("Graphics/Ui/exitblack.png"));
		if (InputMgr::GetMouseButtonDown(Mouse::Left)) {
			std::exit(1);
		}
	}
	else
		exit.setTexture(*RESOURCEMGR->GetTexture("Graphics/Ui/exit.png"));

}

void StartMenu::Exit()
{
	FRAMEWORK->GetWindow().setView(worldView);
}

void StartMenu::Draw(RenderWindow& window)
{
	window.setView(uiView);
	window.draw(back);
	if (playon)
		window.draw(stagespace);
	window.draw(play);
	window.draw(option);
	window.draw(exit);
	/*title.Draw(window);
	if (editbox != nullptr) {
		window.draw(*editbox);
		window.draw(edit);
	}

	if (startbox != nullptr) {
		window.draw(*startbox);
		window.draw(start);
	}
	window.setView(uiView);
	player->Draw(window);*/

	for (auto v : stagelist) {
		window.draw(*v);
	}
}

void StartMenu::LoadFile()
{
	string path = "Map";
	for (const auto& entry : fs::directory_iterator(path)) {
		string path_string = fs::path(entry).filename().string();
		Text* temp = new Text();
		temp->setString(path_string);

		stagelist.push_back(temp);
		stagelist.back()->setFillColor(Color::Blue);
		stagelist.back()->setFont(*RESOURCEMGR->GetFont("Fonts/NanumGothic.otf"));
		Utils::SetOrigin(*stagelist.back(), Origins::MC);
	}

	if (!stagelist.empty()) {
		y =stagespace.getPosition().y-200;

		for (int i = 0; i < stagelist.size(); i++) {
			stagelist[i]->setPosition(stagespace.getPosition().x - 120, y);
			if (stagelist[i] != stagelist.back()) {
				++i;
				stagelist[i]->setPosition(stagespace.getPosition().x + 120, y);
			}

			y += 60;
		}
	}
}

