#pragma once

#include "SFML/Graphics.hpp"
#include "Scene.h"
#include "../FrameWork/Utils.h"
#include <vector>

class EditScene : public Scene
{
public:
	EditScene();
	~EditScene();

	virtual void Init();	// ����
	virtual void Release();		// ����

	virtual void Enter();
	virtual void Update(float dt);
	virtual void Exit();

	void draw(RenderWindow& window);
	void update(float dt);

private:
	RectangleShape* mousePos;
	

};

