#pragma once
#include <SFML/Graphics.hpp>
#include <array>

using namespace sf;
using namespace std;

class WirePointArrows
{
public:
	WirePointArrows();
	void Init();
	void SetPosition(Vector2f pos, float tileSize);
	void Update(float dt);
	void Draw(RenderWindow& window);

private:	
	Sprite up;
	Sprite left;
	Sprite right;
	Sprite down;
	array<Sprite, 4> arrowContainer;

	Vector2f position;
};

