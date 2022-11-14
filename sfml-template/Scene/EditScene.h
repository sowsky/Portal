#pragma once
#include "SFML/Graphics.hpp"
#include "Scene.h"
#include "../FrameWork/Utils.h"
#include <vector>
#include <array>
#include "../Objects/WireableObject.h"
#include "../Objects/WirePointArrows.h"
#include "../Objects/Wire.h"

class SpriteObj;
//class WireableObject;
//class WirePointArrows;
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
	void DrawWireTool(RenderWindow& window);

	void InitMapTool();	
	void ReleaseMapTool();

	void InitWiringTool();
	void ReleaseWiringTool();
	void UpdateWiringTool(float dt);

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
	void Reset();
	void Load();

private:	
	int rowNum;
	int colNum;
	Vector2f startPos;	

	array<array<pair<list<SpriteObj*>, SpriteObj*>, 100>, 100> mapTool;
	array<array<pair<pair<Wire*, WirePointArrows*>, WireableObject*>, 100>, 100> wiringTool;

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
	RectangleShape wiringModGui;

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
	bool isWiring;
};

