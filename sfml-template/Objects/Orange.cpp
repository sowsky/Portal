#include "Orange.h"
#include "../Manager/ResourceMgr.h"

Orange::Orange()
{
	SetResourceTexture("Graphics/orange.png");

	Utils::SetOrigin(sprite, Origins::MC);
	SetPos({ -100, -100 });
	hitbox = new RectangleShape;
	hitbox->setFillColor(Color::Red);

	///////////////////
	light.setSize({ 40, 5 });
	Utils::SetOrigin(light, Origins::BC);
	light.setTexture(RESOURCEMGR->GetTexture("Graphics/Shader/orange.png"));
	light.setFillColor(Color(255, 255, 255, 150));
	

	portalArray.setPrimitiveType(Quads);
	portalArray.resize(4);

	orangeTex = RESOURCEMGR->GetTexture("Graphics/orangeportal.png");

	Vector2f texSize = (Vector2f)orangeTex->getSize();

	portalArray[0].texCoords = { 0,0 };
	portalArray[1].texCoords = { texSize.x,0 };
	portalArray[2].texCoords = { texSize.x,texSize.y };
	portalArray[3].texCoords = { 0,texSize.y };
		
	shader.distortionFactor = 0.1f;
	PortalState.texture = orangeTex;
	PortalState.shader = &shader.shader;
}

Orange::~Orange()
{
	delete hitbox;
}

void Orange::Update(float dt)
{
	hitbox->setSize({ sprite.getGlobalBounds().width - 10,sprite.getGlobalBounds().height - 10 });

	Utils::SetOrigin(*hitbox, Origins::MC);
	Translate(direction * dt * projectilespeed);

	hitbox->setPosition(sprite.getPosition());
	hitbox->setRotation(sprite.getRotation());

	shader.Update(dt);
}

void Orange::Draw(RenderWindow& window)
{
	window.draw(light, &shader.shader);
	//SpriteObj::Draw(window);	
	DrawPortalArray(window);
	//window.draw(*hitbox);

}

void Orange::SetLightDir(int side, bool texdir)
{
	light.setRotation(side);	
	texStand = texdir;
}

void Orange::DrawPortalArray(RenderWindow& window)
{
	Vector2f vanishingPoint = window.getView().getCenter();

	light.setPosition(sprite.getPosition());

	frontFace.setPosition(
		sprite.getPosition() - (vanishingPoint - sprite.getPosition()) * (1.f - DEPTH)
	);

	backFace.setPosition(
		sprite.getPosition() + (vanishingPoint - sprite.getPosition()) * (1.f - DEPTH)
	);

	if (dir == 1 || dir == 3)
	{
		portalArray[0].position = backFace.getTransform().transformPoint(backFace.getPoint(0));
		portalArray[1].position = frontFace.getTransform().transformPoint(frontFace.getPoint(1));
		portalArray[2].position = frontFace.getTransform().transformPoint(frontFace.getPoint(2));
		portalArray[3].position = backFace.getTransform().transformPoint(backFace.getPoint(3));
	}

	if (dir == 0 || dir == 2)
	{
		portalArray[0].position = backFace.getTransform().transformPoint(backFace.getPoint(3));
		portalArray[1].position = frontFace.getTransform().transformPoint(frontFace.getPoint(0));
		portalArray[2].position = frontFace.getTransform().transformPoint(frontFace.getPoint(1));
		portalArray[3].position = backFace.getTransform().transformPoint(backFace.getPoint(2));
	}

	window.draw(portalArray, PortalState);
	//window.draw(backFace);
	//window.draw(frontFace);
}

void Orange::SetSize(Vector2f size)
{
	SpriteObj::SetSize(size);

	float dp = DEPTH * 2 - 1.f;
	if (texStand)
	{
		frontFace.setSize({0.1f, size.y / DEPTH});
		backFace.setSize({ 0.1f, size.y * dp });
	}
	else
	{
		frontFace.setSize({ size.x / DEPTH, 0.1f, });
		backFace.setSize({ size.x * dp, 0.1f,  });
	}		

	Utils::SetOrigin(frontFace, Origins::MC);
	Utils::SetOrigin(backFace, Origins::MC);
}
