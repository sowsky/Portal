#include "AfterSwitch.h"

AfterSwitch::AfterSwitch()
{
	SetResourceTexture("Graphics/switch.png");
	id = 'as';
	type = ObjectType::Trigger;
	objSize = ObjectSize::Normal;
	attatchedPos = Rotate::Down;

	switchType = true;
	time = 3.f;
}

SpriteObj* AfterSwitch::NewThis()
{
    return new AfterSwitch;
}
