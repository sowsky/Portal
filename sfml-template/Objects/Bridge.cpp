#include "Bridge.h"
#include"../FrameWork/InputMgr.h"
#include "../FrameWork/stdafx.h"
#include "../FrameWork/Const.h"
Bridge::Bridge()
{
	SetResourceTexture("Graphics/temp/bridge.png");
	id = 'l';

	objSize = ObjectSize::Normal;
	type = ObjectType::Catcher;
}

Bridge::Bridge(b2World* world, Vector2f& position, vector<int> buttonlist, bool active, int dir, int connected)
	:dir(dir), active(active), connected(connected)
{
	SetSpriteTex(frontEmitter, "Graphics/bridge/front.png");
	SetSpriteTex(backEmitter, "Graphics/bridge/back.png");
	frontEmitter.setScale(0.3, 0.3);
	backDp = DEPTH *2 - 1.f;
	backEmitter.setScale(frontEmitter.getScale()* backDp);

	Utils::SetOrigin(frontEmitter, Origins::ML);
	Utils::SetOrigin(backEmitter, Origins::ML);
	
	if (dir == 0 || dir == 2) {
		if (dir == 0) {
			Utils::SetOrigin(bridge, Origins::TC);
			Utils::SetOrigin(bridge_front, Origins::TC);
			Utils::SetOrigin(bridge_back, Origins::TC);
			startpos = { position.x, position.y - GRIDSIZE / 2 };
			frontEmitter.setRotation(90.f);
			backEmitter.setRotation(90.f);			
		}
		else if (dir == 2) {
			Utils::SetOrigin(bridge, Origins::BC);
			Utils::SetOrigin(bridge_front, Origins::BC);
			Utils::SetOrigin(bridge_back, Origins::BC);
			startpos = { position.x,position.y + GRIDSIZE / 2 };
			frontEmitter.setRotation(270.f);
			backEmitter.setRotation(270.f);
		}		
	}
	else if (dir == 1 || dir == 3) {
		if (dir == 1) {
			Utils::SetOrigin(bridge, Origins::MR);
			Utils::SetOrigin(bridge_front, Origins::MR);
			Utils::SetOrigin(bridge_back, Origins::MR);
			startpos = { position.x + GRIDSIZE / 2,position.y };
			frontEmitter.setRotation(180.f);
			backEmitter.setRotation(180.f);
			
		}
		else if (dir == 3) {
			Utils::SetOrigin(bridge, Origins::ML);
			Utils::SetOrigin(bridge_front, Origins::ML);
			Utils::SetOrigin(bridge_back, Origins::ML);
			startpos = { position.x - GRIDSIZE / 2,position.y };
			

		}
	}

	frontEmitter.setPosition(startpos);
	backEmitter.setPosition(startpos);
	bridge.setPosition(startpos);
	bridge.setSize({ 0,10 });

	bridge.setFillColor(Color(80, 188, 233, 255));
	bridge_front.setFillColor(Color::Red);
	bridge_back.setFillColor(Color::Yellow);

	this->world = world;
	b2BodyDef bodyDef;
	bodyDef.type = b2_staticBody;
	bodyDef.position.Set(position.x / SCALE, position.y / SCALE * -1);
	body = this->world->CreateBody(&bodyDef);

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

	if (body != nullptr)
		world->DestroyBody(body);
}

