#include "EditScene.h"
#include "../FrameWork/stdafx.h"
#include "SceneMgr.h"
#include "../FrameWork/InputMgr.h"
#include "../Objects/SpriteObj.h"
#include "../Manager/ResourceMgr.h"
#include "../FrameWork/Const.h"
#include "../FrameWork/Framework.h"
#include "../FrameWork/Utils.h"

EditScene::EditScene()
{
	topLine.setFillColor(Color::Black);
	leftLine.setFillColor(Color::Black);
	rightLine.setFillColor(Color::Black);
	bottomLine.setFillColor(Color::Black);	

	uiBackGround.setFillColor(Color::White);
	uiOutLine.setTexture(*RESOURCEMGR->GetTexture("Graphics/Ui/uioutline.png"));
	uiMove.setTexture(*RESOURCEMGR->GetTexture("Graphics/Ui/cross.png"));
	Utils::SetOrigin(uiMove, Origins::MC);
}

EditScene::~EditScene()
{
	Release();
}

void EditScene::Init()
{		
	isScenePlay = true;
	rowNum = 10;
	colNum = 10;

	Vector2u tileSize = RESOURCEMGR->GetTexture("Graphics/grid.png")->getSize();
	auto winSize = (Vector2f)FRAMEWORK->GetWindowSize();

	startPos.x = (winSize.x - rowNum * tileSize.x) * 0.5f;
	startPos.y = (winSize.y - colNum * tileSize.y) * 0.5f + (colNum - 1) * tileSize.y;

	InitTool();

	zoomCount = 0;

	Vector2f uiViewSize = uiView.getSize();
	Vector2f uiStartPos;
	uiStartPos.x = 75.f;
	uiStartPos.y = (uiViewSize.y - uiOutLine.getGlobalBounds().height) * 0.5f;
	uiOutLine.setPosition(uiStartPos);

	isUiMoving = false;
	InitUiTool();
}

void EditScene::Release()
{
	for (int i = 0; i < colNum; i++)
	{
		for (int j = 0; j < rowNum; j++)
		{
			for (auto array : mapArray[i][j])
			{
				if(array != nullptr)
					delete array;
			}
			mapArray[i][j].clear();
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
	Input(dt);

	if (!isScenePlay)
		return;

	for (int i = 0; i < colNum; i++)
	{
		for (int j = 0; j < rowNum; j++)
		{
			for (auto array : mapArray[i][j])
			{
				array->Update(dt);
			}
		}
	}

	for (int i = 0; i < uiTool.size(); i++)
	{
		for (int j = 0; j < uiTool[i].size(); j++)
		{
			if (uiTool[i][j].first != nullptr && uiTool[i][j].first->GetActive())
				uiTool[i][j].first->Update(dt);		
		}
	}
}

void EditScene::Draw(RenderWindow& window)
{
	///////////////////////////// ¿ùµåºä
	window.setView(worldView);

	for (int i = 0; i < colNum; i++)
	{
		for (int j = 0; j < rowNum; j++)
		{
			if (mapArray[i][j].empty())
				continue;
			for (auto array : mapArray[i][j])
			{
				array->Draw(window);
			}
		}
	}
	DrawOutLine(window);

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
	window.draw(uiMove);
}


void EditScene::InitTool()
{
	for (int i = 0; i < mapArray.size(); i++)
	{
		for (int j = 0; j < mapArray[i].size(); j++)
		{
			mapArray[i][j].push_back(new SpriteObj);
			mapArray[i][j].back()->SetResourceTexture("Graphics/grid.png");
			mapArray[i][j].back()->SetActive(false);
		}
	}

	for (int i = 0; i < colNum; i++)
	{
		for (int j = 0; j < rowNum; j++)
		{
			mapArray[i][j].back()->SetActive(true);
		}
	}

	SetToolPos();
}

void EditScene::SetToolPos()
{
	if (mapArray.empty())
		return;
	
	Vector2u size = RESOURCEMGR->GetTexture("Graphics/grid.png")->getSize();	

	for (int i = 0; i < colNum; i++)
	{
		for (int j = 0; j < rowNum; j++)
		{
			Vector2f pos = { (float)size.x * j, (float)size.y * (-i) };
			mapArray[i][j].back()->SetPos(pos + startPos);
		}
	}

	topLine.setPosition(mapArray[colNum - 1][0].back()->GetPos());
	topLine.setSize({ (float)size.x * rowNum , 1.f });
	leftLine.setPosition(topLine.getPosition());
	leftLine.setSize({ 1.f, (float)size.y * colNum });

	Vector2f fixPos;
	fixPos = { (float)size.x, 0.f };
	rightLine.setPosition(mapArray[colNum - 1][rowNum - 1].back()->GetPos() + fixPos);
	rightLine.setSize(leftLine.getSize());	
	fixPos = { 0.f, (float)size.y - 1.f};
	bottomLine.setPosition(mapArray[0][0].back()->GetPos() + fixPos);
	bottomLine.setSize(topLine.getSize());
}

void EditScene::SetToolSize()
{
	for (int i = 0; i < mapArray.size(); i++)
	{
		for (int j = 0; j < mapArray[i].size(); j++)
		{
			for (auto array : mapArray[i][j])
			{
				array->SetActive(false);
			}
		}
	}

	for (int i = 0; i < colNum; i++)
	{
		for (int j = 0; j < rowNum; j++)
		{
			for (auto array : mapArray[i][j])
			{
				array->SetActive(true);
			}
		}
	}

	SetToolPos();
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
		worldView.zoom(0.95f);		
	}
	if (InputMgr::GetMouseWheelState() == -1)
	{		
		if (zoomCount < -3)
			return;
		zoomCount--;
		worldView.zoom(1.05f);
	}

	if (InputMgr::GetKeyDown(Keyboard::Numpad6))
	{
		rowNum++;
		SetToolSize();
	}
	if (InputMgr::GetKeyDown(Keyboard::Numpad4))
	{
		if (rowNum <= 1)
			return;
		rowNum--;
		SetToolSize();
	}
	if (InputMgr::GetKeyDown(Keyboard::Numpad8))
	{
		colNum++;
		SetToolSize();
	}
	if (InputMgr::GetKeyDown(Keyboard::Numpad2))
	{
		if (colNum <= 1)
			return;
		colNum--;
		SetToolSize();
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
}

void EditScene::SetUiToolPos(Vector2f pos)
{
	uiOutLine.setPosition(pos);
	uiBackGround.setPosition(pos);
	uiMove.setPosition(pos);

	for (int i = 0; i < uiTool.size(); i++)
	{
		for (int j = 0; j < uiTool[i].size(); j++)
		{
			Vector2f setPos = { 75.f * j, 75.f * i };
			uiTool[i][j].second.setPosition(setPos + pos);
		}
	}
}
