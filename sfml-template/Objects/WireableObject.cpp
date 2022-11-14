#include "WireableObject.h"
#include "../Manager/ResourceMgr.h"
#include "../FrameWork/InputMgr.h"
#include "../FrameWork/Utils.h"

WireableObject::~WireableObject()
{
}

void WireableObject::Init()
{
	Object::Init();
	SetWireCheckBox();
	isSelected = false;
}

void WireableObject::Draw(RenderWindow& window)
{
	Vector2f mousePos = InputMgr::GetMousePos();
	Vector2f mouseWorldPos = window.mapPixelToCoords((Vector2i)mousePos, window.getView());
	bool isMouseIn = wireCheckBox.getGlobalBounds().contains(mouseWorldPos);		
	
	if (InputMgr::GetMouseButtonDown(Mouse::Left) && isWiring)
	{
		isSelected = isMouseIn ? true : false;
	}

	wireCheckBox.setFillColor(isMouseIn || isSelected ? Color(248, 147, 30) : Color(37, 255, 254));

	SpriteObj::Draw(window);
	if (isWiring && isInMapTool)
	{	
		window.draw(wireCheckBox);
	}
}

void WireableObject::SetWireCheckBox()
{
	wireCheckBox.setTexture(RESOURCEMGR->GetTexture("Graphics/Ui/wirebox.png"));
	wireCheckBox.setSize((Vector2f)sprite.getTexture()->getSize());
	Utils::SetOrigin(wireCheckBox, Origins::BC);
	Vector2f scale = sprite.getScale();
	wireCheckBox.setSize((Vector2f)sprite.getTexture()->getSize());
	wireCheckBox.setScale(scale);
	wireCheckBox.setPosition(sprite.getPosition());
}
