#include "Dropper.h"
#include "../Manager/ResourceMgr.h"
#include "Switch.h"
#include "../FrameWork/InputMgr.h"

Dropper::Dropper()
{
	SetResourceTexture("Graphics/temp/droppertool.png");
	id = 'd';

	type = ObjectType::Catcher;

	objSize = ObjectSize::Normal;
	attatchedPos = Rotate::Up;

	InitTexBox();
}

Dropper::~Dropper()
{
}

void Dropper::Update(float dt)
{
}

void Dropper::Draw(RenderWindow& window)
{
	if (!isPlayingGame)
	{
		WireableObject::Draw(window);
		if (isInMapTool)
		{
			DrawTexBox(window);			
		}
	}
	else
	{

	}
}

SpriteObj* Dropper::NewThis()
{
	return new Dropper;
}

void Dropper::InitTexBox()
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

void Dropper::DrawTexBox(RenderWindow& window)
{
	if (attatchedPos != Rotate::Up)
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

	if (Switch::GetShowTimer())
	{
		window.draw(onOfftexBox);
		window.draw(onOffTex);
	}
}
