#include "EditScene.h"
#include "../FrameWork/stdafx.h"
#include "SceneMgr.h"
#include "../FrameWork/InputMgr.h"
#include "../Objects/SpriteObj.h"
#include "../Manager/ResourceMgr.h"
#include "../FrameWork/Const.h"
#include "../FrameWork/Framework.h"
#include "../FrameWork/Utils.h"
#include "../FrameWork/ObjectHeaders.h"
#include <fstream>

EditScene::EditScene()
{
	topLine.setFillColor(Color::Black);
	leftLine.setFillColor(Color::Black);
	rightLine.setFillColor(Color::Black);
	bottomLine.setFillColor(Color::Black);

	background.setTexture(*RESOURCEMGR->GetTexture("Graphics/backgrounds/tiles.png"));	
	shadow.setTexture(*RESOURCEMGR->GetTexture("Graphics/Ui/shadow.png"));
	

	uiBackGround.setFillColor(Color::White);
	uiOutLine.setTexture(*RESOURCEMGR->GetTexture("Graphics/Ui/uioutline.png"));
	uiMove.setTexture(*RESOURCEMGR->GetTexture("Graphics/Ui/cross.png"));
	Utils::SetOrigin(uiMove, Origins::MC);

	mapToolCheckBox = new SpriteObj;
	mapToolCheckBox->SetResourceTexture("Graphics/Ui/checkbox.png");	
	mapToolCheckBox->FitScale(TILE_SIZE);

	uiToolCheckBox = new SpriteObj;
	uiToolCheckBox->SetResourceTexture("Graphics/Ui/checkbox.png");
	uiToolCheckBox->FitScale(TILE_SIZE * 3.f);
}

EditScene::~EditScene()
{
	Release();
	delete mouseBoxSprite;
	delete mapToolCheckBox;
	delete uiToolCheckBox;
}

void EditScene::Init()
{		
	isScenePlay = true;
	rowNum = 20;
	colNum = 20;
	isPlayer = false;

	mapToolCheckBox->SetActive(false);
	uiToolCheckBox->SetActive(false);

	//Vector2u tileSize = RESOURCEMGR->GetTexture("Graphics/grid.png")->getSize();
	Vector2u tileSize = { TILE_SIZE, TILE_SIZE };
	auto winSize = (Vector2f)FRAMEWORK->GetWindowSize();

	startPos.x = (winSize.x - rowNum * tileSize.x) * 0.5f;
	startPos.y = (winSize.y - colNum * tileSize.y) * 0.5f + (colNum - 1) * tileSize.y;

	InitMapTool();

	zoomCount = 0;

	Vector2f uiViewSize = uiView.getSize();
	Vector2f uiStartPos;
	uiStartPos.x = 75.f;
	uiStartPos.y = (uiViewSize.y - uiOutLine.getGlobalBounds().height) * 0.5f;
	uiOutLine.setPosition(uiStartPos);

	isUiMoving = false;
	mouseOnUi = false;
	InitUiTool();
}

void EditScene::Release()
{
	ReleaseMapTool();

	for (int i = 0; i < uiTool.size(); i++)
	{
		for (int j = 0; j < uiTool[i].size(); j++)
		{
			if (uiTool[i][j].first != nullptr)
				delete uiTool[i][j].first;	
		}
	}
}

void EditScene::Enter()
{	
	cout << "Enter EditScene\n";	
	Scene::SetWorldView();
	Scene::SetUiView();
	Init();
}

void EditScene::Exit()
{
	cout << "Exit EditScene\n";
	isScenePlay = false;
	Release();
}

void EditScene::Update(float dt)
{		
	if (!isScenePlay)
		return;

	Input(dt);
	UpdateMapTool(dt);
	UpdateUiTool(dt);

	MouseSpriteBoxUpdate();	
}

void EditScene::Draw(RenderWindow& window)
{
	///////////////////////////// ¿ùµåºä
	window.setView(worldView);
	window.draw(shadow);
	window.draw(background);

	for (int i = 0; i < colNum; i++)
	{
		for (int j = 0; j < rowNum; j++)
		{
			if (!mapArray[i][j].first.empty())
			{
				for (auto array : mapArray[i][j].first)
				{
					if (array->GetActive() && array != nullptr)
						array->Draw(window);
				}
			}

			if (mapArray[i][j].second->GetActive())
				mapArray[i][j].second->Draw(window);			
		}
	}
	DrawOutLine(window);

	if (mapToolCheckBox->GetActive())
		mapToolCheckBox->Draw(window);

	////////////////////////////// UIºä
	window.setView(uiView);

	window.draw(uiBackGround);

	for (int i = 0; i < uiTool.size(); i++)
	{
		for (int j = 0; j < uiTool[i].size(); j++)
		{
			if (uiTool[i][j].first != nullptr && uiTool[i][j].first->GetActive())
				uiTool[i][j].first->Draw(window);
			
			window.draw(uiTool[i][j].second);
		}
	}

	window.draw(uiOutLine);	

	if (uiToolCheckBox->GetActive())
		uiToolCheckBox->Draw(window);

	window.draw(uiMove);

	if (mouseBoxSprite != nullptr)
		mouseBoxSprite->Draw(window);
}


