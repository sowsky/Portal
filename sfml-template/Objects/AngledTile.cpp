#include "AngledTile.h"

AngledTile::AngledTile()
{
	SetResourceTexture("Graphics/Ui/angletool.png");
	id = 'a';

	type = ObjectType::None;
	objSize = ObjectSize::Normal;
	attatchedPos = Rotate::Down;
}

AngledTile::AngledTile(b2World* world, Vector2f position, int angle)
{
	triangle.setPointCount(3);
	triangle.setPoint(0, Vector2f(0, 0));
	triangle.setPoint(1, Vector2f(GRIDSIZE, GRIDSIZE));
	triangle.setPoint(2, Vector2f(0, GRIDSIZE));

	Utils::SetOrigin(triangle, Origins::MC);
	triangle.setPosition(position);
	dir = angle;

	if (angle == 0) {
		triangle.setRotation(180);
	}
	else if (angle == 3) {
		triangle.setRotation(90);
	}
	else if (angle == 1) { 
		triangle.setRotation(270); 
	}

	hitbox.setFillColor(Color::Red);
	if (dir == 1 || dir == 3) {}


}

AngledTile::~AngledTile()
{
}

SpriteObj* AngledTile::NewThis()
{
	return new AngledTile;
}

void AngledTile::Update(float dt)
{
}

void AngledTile::Draw(RenderWindow& window)
{
	if (isPlayingGame)
	{
		window.draw(triangle);
		window.draw(hitbox);
	}
	else
	{
		window.draw(sprite);
	}
}
