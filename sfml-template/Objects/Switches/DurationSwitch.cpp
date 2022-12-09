#include "DurationSwitch.h"
#include "../../Manager/ResourceMgr.h"
#include "../../FrameWork/InputMgr.h"

DurationSwitch::DurationSwitch()
{
	SetResourceTexture("Graphics/switch.png");
	id = '8';
	type = ObjectType::Trigger;
	objSize = ObjectSize::Normal;
	attatchedPos = Rotate::Down;

	switchType = false;
	time = 3.f;

	num.setFont(*RESOURCEMGR->GetFont("Fonts/D-DINCondensed-Bold.otf"));
	num.setCharacterSize(13);
	num.setFillColor(Color::Black);
	box.setSize({ 10.f, 10.f });
	Utils::SetOrigin(box, Origins::MC);
	box.setFillColor(Color::White);
	box.setOutlineThickness(0.5f);
	box.setOutlineColor(Color::Black);

	up.setPointCount(3);
	up.setFillColor(Color::Black);
	up.setRadius(4.f);
	Utils::SetOrigin(up, Origins::MC);

	down.setPointCount(3);
	down.setFillColor(Color::Black);
	down.setRadius(4.f);
	Utils::SetOrigin(down, Origins::MC);
	down.setRotation(180.f);
}

SpriteObj* DurationSwitch::NewThis()
{
	return new DurationSwitch;
}

void DurationSwitch::Draw(RenderWindow& window)
{
	box.setPosition(sprite.getPosition());		
	up.setPosition(box.getPosition().x + 9.15f, box.getPosition().y - 5);
	down.setPosition(box.getPosition().x + 10.f, box.getPosition().y + 5);

	Vector2f mousePos = window.mapPixelToCoords((Vector2i)InputMgr::GetMousePos(), window.getView());

	if (up.getGlobalBounds().contains(mousePos) &&
		InputMgr::GetMouseButtonDown(Mouse::Left) && showTimer)
	{
		time += 1.f;
	}

	if (down.getGlobalBounds().contains(mousePos) &&
		InputMgr::GetMouseButtonDown(Mouse::Left) && showTimer)
	{
		if (time <= 1.f)
			return;
		time -= 1.f;
	}

	num.setString(to_string((int)time));
	Utils::SetOrigin(num, Origins::BC);
	num.setPosition(box.getPosition());

	if (!isPlayingGame)
	{
		WireableObject::Draw(window);
		if (isInMapTool && showTimer)
		{
			window.draw(box);
			window.draw(num);
			window.draw(up);
			window.draw(down);
		}
	}
}
