#include "Player.h"
#include "../FrameWork/InputMgr.h"
#include "../FrameWork/Utils.h"

Player::Player()
{
	SetResourceTexture("Graphics/player.png");
	id = 'p';

	hitbox = new RectangleShape;
	hitbox->setFillColor(Color::Red);
	

}

Player::~Player()
{
	delete hitbox;
}

SpriteObj* Player::NewThis()
{
	return new Player;
}

void Player::Move(float dt)
{
	if (InputMgr::GetKey(Keyboard::A)) {
		SetPos({ GetPos().x - 100 * dt
			, GetPos().y });
	}
	else if (InputMgr::GetKey(Keyboard::D)) {
		SetPos({GetPos().x + 100 * dt
			,GetPos().y });
	}
	
	//jump
	if (InputMgr::GetKeyDown(Keyboard::Space) && ground) {
		ground = false;
		verticalspeed = -50;
	}

	if (!ground) {
		if (verticalspeed < 0) {//going up
			verticalspeed = verticalspeed + (dt * 100);
		}
		else {
			verticalspeed = verticalspeed + (dt * addspeed);
		}
		SetPos({ GetPos().x,GetPos().y + verticalspeed * dt });
	}
	else if (ground) {
		verticalspeed = 0;

	}
	
}

void Player::Update(float dt)
{
	SpriteObj::Update(dt);
	Utils::SetOrigin(*hitbox, Origins::BC);

	hitbox->setSize({ sprite.getGlobalBounds().width - 10,sprite.getGlobalBounds().height });
	hitbox->setPosition(sprite.getPosition());
}

void Player::Draw(RenderWindow& window)
{
	SpriteObj::Draw(window);
	window.draw(*hitbox);

}
