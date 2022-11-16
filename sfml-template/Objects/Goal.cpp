#include "Goal.h"

int Goal::goalNum = 0;

Goal::Goal()
{
	SetResourceTexture("Graphics/goal.png");
	id = '@';
	goalNum++;

	Utils::SetOrigin(sprite, Origins::BC);
}

Goal::Goal(Vector2f currgrid, float size, string buttonlist)
{
	SetResourceTexture("Graphics/goal.png");
	id = '@';
	goalNum++;

	Utils::SetOrigin(sprite, Origins::MC);

	SetSize({ GRIDSIZE,GRIDSIZE });
	SetPos(currgrid);
	
	for (int i = 0; i < buttonlist.size(); i++) {
		char temp = buttonlist[i];
		buttonid.push_back(atoi(&temp));
	}

}

Goal::~Goal()
{
	goalNum--;
	for (auto b : button)
		delete b;
	button.clear();
}

SpriteObj* Goal::NewThis()
{
	return new Goal;
}

void Goal::Update(float dt)
{
	for (auto b : button) {
		if (!b->GetPressed()) {
			on = false;
			return;
		}
	}
	//active door
	on = true;

	SetDoor(on);
}

void Goal::Draw(RenderWindow& window)
{
	SpriteObj::Draw(window);
	window.draw(sprite);
}

void Goal::SetDoor(bool Isopen)
{
	on = Isopen;
	if (on) {
		SetResourceTexture("Graphics/goalopen.png");

	}
	else
		SetResourceTexture("Graphics/goal.png");

}

void Goal::SetButtonlist(vector<Button*>& button)
{
	for (auto b : button) {
		for (int i = 0; i < buttonid.size(); i++) {
			if (b->GetButtonId() == buttonid[i]) {
				this->button.push_back(b);
			}
		}
	}
}

int Goal::GetGoalNum()
{
	return goalNum;
}
