#include "Player.h"
#include "../FrameWork/InputMgr.h"
#include "../FrameWork/Utils.h"
#include "../FrameWork/stdafx.h"


Player::Player()
{
	SetResourceTexture("Graphics/player.png");
	id = 'p';

	hitbox = new RectangleShape;
	hitbox->setFillColor(Color::Red);
}

Player::Player(b2World* world, const Vector2f& position, Vector2f dimensions)
{
	SetResourceTexture("Graphics/player.png");
	id = 'p';

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
	fixtureDef.friction = 0.2f;
	fixture = body->CreateFixture(&fixtureDef);
	body->SetFixedRotation(true);

	Utils::ChangeBCSpriteSFMLPosToBox2dPos(sprite, *body);
	hitbox->setPosition(sprite.getPosition());
}

Player::~Player()
{
	delete hitbox;
}

SpriteObj* Player::NewThis()
{
	return new Player;
}

void Player::Update(float dt)
{
	SpriteObj::Update(dt);
	Utils::SetOrigin(*hitbox, Origins::BC);

	Utils::ChangeBCSpriteSFMLPosToBox2dPos(sprite, *body);

	//Utils::ChangeBCSpriteSFMLPosToBox2dPos(sprite, *body);
	//cout << sprite.getPosition().x << " " << sprite.getPosition().y << endl;
	hitbox->setSize({ sprite.getGlobalBounds().width - 10,sprite.getGlobalBounds().height });
	hitbox->setPosition(sprite.getPosition());

	/*static int a;
	a += dt;
	cout << a << endl;
	if (a >= 1.0f) {*/
	//	a = 0;
	
}

void Player::PhysicsUpdate()
{
	if (InputMgr::GetKey(Keyboard::A)) {
		body->ApplyForce(b2Vec2({ 10000 * -333,GetPlayerBodyForce().y }), body->GetWorldCenter(), true);
	}
	else if (InputMgr::GetKey(Keyboard::D)) {
		body->ApplyForce(b2Vec2({ 10000 * 333,GetPlayerBodyForce().y }), body->GetWorldCenter(), true);
	}

	if (InputMgr::GetKeyDown(Keyboard::Space)&&(int)(body->GetLinearVelocity().y)==0) {
		//	body->ApplyLinearImpulse(b2Vec2({body->GetTransform().q.GetYAxis().x, 10000 * 333}), body->GetWorldCenter(), true);
		SetPlayerBodyForce({ GetPlayerBodyForce().x,10000000 });
	}
}

void Player::Draw(RenderWindow& window)
{
	SpriteObj::Draw(window);
	//window.draw(*hitbox);

}

void Player::SetPlayerBodyPos(Vector2f pos)
{
	b2Vec2 newPos({ pos.x,pos.y * -1 });
	body->SetTransform(newPos, 0);
}

void Player::SetPlayerBodyForce(b2Vec2 force)
{
	body->ApplyLinearImpulse(force, body->GetWorldCenter(), true);

}
