#include "SpriteObj.h"
#include "../Manager/ResourceMgr.h"

SpriteObj::SpriteObj()
{
}

SpriteObj::~SpriteObj()
{
}

void SpriteObj::SetOrigin(Origins origin)
{
	Utils::SetOrigin(sprite, origin);
}

void SpriteObj::SetPos(const Vector2f& pos)
{
	Object::SetPos(pos);
	sprite.setPosition(pos);
}

void SpriteObj::Update(float dt)
{
	
}

void SpriteObj::Draw(RenderWindow& window)
{
	window.draw(sprite);
}

void SpriteObj::SetResourceTexture(String id)
{	
	sprite.setTexture(*RESOURCEMGR->GetTexture(id));
}

void SpriteObj::SetUiTexture(String id)
{
	SetResourceTexture(id);
	sprite.setScale({ 1.5f, 1.5f });
}

Sprite* SpriteObj::GetSprite()
{
	return &sprite;
}

void SpriteObj::SetScale(Vector2f scale)
{
	sprite.setScale(scale);
}
