#include "Water.h"

Water::Water()
    :sideFaces(frontFace, sprite)
{
    id = 'w';

    SetResourceTexture("Graphics/Ui/goo.png");

    type = ObjectType::None;
    objSize = ObjectSize::Big;
    attatchedPos = Rotate::Down;

    //Utils::SetOrigin(water, Origins::MC);
    //water.setFillColor(Color::Blue);
}

Water::Water(Vector2f position)
    :sideFaces(frontFace, sprite)
{
    Utils::SetOrigin(water, Origins::MC);

    water.setSize({ GRIDSIZE, GRIDSIZE });
    pos= position;
    water.setFillColor(Color::Blue);
    sprite.setPosition(pos);

    frontSize = { GRIDSIZE / DEPTH, GRIDSIZE / DEPTH };
    SetSpriteTex(frontFace, "Graphics/water.png");
    Utils::SetOrigin(frontFace, Origins::MC);
    Utils::SetSpriteSize(frontFace, frontSize);

    sideFaces.SetDepth(DEPTH);
    sideFaces.SetSidesTex("Graphics/water.png", 0);
    sideFaces.SetBackFaceSize(frontSize);
    sideFaces.SetBackFaceOrigin(Origins::MC);
 
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
        sideFaces.Draw(window);
        window.draw(frontFace);        
    }
    else
        window.draw(sprite);

}

void Water::SetActiveSurface(bool active)
{
    sideFaces.SetActiveSides(0, active);
}
