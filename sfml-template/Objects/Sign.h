#pragma once
#include "SpriteObj.h"

class VertexArrayObj;
class Sign : public SpriteObj
{
public:
	Sign(char sId, bool editing = true);
	virtual ~Sign();

	virtual void Update(float dt);
	virtual void Draw(RenderWindow& window);

	virtual SpriteObj* NewThis();

	char GetSignId() { return signId; }
	void SetSignId(char id) { signId = id; }
protected:
	char signId;
	bool isEditing;

	Vector2f frontSize;

	Sprite frontFace;
	VertexArrayObj sideFaces;
	
};

