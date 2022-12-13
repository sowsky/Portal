#include "AngledTile.h"
#include "../Manager/ResourceMgr.h"

bool AngledTile::isBlueOn = false;
bool AngledTile::isOrangeOn = false;

AngledTile::AngledTile()
{
	SetResourceTexture("Graphics/Ui/angletool.png");
	id = 'a';

	type = ObjectType::None;
	objSize = ObjectSize::Normal;
	attatchedPos = Rotate::Down;
}

AngledTile::AngledTile(b2World* world, Vector2f position, int angle)
{
	hitboxpos = position;
	triangle.setPointCount(3);
	triangle.setPoint(0, Vector2f(0, 0));
	triangle.setPoint(1, Vector2f(GRIDSIZE, GRIDSIZE));
	triangle.setPoint(2, Vector2f(0, GRIDSIZE));

	Utils::SetOrigin(triangle, Origins::MC);
	triangle.setPosition(position);
	dir = angle;

	if (angle == 0) {
		triangle.setRotation(180);
	}
	else if (angle == 3) {
		triangle.setRotation(90);
	}
	else if (angle == 1) { 
		triangle.setRotation(270); 
	}

	hitbox.setFillColor(Color::Red);
	hitbox.setSize({ 10,40 });
	hitbox.setPosition(hitboxpos);
	if (dir == 1 || dir == 3) {
		hitbox.setRotation(45);
	}
	else
		hitbox.setRotation(315);

	SetSpriteTex(front, "Graphics/angle/side.png");
	back.setTexture(RESOURCEMGR->GetTexture("Graphics/angle/side.png"));
	upTex = RESOURCEMGR->GetTexture("Graphics/angle/up.png");
	blue = RESOURCEMGR->GetTexture("Graphics/angle/blue.png");
	orange = RESOURCEMGR->GetTexture("Graphics/angle/orange.png");

	Utils::SetSpriteSize(front, { FRONTSIZE,FRONTSIZE });

	float dp = DEPTH * 2 - 1.f;
	
	back.setSize({ FRONTSIZE * dp, FRONTSIZE * dp });

	Utils::SetOrigin(front, Origins::MC);
	Utils::SetOrigin(back, Origins::MC);

	front.setRotation(triangle.getRotation());
	back.setRotation(triangle.getRotation());

	Vector2f upTexSize = (Vector2f)RESOURCEMGR->GetTexture("Graphics/angle/up.png")->getSize();

	topSide.setPrimitiveType(Quads);
	topSide.resize(4);

	topSide[0].texCoords = { 0,0 };
	topSide[1].texCoords = { upTexSize.x,0 };
	topSide[2].texCoords = upTexSize;
	topSide[3].texCoords = { 0,upTexSize.y };
	
	//SetTransparent(155);

	wave.distortionFactor = 0.1f;
	render.texture = upTex;
	render.shader = &wave.shader;

	blueLight = RESOURCEMGR->GetTexture("Graphics/Shader/blue.png");
	orangeLight = RESOURCEMGR->GetTexture("Graphics/Shader/orange.png");

	lightRender.shader = &wave.shader;

	light.setSize({ 35, 15 });
	light.setPosition(triangle.getPosition());
	light.setRotation(triangle.getRotation() + 45.f);
	Utils::SetOrigin(light, Origins::BC);

	state = AngleState::Noraml;
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
	if (isPlayingGame)
		wave.Update(dt);
	ChangeTex();
	Utils::SetOrigin(hitbox, Origins::MC);

}

void AngledTile::Draw(RenderWindow& window)
{
	if (isPlayingGame)
	{
		//window.draw(triangle);
		//window.draw(hitbox);
		DrawFaces(window);
	}
	else
	{
		window.draw(sprite);
	}
}

void AngledTile::DrawFaces(RenderWindow& window)
{
	Vector2f vanishingPoint = window.getView().getCenter();

	front.setPosition(
		triangle.getPosition() - (vanishingPoint - triangle.getPosition()) * (1.f - DEPTH)
	);

	back.setPosition(
		triangle.getPosition() + (vanishingPoint - triangle.getPosition()) * (1.f - DEPTH)
	);

	FloatRect rect = front.getLocalBounds();

	topSide[0].position = front.getTransform().transformPoint({ rect.left,rect.top });
	topSide[1].position = back.getTransform().transformPoint(back.getPoint(0));
	topSide[2].position = back.getTransform().transformPoint(back.getPoint(2));
	topSide[3].position = front.getTransform().transformPoint({ rect.left + rect.width,rect.top + rect.height});	

	window.draw(topSide, render);
	if(state != AngleState::Noraml)
		window.draw(light, lightRender.shader);
	

	window.draw(front);
}

void AngledTile::DrawBackFace(RenderWindow& window)
{
	window.draw(back);
}

void AngledTile::SetTransparent(int t)
{
	front.setColor(Color(255, 255, 255, t));
	back.setFillColor(Color(255, 255, 255, t));
	topSide[0].color = Color(255, 255, 255, t);
	topSide[1].color = Color(255, 255, 255, t);
	topSide[2].color = Color(255, 255, 255, t);
	topSide[3].color = Color(255, 255, 255, t);
}

void AngledTile::ChangeTex()
{
	if (prevState == state)
		return;

	prevState = state;

	switch (state)
	{
	case AngleState::Noraml:
		render.texture = upTex;		
		break;
	case AngleState::Blue:
		render.texture = blue;
		light.setTexture(blueLight);
		break;
	case AngleState::Orange:
		render.texture = orange;
		light.setTexture(orangeLight);
		break;
	default:
		break;
	}
}
