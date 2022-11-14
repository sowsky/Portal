#include "Player.h"
#include "../FrameWork/InputMgr.h"
#include "../FrameWork/Utils.h"
#include "../FrameWork/stdafx.h"

int Player::playerNum = 0;

Player::Player()
{
	SetResourceTexture("Graphics/player.png");
	id = 'p';

	playerNum++;

	hitbox = new RectangleShape;
	hitbox->setFillColor(Color::Red);	
}

Player::Player(b2World* world, const Vector2f& position, Vector2f dimensions)
{
	SetResourceTexture("Graphics/player.png");
	id = 'p';

	playerNum++;

	hitbox = new RectangleShape;
	hitbox->setFillColor(Color::Red);
	Utils::SetSpriteSize(sprite, dimensions);
	Utils::SetOrigin(sprite, Origins::BC);
	////////////////////////////////////////////
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

	Utils::ChangeBCSpriteSFMLPosToBox2dPos(sprite, *body);
	hitbox->setPosition({ body->GetPosition().x, body->GetPosition().y * -1 });
}

Player::~Player()
{
	playerNum--;

	delete hitbox;
}

SpriteObj* Player::NewThis()
{
	return new Player;
}


int Player::GetPlayerNum()
{
	return playerNum;

}

void Player::Update(float dt)
{
	SpriteObj::Update(dt);
	Utils::SetOrigin(*hitbox, Origins::BC);

	sprite.setRotation(body->GetAngle());
	Utils::ChangeBCSpriteSFMLPosToBox2dPos(sprite, *body);
	cout << sprite.getPosition().x << " " << sprite.getPosition().y << endl;
	hitbox->setSize({ sprite.getGlobalBounds().width - 10,sprite.getGlobalBounds().height });
	hitbox->setPosition(sprite.getPosition());
}

void Player::PhysicsUpdate()
{
	if (InputMgr::GetKey(Keyboard::A)) {
		body->ApplyForce(b2Vec2({ 1000 * -333,0 }), body->GetWorldCenter(), true);
	}else if (InputMgr::GetKey(Keyboard::D)) {
		body->ApplyForce(b2Vec2({ 1000 * 333,0 }), body->GetWorldCenter(), true);
	}

	if (InputMgr::GetKey(Keyboard::Space)) {
		body->ApplyForce(b2Vec2({body->GetTransform().q.GetYAxis().x, 1000 * 333}), body->GetWorldCenter(), true);
	}
}

void Player::Draw(RenderWindow& window)
{
	SpriteObj::Draw(window);
	window.draw(*hitbox);

}
