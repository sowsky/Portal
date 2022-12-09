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

MovingPlatform::MovingPlatform(b2World* world, Vector2f& position, bool on, float destX, float destY, vector<int> buttonlist)
	:buttonid(buttonlist), enable(on), world(world)
{
	destiny = { destX, destY };
	if (position.y > destY) {
		Utils::SetOrigin(Pillar, Origins::BC);
		endpos = { destX,destY-30 };
		dir = 2;
	}
	else {
		Utils::SetOrigin(Pillar, Origins::TC);
		endpos = { destX,destY + 30 };

		dir = 0;
	}

	Pillar.setPosition(position);
	
	Utils::SetOrigin(platform, Origins::MC);
	platform.setPosition(endpos);
	platform.setSize({ GRIDSIZE, 20 });



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
