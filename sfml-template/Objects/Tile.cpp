#include "Tile.h"

Tile::Tile()	
{
	String str;
	int rand = Utils::RandomRange(0, 5);
	switch (rand)
	{
	case 0:
		str = "Graphics/Tile/tile.png";
		break;
	case 1:
		str = "Graphics/Tile/tile2.png";
		break;
	case 2:
		str = "Graphics/Tile/tile3.png";
		break;
	case 3:
		str = "Graphics/Tile/tile4.png";
		break;
	case 4:
		str = "Graphics/Tile/tile5.png";
		break;
	}
	SetResourceTexture(str);
	id = '1';
}

Tile::~Tile()
{
}

SpriteObj* Tile::NewThis()
{
	return new Tile;
}
