#include "Button.h"
#include "../Manager/ResourceMgr.h"
#include "../FrameWork/Utils.h"
//#include "NumBox.h"

bool Button::isEditMap = false;
int Button::buttonNum = 0;

Button::Button()
	:sideFaces(frontFace, sprite),
	b_sideFaces(b_frontFace, b_pivot)
{
	SetResourceTexture("Graphics/button.png");
	id = 'b';

	type = ObjectType::Trigger;

	hitbox = new RectangleShape;
	hitbox->setFillColor(Color::Red);
	hitbox->setSize(sprite.getPosition());
	hitbox->setPosition(sprite.getPosition());

	objSize = ObjectSize::Normal;
	attatchedPos = Rotate::Down;

	buttonNum++;
	buttonId = buttonNum;

	/////////////////////
	
	Vector2u buttonTexSize = RESOURCEMGR->GetTexture("Graphics/button/front_n.png")->getSize();

	float buttonTexRatio = buttonTexSize.x / buttonTexSize.y;

	frontSize = { GRIDSIZE / DEPTH * 0.8f, GRIDSIZE / DEPTH / buttonTexRatio * 0.8f };

	SetSpriteTex(frontFace, "Graphics/button/front.png");
	Utils::SetOrigin(frontFace, Origins::BC);	
	Utils::SetSpriteSize(frontFace, frontSize);

	normal = RESOURCEMGR->GetTexture("Graphics/button/front_n.png");

	sideFaces.SetDepth(DEPTH);
	sideFaces.SetSidesTex("Graphics/button/front.png", 1);
	sideFaces.SetSidesTex("Graphics/button/front.png", 3);
	sideFaces.SetSidesTex("Graphics/button/up.png", 0);	
	sideFaces.SetBackFaceSize(frontSize);
	sideFaces.SetBackFaceOrigin(Origins::BC);
}



Button::~Button()
{

}

SpriteObj* Button::NewThis()
{
	return new Button;
}

void Button::Draw(RenderWindow& window)
{
	
	if(!isPlayingGame)
		WireableObject::Draw(window);
	else
	{
		Utils::SetOrigin(*hitbox, Origins::MC);
		hitbox->setSize({ Utils::GetSpriteSize(sprite).x - 20,Utils::GetSpriteSize(sprite).y });
		hitbox->setPosition(sprite.getPosition());
		if (hitbox != nullptr
			&& !isEditMap) {
			//	window.draw(*hitbox);
		}		
		sideFaces.Draw(window);
	}
}

void Button::Draw(RenderTexture& diffuse, Shader& nShader, RenderTexture& normal)
{
	diffuse.draw(frontFace);
	NormalPass(normal, frontFace, this->normal, nShader);
}
