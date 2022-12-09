#pragma once
#include "SpriteObj.h"
class AngledTile : public SpriteObj
{
public:
	AngledTile();
	virtual ~AngledTile();	

	virtual SpriteObj* NewThis();

	virtual void Update(float dt);
	virtual void Draw(RenderWindow& window);
protected:
};

