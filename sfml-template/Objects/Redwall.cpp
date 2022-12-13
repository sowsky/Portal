#include "Redwall.h"
#include "../FrameWork/InputMgr.h"
#include "../Manager/ResourceMgr.h"
#include "Switch.h"

Redwall::Redwall()
{
	SetResourceTexture("Graphics/Ui/fizzlertool.png");
	id = 'r';

	type = ObjectType::Catcher;

	objSize = ObjectSize::Normal;
	attatchedPos = Rotate::Down;

	InitTexBox();
}

Redwall::Redwall(Vector2f& position, vector<int> buttonlist, bool active, int dir)
	:enable(active), dir(dir), buttonid(buttonlist), originactive(active)
{
	redwall.setFillColor(Color(255, 0, 0, 100));

	if (dir == 0 || dir == 2) {
		if (dir == 0) {
			Utils::SetOrigin(redwall, Origins::TC);
			startpos = { position.x, position.y  };
			redwall.setPosition(startpos);
		}
		else if (dir == 2) {
			Utils::SetOrigin(redwall, Origins::BC);
			startpos = { position.x,position.y  };
			redwall.setPosition(startpos);
		}
		redwall.setSize({ GRIDSIZE,10 });
		//start.setSize({ 50,10 });
	}
	else {
		if (dir == 1) {
			Utils::SetOrigin(redwall, Origins::MR);
			startpos = { position.x ,position.y };
			redwall.setPosition(startpos);
		}
		else if (dir == 3) {
			Utils::SetOrigin(redwall, Origins::ML);
			startpos = { position.x  ,position.y };
			redwall.setPosition(startpos);

		}
		redwall.setSize({ 10,GRIDSIZE });
		//start.setSize({ 10,50 });

	}
	Utils::SetOrigin(redwall, Origins::MC);

}

Redwall::~Redwall()
{

}

void Redwall::Update(float dt)
{
	enable = originactive;

	for (auto b : button) {
		if (!b->GetPressed()) {
			enable = !originactive;
			hitbox.setPosition(-100, -100);
			//destiny.setPosition(startpos);
			//redwall.setSize({ 0,0 });
			return;
		}
	}

	if (!enable) {
		if (dir == 0 || dir == 2) {
			if (dir == 0) {
				Utils::SetOrigin(redwall, Origins::MC);
				redwall.setPosition(startpos);
			}
			else if (dir == 2) {
				Utils::SetOrigin(redwall, Origins::MC);
				redwall.setPosition(startpos);
			}
			//redwall.setSize({ thickness,50 });
		}
		else {
			if (dir == 1) {
				Utils::SetOrigin(redwall, Origins::MC);
				redwall.setPosition(startpos);
			}
			else if (dir == 3) {
				Utils::SetOrigin(redwall, Origins::MC);
				redwall.setPosition(startpos);

			}
			//redwall.setSize({ 0,0 });
		}
		//hitbox.setSize(redwall.getSize());
		hitwall = false;

		redwall.setPosition(startpos);
		return;
	}

	Utils::SetOrigin(redwall, Origins::MC);

	if (!hitwall) {
	//	if (dir == 0 || dir == 2) {
	//		redwall.setSize({ redwall.getSize().x,redwall.getSize().y + 100 });
	//		if (dir == 0) {
	//			Utils::SetOrigin(redwall, Origins::TC);
	//		}
	//		else if (dir == 2) {
	//			Utils::SetOrigin(redwall, Origins::BC);

	//		}
	//	}
	//	else {
	//		redwall.setSize({ redwall.getSize().x + 100,redwall.getSize().y });
	//		if (dir == 1) {
	//			Utils::SetOrigin(redwall, Origins::MR);

	//		}
	//		else if (dir == 3) {
	//			Utils::SetOrigin(redwall, Origins::ML);
	//		}

	//	}
	////	AddParticle();
	//}
	//else if (hitwall ) {
	//	if (dir == 0) {
	//		redwall.setSize({ redwall.getSize().x,whohitwall->GetGlobalBounds().top - redwall.getPosition().y });
	//	}
	//	else if (dir == 2) {
	//		Utils::SetOrigin(redwall, Origins::BC);
	//		redwall.setSize({ redwall.getSize().x,redwall.getPosition().y - (whohitwall->GetGlobalBounds().top + whohitwall->GetGlobalBounds().height) });

	//	}
	//	else if (dir == 1) {
	//		Utils::SetOrigin(redwall, Origins::MR);

	//		redwall.setSize({ redwall.getPosition().x - (whohitwall->GetGlobalBounds().left + whohitwall->GetGlobalBounds().width),redwall.getSize().y });

	//	}
	//	else if (dir == 3) {
	//		Utils::SetOrigin(redwall, Origins::ML);

	//		redwall.setSize({ (whohitwall->GetGlobalBounds().left) - redwall.getPosition().x,redwall.getSize().y });

	//	}
	}

	if (dir == 0 || dir == 2) {
		redwall.setSize({ GRIDSIZE,thickness });
	}else
		redwall.setSize({ thickness,GRIDSIZE });

	redwall.setPosition(startpos);

	//	Utils::SetOrigin(destiny, Origins::MC);
	hitbox.setSize({ redwall.getSize().x+40, redwall.getSize().y+40});
	hitbox.setOrigin(redwall.getOrigin());
	hitbox.setPosition(redwall.getPosition());
	hitbox.setFillColor(Color::Green);
}

void Redwall::Draw(RenderWindow& window)
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
		if (enable){
			window.draw(redwall);
			//window.draw(hitbox);
		}

	}

	
}


void Redwall::SetButtonlist(vector<Button*>& button)
{
	for (auto b : button) {
		for (int i = 0; i < buttonid.size(); i++) {
			if (b->GetButtonId() == buttonid[i]) {
				this->button.push_back(b);
			}
		}
	}
}

SpriteObj* Redwall::NewThis()
{
	return new Redwall;
}

void Redwall::InitTexBox()
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

void Redwall::DrawTexBox(RenderWindow& window)
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