void EditScene::InitMapTool()
{
	for (int i = 0; i < mapArray.size(); i++)
	{
		for (int j = 0; j < mapArray[i].size(); j++)
		{
			mapArray[i][j].second = new SpriteObj;
			mapArray[i][j].second->SetResourceTexture("Graphics/grid.png");
			mapArray[i][j].second->FitScale(TILE_SIZE);
			mapArray[i][j].second->SetActive(false);
		}
	}

	for (int i = 0; i < colNum; i++)
	{
		for (int j = 0; j < rowNum; j++)
		{
			mapArray[i][j].second->SetActive(true);
		}
	}

	Vector2f reSize = { (float)TILE_SIZE * rowNum, (float)TILE_SIZE * colNum };
	Utils::SetSpriteSize(background, reSize);
	Utils::SetSpriteSize(shadow, reSize * 1.01f);

	SetMapToolPos();
}

void EditScene::ReleaseMapTool()
{
	for (int i = 0; i < mapArray.size(); i++)
	{
		for (int j = 0; j < mapArray[i].size(); j++)
		{
			delete mapArray[i][j].second;

			for (auto array : mapArray[i][j].first)
			{
				if (array != nullptr)
				{
					delete array;					
				}					
			}
			mapArray[i][j].first.clear();
		}
	}
}

void EditScene::SetMapToolPos()
{
	if (mapArray.empty())
		return;
	
	//Vector2u size = RESOURCEMGR->GetTexture("Graphics/grid.png")->getSize();	
	Vector2u tileSize = { TILE_SIZE, TILE_SIZE };

	for (int i = 0; i < colNum; i++)
	{
		for (int j = 0; j < rowNum; j++)
		{
			Vector2f pos = { (float)tileSize.x * j, (float)tileSize.y * (-i) };
			mapArray[i][j].second->SetPos(pos + startPos);
		}
	}

	background.setPosition(mapArray[colNum - 1][0].second->GetPos());
	Vector2f shadowPosFix{ 8.f, 8.f };
	shadow.setPosition(mapArray[colNum - 1][0].second->GetPos() + shadowPosFix);

	topLine.setPosition(mapArray[colNum - 1][0].second->GetPos());
	topLine.setSize({ (float)tileSize.x * rowNum , 1.f });
	leftLine.setPosition(topLine.getPosition());
	leftLine.setSize({ 1.f, (float)tileSize.y * colNum });

	Vector2f fixPos;
	fixPos = { (float)tileSize.x, 0.f };
	rightLine.setPosition(mapArray[colNum - 1][rowNum - 1].second->GetPos() + fixPos);
	rightLine.setSize(leftLine.getSize());	
	fixPos = { 0.f, (float)tileSize.y - 1.f};
	bottomLine.setPosition(mapArray[0][0].second->GetPos() + fixPos);
	bottomLine.setSize(topLine.getSize());
}

void EditScene::SetMapToolSize()
{
	for (int i = 0; i < mapArray.size(); i++)
	{
		for (int j = 0; j < mapArray[i].size(); j++)
		{
			mapArray[i][j].second->SetActive(false);

			for (auto array : mapArray[i][j].first)
			{
				array->SetActive(false);
			}
		}
	}

	for (int i = 0; i < colNum; i++)
	{
		for (int j = 0; j < rowNum; j++)
		{
			mapArray[i][j].second->SetActive(true);

			for (auto array : mapArray[i][j].first)
			{
				array->SetActive(true);
			}
		}
	}

	Vector2f reSize = { (float)TILE_SIZE * rowNum, (float)TILE_SIZE * colNum };
	Utils::SetSpriteSize(background, reSize);
	Utils::SetSpriteSize(shadow, reSize * 1.01f);

	SetMapToolPos();
}

