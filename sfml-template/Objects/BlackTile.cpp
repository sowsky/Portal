#include "BlackTile.h"
#include "../FrameWork/InputMgr.h"
#include "../Manager/ResourceMgr.h"

BlackTile::BlackTile()
{
	SetResourceTexture(GetRandTileTex64());
	id = '2';

	type = ObjectType::Tile;
	objSize = ObjectSize::Big;
	attatchedPos = Rotate::Down;
}


BlackTile::BlackTile(b2World* world, const Vector2f& position, Vector2f dimensions, Vector2f box2dposition, bool isEnd)
{
	GetRandDiffuseAndNormal64();
	id = '2';
	SetSize({ GRIDSIZE,GRIDSIZE });

	Utils::SetOrigin(sprite, Origins::MC);
	if (isEnd) {
		float tilewidth = dimensions.y;
		b2BodyDef bodyDef;
		bodyDef.type = b2_staticBody;
		bodyDef.position.Set(((box2dposition.x + dimensions.x / 2) - tilewidth / 2) / SCALE, (box2dposition.y - GRIDSIZE) / SCALE * -1);
		body = world->CreateBody(&bodyDef);

		b2PolygonShape boxShape;
		boxShape.SetAsBox(dimensions.x / SCALE / 2.0f, dimensions.y / SCALE / 2.0f);

		b2FixtureDef fixtureDef;
		fixtureDef.shape = &boxShape;
		fixtureDef.density = 1.0f;
		fixtureDef.friction = 1.f;
		fixture = body->CreateFixture(&fixtureDef);
	}

	SetPos({ position.x,position.y });

	hitbox = new RectangleShape;
	Utils::SetOrigin(*hitbox, Origins::MC);
	hitbox->setFillColor(Color::Red);
	hitbox->setPosition(GetPos());

	type = ObjectType::Tile;

	float dp = DEPTH * 2 - 1.f;
	Utils::SetSpriteSize(frontFace, { FRONTSIZE, FRONTSIZE });
	Utils::SetOrigin(frontFace, Origins::MC);

	backFace.setSize({ FRONTSIZE * dp, FRONTSIZE * dp });
	Utils::SetOrigin(backFace, Origins::MC);

	Vector2u texSize = sprite.getTexture()->getSize();

	for (int i = 0; i < sideTiles.size(); i++)
	{
		tileTextures[i] = RESOURCEMGR->GetTexture(GetRandTileTex64());
		sideTiles[i].first = true;
		sideTiles[i].second.setPrimitiveType(Quads);
		sideTiles[i].second.resize(4);
		sideTiles[i].second[0].texCoords = { 0.f, 0.f };
		sideTiles[i].second[1].texCoords = { (float)texSize.x, 0.f };
		sideTiles[i].second[2].texCoords = (Vector2f)texSize;
		sideTiles[i].second[3].texCoords = { 0.f, (float)texSize.y };
	}
	backFace.setFillColor(Color::Red);


	hitbox = new RectangleShape;
	hitbox->setFillColor(Color::Red);
	Utils::SetOrigin(*hitbox, Origins::MC);
	hitbox->setSize(Utils::GetSpriteSize(sprite));
	hitbox->setPosition(GetPos());
}


BlackTile::~BlackTile()
{
	//delete fixture;
	delete hitbox;
}

void BlackTile::SetOrigin(Origins origin)
{
	SpriteObj::SetOrigin(origin);
	Utils::SetOrigin(backFace, origin);
}

SpriteObj* BlackTile::NewThis()
{
	return new BlackTile;
}

void BlackTile::Update(float dt)
{
	if (body != nullptr)
	{
		Utils::SetOrigin(*hitbox, Origins::MC);
		hitbox->setSize(GetSize());
		hitbox->setPosition(body->GetPosition().x * SCALE, body->GetPosition().y * SCALE * -1);
	}
}

void BlackTile::Draw(RenderWindow& window)
{
	if (!isPlayingGame)
		window.draw(sprite);

	if (isPlayingGame)
		DrawSideTiles(window);
}

void BlackTile::Draw(RenderTexture& diffuse, Shader& nShader, RenderTexture& normal)
{
	diffuse.draw(frontFace);
	NormalPass(normal, frontFace, normalMap, nShader);
}

void BlackTile::PhysicsUpdate()
{
}

void BlackTile::DrawHitbox(RenderWindow& window)
{
	window.draw(*hitbox);
}

