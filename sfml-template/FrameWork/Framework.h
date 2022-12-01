#pragma once
#include "../3rd/Singleton.h"
#include <SFML/Graphics.hpp>
#include <box2d/box2d.h>

using namespace sf;
using namespace std;
class Framework : public Singleton<Framework>
{
protected:
	RenderWindow window;
	Vector2i windowSize;

	Clock clock;
	Time deltaTime;
	float timeScale;
	int fps = 0;
	float time = 0;

public:
	Framework();
	virtual ~Framework();

	float GetDT() const;
	float GetRealDT() const;
	const Vector2i& GetWindowSize() const;
	RenderWindow& GetWindow();

	bool Init(int width, int height);
	bool Do();
};

#define FRAMEWORK (Framework::GetInstance())