void EditScene::FillMapTool()
{
	Vector2f mousePos = ScreenToWorldPos((Vector2i)InputMgr::GetMousePos());
	
	for (int i = 0; i < colNum; i++)
	{
		for (int j = 0; j < rowNum; j++)
		{
			if (mapArray[i][j].second->GetGlobalBounds().contains(mousePos) &&
				mouseBoxSprite != nullptr &&
				InputMgr::GetMouseButton(Mouse::Left) &&
				!mouseOnUi)
			{
				if (!(mouseBoxSprite->GetId() == 'p' && Player::GetPlayerNum() > 2) &&
					!(mouseBoxSprite->GetId() == '@' && Goal::GetGoalNum() > 2))
				{
					if (!mapArray[i][j].first.empty())
					{
						delete mapArray[i][j].first.front();
						mapArray[i][j].first.clear();
					}

					mapArray[i][j].first.push_front(mouseBoxSprite->NewThis());
					mapArray[i][j].first.front()->FitScale(TILE_SIZE);
					mapArray[i][j].first.front()->SetPos(mapArray[i][j].second->GetPos());
				}
			}

			if (mapArray[i][j].second->GetGlobalBounds().contains(mousePos) &&
				mouseBoxSprite == nullptr &&
				InputMgr::GetMouseButton(Mouse::Right) &&
				!mapArray[i][j].first.empty())
			{
				delete mapArray[i][j].first.front();
				mapArray[i][j].first.clear();
			}
		}
	}
}

void EditScene::UpdateMapTool(float dt)
{
	if (!isScenePlay)
		return;

	FillMapTool();

	//for (int i = 0; i < colNum; i++)
	//{
	//	for (int j = 0; j < rowNum; j++)
	//	{
	//		for (auto array : mapArray[i][j])
	//		{
	//			if(array->GetActive())
	//				array->Update(dt);				
	//		}	
	//	}
	//}

	Vector2f mousePos = ScreenToWorldPos((Vector2i)InputMgr::GetMousePos());
	mapToolCheckBox->SetActive(false);

	for (int i = 0; i < colNum; i++)
	{
		for (int j = 0; j < rowNum; j++)
		{
			if (mapArray[i][j].second->GetGlobalBounds().contains(mousePos) &&
				!mouseOnUi)
			{
				mapToolCheckBox->SetActive(true);
				mapToolCheckBox->SetPos(mapArray[i][j].second->GetPos());
				break;
			}
		}
	}
}

