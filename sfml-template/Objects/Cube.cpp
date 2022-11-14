#include "Cube.h"

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

	hitbox = new RectangleShape;
	hitbox->setFillColor(Color::Red);

	b2BodyDef bodyDef;
	bodyDef.type = b2_dynamicBody;
	bodyDef.position.Set(position.x, position.y);
	body = world->CreateBody(&bodyDef);

	b2PolygonShape boxShape;
	boxShape.SetAsBox(dimensions.x / 2.0f, dimensions.y / 2.0f);

	b2FixtureDef fixtureDef;
	fixtureDef.shape = &boxShape;
	fixtureDef.density = 1.0f;
	fixtureDef.friction = 0.3f;
	fixture = body->CreateFixture(&fixtureDef);
}

Cube::~Cube()
{
	delete fixture;
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
	sprite.setPosition({ body->GetPosition().x,body->GetPosition().y});

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
