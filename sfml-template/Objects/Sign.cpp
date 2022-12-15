#include "Sign.h"
#include "../Manager/ResourceMgr.h"


Sign::Sign(char sId, bool editing)
	:signId(sId), sideFaces(frontFace, sprite)
{
	string texId;
	switch (signId)
	{
	case '0':
		texId = "Graphics/signs/sign0.png";
		break;
	case '1':
		texId = "Graphics/signs/sign1.png";
		break;
	case '2':
		texId = "Graphics/signs/sign2.png";
		break;
	case '3':
		texId = "Graphics/signs/sign3.png";
		break;
	case '4':
		texId = "Graphics/signs/sign4.png";
		break;
	case '5':
		texId = "Graphics/signs/sign5.png";
		break;
	case '6':
		texId = "Graphics/signs/sign6.png";
		break;
	case '7':
		texId = "Graphics/signs/sign7.png";
		break;
	case '8':
		texId = "Graphics/signs/sign8.png";
		break;
	case '9':
		texId = "Graphics/signs/sign9.png";
		break;
	case 'a':
		texId = "Graphics/signs/sign10.png";
		break;
	case 'b':
		texId = "Graphics/signs/sign11.png";
		break;
	case 'c':
		texId = "Graphics/signs/sign12.png";
		break;
	case 'd':
		texId = "Graphics/signs/sign13.png";
		break;
	case 'e':
		texId = "Graphics/signs/sign14.png";
		break;
	case 'f':
		texId = "Graphics/signs/sign15.png";
		break;
	case 'g':
		texId = "Graphics/signs/sign16.png";
		break;
	case 'h':
		texId = "Graphics/signs/sign17.png";
		break;
	case 'i':
		texId = "Graphics/signs/sign18.png";
		break;
	case 'j':
		texId = "Graphics/signs/sign19.png";
		break;
	case 'k':
		texId = "Graphics/signs/sign20.png";
		break;
	case 'l':
		texId = "Graphics/signs/sign21.png";
		break;
	}

	SetResourceTexture(texId);

	id = '7';

	type = ObjectType::None;
	objSize = ObjectSize::Big;
	attatchedPos = Rotate::Down;

	Utils::SetOrigin(sprite, Origins::BC);

	if (editing)
		return;
	
	frontSize = { GRIDSIZE / DEPTH, GRIDSIZE / DEPTH };
	SetSpriteTex(frontFace, texId);
	Utils::SetOrigin(frontFace, Origins::MC);
	Utils::SetSpriteSize(frontFace, frontSize);
	
	
	Utils::SetOrigin(sprite, Origins::MC);
	SetResourceTexture(texId);
	Utils::SetSpriteSize(sprite, { GRIDSIZE,GRIDSIZE });

	sideFaces.SetDepth(DEPTH);
	sideFaces.GetBackFace().setTexture(RESOURCEMGR->GetTexture(texId));
	sideFaces.SetBackFaceSize(frontSize);
	sideFaces.SetBackFaceOrigin(Origins::MC);

	if (signId == 'l')
	{
		frontSize = { GRIDSIZE * 2.f / DEPTH, GRIDSIZE / DEPTH };
		SetSpriteTex(frontFace, texId);
		Utils::SetOrigin(frontFace, Origins::ML);
		frontFace.setOrigin(frontFace.getOrigin().x + GRIDSIZE * 0.5f, frontFace.getOrigin().y);
		Utils::SetSpriteSize(frontFace, frontSize);


		Utils::SetOrigin(sprite, Origins::ML);
		sprite.setOrigin(sprite.getOrigin().x + GRIDSIZE * 0.5f, sprite.getOrigin().y);
		SetResourceTexture(texId);
		Utils::SetSpriteSize(sprite, { GRIDSIZE * 2.f ,GRIDSIZE });

		sideFaces.SetDepth(DEPTH);
		sideFaces.GetBackFace().setTexture(RESOURCEMGR->GetTexture(texId));
		sideFaces.SetBackFaceSize(frontSize);
		sideFaces.SetBackFaceOrigin(Origins::ML);
		sideFaces.GetBackFace().setOrigin(sideFaces.GetBackFace().getOrigin().x + GRIDSIZE * 0.5f, sideFaces.GetBackFace().getOrigin().y);		
	}

	if (
		signId == '0' ||
		signId == '1' ||
		signId == '2' ||
		signId == '3' ||
		signId == '4' ||
		signId == '5' ||
		signId == '6' ||
		signId == '7' ||
		signId == '8' ||
		signId == '9' ||
		signId == 'a'
		)
	{
		frontSize = { GRIDSIZE * 1.5f / DEPTH, GRIDSIZE  * 1.5f / DEPTH };
		SetSpriteTex(frontFace, texId);
		Utils::SetOrigin(frontFace, Origins::TL);
		frontFace.setOrigin(frontFace.getOrigin().x + GRIDSIZE * 0.25f, frontFace.getOrigin().y + GRIDSIZE * 0.25f);
		Utils::SetSpriteSize(frontFace, frontSize);


		Utils::SetOrigin(sprite, Origins::TL);
		sprite.setOrigin(sprite.getOrigin().x + GRIDSIZE * 0.25f, sprite.getOrigin().y + GRIDSIZE * 0.25f);
		SetResourceTexture(texId);
		Utils::SetSpriteSize(sprite, { GRIDSIZE * 2.f ,GRIDSIZE });

		sideFaces.SetDepth(DEPTH);
		sideFaces.GetBackFace().setTexture(RESOURCEMGR->GetTexture(texId));
		sideFaces.SetBackFaceSize(frontSize);
		sideFaces.SetBackFaceOrigin(Origins::TL);
		sideFaces.GetBackFace().setOrigin(sideFaces.GetBackFace().getOrigin().x + GRIDSIZE * 0.25f, sideFaces.GetBackFace().getOrigin().y + GRIDSIZE * 0.25f);
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
		sideFaces.Draw(window);
		window.draw(sideFaces.GetBackFace());
	}

}

SpriteObj* Sign::NewThis()
{
	return new Sign(signId);
}
