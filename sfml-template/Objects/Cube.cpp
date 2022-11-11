#include "Cube.h"

Cube::Cube()
{
	SetResourceTexture("Graphics/cube.png");
	id = 'c';

	hitbox = new RectangleShape;
	hitbox->setFillColor(Color::Red);
}

Cube::~Cube()
{
	delete hitbox;

}

SpriteObj* Cube::NewThis()
{
	return new Cube;
}

void Cube::Update(float dt)
{
	Utils::SetOrigin(*hitbox, Origins::BC);

	hitbox->setSize({ sprite.getGlobalBounds().width,sprite.getGlobalBounds().height });
	hitbox->setPosition(sprite.getPosition());

	if (!ground) {
		if (verticalspeed < 0) {//going up
			verticalspeed = verticalspeed + (dt * 100);
		}
		else {
			verticalspeed = verticalspeed + (dt * addspeed);
		}
		SetPos({ GetPos().x,GetPos().y + verticalspeed * dt });
	}
	else if (ground) {
		verticalspeed = 0;
	}
}

void Cube::Draw(RenderWindow& window)
{
	SpriteObj::Draw(window);
	window.draw(*hitbox);
}
