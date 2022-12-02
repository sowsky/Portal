#include "Bridge.h"
#include"../FrameWork/InputMgr.h"
#include "../FrameWork/stdafx.h"
#include "../Manager/ResourceMgr.h"
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
	///////////
	buttonid = buttonlist;
	SetSpriteTex(frontEmitter, "Graphics/bridge/front.png");
	SetSpriteTex(backEmitter, "Graphics/bridge/back.png");
	bridge_color = RESOURCEMGR->GetTexture("Graphics/bridge/color.png");
	frontEmitter.setScale(0.3, 0.3);
	backDp = DEPTH * 2 - 1.f;
	backEmitter.setScale(frontEmitter.getScale() * backDp);

	Utils::SetOrigin(frontEmitter, Origins::ML);
	Utils::SetOrigin(backEmitter, Origins::ML);

	start.setFillColor(Color(0, 255, 0, 255));

	bridge_rect.setPrimitiveType(Quads);
	bridge_rect.resize(4);

	bridge_rect[0].texCoords = { 0.f ,0.f };
	bridge_rect[1].texCoords = { 32.f ,0.f };
	bridge_rect[2].texCoords = { 32.f ,32.f };
	bridge_rect[3].texCoords = { 0.f ,32.f };

	///////////

	float bridgeThickness = 5.f;

	if (dir == 0 || dir == 2) {
		if (dir == 0) {
			Utils::SetOrigin(bridge, Origins::TC);
			startpos = { position.x, position.y - GRIDSIZE / 2 };
			bridge.setPosition(startpos);
			frontEmitter.setRotation(90.f);
			backEmitter.setRotation(90.f);
		}
		else if (dir == 2) {
			Utils::SetOrigin(bridge, Origins::BC);
			startpos = { position.x,position.y + GRIDSIZE / 2 };
			bridge.setPosition(startpos);
			frontEmitter.setRotation(270.f);
			backEmitter.setRotation(270.f);
		}
		bridge.setSize({ bridgeThickness,0 });
		start.setSize({ 50,5 });

	}
	else if (dir == 1 || dir == 3) {
		if (dir == 1) {
			Utils::SetOrigin(bridge, Origins::MR);
			startpos = { position.x + GRIDSIZE / 2,position.y };
			bridge.setPosition(startpos);
			frontEmitter.setRotation(180.f);
			backEmitter.setRotation(180.f);
			cout << startpos.x<<" "<<startpos.y << endl;
		}
		else if (dir == 3) {
			Utils::SetOrigin(bridge, Origins::ML);
			startpos = { position.x - GRIDSIZE / 2,position.y };
			bridge.setPosition(startpos);

		}
		bridge.setSize({ 0, bridgeThickness });
		start.setSize({ 5,50 });
	}
	if (connected != 0) {
		startpos.y += 25;
	}
	start.setPosition(startpos);

	bridge.setFillColor(Color(80, 188, 233, 255));

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

	///////////

	frontEmitter.setPosition(startpos);
	backEmitter.setPosition(startpos);

	///////////
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
	Utils::SetOrigin(start, Origins::MC);

	/*if (InputMgr::GetKeyDown(Keyboard::R))
		active = !active;*/

	active = true;

	for (auto b : button) {
		if (!b->GetPressed()) {
			active = false;
			destiny.setPosition(startpos);
			return;
		}
	}

	if (!active) {
		if (dir == 0 || dir == 2) {
			if (dir == 0) {
				Utils::SetOrigin(bridge, Origins::TC);
				bridge.setPosition(startpos);
			}
			else if (dir == 2) {
				Utils::SetOrigin(bridge, Origins::BC);
				bridge.setPosition(startpos);
			}
			bridge.setSize({ 50,0 });
		}
		else {
			if (dir == 1) {
				Utils::SetOrigin(bridge, Origins::MR);
				bridge.setPosition(startpos);
			}
			else if (dir == 3) {
				Utils::SetOrigin(bridge, Origins::ML);
				bridge.setPosition(startpos);

			}
			bridge.setSize({ 0,50 });
		}
		hitbox.setSize(bridge.getSize());
		hitwall = false;

		return;
	}

	if (!hitwall) {
		if (dir == 0 || dir == 2) {
			bridge.setSize({ bridge.getSize().x,bridge.getSize().y + 100 });
			if (dir == 0) {
				Utils::SetOrigin(bridge, Origins::TC);
			}
			else if (dir == 2) {
				Utils::SetOrigin(bridge, Origins::BC);
			}

		}
		else {
			bridge.setSize({ bridge.getSize().x + 100,bridge.getSize().y });
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
			bridge.setSize({ bridge.getSize().x ,whohitwall->GetGlobalBounds().top - bridge.getPosition().y });
			x = bridge.getPosition().x / SCALE;
			y = (bridge.getPosition().y + (bridge.getSize().y / 2)) / SCALE * -1;
			endpos = { bridge.getPosition().x,bridge.getPosition().y + bridge.getSize().y };
			destiny.setSize({ bridge.getSize().x,10 });

		}
		else if (dir == 2) {

			Utils::SetOrigin(bridge, Origins::BC);

			x = bridge.getPosition().x / SCALE;
			y = (bridge.getPosition().y + (bridge.getSize().y / 2) - bridge.getSize().y) / SCALE * -1;
			endpos = { bridge.getPosition().x,bridge.getPosition().y - bridge.getSize().y };
			destiny.setSize({ bridge.getSize().x,10 });
			bridge.setSize({ bridge.getSize().x,bridge.getPosition().y - (whohitwall->GetGlobalBounds().top + whohitwall->GetGlobalBounds().height) });

		}
		else if (dir == 1) {
			Utils::SetOrigin(bridge, Origins::MR);

			bridge.setSize({ bridge.getPosition().x - (whohitwall->GetGlobalBounds().left + whohitwall->GetGlobalBounds().width),bridge.getSize().y });
			x = (bridge.getPosition().x - (bridge.getSize().x / 2)) / SCALE;
			y = bridge.getPosition().y / SCALE * -1;
			destiny.setSize({ 10,bridge.getSize().y });
			endpos = { bridge.getPosition().x - bridge.getSize().x ,bridge.getPosition().y, };

		}


		else if (dir == 3) {
			Utils::SetOrigin(bridge, Origins::ML);

			bridge.setSize({ (whohitwall->GetGlobalBounds().left) - bridge.getPosition().x,bridge.getSize().y });
			x = (bridge.getPosition().x + (bridge.getSize().x / 2)) / SCALE;
			y = bridge.getPosition().y / SCALE * -1;
			destiny.setSize({ 10,bridge.getSize().y });

			endpos = { bridge.getPosition().x + bridge.getSize().x ,bridge.getPosition().y, };
		}

		body->SetTransform({ x,y }, 0);
		setedpos = true;
	}

	//Utils::SetOrigin(hitbox, Origins::MC);

	destiny.setPosition(endpos);
	bridge.setPosition(startpos);
	hitbox.setOrigin(bridge.getOrigin());

	hitbox.setSize(bridge.getSize());
	if (body != nullptr) {
		Vector2f pos = { body->GetPosition().x * SCALE,body->GetPosition().y * SCALE * -1 };
		hitbox.setPosition(pos);
	}
}

