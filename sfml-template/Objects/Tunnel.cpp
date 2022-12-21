#include "Tunnel.h"
#include "../FrameWork/stdafx.h"
#include "../FrameWork/InputMgr.h"
#include "../Manager/ResourceMgr.h"
#include "../FrameWork/Const.h"

Tunnel::Tunnel()
{
	SetResourceTexture("Graphics/temp/tunneltool.png");
	id = 't';

	objSize = ObjectSize::Normal;

	type = ObjectType::Catcher;

	InitTexBox();
	InitColorBox();
}

Tunnel::Tunnel(const Vector2f& position, int dir, vector<int> buttonlist, bool Isblue, bool active, int connected)
	:IsBlue(Isblue), dir(dir), enable(active), connected(connected), originactive(active)
{
	if (Isblue)
		tuns.setFillColor(Color(BLUE, 50));
	else {
		tuns.setFillColor(Color(ORANGE, 50));
	}
	Utils::SetOrigin(start, Origins::MC);
	start.setFillColor(Color(0, 255, 0, 255));

	buttonid = buttonlist;

	if (dir == 0 || dir == 2) {
		if (dir == 0) {
			Utils::SetOrigin(tuns, Origins::TC);
			startpos = { position.x, position.y + 1 - GRIDSIZE / 2 };
			tuns.setPosition(startpos);
		}
		else if (dir == 2) {
			Utils::SetOrigin(tuns, Origins::BC);
			startpos = { position.x,position.y - 1 + GRIDSIZE / 2 };
			tuns.setPosition(startpos);
		}
		tuns.setSize({ 50,0 });
		start.setSize({ 50,10 });
	}
	else {
		if (dir == 1) {
			Utils::SetOrigin(tuns, Origins::MR);
			startpos = { position.x - 1 + GRIDSIZE / 2,position.y };
			tuns.setPosition(startpos);
		}
		else if (dir == 3) {
			Utils::SetOrigin(tuns, Origins::ML);
			startpos = { position.x + 1 - GRIDSIZE / 2 + 2 ,position.y };
			tuns.setPosition(startpos);

		}
		tuns.setSize({ 0,50 });
		start.setSize({ 10,50 });

	}
	start.setPosition(startpos);

	SetSpriteTex(emitter, "Graphics/tunnel/tunnel.png");
	emitter.setScale(1.55f, 1.0f);
	Utils::SetOrigin(emitter, Origins::BC);
	emitter.setPosition(startpos);

	particles.setPrimitiveType(Points);
	if (Isblue)
	{
		switch (this->dir)
		{
		case 0:
			particleDir = { 0.f, 1.f };
			emitter.setRotation(180.f);
			break;
		case 1:
			particleDir = { -1.f, 0.f };
			emitter.setRotation(270.f);
			break;
		case 2:
			particleDir = { 0.f, -1.f };
			break;
		case 3:
			particleDir = { 1.f, 0.f };
			emitter.setRotation(90.f);
			break;
		}
	}
	else
	{
		switch (this->dir)
		{
		case 0:
			particleDir = { 0.f, -1.f };
			emitter.setRotation(180.f);
			break;
		case 1:
			particleDir = { 1.f, 0.f };
			emitter.setRotation(270.f);
			break;
		case 2:
			particleDir = { 0.f, 1.f };
			break;
		case 3:
			particleDir = { -1.f, 0.f };
			emitter.setRotation(90.f);
			break;
		}
	}

}

Tunnel::~Tunnel()
{

}


