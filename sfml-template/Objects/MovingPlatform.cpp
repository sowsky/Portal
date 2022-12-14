#include "MovingPlatform.h"
#include "../Manager/ResourceMgr.h"
#include "Switch.h"
#include "../FrameWork/InputMgr.h"

MovingPlatform::MovingPlatform()
	:sideFaces(frontFace, sprite)
{
	SetResourceTexture("Graphics/panelup.png");

	id = 'm';

	type = ObjectType::Catcher;
	objSize = ObjectSize::Normal;
	attatchedPos = Rotate::Down;

	SetOrigin(Origins::BC);

	for (auto& ar : arrows)
	{
		ar.setTexture(*RESOURCEMGR->GetTexture("Graphics/Ui/arrow.png"));
		Utils::SetOrigin(ar, Origins::BC);
	}

	up.setPointCount(3);
	up.setFillColor(Color::Black);
	up.setRadius(4.f);
	Utils::SetOrigin(up, Origins::MC);

	down.setPointCount(3);
	down.setFillColor(Color::Black);
	down.setRadius(4.f);
	
	Utils::SetOrigin(down, Origins::MC);

	InitTexBox();
}

MovingPlatform::MovingPlatform(b2World* world, Vector2f& position, bool on, float rot, float destY, vector<float> buttonlist)
	:buttonid(buttonlist), enable(on), world(world), originactive(on),
	 sideFaces(frontFace, sprite)
{
	if (rot == 0) {
		dir = 0;
		platform.setPosition(position.x, position.y - (GRIDSIZE / 2));
		destiny.y = platform.getPosition().y + (destY * GRIDSIZE);

	}
	else if (rot == 2) {
		dir = 2;
		platform.setPosition(position.x, position.y + (GRIDSIZE / 2));
		destiny.y = platform.getPosition().y - (destY * GRIDSIZE);
	}

	if (dir == 0) {
		Utils::SetOrigin(pillar, Origins::TC);
		

	}
	else if (dir == 2) {
		Utils::SetOrigin(pillar, Origins::BC);
		
	}

	originpos = platform.getPosition();
	//pillar.setFillColor(Color::Green);
	pillar.setPosition(platform.getPosition());
	platform.setFillColor(Color::Green);
	platform.setSize({ GRIDSIZE, 10 });

	this->world = world;
	b2BodyDef bodyDef;
	bodyDef.type = b2_kinematicBody;
	bodyDef.position.Set(platform.getPosition().x / SCALE, platform.getPosition().y / SCALE * -1);
	platformbody = this->world->CreateBody(&bodyDef);

	b2PolygonShape boxShape;
	boxShape.SetAsBox(platform.getSize().x / SCALE / 2, platform.getSize().y / SCALE / 2);

	platformbody->SetGravityScale(0);
	platformbody->SetFixedRotation(1);

	b2FixtureDef fixtureDef;
	fixtureDef.shape = &boxShape;
	fixtureDef.density = 1.0f;
	fixtureDef.friction = 0.2f;
	platformfixture = platformbody->CreateFixture(&fixtureDef);



	b2BodyDef bodyDef1;
	bodyDef1.type = b2_staticBody;
	bodyDef1.position.Set(pillar.getPosition().x / SCALE, pillar.getPosition().y / SCALE * -1);
	pillarbody = this->world->CreateBody(&bodyDef1);

	b2PolygonShape boxShape1;
	boxShape1.SetAsBox(pillar.getSize().x / SCALE / 2, pillar.getSize().y / SCALE / 2);

	b2FixtureDef fixtureDef1;
	fixtureDef1.shape = &boxShape1;
	fixtureDef1.density = 100.0f;
	fixtureDef1.friction = 1.0f;
	pillarfixture = pillarbody->CreateFixture(&fixtureDef1);

	////////////////////////////////////////

	Vector2u pTexSize = RESOURCEMGR->GetTexture("Graphics/platform/front.png")->getSize();

	float pTexRatio = pTexSize.x / pTexSize.y;
	frontSize = { FRONTSIZE,FRONTSIZE / pTexRatio };	
	Utils::SetOrigin(sprite, Origins::MC);
	if (dir == 0)
		sprite.setRotation(180.f);

	SetSpriteTex(frontFace, "Graphics/platform/front.png");
	Utils::SetSpriteSize(frontFace, frontSize);
	Utils::SetOrigin(frontFace, Origins::MC);

	normal = RESOURCEMGR->GetTexture("Graphics/platform/front_n.png");

	sideFaces.SetDepth(DEPTH);
	sideFaces.SetSidesTex("Graphics/platform/side.png", 1);
	sideFaces.SetSidesTex("Graphics/platform/side.png", 3);
	sideFaces.SetSidesTex("Graphics/platform/floor.png", 0);
	sideFaces.SetSidesTex("Graphics/platform/floor.png", 2);
	sideFaces.SetBackFaceSize(frontSize);
	sideFaces.SetBackFaceOrigin(Origins::MC);

	sprite.setPosition(platform.getPosition());

	
	pillar_diffuse.setRotation(sprite.getRotation());
	pillar_diffuse.setTexture(RESOURCEMGR->GetTexture("Graphics/platform/pillar.png"));
	pillar_n = RESOURCEMGR->GetTexture("Graphics/platform/pillar_n.png");
	pillar_diffuse.setPosition(originpos);
}

