#include "SceneMgr.h"
#include "StartMenu.h"
#include "EditScene.h"

bool SceneMgr::Init()
{
    Scene* startMenu=new StartMenu();
    sceneMap.insert({ Scenes::GAMESTART,startMenu });
    Scene* editScene = new EditScene();
    sceneMap.insert({ Scenes::MAPEDITER,editScene });

    currScene = Scenes::GAMESTART;
    sceneMap[currScene]->Enter();

    return true;
}

Scene* SceneMgr::GetCurrScene() 
{
    return sceneMap[currScene];
}

Scene* SceneMgr::GetScene(Scenes scene)
{
    return sceneMap[scene];
}

Scenes SceneMgr::GetCurrKey()
{
    return currScene;
}

void SceneMgr::ChangeScene(Scenes scene)
{
    sceneMap[currScene]->Exit();
    currScene = scene;
    sceneMap[currScene]->Enter();
}

void SceneMgr::Update(float dt)
{
    sceneMap[currScene]->Update(dt);
}

void SceneMgr::Draw(RenderWindow& window)
{
    sceneMap[currScene]->Draw(window);
}