void EditScene::Input(float dt)
{
	if (InputMgr::GetKeyDown(Keyboard::Escape))
	{
		SCENE_MGR->ChangeScene(Scenes::GAMESTART);
	}

	if (InputMgr::GetKeyDown(Keyboard::BackSpace))
	{
		exit(1);
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

	if (InputMgr::GetKeyDown(Keyboard::Numpad6))
	{
		rowNum++;
		SetMapToolSize();
	}
	if (InputMgr::GetKeyDown(Keyboard::Numpad4))
	{
		if (rowNum <= 1)
			return;
		rowNum--;
		SetMapToolSize();
	}
	if (InputMgr::GetKeyDown(Keyboard::Numpad8))
	{
		colNum++;
		SetMapToolSize();
	}
	if (InputMgr::GetKeyDown(Keyboard::Numpad2))
	{
		if (colNum <= 1)
			return;
		colNum--;
		SetMapToolSize();
	}

	if (InputMgr::GetMouseButton(Mouse::Middle))
	{
		Vector2f pos = InputMgr::GetMousePosDisplacement();
		worldView.setCenter(worldView.getCenter() + pos);
	}

	if (InputMgr::GetMouseButtonDown(Mouse::Left)
		&& uiMove.getGlobalBounds().contains(InputMgr::GetMousePos()))
	{
		isUiMoving = true;
	}

	if (isUiMoving && InputMgr::GetMouseButton(Mouse::Left))
	{
		SetUiToolPos(InputMgr::GetMousePos());
	}

	if (InputMgr::GetMouseButtonUp(Mouse::Left))
	{
		isUiMoving = false;
	}

	if (InputMgr::GetKeyDown(Keyboard::F5))
	{
		Save();
	}

	if (InputMgr::GetKeyDown(Keyboard::F9))
	{
		Load();
	}

	if (InputMgr::GetKeyDown(Keyboard::R))
	{
		ReleaseMapTool();
		InitMapTool();
	}
}

void EditScene::DrawOutLine(RenderWindow& window)
{
	window.draw(topLine);
	window.draw(leftLine);
	window.draw(rightLine);
	window.draw(bottomLine);
}

void EditScene::InitUiTool()
{
	FloatRect rect = uiOutLine.getLocalBounds();
	uiBackGround.setSize({ rect.width, rect.height });

	Vector2f uiStartPos = uiOutLine.getPosition();
	uiBackGround.setPosition(uiStartPos);
	
	uiMove.setPosition(uiStartPos);

	for (int i = 0; i < uiTool.size(); i++)
	{
		for (int j = 0; j < uiTool[i].size(); j++)
		{
			uiTool[i][j].first = nullptr;

			uiTool[i][j].second.setTexture(*RESOURCEMGR->GetTexture("Graphics/grid.png"));
			uiTool[i][j].second.setScale({ 1.5f,1.5f });			

			Vector2f setPos = { 75.f * j, 75.f * i };
			uiTool[i][j].second.setPosition(setPos + uiStartPos);
		}
	}

	FillUiToolBox();

	Vector2f fixPos = {75.f *0.5f, 75.f *0.5f};
	for (int i = 0; i < uiTool.size(); i++)
	{
		for (int j = 0; j < uiTool[i].size(); j++)
		{
			if (uiTool[i][j].first != nullptr)
			{
				uiTool[i][j].first->FitScale(60.f);
				uiTool[i][j].first->SetOrigin(Origins::MC);
				uiTool[i][j].first->SetPos(uiTool[i][j].second.getPosition() + fixPos);
			}
		}
	}
}

void EditScene::UpdateUiTool(float dt)
{
	uiToolCheckBox->SetActive(false);
	mouseOnUi = false;

	Vector2f mousePos = InputMgr::GetMousePos();

	for (int i = 0; i < uiTool.size(); i++)
	{
		for (int j = 0; j < uiTool[i].size(); j++)
		{
			if (uiTool[i][j].second.getGlobalBounds().contains(mousePos) &&
				!uiMove.getGlobalBounds().contains(mousePos))
			{
				mouseOnUi = true;
				uiToolCheckBox->SetActive(true);
				uiToolCheckBox->SetPos(uiTool[i][j].second.getPosition());
				break;
			}
		}
	}

	//for (int i = 0; i < uiTool.size(); i++)
	//{
	//	for (int j = 0; j < uiTool[i].size(); j++)
	//	{
	//		if (uiTool[i][j].first != nullptr && uiTool[i][j].first->GetActive())
	//			uiTool[i][j].first->Update(dt);
	//	}
	//}
}

void EditScene::FillUiToolBox()
{
	uiTool[0][0].first = new Tile;
	uiTool[0][1].first = new Cube;
	uiTool[0][2].first = new Player;

	uiTool[0][3].first = new Button;	
	uiTool[0][3].first->SetResourceTexture("Graphics/Ui/buttonui.png");
	Vector2u size = uiTool[0][3].first->GetSprite()->getTexture()->getSize();
	uiTool[0][3].first->GetSprite()->setTextureRect({ 0,0, (int)size.x, (int)size.y });

	uiTool[1][0].first = new Goal;
}

void EditScene::SetUiToolPos(Vector2f pos)
{
	uiOutLine.setPosition(pos);
	uiBackGround.setPosition(pos);
	uiMove.setPosition(pos);

	Vector2f fixPos = { 75.f * 0.5f, 75.f * 0.5f };
	for (int i = 0; i < uiTool.size(); i++)
	{
		for (int j = 0; j < uiTool[i].size(); j++)
		{
			Vector2f setPos = { 75.f * j, 75.f * i };
			uiTool[i][j].second.setPosition(setPos + pos);
			if (uiTool[i][j].first != nullptr)
				uiTool[i][j].first->SetPos(uiTool[i][j].second.getPosition() + fixPos);
		}
	}
}

void EditScene::MouseSpriteBoxUpdate()
{
	Vector2f mousePos = InputMgr::GetMousePos();

	for (int i = 0; i < uiTool.size(); i++)
	{
		for (int j = 0; j < uiTool[i].size(); j++)
		{
			if (uiTool[i][j].first != nullptr &&
				uiTool[i][j].second.getGlobalBounds().contains(mousePos) &&
				InputMgr::GetMouseButtonDown(Mouse::Left)&&
				!uiMove.getGlobalBounds().contains(InputMgr::GetMousePos()))
			{
				if (mouseBoxSprite != nullptr)
					delete mouseBoxSprite;

				mouseBoxSprite = uiTool[i][j].first->NewThis();
				mouseBoxSprite->FitScale(50.f);		
			}
		}
	}

	if (InputMgr::GetMouseButtonUp(Mouse::Right) &&
		mouseBoxSprite != nullptr)
	{
		delete mouseBoxSprite;
		mouseBoxSprite = nullptr;
	}

	if (mouseBoxSprite != nullptr)
		mouseBoxSprite->SetPos(mousePos);
}

void EditScene::Save()
{
	cout << "ÆÄÀÏ ÀúÀå\n";	
	ofstream txt("Map/temp.txt");
	
	for (int i = colNum - 1; i >= 0 ; i--)
	{
		for (int j = 0; j < rowNum; j++)
		{
			if (mapArray[i][j].first.empty())
				txt << '0';
			else
				txt << mapArray[i][j].first.front()->GetId();
		}
		txt << '\n';
	}
}

void EditScene::Load()
{
}
