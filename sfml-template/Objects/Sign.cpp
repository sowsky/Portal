#include "Sign.h"
#include "../Manager/ResourceMgr.h"


Sign::Sign(char sId, bool editing)
	:signId(sId), sideFaces(frontFace, sprite)
{
	SetResourceTexture("Graphics/signs/dropper.png");

	id = '7';

	type = ObjectType::None;
	objSize = ObjectSize::Big;
	attatchedPos = Rotate::Down;

	Utils::SetOrigin(sprite, Origins::BC);

	if (editing)
		return;

	frontSize = { GRIDSIZE / DEPTH, GRIDSIZE / DEPTH };
	SetSpriteTex(frontFace, "Graphics/signs/dropper_t.png");
	Utils::SetOrigin(frontFace, Origins::MC);
	Utils::SetSpriteSize(frontFace, frontSize);
	
	
	Utils::SetOrigin(sprite, Origins::MC);
	SetResourceTexture("Graphics/signs/dropper_t.png");
	Utils::SetSpriteSize(sprite, { GRIDSIZE,GRIDSIZE });

	sideFaces.SetDepth(DEPTH);
	sideFaces.SetAllSidesTex("Graphics/Tile/64/tile1.png");
	sideFaces.GetBackFace().setTexture(RESOURCEMGR->GetTexture("Graphics/signs/dropper_t.png"));
	sideFaces.SetBackFaceSize(frontSize);
	sideFaces.SetBackFaceOrigin(Origins::MC);

	if (signId == '2')
	{
		Utils::SetSpriteSize(frontFace, { GRIDSIZE ,GRIDSIZE });
	}

	if (signId == '3')
	{
		for (int i = 0; i < 4; i++)
		{
			sideFaces.SetActiveSides(i, false);
		}
	}
}

Sign::~Sign()
{
}

void Sign::Update(float dt)
{
}

void Sign::Draw(RenderWindow& window)
{
	if(!isPlayingGame)
		window.draw(sprite);
	else
	{
		switch (signId)
		{
		case '1':
		{
			sideFaces.Draw(window);
			window.draw(frontFace);
			break;
		}
		case '2':
		{
			sideFaces.DrawHalf(window);
			window.draw(frontFace);
			break;
		}
		case '3':
		{
			sideFaces.Draw(window);
			window.draw(sideFaces.GetBackFace());
			break;
		}
		}
	}

}

SpriteObj* Sign::NewThis()
{
	return new Sign(signId);
}
