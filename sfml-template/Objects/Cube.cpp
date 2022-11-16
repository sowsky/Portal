#include "Cube.h"
#include "../FrameWork/Const.h"

Cube::Cube()
{
	SetResourceTexture("Graphics/cube.png");
	id = 'c';
	
	hitbox = new RectangleShape;
	hitbox->setFillColor(Color::Red);
}

Cube::Cube(b2World* world, const Vector2f& position, Vector2f dimensions)
{
	SetResourceTexture("Graphics/cube.png");
	id = 'c';

	Utils::SetSpriteSize(sprite, dimensions);
	Utils::SetOrigin(sprite, Origins::BC);
	hitbox = new RectangleShape;
	hitbox->setFillColor(Color::Red);

	b2BodyDef bodyDef;
	bodyDef.type = b2_dynamicBody;
	bodyDef.position.Set(position.x, position.y * -1);
	body = world->CreateBody(&bodyDef);

	b2PolygonShape boxShape;
	boxShape.SetAsBox(dimensions.x / 2.0f, dimensions.y / 2.0f);

	b2FixtureDef fixtureDef;
	fixtureDef.shape = &boxShape;
	fixtureDef.density = 1.0f;
	fixtureDef.friction = 0.3f;
	fixture = body->CreateFixture(&fixtureDef);

	sprite.setPosition({ body->GetPosition().x, body->GetPosition().y*-1});
	hitbox->setPosition({ body->GetPosition().x, body->GetPosition().y*-1 });
}

Cube::~Cube()
{
	//delete fixture;
	delete hitbox;
}

SpriteObj* Cube::NewThis()
{
	return new Cube;
}

void Cube::Update(float dt)
{
	Utils::SetOrigin(*hitbox, Origins::BC);

	sprite.setRotation(body->GetAngle());
	Utils::ChangeBCSpriteSFMLPosToBox2dPos(sprite,*body);

	hitbox->setSize({ sprite.getGlobalBounds().width,sprite.getGlobalBounds().height });
	hitbox->setPosition(sprite.getPosition());

}

void Cube::PhysicsUpdate()
{
}

void Cube::Draw(RenderWindow& window)
{
	SpriteObj::Draw(window);
	window.draw(*hitbox);
}