void Bridge::Draw(RenderWindow& window)
{
	if (isPlayingGame)
	{

		if (active)
		{
			window.draw(bridge);
			if (setedpos) {
				UpdateBridgeDraw(window);
				window.draw(bridge_rect, bridge_color);
				window.draw(frontEmitter);
			}
		}

		//window.draw(hitbox);
		//window.draw(start);
		//window.draw(destiny);		
	}
	if (!isPlayingGame)
		WireableObject::Draw(window);
}


void Bridge::SetButtonlist(vector<Button*>& button)
{
	for (auto b : button) {
		for (int i = 0; i < buttonid.size(); i++) {
			if (b->GetButtonId() == buttonid[i]) {
				this->button.push_back(b);
			}
		}
	}
}

void Bridge::UpdateBridgeDraw(RenderWindow& window)
{
	Vector2f vanishingPoint = window.getView().getCenter();

	frontEmitter.setPosition(
		startpos - (vanishingPoint - startpos) * (1.f - DEPTH)
	);

	backEmitter.setPosition(
		startpos + (vanishingPoint - startpos) * (1.f - DEPTH)
	);

	front_des_pos = endpos - (vanishingPoint - endpos) * (1.f - DEPTH);
	back_des_pos = endpos + (vanishingPoint - endpos) * (1.f - DEPTH);

	if (active)
	{
		bridge_rect[0].position = backEmitter.getPosition();
		bridge_rect[1].position = frontEmitter.getPosition();
		bridge_rect[2].position = front_des_pos;
		bridge_rect[3].position = back_des_pos;
	}

}

void Bridge::DrawBackEmmiter(RenderWindow& window)
{
	window.draw(backEmitter);
}
