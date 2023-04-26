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

	InitOptionSetting();
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
			optionon = !optionon;
			for (auto v : stagelist) {
				delete v;
			}
			stagelist.clear();
		}
	}
	else
	{
		if(!optionon)
			option.setTexture(*RESOURCEMGR->GetTexture("Graphics/Ui/option.png"));		
	}

	for (auto s:stagelist) {
		if (s->getGlobalBounds().contains(InputMgr::GetMousePos())) {
			if (InputMgr::GetMouseButtonDown(Mouse::Left)) {
				string temp = s->getString();
				SCENE_MGR->AddScene("Map\\" + s->getString());
				SCENE_MGR->ChangeScene(Scenes::PLAY);
				return;
			}
		}
	}

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

	if (optionon)
		DrawOption(window);

	//cout << InputMgr::GetMousePos().x << ", " << InputMgr::GetMousePos().y << endl;
}

void StartMenu::LoadFile()
{
	string path = "Map";
	for (const auto& entry : fs::directory_iterator(path)) {
		string path_string = fs::path(entry).filename().string();

		//for (int i = 0; i < 5; i++)
		//{
		//	path_string.pop_back();
		//}	
		
		//std::transform(path_string.begin(), path_string.end(), path_string.begin(),
		//	[](unsigned char c) { return std::toupper(c); });		

		//std::replace(path_string.begin(), path_string.end(), '_', ' ');

		Text* temp = new Text();
		temp->setString(path_string);
		

		stagelist.push_back(temp);
		stagelist.back()->setFillColor(Color::Black);
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

void StartMenu::InitOptionSetting()
{
	optionPos = { 384.f , 148.f };

	optionMain.setTexture(*RESOURCEMGR->GetTexture("Graphics/option/main.png"));
	scroll.setTexture(*RESOURCEMGR->GetTexture("Graphics/option/scroll.png"));
	scrollButton.setTexture(*RESOURCEMGR->GetTexture("Graphics/option/button.png"));

	blank = RESOURCEMGR->GetTexture("Graphics/option/blank.png");
	checkered = RESOURCEMGR->GetTexture("Graphics/option/check.png");

	indicatorOn.setTexture(*checkered);
	indicatorOff.setTexture(*blank);
	soundOn.setTexture(*checkered);
	soundOff.setTexture(*blank);

	optionMain.setScale(0.68f, 0.68f);
	scroll.setScale(0.68f, 0.68f);
	scrollButton.setScale(0.68f, 0.68f);
	indicatorOn.setScale(0.68f, 0.68f);
	indicatorOff.setScale(0.68f, 0.68f);
	soundOn.setScale(0.68f, 0.68f);
	soundOff.setScale(0.68f, 0.68f);

	optionMain.setPosition(optionPos);
	indicatorOn.setPosition((optionMain.getPosition() + Vector2f{ 183.f, 140.f }));
	indicatorOff.setPosition((optionMain.getPosition() + Vector2f{ 463.f, 140.f }));

	soundOn.setPosition((optionMain.getPosition() + Vector2f{ 183.f, 374.f }));
	soundOff.setPosition((optionMain.getPosition() + Vector2f{ 463.f, 374.f }));

	scroll.setPosition((optionMain.getPosition() + Vector2f{ 49.f, 468.f }));
	Utils::SetOrigin(scrollButton, Origins::MC);

	cout << scroll.getGlobalBounds().height << endl;
	scrollButton.setPosition(scroll.getPosition());
	scrollButton.move({ 0, 3.06f });

	FloatRect rect = scroll.getGlobalBounds();
	float y = scrollButton.getPosition().y;

	scrollButton.setPosition(rect.left + (rect.width * volume) / 100, y);
}

void StartMenu::UpdateOption()
{
	Vector2f mousePos = InputMgr::GetMousePos();
	bool mouseLeft = InputMgr::GetMouseButtonDown(Mouse::Left);

	if (indicatorOn.getGlobalBounds().contains(mousePos) && mouseLeft)
		SCENE_MGR->SetIndicator(true);

	if (indicatorOff.getGlobalBounds().contains(mousePos) && mouseLeft)
		SCENE_MGR->SetIndicator(false);

	if (soundOn.getGlobalBounds().contains(mousePos) && mouseLeft)
	{
		isSoundOn = true;

	}

	if (soundOff.getGlobalBounds().contains(mousePos) && mouseLeft)
	{
		FloatRect rect = scroll.getGlobalBounds();
		float y = scrollButton.getPosition().y;

		isSoundOn = false;

		volume = 0;
		scrollButton.setPosition(rect.left, y);
	}

	indicatorOn.setTexture(SCENE_MGR->GetIndicator() ? *checkered : *blank);
	indicatorOff.setTexture(!SCENE_MGR->GetIndicator() ? *checkered : *blank);

	soundOn.setTexture(isSoundOn ? *checkered : *blank);
	soundOff.setTexture(!isSoundOn ? *checkered : *blank);

	if ((scroll.getGlobalBounds().contains(mousePos) ||
		scrollButton.getGlobalBounds().contains(mousePos))
		&& mouseLeft)
	{
		isScrolling = true;
		isSoundOn = true;
	}

	if (isScrolling && InputMgr::GetMouseButtonUp(Mouse::Left))
	{
		isScrolling = false;
	}

	if (isScrolling)
	{
		FloatRect rect = scroll.getGlobalBounds();
		float y = scrollButton.getPosition().y;

		scrollButton.setPosition({ mousePos.x, y });
		if (scrollButton.getPosition().x < rect.left)
			scrollButton.setPosition(rect.left, y);
		if (scrollButton.getPosition().x > rect.left + rect.width)
			scrollButton.setPosition(rect.left + rect.width, y);

		volume = (int)(((scrollButton.getPosition().x - rect.left) / rect.width) * 100);
	}

	cout << SOUNDMGR->GetVolumeInt() << endl;
}

void StartMenu::DrawOption(RenderWindow& window)
{
	UpdateOption();

	window.draw(optionMain);
	window.draw(indicatorOn);
	window.draw(indicatorOff);
	window.draw(soundOn);
	window.draw(soundOff);

	window.draw(scroll);
	window.draw(scrollButton);
}

