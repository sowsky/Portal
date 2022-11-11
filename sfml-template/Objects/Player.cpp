#include "Player.h"

int Player::playerNum = 0;

Player::Player()
{
	SetResourceTexture("Graphics/player.png");
	id = 'p';
	playerNum++;
}

Player::~Player()
{
	playerNum--;
}

SpriteObj* Player::NewThis()
{
	return new Player;
}

int Player::GetPlayerNum()
{
	return playerNum;
}
