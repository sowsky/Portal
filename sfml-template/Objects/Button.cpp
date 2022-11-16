#include "Button.h"


Button::Button()
{
	SetResourceTexture("Graphics/button.png");
	id = 'b';	
	buttonId++;

}

Button::~Button()
{
}

SpriteObj* Button::NewThis()
{
	return new Button;
}