void MovingPlatform::Update(float dt)
{
	Utils::SetOrigin(platform, Origins::MC);

	if (dir == 0) {
		Utils::SetOrigin(pillar, Origins::TC);		
	}
	else if (dir == 2) {
		Utils::SetOrigin(pillar, Origins::BC);		
	}

	if (InputMgr::GetKeyDown(Keyboard::Y))
	{
		enable = !enable;
	}

	enable = originactive;

	for (auto b : button) {
		if (!b->GetPressed()) {
			enable = !originactive;
		}
	}


	if (enable) {
		bool check;
		if (dir == 0) {
			check = platform.getPosition().y > destiny.y ? false : true;
		}
		else if (dir == 2) {
			check = platform.getPosition().y < destiny.y ? false : true;
		}

		if (check && dir == 2) {
			float tempy = Utils::Lerp(platform.getPosition().y, destiny.y, 0.001);
			pillar.setSize({ 10, abs(originpos.y - tempy) });
			platformbody->SetLinearVelocity({ 0,1.f });
		}
		else if (check && dir == 0) {
			float tempy = Utils::Lerp(platform.getPosition().y, destiny.y, 0.001);
			pillar.setSize({ 10, abs(originpos.y - tempy) });
			platformbody->SetLinearVelocity({ 0,-1.f });
		}
		else {
			platformbody->SetLinearVelocity({ 0,0 });

		}
		platformbody->SetTransform({ originpos.x / SCALE,platformbody->GetPosition().y }, 0);

	}
	else {
		bool check;
		if (dir == 0) {
			check = platform.getPosition().y > originpos.y ? true : false;
		}
		else if (dir == 2) {
			check = platform.getPosition().y < originpos.y ? true : false;
			//cout << check << endl;
		}

		if (check && dir == 2) {
			platformbody->SetLinearVelocity({ 0,-1.f });
		}
		if (check && dir == 0) {
			platformbody->SetLinearVelocity({ 0,1.f });

		}

		if (!check)
		{
			platformbody->SetLinearVelocity({ 0,0 });
		}
		float tempy = Utils::Lerp(platform.getPosition().y, originpos.y, 0.001);
		pillar.setSize({ 10, abs(originpos.y - tempy) });

		platformbody->SetTransform({ originpos.x / SCALE,platformbody->GetPosition().y }, 0);
	}

	platform.setPosition(platformbody->GetPosition().x * SCALE, platformbody->GetPosition().y * SCALE * -1);


	if (pillarfixture != nullptr) {
		pillarbody->DestroyFixture(pillarbody->GetFixtureList());
	}

	b2PolygonShape boxShape1;
	boxShape1.SetAsBox(pillar.getSize().x / SCALE / 2, pillar.getSize().y / SCALE / 2);

	b2FixtureDef fixtureDef;
	fixtureDef.shape = &boxShape1;
	fixtureDef.density = 1;
	fixtureDef.friction = 0.3f;
	pillarfixture = pillarbody->CreateFixture(&fixtureDef);

	if (dir == 0)
		pillarbody->SetTransform({ pillarbody->GetPosition().x,(pillar.getPosition().y+pillar.getSize().y/2)/SCALE*-1 }, 0);
	else
		pillarbody->SetTransform({ pillarbody->GetPosition().x,(pillar.getPosition().y - pillar.getSize().y / 2) / SCALE * -1 }, 0);

	sprite.setPosition(platform.getPosition());	
	//Utils::SetOrigin(sprite, Origins::MC);
	if (dir == 0)
	{
		pillar_diffuse.setSize({ 10, (sprite.getPosition().y - platFormHeightHalf) - pillar_diffuse.getPosition().y });
		if(pillar_diffuse.getSize().y <= 0.f)
			pillar_diffuse.setSize({ 10, 0.f });
	}
	if (dir == 2)
	{
		pillar_diffuse.setSize({ 10, pillar_diffuse.getPosition().y - (sprite.getPosition().y + platFormHeightHalf) });
		if (pillar_diffuse.getSize().y <= 0.f)
			pillar_diffuse.setSize({ 10, 0.f });
	}	

	Utils::SetOrigin(pillar_diffuse, Origins::BC);	
	//cout << pillar.getPosition().y << endl;
}

