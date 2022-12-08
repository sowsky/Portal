#pragma once
#include "../Switch.h"
class DurationSwitch : public Switch
{
public:
	DurationSwitch();
	virtual ~DurationSwitch() {}

	virtual SpriteObj* NewThis();
	float GetTime() { return time; }
};

