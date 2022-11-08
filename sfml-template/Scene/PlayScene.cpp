#include "PlayScene.h"
#include <fstream>
#include "../FrameWork/stdafx.h"
#include "../FrameWork/InputMgr.h"
#include "SceneMgr.h"
void PlayScene::Update(float dt)
{
	if (InputMgr::GetKeyDown(Keyboard::Escape)) {
		SCENE_MGR->ChangeScene(Scenes::GAMESTART);
	}
}

void PlayScene::Draw(RenderWindow& window)
{

}

PlayScene::PlayScene(string path)
{
	ifstream fin;
	fin.open(path);

	string str;
	while (getline(fin, str)) {
		for (int i = 0; i < str.size(); i++) {
			cout << str[i] << endl;
		}

	}

	fin.close();

}

PlayScene::~PlayScene()
{

}

void PlayScene::Init()
{
}

void PlayScene::Release()
{
}

void PlayScene::Enter()
{

}

void PlayScene::Exit()
{
}
