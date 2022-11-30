#include "Bridge.h"

Bridge::Bridge()
{
	SetResourceTexture("Graphics/temp/bridge.png");
	id = 'l';

	objSize = ObjectSize::Normal;
	type = ObjectType::Catcher;
}

Bridge::Bridge(b2World* world, const Vector2f& position, Vector2f dimensions, vector<int> buttonlist, bool active, int dir, int connected)
	:dir(dir), active(active), connected(connected)
{

	if (dir == 0 || dir == 2) {
		if (dir == 0) {
			Utils::SetOrigin(bridge, Origins::TC);
			startpos = { position.x, position.y - GRIDSIZE / 2 };
			bridge.setPosition(startpos);
		}
		else if (dir == 2) {
			Utils::SetOrigin(bridge, Origins::BC);
			startpos = { position.x,position.y + GRIDSIZE / 2 };
			bridge.setPosition(startpos);
		}
		bridge.setSize({ 10,0 });
	}
	else {
		if (dir == 1) {
			Utils::SetOrigin(bridge, Origins::MR);
			startpos = { position.x + GRIDSIZE / 2,position.y };
			bridge.setPosition(startpos);
		}
		else if (dir == 3) {
			Utils::SetOrigin(bridge, Origins::ML);
			startpos = { position.x - GRIDSIZE / 2,position.y };
			bridge.setPosition(startpos);

		}
		bridge.setSize({ 0,10 });
	}

	bridge.setFillColor(Color(80, 188, 233, 255));

	b2BodyDef bodyDef;
	bodyDef.type = b2_staticBody;
	bodyDef.position.Set(position.x / SCALE, position.y / SCALE * -1);
	body = world->CreateBody(&bodyDef);

	b2PolygonShape boxShape;
	boxShape.SetAsBox(bridge.getSize().x / SCALE / 2, bridge.getSize().y / SCALE / 2);

	b2FixtureDef fixtureDef;
	fixtureDef.shape = &boxShape;
	fixtureDef.density = 1.0f;
	fixtureDef.friction = 0.2f;
	fixture = body->CreateFixture(&fixtureDef);
}

Bridge::~Bridge()
{
	for (auto v : button) {
		delete v;
	}
	button.clear();
}

void Bridge::Update(float dt)
{
	if (!active) {

		return;
	}

	if (!hitwall) {
		if (dir == 0 || dir == 2) {
			bridge.setSize({ bridge.getSize().x,bridge.getSize().y + 10 });
			if (dir == 0) {
				Utils::SetOrigin(bridge, Origins::TC);
			}
			else if (dir == 2) {
				Utils::SetOrigin(bridge, Origins::BC);

			}
		}
		else {
			bridge.setSize({ bridge.getSize().x + 10,bridge.getSize().y });
			if (dir == 1) {
				Utils::SetOrigin(bridge, Origins::MR);
			}
			else if (dir == 3) {
				Utils::SetOrigin(bridge, Origins::ML);
			}

		}
	}
	else if (hitwall && whohitwall != nullptr) {
		if (dir == 0) {
			bridge.setSize({ bridge.getSize().x,whohitwall->GetGlobalBounds().top - bridge.getPosition().y });
		}
		else if (dir == 2) {
			Utils::SetOrigin(bridge, Origins::BC);
			bridge.setSize({ bridge.getSize().x,bridge.getPosition().y - (whohitwall->GetGlobalBounds().top + whohitwall->GetGlobalBounds().height) });

		}
		else if (dir == 1) {
			Utils::SetOrigin(bridge, Origins::MR);

			bridge.setSize({ bridge.getPosition().x - (whohitwall->GetGlobalBounds().left + whohitwall->GetGlobalBounds().width),bridge.getSize().y });

		}
		else if (dir == 3) {
			Utils::SetOrigin(bridge, Origins::ML);

			bridge.setSize({ (whohitwall->GetGlobalBounds().left) - bridge.getPosition().x,bridge.getSize().y });

		}
	}

	bridge.setPosition(startpos);
	hitbox.setSize(bridge.getSize());
	hitbox.setOrigin(bridge.getOrigin());
	hitbox.setPosition(bridge.getPosition());
}

void Bridge::Draw(RenderWindow& window)
{
	window.draw(bridge);
	window.draw(hitbox);
	if (!isPlayingGame)
		WireableObject::Draw(window);

}
