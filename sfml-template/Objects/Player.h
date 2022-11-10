#pragma once
#include "SpriteObj.h"
class Player : public SpriteObj
{
public:
	Player();
	virtual ~Player();

	virtual SpriteObj* NewThis();
protected:
};

