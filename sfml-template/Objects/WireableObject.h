#pragma once
#include "SpriteObj.h"
class WireableObject : public SpriteObj
{
public:	
	virtual ~WireableObject();

	virtual void Init();

	virtual void Draw(RenderWindow& window);
	virtual void SetWireCheckBox();
protected:
	RectangleShape wireCheckBox;

	bool isSelected;

};

