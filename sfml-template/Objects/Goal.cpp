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

void Goal::SetDoor(bool Isopen)
{
	on = Isopen;
	if (on) {
	//	SetResourceTexture("Graphics/goalopen.png");

	}else
		SetResourceTexture("Graphics/goal.png");

}

int Goal::GetGoalNum()
{
	return goalNum;
}
