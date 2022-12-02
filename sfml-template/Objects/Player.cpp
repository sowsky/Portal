#include "Player.h"
#include "../FrameWork/InputMgr.h"
#include "../FrameWork/Utils.h"
#include "../FrameWork/stdafx.h"
#include "../FrameWork/Const.h"
#include "../Manager/ResourceMgr.h"

Player::Player()
{
	SetResourceTexture("Graphics/player.png");
	id = 'p';

	hitbox = new RectangleShape;
	hitbox->setFillColor(Color::Red);

	objSize = ObjectSize::Carriable;
	attatchedPos = Rotate::Down;
}

Player::Player(b2World* world, const Vector2f& position, Vector2f dimensions)
{
	SetResourceTexture("Graphics/player.png");
	id = 'p';

	hitbox = new RectangleShape;
	hitbox->setFillColor(Color::Red);
	Utils::SetSpriteSize(sprite, dimensions);
	Utils::SetOrigin(sprite, Origins::BC);

	////////////////////////////////////////////////////////////////////////
	b2BodyDef bodyDef;
	bodyDef.type = b2_dynamicBody;
	bodyDef.position.Set(position.x / SCALE, position.y / SCALE * -1);
	body = world->CreateBody(&bodyDef);

	FloatRect bound = sprite.getGlobalBounds();
	float radius = bound.width * 0.5f;

	b2PolygonShape boxShape;

	b2Vec2 center(0, 0);
	center.y = (bound.height - radius) / 2 - (bound.height / 2 - radius) - 5;
	center.y /= SCALE;

	boxShape.SetAsBox(
		dimensions.x / SCALE / 2.0f,
		dimensions.y / SCALE / 2.0f,
		center, 0.f);

	b2FixtureDef fixtureDef;
	fixtureDef.shape = &boxShape;
	fixtureDef.density = 1.0f;
	fixtureDef.friction = 0.2f;
	fixture = body->CreateFixture(&fixtureDef);

	body->SetFixedRotation(true);

	b2CircleShape circleShape;
	circleShape.m_radius = radius / SCALE;
	circleShape.m_p.Set(0, -(bound.height / 2 - radius) / SCALE); //position, relative to body position

	b2FixtureDef circlefixtureDef;
	circlefixtureDef.shape = &circleShape;
	circlefixtureDef.density = 1.0f;
	circlefixtureDef.friction = 0.2f;
	fixture = body->CreateFixture(&circlefixtureDef);
	body->SetFixedRotation(true);

	Utils::ChangeBCSpriteSFMLPosToBox2dPos(*this, *body, 1 / 60.f);

	float tempx = position.x;
	float tempy = position.y;
	SetPos({ tempx,tempy });
	hitbox->setPosition(GetPos());

	SetSpriteTex(p_head, "Graphics/bendy/head.png");
	SetSpriteTex(p_body, "Graphics/bendy/body.png");
	SetSpriteTex(p_lleg, "Graphics/bendy/leg.png");
	SetSpriteTex(p_rleg, "Graphics/bendy/leg.png");
	SetSpriteTex(portalGun, "Graphics/bendy/portalgun.png");

	head_normal = RESOURCEMGR->GetTexture("Graphics/bendy/headn.png");
	body_normal = RESOURCEMGR->GetTexture("Graphics/bendy/bodyn.png");
	arm_normal = RESOURCEMGR->GetTexture("Graphics/bendy/armn.png");
	leg_normal = RESOURCEMGR->GetTexture("Graphics/bendy/legn.png");

	p_head.setScale(0.3f, 0.3f);
	Utils::SetOrigin(p_head, Origins::MC);
	p_body.setScale(0.3f, 0.3f);
	Utils::SetOrigin(p_body, Origins::BC);
	p_arm.setSize({ 10.f, 4.5f });
	p_arm.setFillColor(Color::Black);
	Utils::SetOrigin(p_arm, Origins::ML);

	p_lleg.setScale(0.3f, 0.3f);
	p_rleg.setScale(0.3f, 0.3f);

	pelvis.setSize({ Utils::GetSpriteSize(p_body).x * 0.45f, 1.f });
	Utils::SetOrigin(pelvis, Origins::BC);
	pelvis.setFillColor(Color::Blue);

	float spineHeight = 29.2f;
	spine1.setSize({ 1.f, spineHeight - 13.f });
	spine1.setFillColor(Color::Blue);
	Utils::SetOrigin(spine1, Origins::BL);

	spine2.setSize({ 1.f, spineHeight - spine1.getSize().y });
	spine2.setFillColor(Color::Blue);
	Utils::SetOrigin(spine2, Origins::BL);

	clavicle.setSize({ Utils::GetSpriteSize(p_body).x * 0.6f, 1.f });
	clavicle.setFillColor(Color::Blue);
	Utils::SetOrigin(clavicle, Origins::MC);
	Utils::SetOrigin(p_lleg, Origins::TC);

	armBorn.setSize({ 5.4f, 0.1f });
	armBorn.setFillColor(Color::Blue);

	indicator.setSize({ 20.f, 0.1f });
	indicator.setFillColor(Color::Blue);

	Utils::SetOrigin(p_rleg, Origins::TC);
	Utils::SetOrigin(p_arm, Origins::ML);

	Utils::SetOrigin(portalGun, Origins::ML);
	portalGun.setScale(0.3f, 0.3f);


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

	dir.x = InputMgr::GetAxis(Axis::Horizontal);

	Utils::ChangeBCSpriteSFMLPosToBox2dPos(*this, *body, dt);

	Utils::SetOrigin(*hitbox, Origins::BC);
	hitbox->setSize({ GetSize() });
	hitbox->setPosition(GetPos());

	if (body->GetLinearVelocity().x != 0) {
		if (abs(recentspeed.x) <= maximumspeed)
			recentspeed.x = body->GetLinearVelocity().x;
		speedtX = 0;
	}

	if (body->GetLinearVelocity().y != 0) {
		if (abs(recentspeed.y) <= maximumspeed)
			recentspeed.y = body->GetLinearVelocity().y;
		speedtY = 0;
	}

	speedtX += dt;
	speedtY += dt;
	if (speedtX >= 0.2f) {
		recentspeed.x = 0;
		speedtX = 0;

	}
	if (speedtY >= 0.2f) {
		recentspeed.y = 0;
		speedtY = 0;
	}

	UpdatePlayerPos(dt);

	if (InputMgr::GetKeyDown(Keyboard::P))
		devMod = !devMod;
}