void Tunnel::Update(float dt)
{
	Utils::SetOrigin(start, Origins::MC);

	//if (InputMgr::GetKeyDown(Keyboard::R))
	//	active = !active;

	enable = originactive;

	for (auto b : button) {
		if (!b->GetPressed()) {
			enable = !originactive;
		}
	}

	if (!enable) {
		if (dir == 0 || dir == 2) {
			if (dir == 0) {
				Utils::SetOrigin(tuns, Origins::TC);
				tuns.setPosition(startpos);
			}
			else if (dir == 2) {
				Utils::SetOrigin(tuns, Origins::BC);
				tuns.setPosition(startpos);
			}
			tuns.setSize({ 50,0 });
		}
		else {
			if (dir == 1) {
				Utils::SetOrigin(tuns, Origins::MR);
				tuns.setPosition(startpos);
			}
			else if (dir == 3) {
				Utils::SetOrigin(tuns, Origins::ML);
				tuns.setPosition(startpos);

			}
			tuns.setSize({ 0,50 });
		}
		hitbox.setSize(tuns.getSize());
		hitbox.setPosition({ -100,-100 });
		hitwall = false;

		particleNum = 0;
		destiny.setPosition(startpos);

		return;
	}

	if (!hitwall) {
		if (dir == 0 || dir == 2) {
			tuns.setSize({ tuns.getSize().x,tuns.getSize().y + 100 });
			if (dir == 0) {
				Utils::SetOrigin(tuns, Origins::TC);
			}
			else if (dir == 2) {
				Utils::SetOrigin(tuns, Origins::BC);

			}
		}
		else {
			tuns.setSize({ tuns.getSize().x + 100,tuns.getSize().y });
			if (dir == 1) {
				Utils::SetOrigin(tuns, Origins::MR);

			}
			else if (dir == 3) {
				Utils::SetOrigin(tuns, Origins::ML);
			}

		}
		AddParticle();
	}
	else if (hitwall && whohitwall != nullptr) {

		Utils::SetOrigin(destiny, Origins::MC);

		if (dir == 0) {
			destiny.setSize({ tuns.getSize().x,10 });
			tuns.setSize({ tuns.getSize().x,whohitwall->GetGlobalBounds().top - tuns.getPosition().y });

			endpos = { tuns.getPosition().x,tuns.getPosition().y + tuns.getSize().y };

		}
		else if (dir == 2) {
			destiny.setSize({ tuns.getSize().x,10 });

			Utils::SetOrigin(tuns, Origins::BC);
			tuns.setSize({ tuns.getSize().x,tuns.getPosition().y - (whohitwall->GetGlobalBounds().top + whohitwall->GetGlobalBounds().height) });

			endpos = { tuns.getPosition().x,tuns.getPosition().y - tuns.getSize().y };
		}
		else if (dir == 1) {
			destiny.setSize({ 10,tuns.getSize().y });

			Utils::SetOrigin(tuns, Origins::MR);

			tuns.setSize({ tuns.getPosition().x - (whohitwall->GetGlobalBounds().left + whohitwall->GetGlobalBounds().width),tuns.getSize().y });

			endpos = { tuns.getPosition().x - tuns.getSize().x ,tuns.getPosition().y, };


		}
		else if (dir == 3) {
			destiny.setSize({ 10,tuns.getSize().y });

			Utils::SetOrigin(tuns, Origins::ML);

			tuns.setSize({ (whohitwall->GetGlobalBounds().left) - tuns.getPosition().x,tuns.getSize().y });

			endpos = { tuns.getPosition().x + tuns.getSize().x ,tuns.getPosition().y, };


		}

	}

	destiny.setPosition(endpos);
	tuns.setPosition(startpos);
	hitbox.setSize(tuns.getSize());
	hitbox.setOrigin(tuns.getOrigin());
	hitbox.setPosition(tuns.getPosition());

	if ((hitwall && whohitwall != nullptr) && enable)
	{
		SetParticlePos();
		TransParticles(dt);
	}
}

void Tunnel::Draw(RenderWindow& window)
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
		if (enable)
		{
			//	window.draw(tuns);
			window.draw(particles);
		}

		//window.draw(hitbox);			
		//window.draw(emitter);
	}
//	window.draw(destiny);
}

void Tunnel::ChangeDir()
{
	if (dir == 0)
		dir = 2;
	else if (dir == 1)
		dir = 3;
	else if (dir == 2)
		dir = 0;
	else if (dir == 3)
		dir = 1;
}

