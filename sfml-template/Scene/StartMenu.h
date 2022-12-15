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

	void LoadFile();

private:
	Sprite back;
	Sprite stagespace;
	Sprite play;
	Sprite option;
	Sprite exit;

	int count = 1;

	bool playon =false;
	bool optionon = false;
};

