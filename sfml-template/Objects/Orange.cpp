#include "Orange.h"

Orange::Orange()
{
	SetResourceTexture("Graphics/orange.png");

	Utils::SetOrigin(sprite, Origins::MC);

	hitbox = new RectangleShape;
	hitbox->setFillColor(Color::Red);
}

Orange::~Orange()
{
	delete hitbox;
}

void Orange::Update(float dt)
{
	Utils::SetOrigin(*hitbox, Origins::BC);

	hitbox->setSize({ sprite.getGlobalBounds().width - 10,sprite.getGlobalBounds().height });
	hitbox->setPosition(sprite.getPosition());

	
	Translate(direction * dt * projectilespeed);

}

void Orange::Draw(RenderWindow& window)
{
	SpriteObj::Draw(window);
	//window.draw(*hitbox);
}
