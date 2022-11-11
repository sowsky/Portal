#pragma once
#include "SFML/Graphics.hpp"
#include "Scene.h"
#include "../FrameWork/Utils.h"
#include <vector>
#include <array>

class SpriteObj;
class EditScene : public Scene
{
public:
	EditScene();
	~EditScene();

	virtual void Init();	// ����
	virtual void Release();		// ����

	virtual void Enter();
	virtual void Exit();

	virtual void Update(float dt);
	virtual void Draw(RenderWindow& window);
	
public:
	void DrawWorldView(RenderWindow& window);
	void DrawUiView(RenderWindow& window);
	void DrawWire(RenderWindow& window);

	void InitMapTool();	
	void ReleaseMapTool();

	void SetMapToolPos();
	void SetMapToolSize();
	void FillMapTool();
	void UpdateMapTool(float dt);
	void DrawOutLine(RenderWindow& window);

	void Input(float dt);

	void InitUiTool();	
	void ReleaseUiTool();
	void UpdateUiTool(float dt);
	
	void FillUiToolBox();
	void SetUiToolPos(Vector2f pos);

	void MouseSpriteBoxUpdate();

	void Save();
	void Load();

private:	
	int rowNum;
	int colNum;
	Vector2f startPos;

	array<array<pair<list<SpriteObj*>, SpriteObj*>, 100>, 100> mapTool;

	RectangleShape topLine;
	RectangleShape leftLine;
	RectangleShape rightLine;
	RectangleShape bottomLine;	

	Sprite background;
	Sprite shadow;
	
	array<array<pair<SpriteObj*, Sprite>, 4>, 8> uiTool;
	Sprite uiOutLine;
	RectangleShape uiBackGround;
	Sprite uiMove;
	Sprite uiOpenClose;

	array<array<SpriteObj*, 4>, 8> wireTool;

	SpriteObj* mouseBoxSprite;

	SpriteObj* mapToolCheckBox;
	SpriteObj* uiToolCheckBox;
	SpriteObj* crossUiCheckBox;

	bool isScenePlay;

	int zoomCount;		

	bool isGridOn;
	bool isUiMoving;
	bool isUiOpen;
	bool mouseOnUi;
};

