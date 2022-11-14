#include "Tile.h"

Tile::Tile()	
{
	String str;
	int rand = Utils::RandomRange(0, 5);
	switch (rand)
	{
	case 0:
		str = "Graphics/Tile/tile.png";
		break;
	case 1:
		str = "Graphics/Tile/tile2.png";
		break;
	case 2:
		str = "Graphics/Tile/tile3.png";
		break;
	case 3:
		str = "Graphics/Tile/tile4.png";
		break;
	case 4:
		str = "Graphics/Tile/tile5.png";
		break;
	}
	SetResourceTexture(str);
	id = '1';
}

Tile::~Tile()
{
	delete fixture;
}

SpriteObj* Tile::NewThis()
{
	return new Tile;
}

void Tile::Update(float dt)
{
	sprite.setRotation(body->GetAngle());
	sprite.setPosition({ body->GetPosition().x,body->GetPosition().y });
}

Tile::Tile(b2World* world, const Vector2f& position, Vector2f dimensions)
{
	String str;
	int rand = Utils::RandomRange(0, 5);
	switch (rand)
	{
	case 0:
		str = "Graphics/Tile/tile.png";
		break;
	case 1:
		str = "Graphics/Tile/tile2.png";
		break;
	case 2:
		str = "Graphics/Tile/tile3.png";
		break;
	case 3:
		str = "Graphics/Tile/tile4.png";
		break;
	case 4:
		str = "Graphics/Tile/tile5.png";
		break;
	}
	SetResourceTexture(str);
	id = '1';

	b2BodyDef bodyDef;
	bodyDef.type = b2_staticBody;
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
