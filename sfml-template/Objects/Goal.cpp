#include "Goal.h"

int Goal::goalNum = 0;

Goal::Goal()
{
	SetResourceTexture("Graphics/goal.png");
	id = '@';
	goalNum++;
}

Goal::~Goal()
{
	goalNum--;
}

SpriteObj* Goal::NewThis()
{
	return new Goal;
}

int Goal::GetGoalNum()
{
	return goalNum;
}
