#pragma once
#include "SpriteObj.h"
class SmallTile : public SpriteObj
{
public:
	SmallTile();
	virtual ~SmallTile();

	virtual SpriteObj* NewThis();
protected:

};

