#pragma once
#include "SpriteObj.h"
class Button : public SpriteObj
{
public:
	Button();
	virtual ~Button();

	virtual SpriteObj* NewThis();
protected:
};

