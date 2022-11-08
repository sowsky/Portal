#pragma once
#include"Scene.h"

class MapList :public Scene
{
public:
	MapList();
	virtual ~MapList();

	virtual void Init();	// ����
	virtual void Release();		// ����

	virtual void Enter();
	virtual void Update(float dt);
	virtual void Exit();
	virtual void Draw(RenderWindow& window);

private:

};

