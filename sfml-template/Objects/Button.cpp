#include "Button.h"
#include "../Manager/ResourceMgr.h"
#include "../FrameWork/Utils.h"
#include "NumBox.h"

int Button::buttonNum = 0;

Button::Button()
{
	SetResourceTexture("Graphics/button.png");
	id = 'b';	
	type = ObjectType::Trigger;
	buttonNum++;
	buttonId = buttonNum;
	
}

Button::~Button()
{
	buttonNum--;
}

SpriteObj* Button::NewThis()
{
	return new Button;
}
