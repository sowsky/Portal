#pragma once
#include "SpriteObj.h"
#include "Button.h"

class Switch : public Button
{
public:
	Switch();
	Switch(Vector2f position,int rotation,int id, float time,bool switchtype);
	virtual ~Switch();

	virtual SpriteObj* NewThis();

	virtual void Update(float dt);
	virtual void Draw(RenderWindow& window);
	virtual void Draw
	(RenderTexture& diffuse, Shader& nShader, RenderTexture& normal);

	FloatRect GethitboxGlobalBounds() { return hitbox.getGlobalBounds(); }
	
private:
	RectangleShape hitbox;

	float time;
	float remainingtime;
	bool switchType; //false=sustain  true= turn on after time
};

