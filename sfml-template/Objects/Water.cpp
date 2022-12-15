#include "Water.h"
#include "../Manager/ResourceMgr.h"

Water::Water(bool top)
    :sideFaces(frontFace, sprite), isTop(top)
{
    id = 'w';

    if(isTop)
        SetResourceTexture("Graphics/waterup.png");    
    else
        SetResourceTexture("Graphics/water.png"); 
    

    type = ObjectType::None;
    objSize = ObjectSize::Big;
    attatchedPos = Rotate::Down;

    //Utils::SetOrigin(water, Origins::MC);
    //water.setFillColor(Color::Blue);
}

Water::Water(Vector2f position)
    :sideFaces(frontFace, sprite)
{
    attatchedPos = Rotate::Down;

    Utils::SetOrigin(water, Origins::MC);

    water.setSize({ GRIDSIZE, GRIDSIZE });
    pos= position;     

    normal = RESOURCEMGR->GetTexture("Graphics/water_n.png");
}

SpriteObj* Water::NewThis()
{
    return new Water(isTop);
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
        //window.draw(frontFace);        
    }
    else
        window.draw(sprite);

}

void Water::Draw(RenderTexture& diffuse, Shader& nShader, RenderTexture& normal)
{
    diffuse.draw(frontFace);
    NormalPass(normal, frontFace, this->normal, nShader);
}

void Water::InitSetting()
{
    sprite.setPosition(pos);

    frontSize = { GRIDSIZE / DEPTH, GRIDSIZE / DEPTH };
    if(isTop)
        SetSpriteTex(frontFace, "Graphics/waterup.png");
    else
        SetSpriteTex(frontFace, "Graphics/water.png");
    
    Utils::SetOrigin(frontFace, Origins::MC);
    Utils::SetSpriteSize(frontFace, frontSize);

    frontFace.setColor(Color(255, 255, 255, 100));

    sideFaces.SetDepth(DEPTH);
    if(isTop)
        sideFaces.SetSidesTex("Graphics/watersurface.png", 0);    
    sideFaces.SetBackFaceSize(frontSize);
    sideFaces.SetBackFaceOrigin(Origins::MC);
}
