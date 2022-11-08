#pragma once
#include "SFML/Graphics.hpp"
#include "Scene.h"
#include "../FrameWork/Utils.h"
#include <vector>

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
	void SetTool(int row, int col);
	void SetToolPos();
private:
	vector<vector<list<SpriteObj*>>> toolArray;
};

