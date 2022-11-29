#include "Tunnel.h"

Tunnel::Tunnel()
{
	SetResourceTexture("Graphics/tunnel.png");
	id = 't';

	objSize = ObjectSize::Normal;
	type = ObjectType::Catcher;
}

Tunnel::Tunnel(const Vector2f& position, bool Horizon, int d,string buttonlist)
	:IsBlue(true), dir(d)
{
	tuns.setFillColor(Color(0, 255, 0, 128));
	tuns.setPosition(position);
	Utils::SetOrigin(tuns, Origins::MC);

	for (int i = 0; i < buttonlist.size(); i++) {
		char temp = buttonlist[i];
		buttonid.push_back(atoi(&temp));
	}

	if (Horizon) {
		tuns.setSize({ 0,50 });
	}
	else
		tuns.setSize({ 50,0 });
}

Tunnel::~Tunnel()
{
}

void Tunnel::Update(float dt)
{
	if (!hitwall) {
		if (dir == 0 || dir == 2) {
			if (dir == 0) {
				Utils::SetOrigin(tuns, Origins::BC);
			}
			else
				Utils::SetOrigin(tuns, Origins::TC);
			tuns.setSize({ tuns.getSize().x,tuns.getSize().y + 100 });
		}
		else {
			if (dir == 1) {
				Utils::SetOrigin(tuns, Origins::MR);
			}
			else
				Utils::SetOrigin(tuns, Origins::ML);
			tuns.setSize({ tuns.getSize().x + 100,tuns.getSize().y });

		}
	}

	hitbox.setSize(tuns.getSize());
	hitbox.setOrigin(tuns.getOrigin());

	//SetDoor(dt);
	for (auto b : button) {
		if (!b->GetPressed()) {
			active = false;
			return;
		}
	}
	//active door
	active = true;

}

void Tunnel::Draw(RenderWindow& window)
{
	if (active)
		window.draw(tuns);

	WireableObject::Draw(window);
	//window.draw(hitbox);
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
