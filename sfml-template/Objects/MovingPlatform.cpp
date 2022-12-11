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

MovingPlatform::MovingPlatform(b2World* world, Vector2f& position, bool on, float rot, float destY, vector<float> buttonlist)
	:buttonid(buttonlist), enable(on), world(world),originactive(on)
{
	if (rot==0) {
		dir = 0;
		platform.setPosition(position.x, position.y - (GRIDSIZE / 2));
		destiny.y = platform.getPosition().y + (destY * GRIDSIZE);

	}
	else if (rot==2) {
		dir = 2;
		platform.setPosition(position.x , position.y + (GRIDSIZE / 2));
		destiny.y = platform.getPosition().y-(destY * GRIDSIZE);
	}

	originpos = platform.getPosition();
	platform.setFillColor(Color::Green);
	platform.setSize({ GRIDSIZE, 10 });

	this->world = world;
	b2BodyDef bodyDef;
	bodyDef.type = b2_staticBody;
	bodyDef.position.Set(position.x / SCALE, position.y / SCALE * -1);
	platformbody = this->world->CreateBody(&bodyDef);

	b2PolygonShape boxShape;
	boxShape.SetAsBox(platform.getSize().x / SCALE / 2, platform.getSize().y / SCALE / 2);

	b2FixtureDef fixtureDef;
	fixtureDef.shape = &boxShape;
	fixtureDef.density = 1.0f;
	fixtureDef.friction = 0.2f;
	platformfixture = platformbody->CreateFixture(&fixtureDef);

}

void MovingPlatform::Update(float dt)
{
	Utils::SetOrigin(platform, Origins::MC);

	if (InputMgr::GetKeyDown(Keyboard::Y))
	{
		enable = !enable;
	}

	enable = originactive;

	for (auto b : button) {
		if (!b->GetPressed()) {
			enable = !originactive;			
		}
	}

	if (enable) {
		float tempy = Utils::Lerp(platform.getPosition().y, destiny.y, 0.1);
		platform.setPosition(platform.getPosition().x, tempy);
		cout << (int)destiny.y << endl;
	}
	else {
		float tempy = Utils::Lerp(platform.getPosition().y, originpos.y, 0.1);
		platform.setPosition(platform.getPosition().x, tempy);
		cout << (int)originpos.y << endl;

	}
	platformbody->SetTransform({ platform.getPosition().x / SCALE,platform.getPosition().y / SCALE * -1}, 0);

	Utils::SetOrigin(down, Origins::MC);

	InitTexBox();
}

void MovingPlatform::SetButtonlist(vector<Button*>& button)
{
	for (auto b : button) {
		for (int i = 0; i < buttonid.size(); i++) {
			if (b->GetButtonId() == buttonid[i]) {
				this->button.push_back(b);
			}
		}
	}
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
			DrawTexBox(window);
		}
	}
	else
	{
		window.draw(platform);
		//window.draw(pillar);
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
