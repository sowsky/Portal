#pragma once
#include "SpriteObj.h"
class Player : public SpriteObj
{
public:
	Player();
	virtual ~Player();

	virtual SpriteObj* NewThis();
public:
	static int GetPlayerNum();
protected:
	static int playerNum;
};