string BlackTile::GetRandTileTex64()
{
	String str;
	int rand = Utils::RandomRange(0, 1);
	switch (rand)
	{
	case 0:
		str = "Graphics/Tile/64/1.png";
		break;
	case 1:
		str = "Graphics/Tile/64/2.png";
		break;
	case 2:
		str = "Graphics/Tile/64/3.png";
		break;
	}

	return str;
}

void BlackTile::GetRandDiffuseAndNormal64()
{
	int rand = Utils::RandomRange(0, 1);
	switch (rand)
	{
	case 0:
		SetResourceTexture("Graphics/Tile/64/1.png");
		frontFace.setTexture(*RESOURCEMGR->GetTexture("Graphics/Tile/64/1.png"));
		normalMap = RESOURCEMGR->GetTexture("Graphics/Tile/64/tile1n.png");
		break;
	case 1:
		SetResourceTexture("Graphics/Tile/64/2.png");
		frontFace.setTexture(*RESOURCEMGR->GetTexture("Graphics/Tile/64/2.png"));
		normalMap = RESOURCEMGR->GetTexture("Graphics/Tile/64/tile2n.png");
		break;
	case 2:
		SetResourceTexture("Graphics/Tile/64/3.png");
		frontFace.setTexture(*RESOURCEMGR->GetTexture("Graphics/Tile/64/3.png"));
		normalMap = RESOURCEMGR->GetTexture("Graphics/Tile/64/tile3n.png");
		break;
	}
}

void BlackTile::SetActiveSideTiles(int pos, bool active)
{
	sideTiles[pos].first = active;

}

void BlackTile::SetActiveSideTiles(array<bool, 4> array)
{
	for (int i = 0; i < sideTiles.size(); i++)
	{
		sideTiles[i].first = array[i];
	}
}

void BlackTile::SetSideTilesPosition(RenderWindow& window)
{
	Vector2f vanishingPoint = window.getView().getCenter();

	frontFace.setPosition(
		sprite.getPosition() - (vanishingPoint - sprite.getPosition()) * (1.f - DEPTH)
	);

	backFace.setPosition(
		sprite.getPosition() + (vanishingPoint - sprite.getPosition()) * (1.f - DEPTH)
	);

	FloatRect backRect = backFace.getGlobalBounds();
	FloatRect frontRect = frontFace.getGlobalBounds();

	if (sideTiles[0].first)
	{
		sideTiles[0].second[0].position = { backRect.left, backRect.top };
		sideTiles[0].second[1].position = { backRect.left + backRect.width, backRect.top };
		sideTiles[0].second[2].position = { frontRect.left + frontRect.width, frontRect.top };
		sideTiles[0].second[3].position = { frontRect.left, frontRect.top };
	}

	if (sideTiles[1].first)
	{
		sideTiles[1].second[0].position = { frontRect.left + frontRect.width, frontRect.top };
		sideTiles[1].second[1].position = { backRect.left + backRect.width, backRect.top };
		sideTiles[1].second[2].position = { backRect.left + backRect.width, backRect.top + backRect.height };
		sideTiles[1].second[3].position = { frontRect.left + frontRect.width, frontRect.top + frontRect.height };
	}

	if (sideTiles[2].first)
	{
		sideTiles[2].second[0].position = { backRect.left, backRect.top + backRect.height };
		sideTiles[2].second[1].position = { backRect.left + backRect.width, backRect.top + backRect.height };
		sideTiles[2].second[2].position = { frontRect.left + frontRect.width, frontRect.top + frontRect.height };
		sideTiles[2].second[3].position = { frontRect.left , frontRect.top + frontRect.height };
	}

	if (sideTiles[3].first)
	{
		sideTiles[3].second[0].position = { frontRect.left, frontRect.top };
		sideTiles[3].second[1].position = { backRect.left, backRect.top };
		sideTiles[3].second[2].position = { backRect.left, backRect.top + backRect.height };
		sideTiles[3].second[3].position = { frontRect.left , frontRect.top + frontRect.height };
	}

}

void BlackTile::DrawSideTiles(RenderWindow& window)
{
	SetSideTilesPosition(window);

	for (int i = 0; i < sideTiles.size(); i++)
	{
		if (sideTiles[i].first)
			window.draw(sideTiles[i].second, tileTextures[i]);
	}

	//window.draw(backFace);
}