void Bridge::Update(float dt)
{
	if (InputMgr::GetKeyDown(Keyboard::R))
		active = !active;

	if (!active) {
		if (dir == 0 || dir == 2)
			bridge.setSize({ 10,0 });
		else
			bridge.setSize({ 0,10 });

		return;
	}

	if (!hitwall) {
		if (dir == 0 || dir == 2) {
			bridge.setSize({ bridge.getSize().x,bridge.getSize().y + 50 });
			if (dir == 0) {

				Utils::SetOrigin(bridge, Origins::TC);
			}
			else if (dir == 2) {

				Utils::SetOrigin(bridge, Origins::BC);
			}

		}
		else {
			bridge.setSize({ bridge.getSize().x + 50,bridge.getSize().y });
			if (dir == 1) {
				Utils::SetOrigin(bridge, Origins::MR);
			}
			else if (dir == 3) {
				Utils::SetOrigin(bridge, Origins::ML);
			}

		}
	}
	else if (hitwall && whohitwall != nullptr/*) && !setedpos*/) {
		if (fixture != nullptr) {
			body->DestroyFixture(body->GetFixtureList());
		}

		b2PolygonShape boxShape;
		boxShape.SetAsBox(bridge.getSize().x / SCALE / 2, bridge.getSize().y / SCALE / 2);

		b2FixtureDef fixtureDef;
		fixtureDef.shape = &boxShape;
		fixtureDef.density = 1;
		fixtureDef.friction = 0.3f;
		fixture = body->CreateFixture(&fixtureDef);
		float x;
		float y;

		if (dir == 0) {
			Utils::SetOrigin(bridge, Origins::TC);
			bridge.setSize({ bridge.getSize().x,whohitwall->GetGlobalBounds().top - bridge.getPosition().y });
			x = bridge.getPosition().x / SCALE;
			y = (bridge.getPosition().y + (bridge.getSize().y / 2)) / SCALE * -1;
		}
		else if (dir == 2) {
			Utils::SetOrigin(bridge, Origins::BC);
			bridge.setSize({ bridge.getSize().x,bridge.getPosition().y - (whohitwall->GetGlobalBounds().top + whohitwall->GetGlobalBounds().height) });

			x = bridge.getPosition().x / SCALE;
			y = (bridge.getPosition().y + (bridge.getSize().y / 2) - bridge.getSize().y) / SCALE * -1;

		}
		else if (dir == 1) {
			Utils::SetOrigin(bridge, Origins::MR);

			bridge.setSize({ bridge.getPosition().x - (whohitwall->GetGlobalBounds().left + whohitwall->GetGlobalBounds().width),bridge.getSize().y });

			x = (bridge.getPosition().x - (bridge.getSize().x / 2)) / SCALE;
			y = bridge.getPosition().y / SCALE * -1;
		}
		else if (dir == 3) {
			Utils::SetOrigin(bridge, Origins::ML);

			bridge.setSize({ (whohitwall->GetGlobalBounds().left) - bridge.getPosition().x,bridge.getSize().y });
			x = (bridge.getPosition().x + (bridge.getSize().x / 2)) / SCALE;
			y = bridge.getPosition().y / SCALE * -1;
		}

		body->SetTransform({ x,y }, 0);
		setedpos = true;


	}

	//Utils::SetOrigin(hitbox, Origins::MC);

	hitbox.setOrigin(bridge.getOrigin());
	bridge.setPosition(startpos);

	bridge_front.setOrigin(bridge.getOrigin());
	bridge_back.setOrigin(bridge.getOrigin());
	bridge_front.setSize(bridge.getSize() / DEPTH);
	bridge_back.setSize(bridge.getSize() * backDp);
	bridge_front.setPosition(bridge.getPosition());
	bridge_back.setPosition(bridge.getPosition());


	hitbox.setSize(bridge.getSize());
	if (body != nullptr) {
		Vector2f pos = { body->GetPosition().x * SCALE,body->GetPosition().y * SCALE * -1 };
		cout << body->GetPosition().x * SCALE << " " << body->GetPosition().y * SCALE * -1 << endl;
		hitbox.setPosition(pos);
	}
}

void Bridge::Draw(RenderWindow& window)
{
	UpdateBridgeDraw(window);
	window.draw(backEmitter);
	window.draw(bridge_back);
	
	if (active)
		window.draw(bridge);
		//window.draw(hitbox);
	
	if (!isPlayingGame)
		WireableObject::Draw(window);

	window.draw(bridge_front);
	window.draw(frontEmitter);

	cout << bridge_front.getPosition().x << "다리" << endl;
	cout << frontEmitter.getPosition().x << "방출기" << endl;
}

void Bridge::UpdateBridgeDraw(RenderWindow& window)
{
	Vector2f vanishingPoint = window.getView().getCenter();

	frontEmitter.setPosition(
		startpos - (vanishingPoint - startpos) * (1.f - DEPTH)
	);

	//bridge_front.setPosition(frontEmitter.getPosition());

	backEmitter.setPosition(
		startpos + (vanishingPoint - startpos) * (1.f - DEPTH)
	);

	//bridge_back.setPosition(backEmitter.getPosition());
}
