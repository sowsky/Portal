#include "Switch.h"

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
	SetResourceTexture("Graphics/switch.png");
	SetOrigin(Origins::BC);

	SetSize({ 10,40 });

	buttonId = id;

	hitbox = new RectangleShape();
	Utils::SetOrigin(*hitbox, Origins::BC);

	if (rotation == 0) {			//top of gird
		hitbox->setPosition({ position.x,position.y - GRIDSIZE / 2 });
		hitbox->setSize({ GRIDSIZE,GRIDSIZE / 4 });

	}
	else if (rotation == 1) {	//right of gird
		hitbox->setPosition({ position.x + GRIDSIZE / 2,position.y });
		hitbox->setSize({ GRIDSIZE,GRIDSIZE / 4 });

	}
	else if (rotation == 2) {	//bottom of gird
		hitbox->setPosition({ position.x, position.y + GRIDSIZE / 2 });
		hitbox->setSize({ GRIDSIZE,GRIDSIZE / 4 });

	}
	else if (rotation == 3) {	//left of gird
		hitbox->setPosition({ position.x - GRIDSIZE / 2,position.y });
		hitbox->setSize({ GRIDSIZE ,GRIDSIZE / 4 });
	}

	hitbox->setFillColor(Color::Yellow);
	if (rotation == 0 || rotation == 2)
		hitbox->setSize({ 10,40 });
	else
		hitbox->setSize({ 40,10 });

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
	Utils::SetOrigin(*hitbox, Origins::BC);
	if (rot == 0 || rot == 2)
		hitbox->setSize({ 10,40 });
	else
		hitbox->setSize({ 40,10 });

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
