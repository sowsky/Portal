#include "Cube.h"
#include "../FrameWork/Const.h"
#include "../FrameWork/stdafx.h"

Cube::Cube()
{
	SetResourceTexture("Graphics/cube.png");
	id = 'c';
	
	hitbox = new RectangleShape;
	hitbox->setFillColor(Color::Red);

	objSize = ObjectSize::Carriable;
	attatchedPos = Rotate::Down;
}

Cube::Cube(b2World* world, const Vector2f& position, Vector2f dimensions)
{
	SetResourceTexture("Graphics/cube.png");
	id = 'c';

	Utils::SetSpriteSize(sprite, dimensions);
	Utils::SetOrigin(sprite, Origins::BC);
	Utils::SetSpriteSize(sprite, { 30,30 });
	hitbox = new RectangleShape;
	hitbox->setFillColor(Color::Red);
	hitbox->setSize({ sprite.getGlobalBounds().width + 30,sprite.getGlobalBounds().height });

	b2BodyDef bodyDef;
	bodyDef.type = b2_dynamicBody;
	bodyDef.position.Set(position.x, position.y * -1);
	body = world->CreateBody(&bodyDef);

	b2PolygonShape boxShape;
	boxShape.SetAsBox(Utils::GetSpriteSize(sprite).x / 2.0f, Utils::GetSpriteSize(sprite).y / 2.0f);

	b2FixtureDef fixtureDef;
	fixtureDef.shape = &boxShape;
	fixtureDef.density = 1.0f;
	fixtureDef.friction = 1.0f;
	fixture = body->CreateFixture(&fixtureDef);

	sprite.setPosition({ body->GetPosition().x, body->GetPosition().y * -1 });
	hitbox->setPosition({ body->GetPosition().x, body->GetPosition().y * -1 });
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


void Cube::SetCubeBodyPos(Vector2f pos)
{
	b2Vec2 newPos({ pos.x,pos.y * -1 });
	body->SetTransform(newPos, 0);
}

void Cube::ChangeBodyTypeBetweenStaticAndDynamic(bool b)
{
	if (b) {
		body->SetType(b2BodyType::b2_staticBody);
		grab = true;
	}else{
		body->SetType(b2BodyType::b2_dynamicBody);
		grab = false;
	}
}

void Cube::Update(float dt)
{
	Utils::SetOrigin(*hitbox, Origins::BC);

	sprite.setRotation(body->GetAngle());
	Utils::ChangeBCSpriteSFMLPosToBox2dPos(sprite, *body);

	hitbox->setPosition(sprite.getPosition());


	//cout << body->GetLinearVelocity().y << endl;
}

void Cube::PhysicsUpdate()
{
}

void Cube::Draw(RenderWindow& window)
{

	SpriteObj::Draw(window);
	//window.draw(*hitbox);
}

void Cube::SetSide(bool s)
{
	side = s;
}

void Cube::SetCubeBodyForce(b2Vec2 force)
{
	body->ApplyLinearImpulse(force, body->GetWorldCenter(), true);

}