void Player::PhysicsUpdate(float dt)
{
	if ((InputMgr::GetKey(Keyboard::A) || InputMgr::GetKey(Keyboard::D)) && body->GetLinearVelocity().y == 0) {
		body->ApplyLinearImpulse({ 0,0.5f }, GetPlayerBodyLinearVelocity(), 1);
		cout << body->GetLinearVelocity().x << endl;
		if ((int)body->GetLinearVelocity().x == 0 && (int)recentspeed.y > 0) {
			body->SetLinearVelocity({ body->GetLinearVelocity().x,0 });
		}
	}
	if (dir.x != 0)
	{
		IsMoving = true;
		if (body->GetLinearVelocity().x <= 2.5 && body->GetLinearVelocity().x >= -2.5) {
			body->ApplyForce(b2Vec2({ dir.x * 10 ,0.f }), body->GetWorldCenter(), true);
		}

	}
	else
	{
		IsMoving = false;
	}
	
	

	jumpcooltime += dt;
	if ((int)recentspeed.y >= 4) {
		jumpcooltime = 0;
	}
	if (jumpcooltime >= 0.8) {
		if (InputMgr::GetKeyDown(Keyboard::Space) && (int)abs(recentspeed.y) <= 1) {
			body->ApplyLinearImpulse({ 0,3.f }, GetPlayerBodyLinearVelocity(), 1);
			jumpcooltime = 0;
		}
	}


}

void Player::Draw(RenderWindow& window)
{

	if (!isPlayingGame)
		SpriteObj::Draw(window);

	RotateAnimation(window);

	//window.draw(*hitbox);

	//window.draw(*hitbox);	

	window.draw(p_body);
	window.draw(p_lleg);
	window.draw(p_rleg);
	window.draw(p_head);
	window.draw(p_arm);
	window.draw(portalGun);
	if (devMod)
		ShowBornForDev(window);

}

void Player::Draw(RenderTexture& diffuse, Shader& nShader, RenderTexture& normal)
{
	//diffuse.draw(p_body);
	//NormalPass(normal, p_body, body_normal, nShader);
	//diffuse.draw(p_lleg);
	//NormalPass(normal, p_lleg, leg_normal, nShader);
	//diffuse.draw(p_rleg);
	//NormalPass(normal, p_rleg, leg_normal, nShader);
	//diffuse.draw(p_head);
	//NormalPass(normal, p_head, head_normal, nShader);
	//diffuse.draw(p_arm);
	//NormalPass(normal, p_arm, arm_normal, nShader);
}

void Player::SetPlayerBodyPos(Vector2f pos)
{
	b2Vec2 newPos({ pos.x / SCALE,pos.y / SCALE * -1 });
	body->SetTransform(newPos, 0);
}

