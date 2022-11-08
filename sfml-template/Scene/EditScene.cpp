#include "EditScene.h"
#include "../FrameWork/stdafx.h"
#include "SceneMgr.h"
#include "../FrameWork/InputMgr.h"
#include "../Objects/SpriteObj.h"
#include "../Manager/ResourceMgr.h"
#include "../FrameWork/Const.h"

EditScene::EditScene()
{
	Init();
}

EditScene::~EditScene()
{
	
}

void EditScene::Init()
{	
	SetTool(25, 20);
	SetToolPos();	
}

void EditScene::Release()
{
}

void EditScene::Enter()
{	
	cout << "this is EditScene" << endl;
}

void EditScene::Exit()
{

}

void EditScene::Update(float dt)
{	
	if (InputMgr::GetKeyDown(Keyboard::Escape)) 
	{
		SCENE_MGR->ChangeScene(Scenes::GAMESTART);
	}
	if (InputMgr::GetKeyDown(Keyboard::BackSpace))
	{
		exit(1);
	}

	for (int i = 0; i < toolArray.size(); i++)
	{
		for (int j = 0; j < toolArray[i].size(); j++)
		{
			for (auto array : toolArray[i][j])
			{
				array->Update(dt);
			}
		}
	}

	Vector2f mousPos = InputMgr::GetMousePos();	
}

void EditScene::Draw(RenderWindow& window)
{
	for (int i = 0; i < toolArray.size(); i++)
	{
		for (int j = 0; j < toolArray[i].size(); j++)
		{
			for (auto array : toolArray[i][j])
			{
				array->Draw(window);
			}
		}
	}
}

void EditScene::SetTool(int row, int col)
{
	for (int i = 0; i < col; i++)
	{
		vector<list<SpriteObj*>> horizon;

		for (int j = 0; j < row; j++)
		{
			list<SpriteObj*> objList;
			objList.push_back(new SpriteObj);
			objList.back()->SetResourceTexture("Graphics/grid.png");
			horizon.push_back(objList);
		}
		toolArray.push_back(horizon);
	}
}

void EditScene::SetToolPos()
{
	if (toolArray.empty())
		return;

	Vector2u size = RESOURCEMGR->GetTexture("Graphics/grid.png")->getSize();
	int colNum = toolArray.size();
	int rowNum = toolArray[0].size();
		
	float StartY = ((float)WINDOW_HEIGHT - colNum * size.y) * 0.5f;
	float StartX = ((float)WINDOW_WIDTH - rowNum * size.x) * 0.5f;

	Vector2f StartPos = { StartX, StartY };

	for (int i = 0; i < colNum; i++)
	{
		for (int j = 0; j < rowNum; j++)
		{
			Vector2f curPos = { (float)size.x * j, (float)size.y * i };
			toolArray[i][j].back()->SetPos({ curPos + StartPos });
		}
	}
}
