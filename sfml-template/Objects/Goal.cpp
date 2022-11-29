#include "Goal.h"
#include "../Manager/ResourceMgr.h"
#include "../FrameWork/Utils.h"
#include "Button.h"
#include "../FrameWork/InputMgr.h"
#include "../FrameWork/Const.h"

Goal::Goal()	
{
	SetResourceTexture("Graphics/goal2.png");
	
	id = '@';	

	type = ObjectType::Catcher;
	objSize = ObjectSize::Big;
	attatchedPos = Rotate::Down;

	Utils::SetOrigin(sprite, Origins::BC);

}

Goal::Goal(Vector2f currgrid, float size, vector<int> buttonlist)	
{
	SetResourceTexture("Graphics/goal.png");
	id = '@';

	Utils::SetOrigin(sprite, Origins::MC);

	SetSize({ GRIDSIZE,GRIDSIZE });
	SetPos(currgrid);

	buttonid = buttonlist;

	door.setPrimitiveType(Quads);
	door.resize(8);
	doorTex = RESOURCEMGR->GetTexture("Graphics/door.png");

	Vector2f texSize = (Vector2f)doorTex->getSize();
	leftDoorTexCoords = 0.f;
	rightDoorTexCoords = texSize.x;

	Vector2f pos = sprite.getPosition();
	leftDoorPos = pos.x;
	rightDoorPos = pos.x;

	on = false;

	float dp = DEPTH * 2 - 1.f;
	backFace.setSize({ GRIDSIZE * dp, GRIDSIZE * dp });
	Utils::SetOrigin(backFace, Origins::MC);

	Vector2u goalTexSize = sprite.getTexture()->getSize();
	normalMap = RESOURCEMGR->GetTexture("Graphics/goaln.png");
	for (int i = 0; i < sideTiles.size(); i++)
	{
		tileTextures[i] = RESOURCEMGR->GetTexture("Graphics/goalside.png");
		sideTiles[i].first = true;
		sideTiles[i].second.setPrimitiveType(Quads);
		sideTiles[i].second.resize(4);
		sideTiles[i].second[0].texCoords = { 0.f, 0.f };
		sideTiles[i].second[1].texCoords = { (float)goalTexSize.x, 0.f };
		sideTiles[i].second[2].texCoords = (Vector2f)goalTexSize;
		sideTiles[i].second[3].texCoords = { 0.f, (float)goalTexSize.y };
	}
}

Goal::~Goal()
{	
	/*for (auto b : button)
		delete b;
	button.clear();*/
}

SpriteObj* Goal::NewThis()
{
	return new Goal;
}

void Goal::Update(float dt)
{
	SetDoor(dt);
	for (auto b : button) {
		if (!b->GetPressed()) {
			on = false;
			return;
		}
	}

	//active door
	on = true;
}

void Goal::Draw(RenderWindow& window)
{	
	if (!isPlayingGame)
	{		
		WireableObject::Draw(window);
	}	
	if (isPlayingGame)
	{
		DrawSides(window);
		window.draw(door, doorTex);
		window.draw(sprite);
	}		
}

void Goal::Draw(RenderTexture& diffuse, Shader& nShader, RenderTexture& normal)
{
	//diffuse.draw(sprite);
	//NormalPass(normal, sprite, normalMap, nShader);
}

void Goal::DrawSides(RenderWindow& window)
{
	Vector2f vanishingPoint = window.getView().getCenter();

	backFace.setPosition(
		sprite.getPosition() + (vanishingPoint - sprite.getPosition()) * (1.f - DEPTH)
	);

	FloatRect backRect = backFace.getGlobalBounds();
	FloatRect frontRect = sprite.getGlobalBounds();

	if (sideTiles[0].first)
	{
		sideTiles[0].second[0].position = { backRect.left, backRect.top };
		sideTiles[0].second[1].position = { backRect.left + backRect.width, backRect.top };
		sideTiles[0].second[2].position = { frontRect.left + frontRect.width, frontRect.top };
		sideTiles[0].second[3].position = { frontRect.left, frontRect.top };
	}

	if (sideTiles[1].first)
	{
		sideTiles[1].second[0].position = { frontRect.left + frontRect.width, frontRect.top };
		sideTiles[1].second[1].position = { backRect.left + backRect.width, backRect.top };
		sideTiles[1].second[2].position = { backRect.left + backRect.width, backRect.top + backRect.height };
		sideTiles[1].second[3].position = { frontRect.left + frontRect.width, frontRect.top + frontRect.height };
	}

	if (sideTiles[2].first)
	{
		sideTiles[2].second[0].position = { backRect.left, backRect.top + backRect.height };
		sideTiles[2].second[1].position = { backRect.left + backRect.width, backRect.top + backRect.height };
		sideTiles[2].second[2].position = { frontRect.left + frontRect.width, frontRect.top + frontRect.height };
		sideTiles[2].second[3].position = { frontRect.left , frontRect.top + frontRect.height };
	}

	if (sideTiles[3].first)
	{
		sideTiles[3].second[0].position = { frontRect.left, frontRect.top };
		sideTiles[3].second[1].position = { backRect.left, backRect.top };
		sideTiles[3].second[2].position = { backRect.left, backRect.top + backRect.height };
		sideTiles[3].second[3].position = { frontRect.left , frontRect.top + frontRect.height };
	}

	for (int i = 0; i < sideTiles.size(); i++)
	{
		if (sideTiles[i].first)
			window.draw(sideTiles[i].second, tileTextures[i]);
	}
}

