#include "Blue.h"

Blue::Blue()
{
	SetResourceTexture("Graphics/blue.png");
	Utils::SetOrigin(sprite, Origins::MC);
	hitbox = new RectangleShape;
	hitbox->setFillColor(Color::Red);
}

Blue::~Blue()
{
	delete hitbox;

}

void Blue::Update(float dt)
{
	Utils::SetOrigin(*hitbox, Origins::BC);

	hitbox->setSize({ sprite.getGlobalBounds().width - 10,sprite.getGlobalBounds().height });
	hitbox->setPosition(sprite.getPosition());

	Translate(direction *dt* projectilespeed);

}

void Blue::Draw(RenderWindow& window)
{
	SpriteObj::Draw(window);

}
