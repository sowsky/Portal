#include "Cube.h"
#include "../FrameWork/Const.h"
#include "../FrameWork/stdafx.h"
#include "../Manager/ResourceMgr.h"

Cube::Cube()
	:sideFaces(frontFace, sprite)
{
	SetResourceTexture("Graphics/cube.png");
	id = 'c';
	
	hitbox = new RectangleShape;
	hitbox->setFillColor(Color::Red);

	objSize = ObjectSize::Carriable;
	attatchedPos = Rotate::Down;
}

Cube::Cube(b2World* world, const Vector2f& position, Vector2f dimensions)
	:sideFaces(frontFace, sprite),startpos(position)
{	
	SetResourceTexture("Graphics/cube.png");
	id = 'c';
	float cubeSize = 30.f;
	Vector2f cubeSizeV2f = { cubeSize,cubeSize };

	Utils::SetSpriteSize(sprite, dimensions);
	Utils::SetOrigin(sprite, Origins::MC);
	Utils::SetSpriteSize(sprite, cubeSizeV2f);
	hitbox = new RectangleShape;
	hitbox->setFillColor(Color::Red);
	hitbox->setSize({ sprite.getGlobalBounds().width + cubeSize,sprite.getGlobalBounds().height });

	b2BodyDef bodyDef;
	bodyDef.type = b2_dynamicBody;
	bodyDef.position.Set(position.x/SCALE, position.y/SCALE* -1);
	bodyDef.bullet = true;
	body = world->CreateBody(&bodyDef);

	b2PolygonShape boxShape;
	boxShape.SetAsBox(30.f/ SCALE / 2.0f, cubeSize / SCALE / 2.0f);

	b2FixtureDef fixtureDef;
	fixtureDef.shape = &boxShape;
	fixtureDef.density = 1.0f;
	fixtureDef.friction = 1.0f;
	fixture = body->CreateFixture(&fixtureDef);

	Utils::ChangeBCSpriteSFMLPosToBox2dPos(*this, *body,1/60.f);

	float tempx = position.x;
	float tempy = position.y;
	SetPos({ tempx,tempy });
	hitbox->setPosition(GetPos());

	///////
	Vector2f frontSize = { cubeSizeV2f.x / DEPTH, cubeSizeV2f.y / DEPTH };

	SetSpriteTex(frontFace, "Graphics/temp/cube.png");
	Utils::SetOrigin(frontFace, Origins::MC);
	Utils::SetSpriteSize(frontFace, frontSize);
	normal = RESOURCEMGR->GetTexture("Graphics/temp/cuben.png");

	sideFaces.SetDepth(DEPTH + 0.005f);
	sideFaces.SetAllSidesTex("Graphics/temp/cube.png");
	sideFaces.SetBackFaceSize(frontSize);
	sideFaces.SetBackFaceOrigin(Origins::MC);
}

void Cube::Respawn()
{
	body->SetTransform({ startpos.x / SCALE,(startpos.y-10) / SCALE * -1 }, 0);
	body->SetLinearVelocity({ 0,-1 });
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
	b2Vec2 newPos({ pos.x/SCALE,pos.y/SCALE * -1 });
	body->SetTransform(newPos, 0);
}

void Cube::ChangeBodyTypeBetweenStaticAndDynamic(bool b)
{
	if (b) {
		body->SetType(b2BodyType::b2_kinematicBody);
		grab = true;
	}else{
		body->SetType(b2BodyType::b2_dynamicBody);
		grab = false;
	}
}

void Cube::Update(float dt)
{
	Utils::SetOrigin(*hitbox, Origins::MC);

	Vector2f temp(body->GetPosition().x * SCALE, (body->GetPosition().y * SCALE * -1));
	SetPos(temp);

	sprite.setRotation(180.0 * body->GetAngle()*-1 / M_PI);

	hitbox->setSize({ GetSize().x+10,GetSize().y});
	hitbox->setPosition(temp );

	if (body->GetLinearVelocity().x != 0) {
		if (maxspeed.x > body->GetLinearVelocity().x && abs(maxspeed.x) <= maximumspeed)
			maxspeed.x = body->GetLinearVelocity().x;
		speedtX = 0;
	}

	if (body->GetLinearVelocity().y != 0) {
		if (maxspeed.y > body->GetLinearVelocity().y && abs(maxspeed.y) <= maximumspeed)
			maxspeed.y = body->GetLinearVelocity().y;
		speedtY = 0;
	}

	speedtX += dt;
	speedtY += dt;
	if (speedtX >= 0.1f) {
		maxspeed.x = 0;
	//	cout << "x����" << endl;
		speedtX = 0;

	}
	if (speedtY >= 0.1f) {
		maxspeed.y = 0;
	//	cout << "y����" << endl;
		speedtY = 0;
	}

	//cout << body->GetLinearVelocity().y << endl;
}

void Cube::PhysicsUpdate()
{
	//body->SetTransform(b2Vec2(GetPos().x / SCALE,GetPos().y / SCALE),body->GetAngle());
}

void Cube::Draw(RenderWindow& window)
{
	if (isPlayingGame)
		sideFaces.Draw(window);
	
	if (!isPlayingGame)
		SpriteObj::Draw(window);
	//window.draw(*hitbox);
}

void Cube::Draw(RenderTexture& diffuse, Shader& nShader, RenderTexture& normal)
{
	diffuse.draw(frontFace);
	NormalPass(normal, frontFace, this->normal, nShader);
}

void Cube::SetSide(bool s)
{
	side = s;
}

void Cube::SetCubeBodyForce(b2Vec2 force)
{
	body->ApplyLinearImpulse(force, body->GetWorldCenter(), true);

}

void Cube::MovetoStartpos()
{
	body->SetTransform({ startpos.x / SCALE,startpos.y / SCALE * -1 },0);
}

