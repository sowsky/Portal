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
}

void Switch::Draw(RenderWindow& window)
{
	//if (!isPlayingGame)
		SpriteObj::Draw(window);
}

void Switch::Draw(RenderTexture& diffuse, Shader& nShader, RenderTexture& normal)
{
}
