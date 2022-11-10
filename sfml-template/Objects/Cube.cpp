#include "Cube.h"

Cube::Cube()
{
	SetResourceTexture("Graphics/cube.png");
	id = 'c';
}

Cube::~Cube()
{
}

SpriteObj* Cube::NewThis()
{
	return new Cube;
}
