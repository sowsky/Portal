#include "Tile.h"
#include "../FrameWork/Const.h"
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
	//delete fixture;
	delete hitbox;

}

SpriteObj* Tile::NewThis()
{
	return new Tile;
}

void Tile::Update(float dt)
{
	Utils::SetOrigin(*hitbox, Origins::MC);
	sprite.setRotation(body->GetAngle());
	//sprite.setPosition({ body->GetPosition().x,body->GetPosition().y*-1 });
	SetPos({ body->GetPosition().x,body->GetPosition().y * -1 });
	float globalboundcenterx = sprite.getGlobalBounds().left + (sprite.getGlobalBounds().width / 2);
	float globalboundcentery = sprite.getGlobalBounds().top + (sprite.getGlobalBounds().height / 2);

	hitbox->setSize({ sprite.getGlobalBounds().width,sprite.getGlobalBounds().height });
	hitbox->setPosition({ globalboundcenterx,globalboundcentery });
}

void Tile::Draw(RenderWindow& window)
{
	SpriteObj::Draw(window);
	//window.draw(*hitbox);
}

void Tile::PhysicsUpdate()
{
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

	Utils::SetOrigin(sprite, Origins::MC);

	hitbox = new RectangleShape;
	hitbox->setFillColor(Color::Red);
	Utils::SetOrigin(*hitbox, Origins::MC);
	b2BodyDef bodyDef;
	bodyDef.type = b2_staticBody;
	bodyDef.position.Set(position.x, position.y*-1);
	body = world->CreateBody(&bodyDef);

	hitbox->setPosition({ bodyDef.position.x,bodyDef.position.y});
	b2PolygonShape boxShape;
	boxShape.SetAsBox(dimensions.x / 2.0f,dimensions.x / 2.0f);

	b2FixtureDef fixtureDef;
	fixtureDef.shape = &boxShape;
	fixtureDef.density = 1.0f;
	fixtureDef.friction = 1.f;
	fixture = body->CreateFixture(&fixtureDef);

	sprite.setPosition({ body->GetPosition().x, body->GetPosition().y * -1 });
	hitbox->setPosition({ body->GetPosition().x, body->GetPosition().y * -1 });
}
