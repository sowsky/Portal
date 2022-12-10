#include "Gel.h"
#include "../FrameWork/InputMgr.h"
#include "../Manager/ResourceMgr.h"
#include "../FrameWork/Const.h"
#include "Switch.h"

Gel::Gel()
{
	SetResourceTexture("Graphics/temp/geltool.png");
    id = 'g';

	objSize = ObjectSize::Normal;

	type = ObjectType::Catcher;

	InitTexBox();
	InitColorBox();
}

Gel::~Gel()
{
}

void Gel::Update(float dt)
{
}

void Gel::Draw(RenderWindow& window)
{
	if (!isPlayingGame)
	{
		WireableObject::Draw(window);
		if (isInMapTool)
		{
			DrawTexBox(window);
			DrawColorBox(window);
		}
	}
	else
	{

	}	
}

SpriteObj* Gel::NewThis()
{
    return new Gel;
}

void Gel::InitTexBox()
{
	onOffTex.setFont(*RESOURCEMGR->GetFont("Fonts/D-DINCondensed-Bold.otf"));
	onOffTex.setCharacterSize(7);
	onOffTex.setFillColor(Color::Black);
	onOfftexBox.setSize({ 8.f, 8.f });
	Utils::SetOrigin(onOfftexBox, Origins::MC);
	onOfftexBox.setFillColor(Color::White);
	onOfftexBox.setOutlineThickness(0.5f);
	onOfftexBox.setOutlineColor(Color::Black);
}

void Gel::InitColorBox()
{
	colorBox.setSize({ 8.f, 8.f });
	colorBox.setFillColor(Color::Blue);
	colorBox.setOutlineThickness(0.5f);
	colorBox.setOutlineColor(Color::Black);
}

void Gel::DrawTexBox(RenderWindow& window)
{
	if (!Switch::GetShowTimer())
		return;

	onOfftexBox.setPosition(sprite.getPosition());
	onOffTex.setPosition(onOfftexBox.getPosition());

	Vector2f mousePos = window.mapPixelToCoords((Vector2i)InputMgr::GetMousePos(), window.getView());

	if (onOfftexBox.getGlobalBounds().contains(mousePos) &&
		InputMgr::GetMouseButtonDown(Mouse::Left) && Switch::GetShowTimer())
	{
		isTurnOn = !isTurnOn;
	}

	onOffTex.setString(isTurnOn ? "ON" : "OFF");
	Utils::SetOrigin(onOffTex, Origins::BC);

	window.draw(onOfftexBox);
	window.draw(onOffTex);
}

void Gel::DrawColorBox(RenderWindow& window)
{
	if (!Switch::GetShowTimer())
		return;

	colorBox.setPosition(onOfftexBox.getTransform().transformPoint(onOfftexBox.getPoint(1)));

	Vector2f mousePos = window.mapPixelToCoords((Vector2i)InputMgr::GetMousePos(), window.getView());

	if (colorBox.getGlobalBounds().contains(mousePos) &&
		InputMgr::GetMouseButtonDown(Mouse::Left) && Switch::GetShowTimer())
	{
		isBlue = !isBlue;		
	}

	colorBox.setFillColor(isBlue ? Color::Blue : Color(ORANGE));

	window.draw(colorBox);
}
