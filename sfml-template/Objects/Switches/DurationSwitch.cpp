#include "DurationSwitch.h"

DurationSwitch::DurationSwitch()
{
	SetResourceTexture("Graphics/switch.png");
	id = '8';
	type = ObjectType::Trigger;
	objSize = ObjectSize::Normal;
	attatchedPos = Rotate::Down;

	switchType = false;
	time = 3.f;
}

SpriteObj* DurationSwitch::NewThis()
{
	return new DurationSwitch;
}
