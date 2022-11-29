#include "Bridge.h"

Bridge::Bridge()
{
}

Bridge::Bridge(b2World* world, const Vector2f& position, Vector2f dimensions, int dir)
	:dir(dir)
{
	b2BodyDef bodyDef;
	bodyDef.type = b2_staticBody;
	bodyDef.position.Set(position.x / SCALE, position.y / SCALE * -1);
	body = world->CreateBody(&bodyDef);

	if (dir == 0 || dir == 2) {
		bridge.setSize({ 10,0 });
	}
	else if (dir == 1 || dir == 3) {
		bridge.setSize({ 0,10 });
	}

	b2PolygonShape boxShape;
	boxShape.SetAsBox(dimensions.x / SCALE / 2, dimensions.y / SCALE / 2);

	b2FixtureDef fixtureDef;
	fixtureDef.shape = &boxShape;
	fixtureDef.density = 1.0f;
	fixtureDef.friction = 0.2f;
	fixture = body->CreateFixture(&fixtureDef);
}

Bridge::~Bridge()
{
}

void Bridge::Update(float dt)
{
}

void Bridge::Draw(RenderWindow& window)
{
}
