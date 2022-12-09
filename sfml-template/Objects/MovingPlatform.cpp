#include "MovingPlatform.h"

MovingPlatform::MovingPlatform()
{
	SetResourceTexture("Graphics/panelup.png");

	id = 'm';

	type = ObjectType::Catcher;
	objSize = ObjectSize::Normal;
	attatchedPos = Rotate::Down;

	SetOrigin(Origins::BC);
}

SpriteObj* MovingPlatform::NewThis()
{
	return new MovingPlatform;
}

void MovingPlatform::Update(float dt)
{
}

void MovingPlatform::Draw(RenderWindow& window)
{
	if (!isPlayingGame)
	{
		WireableObject::Draw(window);
	}
	else
	{
		SpriteObj::Draw(window);
	}
}
