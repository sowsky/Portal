#include "Switch.h"

Switch::Switch()
{
	SetResourceTexture("Graphics/switch.png");
	id = 's';
	type = ObjectType::Trigger;
	objSize = ObjectSize::Normal;
	attatchedPos = Rotate::Down;
}

Switch::~Switch()
{
}

SpriteObj* Switch::NewThis()
{
	return nullptr;
}

void Switch::Update(float dt)
{
}

void Switch::Draw(RenderWindow& window)
{
}

void Switch::Draw(RenderTexture& diffuse, Shader& nShader, RenderTexture& normal)
{
}
