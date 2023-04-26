#include "Switch.h"
#include "../Manager/ResourceMgr.h"

bool Switch::showTimer = false;

Switch::Switch()
{
	SetResourceTexture("Graphics/switch.png");
	id = 's';
	type = ObjectType::Trigger;
	objSize = ObjectSize::Normal;
	attatchedPos = Rotate::Down;

	switchType = false;
	time = 0.f;

	buttonId = buttonNum * -1;
}

Switch::Switch(Vector2f position, int rotation, int id, float time, bool switchtype)
	: switchType(switchtype), time(time), rot(rotation)
{
	switchType ?
		SetResourceTexture("Graphics/switchaf.png") : SetResourceTexture("Graphics/switch.png");
	SetOrigin(Origins::BC);

	SetSize({ 100,40 });

	buttonId = id;

	hitbox = new RectangleShape();
	Utils::SetOrigin(*hitbox, Origins::BC);

	if (rotation == 0) {			//top of gird
		hitbox->setPosition({ position.x,position.y - GRIDSIZE / 2 });
		hitbox->setSize({ GRIDSIZE,GRIDSIZE / 4 });
		SetRotation(180.f);

	}
	else if (rotation == 1) {	//right of gird
		hitbox->setPosition({ position.x + GRIDSIZE / 2,position.y });
		hitbox->setSize({ GRIDSIZE,GRIDSIZE / 4 });
		SetRotation(-90.f);


	}
	else if (rotation == 2) {	//bottom of gird
		hitbox->setPosition({ position.x, position.y + GRIDSIZE / 2 });
		hitbox->setSize({ GRIDSIZE,GRIDSIZE / 4 });

	}
	else if (rotation == 3) {	//left of gird
		hitbox->setPosition({ position.x - GRIDSIZE / 2,position.y });
		hitbox->setSize({ GRIDSIZE ,GRIDSIZE / 4 });
		SetRotation(90.f);

	}

	hitbox->setFillColor(Color::Transparent);
	if (rotation == 0 || rotation == 2)
		hitbox->setSize({ 10,40 });
	else
		hitbox->setSize({ 40,10 });


	timerTex.setFont(*RESOURCEMGR->GetFont("Fonts/DS-DIGI.TTF"));
	timerTex.setFillColor(switchType ? Color::Yellow : Color::Red);
	timerTex.setCharacterSize(40);
	indicator.setPointCount(3);
	indicator.setFillColor(switchType? Color::Yellow : Color::Red);
	indicator.setRadius(30);	
	Utils::SetOrigin(timerTex, Origins::MC);
	timerTex.setPosition(position.x, position.y - GRIDSIZE * 0.5f);

	SetPos(hitbox->getPosition());

}

Switch::~Switch()
{
}

SpriteObj* Switch::NewThis()
{
	return new Switch;
}

void Switch::Update(float dt)
{

	if (rot == 0) {
		Utils::SetOrigin(*hitbox, Origins::TC);
	}
	else if (rot == 1) {
		Utils::SetOrigin(*hitbox, Origins::MR);
	}
	else if (rot == 2) {
		Utils::SetOrigin(*hitbox, Origins::BC);
	}
	else if (rot == 3) {
		Utils::SetOrigin(*hitbox, Origins::ML);
	}
	hitbox->setPosition(GetPos());



	if (time != 0) {
		remainingtime -= dt;
	}

	if (remainingtime <=0) {
		if (!switchType&&time!=0) {   //sustatin while on
			isPress = false;
		}
		else if (switchType&&after) {
			isPress = true;
		}
	}

	//////////////after work
	if (remainingtime <= 0)
		remainingtime = time;

	////////////////

	timerTex.setString(to_string((int)(remainingtime + 0.99f)));


}

void Switch::Draw(RenderWindow& window)
{
	//WireableObject::Draw(window);
	//Utils::SetOrigin(*hitbox-> Origins::MC);
	//hitbox->>setSize({ Utils::GetSpriteSize(sprite).x - 20,Utils::GetSpriteSize(sprite).y });
	//hitbox->>setPosition(sprite.getPosition());
	//if (hitbox->!= nullptr
	//	&& !isEditMap) {
	//	//	window.draw(*hitbox->;
	//}

	if (!isPlayingGame)
	{
		WireableObject::Draw(window);
	}
	else
	{
		window.draw(*hitbox);
		SpriteObj::Draw(window);
		if(!switchType && isPress && remainingtime)
			window.draw(timerTex);		
		if (switchType && !isPress && after)
			window.draw(timerTex);
	}
}

void Switch::Draw(RenderTexture& diffuse, Shader& nShader, RenderTexture& normal)
{
}

void Switch::SetSwitchActive()
{
	isPress = !isPress;
	if (!switchType && time != 0) {
		isPress = true;
	}
	else if (switchType) {
		isPress = false;
		after = true;
	}
	remainingtime = time;

}
