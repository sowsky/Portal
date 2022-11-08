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

void SpriteObj::SetTexture(String id)
{
	//sprite.setTexture()
}

Sprite* SpriteObj::GetSprite()
{
	return &sprite;
}
