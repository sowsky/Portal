#include "Switch.h"

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
	: switchType(switchtype), time(time)
{
	buttonId = id;
	Utils::SetOrigin(hitbox, Origins::BC);

	if (rotation == 0) {			//top of gird
		hitbox.setPosition({ position.x,position.y - GRIDSIZE / 2 });
		hitbox.setSize({ GRIDSIZE,GRIDSIZE / 4 });

	}
	else if (rotation == 1) {	//right of gird
		hitbox.setPosition({ position.x + GRIDSIZE / 2,position.y });
		hitbox.setSize({ GRIDSIZE,GRIDSIZE / 4 });

	}
	else if (rotation == 2) {	//bottom of gird
		hitbox.setPosition({ position.x, position.y + GRIDSIZE / 2 });
		hitbox.setSize({ GRIDSIZE,GRIDSIZE / 4 });

	}
	else if (rotation == 3) {	//left of gird
		hitbox.setPosition({ position.x - GRIDSIZE / 2,position.y });
		hitbox.setSize({ GRIDSIZE ,GRIDSIZE / 4 });
	}

	hitbox.setFillColor(Color::Yellow);
	if (rotation == 0 || rotation == 2)
		hitbox.setSize({ 10,40 });
	else
		hitbox.setSize({ 40,10 });

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
	Utils::SetOrigin(hitbox, Origins::BC);

	if (time != 0) {
		remainingtime -= dt;
	}
}

void Switch::Draw(RenderWindow& window)
{

	if (!isPlayingGame)
	{
		WireableObject::Draw(window);
	}
	else
	{
		SpriteObj::Draw(window);
		window.draw(hitbox);
	}	
}

void Switch::Draw(RenderTexture& diffuse, Shader& nShader, RenderTexture& normal)
{
}
