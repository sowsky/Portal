#include "Goal.h"

Goal::Goal()
{
	SetResourceTexture("Graphics/goal.png");
	id = '@';
}

Goal::~Goal()
{
}

SpriteObj* Goal::NewThis()
{
	return new Goal;
}
