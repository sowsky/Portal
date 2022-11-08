#include "EditScene.h"
#include "../FrameWork/stdafx.h"
#include "SceneMgr.h"
#include "../FrameWork/InputMgr.h"

EditScene::EditScene()
{
	Init();
}

EditScene::~EditScene()
{
}

void EditScene::Init()
{
	
}

void EditScene::Release()
{
}

void EditScene::Enter()
{
}

void EditScene::Update(float dt)
{
	cout << "this is EditScene" << endl;
	if (InputMgr::GetKeyDown(Keyboard::Escape)) {
		SCENE_MGR->ChangeScene(Scenes::GAMESTART);
	}
}

void EditScene::Exit()
{
}

void EditScene::draw(RenderWindow& window)
{
}

void EditScene::update(float dt)
{
}
