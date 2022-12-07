#include "Water.h"

Water::Water()
{
    id = 'w';

    SetResourceTexture("Graphics/Ui/goo.png");

    type = ObjectType::None;
    objSize = ObjectSize::Big;
    attatchedPos = Rotate::Down;

    Utils::SetOrigin(water, Origins::BC);
    water.setFillColor(Color::Blue);
}

SpriteObj* Water::NewThis()
{
    return new Water;
}

void Water::Update(float dt)
{
}

void Water::Draw(RenderWindow& window)
{
    if (isPlayingGame)
    {
        window.draw(water);
    }
    else
        window.draw(sprite);
}
