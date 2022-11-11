#pragma once
#include "SpriteObj.h"
class Tile : public SpriteObj
{
public:
	Tile();
	virtual ~Tile();

	virtual SpriteObj* NewThis();
protected:

};

