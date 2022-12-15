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

Dropper::Dropper(Vector2f pos, vector<float> buttonlist, Cube* cube)
	:buttonid(buttonlist), cube(cube)
{
	dropper.setFillColor(Color::Yellow);
	Utils::SetOrigin(dropper, Origins::MC);

	dropper.setPosition(pos);
	dropper.setSize({ GRIDSIZE,GRIDSIZE });

	sprite.setPosition(dropper.getPosition());
}

Dropper::~Dropper()
{
}

void Dropper::Update(float dt)
{
	Utils::SetOrigin(dropper, Origins::MC);

	if (isTurnOn)
		return;
	this->cube->SetPos({ -1000,1000 });
	this->cube->GetBody()->SetLinearVelocity({ 0,0 });

	//cout << cube->GetPos().x << endl;
	for (auto b : button) {
		if (!b->GetPressed()) {
			return;
		}
	}
	isTurnOn = true;
	cube->Respawn();

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
		window.draw(dropper);
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

void Dropper::SetButtonlist(vector<Button*>& button)
{
	for (auto b : button) {
		for (int i = 0; i < buttonid.size(); i++) {
			if (b->GetButtonId() == buttonid[i]) {
				this->button.push_back(b);
			}
		}
	}
}
