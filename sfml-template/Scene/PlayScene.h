#pragma once
#include "Scene.h"
#include "SFML/Graphics.hpp"
#include <vector>
#include "../FrameWork/Const.h"
#include "../FrameWork/ObjectHeaders.h"
#include "../Objects/Goal.h"
#include <box2d/box2d.h>
#include "../Particle/ParticleSystem.h"
#include <SFML/Audio.hpp>

//////////////////////////
#include <Candle/Candle.hpp>
#include <memory>
using namespace candle;
/////////////////////////

struct Light
{
	Light(sf::Vector3f col, sf::Vector3f pos, sf::Vector3f att) : color(col),
		position(pos),
		attenuation(att)
	{
	}
	sf::Vector3f color;
	sf::Vector3f position;
	sf::Vector3f attenuation;
};

struct PsceneWire
{
	PsceneWire(bool& o, Vector2f start, Vector2f end)
		:isOn(o)
	{
		float x = Utils::Distance(start, end);
		float angle = Utils::Angle(start, end);
		wireRect.setSize({ x, 1.f });
		wireRect.setRotation(angle);
		wireRect.setPosition(start);	
	}

	void SetColor(Color color)
	{	
		wireRect.setFillColor(color);
	}
	
	RectangleShape wireRect;
	bool& isOn;
};

class PlayScene : public Scene
{
public:
	//PlayScene() {};
	PlayScene(string path);
	virtual ~PlayScene();

	virtual void Init();	// ����
	virtual void Release();		// ����

	virtual void Enter();
	virtual void Exit();

	virtual void Update(float dt);
	virtual void PhysicsUpdate(float dt);
	void PuaseUpdate(float dt);

	virtual void Draw(RenderWindow& window);
	void PauseDraw(RenderWindow& window);

	void MakeWall(bool isEnd);
	void MakeCube();
	void MakePlayer();
	void MakeButton(int rotaion, int id);
	void MakePortal();
	void MakeBlackWall(bool isEnd);
	void MakeSwitch(int rotaion, int id, float time, bool switchtype);

	void MakeGoal(vector<int> list);

	void MakeTunnel(string dir, string id);

	void Respawn();

	void PushButton();
	void TunnelCheck();
	void BridgeCheck();
	void RedwallCheck();
	void WaterCheck(float);
	void CheckStillObjectalive();
	void MoveToPortal();

	bool IsHelp() { return help; }

public:
	void DrawBackGroundView(RenderWindow& window);
	void DrawRenderedBackGroundBuffer(RenderWindow& window);
	void DrawRenderedBuffer(RenderWindow& window);
	void Input();
	void LightTestInputForDev();
	void ClearRenderBuffer();
	void OpenStage(float dt);
	void BackAndLightControl();
	void DrawNormalAndDiffuse(RenderWindow& window);

	////////////////////
	static void SetIsDevMod(bool dev) { isDevMod = dev; }
	static bool GetIsDevMod() { return isDevMod; }
	static void TurnOnOffDevMod() { isDevMod = !isDevMod; }
private:
	b2DistanceJoint* joint;
	b2Vec2 mouseWorld;
	Player* player;
	Goal* goal;
	vector<Tile*> wall;
	vector<Button*> button;
	vector<Cube*> cube;
	vector<Tunnel*> tunnel;
	vector<Bridge*> bridge;
	vector<BlackTile*> blackwall;
	vector<Redwall*> redwall;
	vector<Water*> water;
	vector<Switch*> switches;
	vector<MovingPlatform*> movingplat;
	vector<AngledTile*> angledtile;
	vector<Dropper*> dropper;
	/////////////////
	vector<Sign*> sign;
	////////////////


	Vector2f temp = { 0,0 };

	Cube* grabbedcube = nullptr;
	Vector2f currgrid = { GRIDSIZE / 2,GRIDSIZE / 2 };
	float wallbunchwidth = GRIDSIZE;
	Vector2f box2dposition = { GRIDSIZE / 2,GRIDSIZE / 2 };

	View backgroundView;
	View endingView;

	Blue* blue;
	Orange* orange;
	bool madeblue = false;
	bool madeorange = false;

	bool grabitem = false;

	bool IsMadeTunnelFollowOrangePortal = false;
	bool IsMadeTunnelFollowBluePortal = false;
	bool IsMadeBridgeFollowOrangePortal = false;
	bool IsMadeBridgeFollowBluePortal = false;

	RectangleShape ending;

	////////////////////////////////////////////////////
	unique_ptr<b2World> world;

	float dtstack = 0.f;
	int dark = 0;
	bool isMovingViewCenter;

	//////
	ParticleSystem particle;

	//const int width=4000;
	//const int height=4000;

	int width;
	int height;

	float maxspeed = 16;

	// Front and backbuffer as Pointer for std::swap
	unique_ptr<RenderTexture> front, back;
	RenderTexture pass_normals, pass_diffuse;

	unique_ptr<RenderTexture> front2, back2;
	RenderTexture pass_normals2, pass_diffuse2;
	//Texture normal_map, diffuse_map;

	Shader lights_shader;
	Shader normals_shader;

	Light light;

	//float ambient_intensity = 0.0;
	float ambient_intensity = 0.8f;
	Vector3f falloff;
	/////
	Sprite crosshair;

	//float openingTime = 1.5f;	
	float openingTime = 0.8f;
	map<int, list<Vector2f>> wireList;
	list<PsceneWire*> wires;
	bool showWire;

	Sprite background;
	Texture* backgroundNormal;
	bool testLight = false;
	bool isfreeView = false;

	float currentcamposx;
	float currentcamposy;

	Sprite keyhelp;

	/////////////////
	static bool isDevMod;

	bool help = false;
	bool pause = false;

	Sprite diffuseSprite;
	Sprite frontSprite;

	Sprite pause_back;
	Sprite pause_main;
	Sprite pause_exit;
	Sprite pause_option;
	Sprite pause_restart;
	Sprite pause_return;
};

