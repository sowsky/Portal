#include "MovingPlatform.h"
#include "../Manager/ResourceMgr.h"
#include "Switch.h"
#include "../FrameWork/InputMgr.h"

MovingPlatform::MovingPlatform()
{
	SetResourceTexture("Graphics/panelup.png");

	id = 'm';

	type = ObjectType::Catcher;
	objSize = ObjectSize::Normal;
	attatchedPos = Rotate::Down;

	SetOrigin(Origins::BC);

	for (auto& ar : arrows)
	{
		ar.setTexture(*RESOURCEMGR->GetTexture("Graphics/Ui/arrow.png"));
		Utils::SetOrigin(ar, Origins::BC);
	}

	up.setPointCount(3);
	up.setFillColor(Color::Black);
	up.setRadius(4.f);
	Utils::SetOrigin(up, Origins::MC);

	down.setPointCount(3);
	down.setFillColor(Color::Black);
	down.setRadius(4.f);
	Utils::SetOrigin(down, Origins::MC);	

	InitTexBox();
}

SpriteObj* MovingPlatform::NewThis()
{
	return new MovingPlatform;
}

void MovingPlatform::Update(float dt)
{
}

void MovingPlatform::Draw(RenderWindow& window)
{
	if (!isPlayingGame)
	{
		WireableObject::Draw(window);
		if (isInMapTool && Switch::GetShowTimer())
		{
			DrawUi(window);
			DrawTexBox(window);
		}
	}
	else
	{
		SpriteObj::Draw(window);
	}
}

void MovingPlatform::DrawUi(RenderWindow& window)
{
	int rot = (int)attatchedPos;

	if (rot == 1 || rot == 3)
		return;

	if (rot == 2)
	{
		up.setPosition(sprite.getPosition().x + 9.15f, sprite.getPosition().y - 5);
		down.setPosition(sprite.getPosition().x + 10.f, sprite.getPosition().y + 5);
		down.setRotation(180.f);
	}

	if (!rot)
	{
		down.setPosition(sprite.getPosition().x + 9.15f, sprite.getPosition().y - 5);
		up.setPosition(sprite.getPosition().x + 10.f, sprite.getPosition().y + 5);
		up.setRotation(180.f);
	}

	Vector2f mousePos = window.mapPixelToCoords((Vector2i)InputMgr::GetMousePos(), window.getView());

	if (up.getGlobalBounds().contains(mousePos) &&
		InputMgr::GetMouseButtonDown(Mouse::Left))
	{
		if (range >= arrows.size())
			return;

		range += 1;
	}

	if (down.getGlobalBounds().contains(mousePos) &&
		InputMgr::GetMouseButtonDown(Mouse::Left))
	{
		if (range <= 1)
			return;

		range -= 1;
	}

	for (int i = 0; i < range; i++)
	{
		if (i == arrows.size())
			break;

		int rot = (int)attatchedPos == 0 ? 1 : -1;

		arrows[i].setRotation(sprite.getRotation());
		if (!i)
			arrows[i].setPosition(sprite.getPosition());
		else
			arrows[i].setPosition(arrows[i - 1].getPosition().x , arrows[i - 1].getPosition().y + rot * 25);

		window.draw(arrows[i]);
	}
	window.draw(up);
	window.draw(down);	
}

void MovingPlatform::InitTexBox()
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

void MovingPlatform::DrawTexBox(RenderWindow& window)
{
	onOfftexBox.setPosition(sprite.getPosition());
	onOffTex.setPosition(onOfftexBox.getPosition());

	Vector2f mousePos = window.mapPixelToCoords((Vector2i)InputMgr::GetMousePos(), window.getView());

	if (onOfftexBox.getGlobalBounds().contains(mousePos) &&
		InputMgr::GetMouseButtonDown(Mouse::Left) && Switch::GetShowTimer())
	{
		isTurnedOn = !isTurnedOn;
	}

	onOffTex.setString(isTurnedOn ? "ON" : "OFF");
	Utils::SetOrigin(onOffTex, Origins::BC);

	if (Switch::GetShowTimer())
	{
		window.draw(onOfftexBox);
		window.draw(onOffTex);
	}
}
