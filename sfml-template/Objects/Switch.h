#pragma once
#include "SpriteObj.h"
#include "Button.h"

class Switch : public Button
{
public:
	Switch();
	virtual ~Switch();

	virtual void Update(float dt);
	virtual void Draw(RenderWindow& window);
	virtual void Draw
	(RenderTexture& diffuse, Shader& nShader, RenderTexture& normal);

private:
	RectangleShape swtich;
	float time;
	bool type; //false=sustain  true= turn on after time
	int id;
};

