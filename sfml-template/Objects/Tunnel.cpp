#include "Tunnel.h"

Tunnel::Tunnel(const Vector2f& position, bool Horizon)
	:IsBlue(true)
{
	tuns.setFillColor(Color(0,255,0,128));
	tuns.setPosition(position);

	if (Horizon) {
		tuns.setSize({ 0,50 });
	}else
		tuns.setSize({ 50,0 });
}

Tunnel::~Tunnel()
{
}

void Tunnel::Update(float dt)
{
	
}

void Tunnel::Draw(RenderWindow& window)
{
	window.draw(tuns);
}
