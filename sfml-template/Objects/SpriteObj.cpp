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

void SpriteObj::SetSize(Vector2f size)
{
	if (sprite.getTexture() == nullptr)
		return;

	Vector2u texSize = sprite.getTexture()->getSize();
	float ratioX = texSize.x / size.x;
	float ratioY = texSize.y / size.y;

	sprite.setScale({ 1 / ratioX , 1 / ratioY });
}

void SpriteObj::FitScale(float size)
{
	if (sprite.getTexture() == nullptr)
		return;

	Vector2u texSize = sprite.getTexture()->getSize();
	float scaleRatio = texSize.x > texSize.y ? texSize.x / size : texSize.y / size;
	sprite.setScale(sprite.getScale() / scaleRatio);
}

void SpriteObj::SetRotation(int val)
{
	if (val == 0) {
		sprite.setRotation(180.f);
	}
	else if (val == 1) {
		sprite.setRotation(270.f);
	}
	else if (val == 3) {
		sprite.setRotation(90.f);
	}
}

SpriteObj* SpriteObj::NewThis()
{
	return new SpriteObj;
}

FloatRect SpriteObj::GetGlobalBounds()
{
	return sprite.getGlobalBounds();
}
