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
	virtual void SetPressed() {  }

	float GetTime() { return time; }
	void SetTime(float t) { time = t; }

	virtual void SetSwitchActive();
	static void OnOffShowTimer() { showTimer = !showTimer; }

protected:
	float time;
	float remainingtime;
	bool switchType; //false=sustain  true= turn on after time
	int rot;

	static bool showTimer;

	bool after=false;
};