void Tunnel::ChangeColor()
{
	IsBlue = !IsBlue;
	if (IsBlue)
	{
		tuns.setFillColor(Color(0, 255, 0, 128));
	}
	else {
		tuns.setFillColor(Color(255, 255, 0, 128));
	}
}

void Tunnel::TurnOn()
{
	for (auto b : button) {
		if (!b->GetPressed()) {
			enable = false;
		}
	}

	//active door
	enable = true;
}

void Tunnel::SetButtonlist(vector<Button*>& button)
{
	for (auto b : button) {
		for (int i = 0; i < buttonid.size(); i++) {
			if (b->GetButtonId() == buttonid[i]) {
				this->button.push_back(b);
			}
		}
	}
}

void Tunnel::AddParticle()
{
	particleNum += 200;
}

void Tunnel::SetParticlePos()
{
	if (isPtcSetted)
		return;

	isPtcSetted = true;

	particles.resize(particleNum);

	for (int i = 0; i < particles.getVertexCount(); i++)
	{
		particles[i].color = IsBlue ? Color(BLUE) : Color(ORANGE);
	}

	FloatRect rect = tuns.getGlobalBounds();

	for (int i = 0; i < particleNum; i++)
	{
		float xpos = Utils::RandomRange(rect.left, rect.left + rect.width);
		float ypos = Utils::RandomRange(rect.top, rect.top + rect.height);

		particles[i].position = { xpos , ypos };
	}
}

void Tunnel::TransParticles(float dt)
{
	FloatRect rect = tuns.getGlobalBounds();
	for (int i = 0; i < particleNum; i++)
	{	
		particles[i].position = particles[i].position + dt * 130 * particleDir;
		if (IsBlue && !tuns.getGlobalBounds().contains(particles[i].position))
		{
			float xpos = Utils::RandomRange(rect.left, rect.left + rect.width);
			float ypos = Utils::RandomRange(rect.top, rect.top + rect.height);

			particles[i].position = { xpos , ypos };
		}
	}
}

void Tunnel::InitTexBox()
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

void Tunnel::InitColorBox()
{
	colorBox.setSize({ 8.f, 8.f });
	colorBox.setFillColor(Color::Blue);
	colorBox.setOutlineThickness(0.5f);
	colorBox.setOutlineColor(Color::Black);
}

void Tunnel::DrawTexBox(RenderWindow& window)
{
	onOfftexBox.setPosition(sprite.getPosition());
	onOffTex.setPosition(onOfftexBox.getPosition());

	Vector2f mousePos = window.mapPixelToCoords((Vector2i)InputMgr::GetMousePos(), window.getView());

	if (onOfftexBox.getGlobalBounds().contains(mousePos) &&
		InputMgr::GetMouseButtonDown(Mouse::Left) && Switch::GetShowTimer())
	{
		originactive = !originactive;
	}

	onOffTex.setString(originactive ? "ON" : "OFF");
	Utils::SetOrigin(onOffTex, Origins::BC);

	if (Switch::GetShowTimer())
	{
		window.draw(onOfftexBox);
		window.draw(onOffTex);
	}
}

void Tunnel::DrawColorBox(RenderWindow& window)
{
	if (!Switch::GetShowTimer())
		return;

	colorBox.setPosition(onOfftexBox.getTransform().transformPoint(onOfftexBox.getPoint(1)));

	Vector2f mousePos = window.mapPixelToCoords((Vector2i)InputMgr::GetMousePos(), window.getView());

	if (colorBox.getGlobalBounds().contains(mousePos) &&
		InputMgr::GetMouseButtonDown(Mouse::Left) && Switch::GetShowTimer())
	{
		IsBlue = !IsBlue;
	}

	colorBox.setFillColor(IsBlue ? Color::Blue : Color(ORANGE));

	window.draw(colorBox);
}
