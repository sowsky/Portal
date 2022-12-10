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
}

MovingPlatform::MovingPlatform(b2World* world, Vector2f& position, bool on, float destX, float destY, vector<int> buttonlist)
	:buttonid(buttonlist), enable(on), world(world)
{
	Utils::SetOrigin(platform, Origins::MC);
	destiny = { destX, destY };

	if (position.y > destY) {
		Utils::SetOrigin(pillar, Origins::BC);

		pillar.setPosition(position.x, position.y + GRIDSIZE / 2);
		endpos = { pillar.getPosition().x,pillar.getPosition().y - 30 };

		dir = 2;
	}
	else {
		Utils::SetOrigin(pillar, Origins::TC);

		pillar.setPosition(position.x, position.y - GRIDSIZE / 2);
		endpos = { pillar.getPosition().x,pillar.getPosition().y + 30 };

		dir = 0;
	}

	pillar.setFillColor(Color::Red);
	platform.setFillColor(Color::Green);
	platform.setSize({ GRIDSIZE, 20 });
}

void MovingPlatform::Update(float dt)
{
	enable = false;

	Utils::SetOrigin(platform, Origins::MC);

	if (dir == 2) {
		Utils::SetOrigin(pillar, Origins::BC);

	}
	else if (dir == 0) {
		Utils::SetOrigin(pillar, Origins::TC);
	}

	if (enable) {
		if (dir == 2) {
			pillar.setSize({ 10,pillar.getPosition().y - destiny.y });
			endpos.y = pillar.getPosition().y - pillar.getSize().y - 30;
		}
		else if (dir == 0) {
			pillar.setSize({ 10,destiny.y - pillar.getPosition().y });
			endpos.y = pillar.getPosition().y + pillar.getSize().y + 30;
		}
	}
	else {
		pillar.setSize({ 10,0 });
		if (dir == 0) {
			endpos.y = pillar.getPosition().y + 30;
		}
		else if (dir == 2) {
			endpos.y = pillar.getPosition().y - 30;
		}
	}

	platform.setPosition(endpos);
//	platform.setSize({ GRIDSIZE, 20 });
}

SpriteObj* MovingPlatform::NewThis()
{
	return new MovingPlatform;
}

void MovingPlatform::Draw(RenderWindow& window)
{
	if (!isPlayingGame)
	{
		WireableObject::Draw(window);
		if (isInMapTool && Switch::GetShowTimer())
		{
			DrawUi(window);
		}
	}
	else
	{
		window.draw(pillar);
		window.draw(platform);
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
			arrows[i].setPosition(arrows[i - 1].getPosition().x, arrows[i - 1].getPosition().y + rot * 25);

		window.draw(arrows[i]);
	}
	window.draw(up);
	window.draw(down);
}
