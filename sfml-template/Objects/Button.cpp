#include "Button.h"
#include "../Manager/ResourceMgr.h"
#include "../FrameWork/Utils.h"
//#include "NumBox.h"

bool Button::isEditMap = false;
int Button::buttonNum = 0;

Button::Button()
	:sideFaces(frontFace, sprite),
	upSideFaces(upFrontFace, upPivot)
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
	
	Vector2u buttonTexSize = RESOURCEMGR->GetTexture("Graphics/button/front.png")->getSize();

	float buttonTexRatio = buttonTexSize.x / buttonTexSize.y;

	frontSize = { GRIDSIZE / DEPTH * 0.8f, GRIDSIZE / DEPTH / buttonTexRatio * 0.8f };

	SetSpriteTex(frontFace, "Graphics/button/front.png");
	Utils::SetOrigin(frontFace, Origins::BC);	
	Utils::SetSpriteSize(frontFace, frontSize);

	normal = RESOURCEMGR->GetTexture("Graphics/button/front_n.png");

	sideFaces.SetDepth(DEPTH + 0.01f );
	sideFaces.SetSidesTex("Graphics/button/front.png", 1);
	sideFaces.SetSidesTex("Graphics/button/front.png", 3);
	sideFaces.SetSidesTex("Graphics/button/up.png", 0);	
	sideFaces.SetBackFaceSize(frontSize);
	sideFaces.SetBackFaceOrigin(Origins::BC);	

	//////////////////////////
	Utils::SetOrigin(upPivot, Origins::BC);

	Vector2u upButtonTexSize = RESOURCEMGR->GetTexture("Graphics/button/buttonfront.png")->getSize();

	float upButtonTexRatio = upButtonTexSize.x / upButtonTexSize.y;

	upFrontSize = { GRIDSIZE / DEPTH * 0.7f, GRIDSIZE / DEPTH / upButtonTexRatio * 0.7f };

	SetSpriteTex(upFrontFace, "Graphics/button/buttonfront.png");
	Utils::SetOrigin(upFrontFace, Origins::BC);
	Utils::SetSpriteSize(upFrontFace, upFrontSize);

	upNormal = RESOURCEMGR->GetTexture("Graphics/button/buttonfront_n.png");

	upSideFaces.SetDepth(DEPTH + 0.015f);
	upSideFaces.SetSidesTex("Graphics/button/buttonfront.png", 1);
	upSideFaces.SetSidesTex("Graphics/button/buttonfront.png", 2);
	upSideFaces.SetSidesTex("Graphics/button/buttonfront.png", 3);
	upSideFaces.SetSidesTex("Graphics/button/buttonup.png", 0);
	upSideFaces.SetBackFaceSize(upFrontSize);
	upSideFaces.SetBackFaceOrigin(Origins::BC);

	buttonHeightFix = Utils::GetSpriteSize(frontFace).y * DEPTH;	

	upSideFaces.GetBackFace().setFillColor(Color::Red);
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
		window.draw(upSideFaces.GetBackFace());
		upSideFaces.Draw(window);
	}
}

void Button::Update(float dt)
{
	UpdatePressureAnimation(dt);	
}

void Button::SetPressed()
{
	isPress = !isPress;		
	
}



void Button::Draw(RenderTexture& diffuse, Shader& nShader, RenderTexture& normal)
{
	diffuse.draw(upFrontFace);
	NormalPass(normal, upFrontFace, upNormal, nShader);

	diffuse.draw(frontFace);
	NormalPass(normal, frontFace, this->normal, nShader);
}

void Button::SetUpButtonPos()
{
	
	upPivot.setPosition(sprite.getPosition().x,sprite.getPosition().y - buttonHeightFix);
	upPivot.setRotation(sprite.getRotation());
}

void Button::SetButtonRoation(int val)
{
	rot = val;
	if (val == 0) {
		upPivot.setPosition(sprite.getPosition().x, sprite.getPosition().y + buttonHeightFix);
	}
	else if (val == 1) {
		upPivot.setPosition(sprite.getPosition().x - buttonHeightFix, sprite.getPosition().y);
	}
	else if (val == 3) {
		upPivot.setPosition(sprite.getPosition().x + buttonHeightFix, sprite.getPosition().y);
	}
	else
		upPivot.setPosition(sprite.getPosition().x, sprite.getPosition().y - buttonHeightFix);
}

void Button::UpdatePressureAnimation(float dt)
{	
	if (isPress)
	{
		switch (rot)
		{
		case 0 :
		{
			if (upPivot.getPosition().y - sprite.getPosition().y <= limit)
			{
				upPivot.setPosition(sprite.getPosition().x, sprite.getPosition().y + limit);
				break;
			}
			upPivot.move({ 0, - move * dt });			
			break;
		}
		case 1:
		{
			if (sprite.getPosition().x - upPivot.getPosition().x <= limit)
			{
				upPivot.setPosition(sprite.getPosition().x - limit, sprite.getPosition().y);
				break;
			}
			upPivot.move({ move * dt, 0 });
			break;
		}
		case 2:
		{
			if (sprite.getPosition().y - upPivot.getPosition().y <= limit)
			{
				upPivot.setPosition(upPivot.getPosition().x, sprite.getPosition().y - limit);
				break;
			}
			upPivot.move({ 0, move * dt });
			break;
		}
		case 3:
		{
			if (upPivot.getPosition().x - sprite.getPosition().x <= limit)
			{
				upPivot.setPosition(sprite.getPosition().x + limit, sprite.getPosition().y);
				break;
			}
			upPivot.move({ - move * dt, 0 });
			break;
		}

		}
	}
	else
	{
		switch (rot)
		{
		case 0:
		{
			if (upPivot.getPosition().y - sprite.getPosition().y >= (int)buttonHeightFix)
			{
				upPivot.setPosition(sprite.getPosition().x, sprite.getPosition().y + (int)buttonHeightFix);
				break;
			}
			upPivot.move({ 0, move * dt });
			break;
		}
		case 1:
		{
			if (sprite.getPosition().x - upPivot.getPosition().x >= (int)buttonHeightFix)
			{
				upPivot.setPosition(sprite.getPosition().x - (int)buttonHeightFix, sprite.getPosition().y);
				break;
			}
			upPivot.move({  - move * dt, 0 });
			break;
		}
		case 2:
		{
			if (sprite.getPosition().y - upPivot.getPosition().y >= (int)buttonHeightFix)
			{
				upPivot.setPosition(upPivot.getPosition().x, sprite.getPosition().y - (int)buttonHeightFix);
				break;
			}
			upPivot.move({ 0, - move * dt });
			break;
		}
		case 3:
		{
			if (upPivot.getPosition().x - sprite.getPosition().x >= (int)buttonHeightFix)
			{
				upPivot.setPosition(sprite.getPosition().x + (int)buttonHeightFix, sprite.getPosition().y);
				break;
			}
			upPivot.move({ move * dt, 0 });
			break;
		}
		}
	}

	ChageTexOnoff(isPress);
}

void Button::ChageTexOnoff(bool press)
{	
	if (prevState == press)
		return;

	prevState = press;

	if (press)
	{
		SetSpriteTex(frontFace, "Graphics/button/front_on.png");
		sideFaces.SetSidesTex("Graphics/button/front_on.png", 1);
		sideFaces.SetSidesTex("Graphics/button/front_on.png", 3);
	}
	else
	{
		SetSpriteTex(frontFace, "Graphics/button/front.png");
		sideFaces.SetSidesTex("Graphics/button/front.png", 1);
		sideFaces.SetSidesTex("Graphics/button/front.png", 3);
	}
}
