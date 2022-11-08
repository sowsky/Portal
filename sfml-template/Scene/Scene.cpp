#include "Scene.h"
#include "../Framework/Framework.h"

Scene::Scene()
{
}

Scene::~Scene()
{
	Release();

}

void Scene::Release()
{
	
}

void Scene::Update(float dt)
{
	
}

void Scene::Draw(RenderWindow& window)
{

}

Vector2f Scene::ScreenToWorldPos(Vector2i screenPos)
{
	RenderWindow& window = FRAMEWORK->GetWindow();
	return window.mapPixelToCoords(screenPos, worldView);
}

Vector2f Scene::ScreenToUiPos(Vector2i screenPos)
{
	RenderWindow& window = FRAMEWORK->GetWindow();
	return window.mapPixelToCoords(screenPos, uiView);
}
Vector2i Scene::UiPosToScreen(Vector2f UiPos)
{
	RenderWindow& window = FRAMEWORK->GetWindow();
	return window.mapCoordsToPixel(UiPos, uiView);
}

