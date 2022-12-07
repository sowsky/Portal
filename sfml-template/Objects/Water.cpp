#include "Water.h"

Water::Water()
{
    id = 'w';

    SetResourceTexture("Graphics/Ui/goo.png");

    type = ObjectType::None;
    objSize = ObjectSize::Big;
    attatchedPos = Rotate::Down;

    Utils::SetOrigin(water, Origins::MC);
    water.setFillColor(Color::Blue);
}

Water::Water(Vector2f position)
{
    Utils::SetOrigin(water, Origins::MC);

    water.setSize({ GRIDSIZE, GRIDSIZE });
    pos= position;
    water.setFillColor(Color::Blue);

}

SpriteObj* Water::NewThis()
{
    return new Water;
}

void Water::Update(float dt)
{
    Utils::SetOrigin(water, Origins::MC);

    water.setSize({ GRIDSIZE, GRIDSIZE });
    water.setPosition(pos);
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
