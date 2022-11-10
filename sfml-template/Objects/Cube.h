#pragma once
#include "SpriteObj.h"
class Cube : public SpriteObj
{
public:
	Cube();
	virtual ~Cube();

	virtual SpriteObj* NewThis();
protected:
};

