#include "Button.h"
#include "../Manager/ResourceMgr.h"
#include "../FrameWork/Utils.h"

Button::Button()
{
	SetResourceTexture("Graphics/button.png");
	id = 'b';			
}

Button::~Button()
{
}

void Button::Update(float dt)
{	

}

//void Button::Draw(RenderWindow& window)
//{	
//	SpriteObj::Draw(window);
//	if (isWiring && isInMapTool)
//	{
//		SetWireCheckBox();
//		window.draw(wireCheckBox);
//	}		
//}

SpriteObj* Button::NewThis()
{
	return new Button;
}

//void Button::SetWireCheckBox()
//{
//	Utils::SetOrigin(wireCheckBox, Origins::BC);
//	Vector2f scale = sprite.getScale();	
//	wireCheckBox.setSize((Vector2f)sprite.getTexture()->getSize());
//	wireCheckBox.setScale(scale);
//	wireCheckBox.setPosition(sprite.getPosition());
//}