void Player::SetPlayerBodyLinearVelocityForce(b2Vec2 force)
{
	body->ApplyLinearImpulse(force, body->GetWorldCenter(), true);

}

void Player::UpdatePlayerPos(float dt)
{
	Vector2f pos = sprite.getPosition();

	pelvis.setPosition(pos.x, pos.y - 11.f);
	p_body.setPosition(pelvis.getPosition().x, pelvis.getPosition().y + 3.5f);
	p_lleg.setPosition(pelvis.getTransform().transformPoint(pelvis.getPoint(3)));
	p_rleg.setPosition(pelvis.getTransform().transformPoint(pelvis.getPoint(2)));

	spine1.setPosition(pelvis.getPosition());
	spine2.setPosition(spine1.getTransform().transformPoint(spine1.getPoint(0)));

	clavicle.setPosition(spine2.getPosition());
	p_head.setPosition(spine2.getTransform().transformPoint(spine2.getPoint(0)));

	WalkAnimaton(dt);
}

void Player::WalkAnimaton(float dt)
{
	if (!IsMoving /*|| recentspeed.y*/)
	{
		startMove = false;
		p_rleg.setScale(0.3f, 0.3f);
		p_lleg.setScale(0.3f, 0.3f);
		return;
	}

	if (!startMove)
	{
		if (dir.x > 0)
			p_rleg.setScale(0.3f, 0.25f);
		if (dir.x < 0)
			p_lleg.setScale(0.3f, 0.25f);
		startMove = true;
	}

	groundTime -= dt;
	if (groundTime < 0)
		p_rleg.setScale(0.3f, p_rleg.getScale().y + legdir * 0.3f * dt);

	if (p_rleg.getScale().y > 0.3f)
	{
		p_rleg.setScale(0.3f, 0.3f);
		legdir *= -1;
		groundTime = groundTimeMax;
	}

	if (p_rleg.getScale().y < 0.25f)
	{
		p_rleg.setScale(0.3f, 0.25f);
		legdir *= -1;
		groundTime = groundTimeMax;
	}

	p_lleg.setScale(0.3f, 0.55f - p_rleg.getScale().y);
}

void Player::RotateAnimation(RenderWindow& window)
{
	Vector2f mousePos =
		window.mapPixelToCoords((Vector2i)InputMgr::GetMousePos(), window.getView());

	bool right = mousePos.x > pelvis.getPosition().x;
	Vector2f armPos = right ? clavicle.getPoint(1) : clavicle.getPoint(0);

	p_arm.setPosition(clavicle.getTransform().transformPoint(armPos));
	p_arm.setRotation(Utils::Angle(p_arm.getPosition(), mousePos));

	armBorn.setPosition(p_arm.getPosition());
	armBorn.setRotation(p_arm.getRotation());

	portalGun.setPosition(armBorn.getTransform().transformPoint(armBorn.getPoint(1)));
	portalGun.setRotation(armBorn.getRotation());

	indicator.setPosition(armBorn.getTransform().transformPoint(armBorn.getPoint(1)));
	indicator.setRotation(armBorn.getRotation());

	float spineRotation = Utils::Angle(spine1.getPosition(), mousePos);
	float interpolation = 0.25f;
	if (right)
	{
		spineRotation *= interpolation;
		if (20.f < spineRotation)
			spineRotation = 20.f;
		if (-20.f > spineRotation)
			spineRotation = -20.f;

		portalGun.setScale(0.3f, 0.3f);
	}
	else
	{
		spineRotation += 180;
		if (spineRotation > 0.f && spineRotation < 180.f)
			spineRotation *= interpolation;
		if (spineRotation > 20.f && spineRotation < 180.f)
			spineRotation = 20.f;

		if (spineRotation > 180.f && spineRotation < 360.f)
		{
			spineRotation -= 360.f;
			spineRotation *= interpolation;
			spineRotation += 360.f;
		}

		if (spineRotation > 180.f && spineRotation < 340.f)
			spineRotation = 340.f;

		portalGun.setScale(0.3f, -0.3f);
	}

	spine1.setRotation(spineRotation);

	p_body.setRotation(spine1.getRotation());
	clavicle.setRotation(spine1.getRotation());
	spine2.setRotation(spine1.getRotation() * 3.f);


}

void Player::ShowBornForDev(RenderWindow& window)
{
	window.draw(pelvis);
	window.draw(spine1);
	window.draw(spine2);
	window.draw(clavicle);
	window.draw(armBorn);
	window.draw(indicator);
}

Vector2f Player::GetIndicator()
{
	return indicator.getTransform().transformPoint(p_arm.getPoint(1));
}
