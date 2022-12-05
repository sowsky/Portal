#pragma once

#include "SFML/Graphics.hpp"
#include "Scene.h"
#include "../FrameWork/Utils.h"
#include "../Objects/SpriteObj.h"
#include "../Objects/Player.h"

class StartMenu : public Scene
{
public:
	StartMenu();
	~StartMenu();

	virtual void Init() ;	// ����
	virtual void Release();		// ����

	virtual void Enter();
	virtual void Update(float dt);
	virtual void Exit();
	virtual void Draw(RenderWindow& window);

private:
	RectangleShape* editbox;
	RectangleShape* startbox;
	RectangleShape* mousePos;

	SpriteObj title;

	Text start;
	Text edit;

	Player* player;

	unique_ptr<b2World> world;


};

