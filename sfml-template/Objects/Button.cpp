#include "Button.h"
#include "../Manager/ResourceMgr.h"
#include "../FrameWork/Utils.h"
//#include "NumBox.h"

bool Button::isEditMap = false;
int Button::buttonNum = 0;

Button::Button()
{
	SetResourceTexture("Graphics/button.png");
	id = 'b';

	type = ObjectType::Trigger;

	hitbox = new RectangleShape;
	hitbox->setFillColor(Color::Red);
	hitbox->setSize(sprite.getPosition());
	hitbox->setPosition(sprite.getPosition());

	objSize = ObjectSize::Normal;
	attatchedPos = Rotate::Down;

	buttonNum++;
	buttonId = buttonNum;
}

Button::~Button()
{

}

SpriteObj* Button::NewThis()
{
	return new Button;
}

void Button::Draw(RenderWindow& window)
{
	WireableObject::Draw(window);
	Utils::SetOrigin(*hitbox, Origins::MC);
	hitbox->setSize({ Utils::GetSpriteSize(sprite).x - 20,Utils::GetSpriteSize(sprite).y });
	hitbox->setPosition(sprite.getPosition());
	if (hitbox != nullptr
		&& !isEditMap) {
		//	window.draw(*hitbox);
	}
}
