#include "WirePointArrows.h"
#include "../Manager/ResourceMgr.h"
#include "../FrameWork/EnumClasses.h"
#include "../FrameWork/Utils.h"

WirePointArrows::WirePointArrows()
{	
	arrowContainer[0] = up;
	arrowContainer[1] = left;
	arrowContainer[2] = right;
	arrowContainer[3] = down;
	for (auto arrows : arrowContainer)
	{
		arrows.setTexture(*RESOURCEMGR->GetTexture("Graphics/Ui/wirearrow.png"));
		arrows.setColor(Color(37, 255, 254));
		Utils::SetOrigin(arrows, Origins::ML);
	}
}

void WirePointArrows::Init()
{

}

void WirePointArrows::SetPosition(Vector2f pos, float tileSize)
{
	Vector2f fixOrigin{ tileSize * 0.5f,0.f };
	for (auto arrows : arrowContainer)
	{
		arrows.setOrigin(arrows.getOrigin() + fixOrigin);
	}
	up.setRotation(90.f);
	right.setRotation(180.f);
	down.setRotation(270.f);
	for (auto arrows : arrowContainer)
	{
		arrows.setPosition(pos);
	}
}

void WirePointArrows::Update(float dt)
{
}

void WirePointArrows::Draw(RenderWindow& window)
{
	for (auto arrows : arrowContainer)
	{
		window.draw(arrows);		
	}
}
