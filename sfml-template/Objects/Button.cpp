#include "Button.h"

Button::Button()
{
	SetResourceTexture("Graphics/button.png");
	id = 'b';
}

Button::~Button()
{
}

SpriteObj* Button::NewThis()
{
	return new Button;
}
