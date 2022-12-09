#include "Redwall.h"

Redwall::Redwall()
{
	SetResourceTexture("Graphics/Ui/fizzlertool.png");
	id = 'r';

	type = ObjectType::Catcher;

	objSize = ObjectSize::Normal;
	attatchedPos = Rotate::Down;
}

Redwall::Redwall(Vector2f& position, vector<int> buttonlist, bool active, int dir)
	:active(active), dir(dir), buttonid(buttonlist)
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
		redwall.setSize({ thickness,10 });
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
		redwall.setSize({ 10,thickness });
		//start.setSize({ 10,50 });

	}

}

Redwall::~Redwall()
{

}

void Redwall::Update(float dt)
{
	active = true;

	for (auto b : button) {
		if (!b->GetPressed()) {
			active = false;
			hitbox.setPosition(-100, -100);
			//destiny.setPosition(startpos);
			return;
		}
	}

	if (!active) {
		if (dir == 0 || dir == 2) {
			if (dir == 0) {
				Utils::SetOrigin(redwall, Origins::MC);
				redwall.setPosition(startpos);
			}
			else if (dir == 2) {
				Utils::SetOrigin(redwall, Origins::MC);
				redwall.setPosition(startpos);
			}
			redwall.setSize({ thickness,50 });
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
			redwall.setSize({ 50,thickness });
		}
		//hitbox.setSize(redwall.getSize());
		hitwall = false;

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
	}
	else
	{
		if (active){
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