void MovingPlatform::SetButtonlist(vector<Button*>& button)
{
	for (auto b : button) {
		for (int i = 0; i < buttonid.size(); i++) {
			if (b->GetButtonId() == buttonid[i]) {
				this->button.push_back(b);
			}
		}
	}
}


SpriteObj* MovingPlatform::NewThis()
{
	return new MovingPlatform;
}

void MovingPlatform::Draw(RenderWindow& window)
{
	if (!isPlayingGame)
	{
		WireableObject::Draw(window);
		if (isInMapTool && Switch::GetShowTimer())
		{
			DrawUi(window);
			DrawTexBox(window);
		}
	}
	else
	{
		//window.draw(platform);
		//window.draw(pillar);
		//SpriteObj::Draw(window);
		                  	
		
		sideFaces.Draw(window);	
			
	}
}

void MovingPlatform::Draw(RenderTexture& diffuse, Shader& nShader, RenderTexture& normal)
{
	diffuse.draw(frontFace);
	NormalPass(normal, frontFace, this->normal, nShader);
}

void MovingPlatform::DrawPillar(RenderTexture& diffuse, Shader& nShader, RenderTexture& normal)
{
	diffuse.draw(pillar_diffuse);
	NormalPass(normal, pillar_diffuse, pillar_n, nShader);
}

void MovingPlatform::DrawUi(RenderWindow& window)
{
	int rot = (int)attatchedPos;

	if (rot == 1 || rot == 3)
		return;

	if (rot == 2)
	{
		up.setPosition(sprite.getPosition().x + 9.15f, sprite.getPosition().y - 5);
		down.setPosition(sprite.getPosition().x + 10.f, sprite.getPosition().y + 5);
		down.setRotation(180.f);
	}

	if (!rot)
	{
		down.setPosition(sprite.getPosition().x + 9.15f, sprite.getPosition().y - 5);
		up.setPosition(sprite.getPosition().x + 10.f, sprite.getPosition().y + 5);
		up.setRotation(180.f);
	}

	Vector2f mousePos = window.mapPixelToCoords((Vector2i)InputMgr::GetMousePos(), window.getView());

	if (up.getGlobalBounds().contains(mousePos) &&
		InputMgr::GetMouseButtonDown(Mouse::Left))
	{
		if (range >= arrows.size())
			return;

		range += 1;
	}

	if (down.getGlobalBounds().contains(mousePos) &&
		InputMgr::GetMouseButtonDown(Mouse::Left))
	{
		if (range <= 1)
			return;

		range -= 1;
	}

	for (int i = 0; i < range; i++)
	{
		if (i == arrows.size())
			break;

		int rot = (int)attatchedPos == 0 ? 1 : -1;

		arrows[i].setRotation(sprite.getRotation());
		if (!i)
			arrows[i].setPosition(sprite.getPosition());
		else
			arrows[i].setPosition(arrows[i - 1].getPosition().x, arrows[i - 1].getPosition().y + rot * 25);

		window.draw(arrows[i]);
	}
	window.draw(up);
	window.draw(down);
}

void MovingPlatform::InitTexBox()
{
	onOffTex.setFont(*RESOURCEMGR->GetFont("Fonts/D-DINCondensed-Bold.otf"));
	onOffTex.setCharacterSize(7);
	onOffTex.setFillColor(Color::Black);
	onOfftexBox.setSize({ 8.f, 8.f });
	Utils::SetOrigin(onOfftexBox, Origins::MC);
	onOfftexBox.setFillColor(Color::White);
	onOfftexBox.setOutlineThickness(0.5f);
	onOfftexBox.setOutlineColor(Color::Black);
}

void MovingPlatform::DrawTexBox(RenderWindow& window)
{
	onOfftexBox.setPosition(sprite.getPosition());
	onOffTex.setPosition(onOfftexBox.getPosition());

	Vector2f mousePos = window.mapPixelToCoords((Vector2i)InputMgr::GetMousePos(), window.getView());

	if (onOfftexBox.getGlobalBounds().contains(mousePos) &&
		InputMgr::GetMouseButtonDown(Mouse::Left) && Switch::GetShowTimer())
	{
		isTurnedOn = !isTurnedOn;
	}

	onOffTex.setString(isTurnedOn ? "ON" : "OFF");
	Utils::SetOrigin(onOffTex, Origins::BC);

	window.draw(onOfftexBox);
	window.draw(onOffTex);
}
