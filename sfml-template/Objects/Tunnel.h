#pragma once
#include <SFML/Graphics.hpp>
#include "SpriteObj.h"
class Tunnel :public SpriteObj
{
public:
	Tunnel() {};
	Tunnel(const Vector2f& position, bool Horizon);
	virtual ~Tunnel();

	virtual void Update(float dt);
	virtual void Draw(RenderWindow& window);

	void SetDir(bool b) { IsBlue = b; }  //true==blue,false=orange
	bool GetDir() { return IsBlue; }

	FloatRect* GetHitBoxGlobalbound() { return &hitbox.getGlobalBounds(); }
private:
	RectangleShape tuns;
	RectangleShape hitbox;
	bool IsBlue = true;
	bool active = false;
};