void Goal::SetDoor(float dt)
{
	Vector2f texSize = (Vector2f)doorTex->getSize();
	Vector2f pos = sprite.getPosition();
	float transSpeed = dt;

	if (on)
	{
		if (leftDoorTexCoords <= texSize.x * 0.35f)
			leftDoorTexCoords += texSize.x * transSpeed;
		if (leftDoorTexCoords > texSize.x * 0.35f)
			leftDoorTexCoords = texSize.x * 0.35f;

		if (leftDoorPos >= pos.x - GRIDSIZE * 0.35f)
			leftDoorPos -= GRIDSIZE * transSpeed;		
		if (leftDoorPos < pos.x - GRIDSIZE * 0.35f)
			leftDoorPos = pos.x - GRIDSIZE * 0.35f;

		if (rightDoorTexCoords >= texSize.x * 0.65f)
			rightDoorTexCoords -= texSize.x * transSpeed;
		if (rightDoorTexCoords < texSize.x * 0.65f)
			rightDoorTexCoords = texSize.x * 0.65f;

		if (rightDoorPos <= pos.x + GRIDSIZE * 0.35f)
			rightDoorPos += GRIDSIZE * transSpeed;
		if (rightDoorPos > pos.x + GRIDSIZE * 0.35f)
			rightDoorPos = pos.x + GRIDSIZE * 0.35f;
	}
	else
	{
		if (leftDoorTexCoords >= 0.f)
			leftDoorTexCoords -= texSize.x * transSpeed;
		if (leftDoorTexCoords < 0.f)
			leftDoorTexCoords = 0.f;

		if (leftDoorPos <= pos.x)
			leftDoorPos += GRIDSIZE * transSpeed;
		if (leftDoorPos > pos.x)
			leftDoorPos = pos.x;

		if (rightDoorTexCoords <= texSize.x)
			rightDoorTexCoords += texSize.x * transSpeed;
		if (rightDoorTexCoords > texSize.x)
			rightDoorTexCoords = texSize.x;

		if (rightDoorPos >= pos.x)
			rightDoorPos -= GRIDSIZE * transSpeed;
		if (rightDoorPos < pos.x)
			rightDoorPos = pos.x;
	}


	door[0].texCoords = { leftDoorTexCoords,0.f };
	door[1].texCoords = { texSize.x * 0.5f,0.f };
	door[2].texCoords = { texSize.x * 0.5f,texSize.y };
	door[3].texCoords = { leftDoorTexCoords,texSize.y };

	door[0].position = { pos.x - GRIDSIZE * 0.5f, pos.y - GRIDSIZE * 0.5f };
	door[1].position = { leftDoorPos, pos.y - GRIDSIZE * 0.5f };
	door[2].position = { leftDoorPos, pos.y + GRIDSIZE * 0.5f };
	door[3].position = { pos.x - GRIDSIZE * 0.5f, pos.y + GRIDSIZE * 0.5f };

	door[4].texCoords = { texSize.x * 0.5f,0.f };
	door[5].texCoords = { rightDoorTexCoords, 0.f };
	door[6].texCoords = { rightDoorTexCoords, texSize.y };
	door[7].texCoords = { texSize.x * 0.5f, texSize.y };

	door[4].position = { rightDoorPos, pos.y - GRIDSIZE * 0.5f };
	door[5].position = { pos.x + GRIDSIZE * 0.5f, pos.y - GRIDSIZE * 0.5f };
	door[6].position = { pos.x + GRIDSIZE * 0.5f, pos.y + GRIDSIZE * 0.5f };
	door[7].position = { rightDoorPos, pos.y + GRIDSIZE * 0.5f };
}

void Goal::SetButtonlist(vector<Button*>& button)
{
	for (auto b : button) {
		for (int i = 0; i < buttonid.size(); i++) {
			if (b->GetButtonId() == buttonid[i]) {
				this->button.push_back(b);
			}
		}
	}
}
