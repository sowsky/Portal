#include "SmallTile.h"

SmallTile::SmallTile()	
{
	SetResourceTexture("Graphics/Tile/standTile.png");
	id = '1';
}

SmallTile::~SmallTile()
{
}

SpriteObj* SmallTile::NewThis()
{
	return new SmallTile;
}
