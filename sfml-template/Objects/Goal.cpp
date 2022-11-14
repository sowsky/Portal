#include "Goal.h"
#include "../Manager/ResourceMgr.h"
#include "../FrameWork/Utils.h"

int Goal::goalNum = 0;

Goal::Goal()
{
	SetResourceTexture("Graphics/goal.png");
	id = '@';
	goalNum++;

	wireCheckBox.setTexture(RESOURCEMGR->GetTexture("Graphics/Ui/wirebox.png"));
	wireCheckBox.setSize((Vector2f)sprite.getTexture()->getSize());	
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
