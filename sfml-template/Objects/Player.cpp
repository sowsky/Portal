#include "Player.h"

Player::Player()
{
	SetResourceTexture("Graphics/player.png");
	id = 'p';
}

Player::~Player()
{
}

SpriteObj* Player::NewThis()
{
	return new Player;
}
