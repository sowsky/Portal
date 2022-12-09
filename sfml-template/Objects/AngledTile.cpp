#include "AngledTile.h"

AngledTile::AngledTile()
{
    SetResourceTexture("Graphics/Ui/angletool.png");
    id = 'a';

    type = ObjectType::None;
    objSize = ObjectSize::Normal;
    attatchedPos = Rotate::Down;
}

AngledTile::~AngledTile()
{
}

SpriteObj* AngledTile::NewThis()
{
    return new AngledTile;
}

void AngledTile::Update(float dt)
{
}

void AngledTile::Draw(RenderWindow& window)
{
    if (isPlayingGame)
    {

    }
    else
    {
        window.draw(sprite);
    }
}
