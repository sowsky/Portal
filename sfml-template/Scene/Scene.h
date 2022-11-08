#pragma once
#include <SFML/Graphics.hpp>
#include <list>

using namespace sf;
using namespace std;

class Scene
{
protected:

	View worldView;
	View uiView;

public:
	Scene();
	virtual ~Scene();

	virtual void Init() = 0;	// ����
	virtual void Release();		// ����

	virtual void Enter() = 0;
	virtual void Exit() = 0;

	virtual void Update(float dt);
	virtual void Draw(RenderWindow& window);

	Texture* GetTexture(const string& id);

	View& GetWorldView() { return worldView;  }
	View& GetUiView() { return uiView; }

	Vector2f ScreenToWorldPos(Vector2i screenPos);
	Vector2f ScreenToUiPos(Vector2i screenPos);
	Vector2i UiPosToScreen(Vector2f UiPos);

		
};

