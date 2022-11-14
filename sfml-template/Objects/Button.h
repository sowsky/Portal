#pragma once
#include "WireableObject.h"
class Button : public WireableObject
{
public:
	Button();
	virtual ~Button();

	virtual void Update(float dt);	

	virtual SpriteObj* NewThis();
public:
	
protected:
	bool isPressed;
};

