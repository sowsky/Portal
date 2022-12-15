#pragma once

#include "SFML/Graphics.hpp"
#include "Scene.h"
#include "../FrameWork/Utils.h"
#include "../Objects/SpriteObj.h"
#include "../Objects/Player.h"
#include "../Manager/SoundMgr.h"

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

	////////////////////

	void InitOptionSetting();
	void UpdateOption();
	void DrawOption(RenderWindow& window);

private:
	vector<Text*> stagelist;

	Sprite back;
	Sprite stagespace;
	Sprite play;
	Sprite option;
	Sprite exit;

	int y;

	int count = 1;

	bool playon =false;
	bool optionon = false;

	Vector2f optionPos;

	Sprite optionMain;
	Sprite scroll;
	Sprite scrollButton;
	Sprite indicatorOn;
	Sprite indicatorOff;
	Sprite soundOn;
	Sprite soundOff;

	Texture* blank;
	Texture* checkered;

	bool isIndicatorOn = true;
	bool isSoundOn = true;
	bool isScrolling = false;

	int& volume = SOUNDMGR->GetVolumeInt();

};

