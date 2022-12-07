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
	PsceneWire(bool& o)
		:isOn(o)
	{
		wire.resize(2);
		wire.setPrimitiveType(Lines);		
	}
	void SetColor(Color color)
	{
		wire[0].color = color;
		wire[1].color = color;
	}
	VertexArray wire;
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

	virtual void Draw(RenderWindow& window);

	void MakeWall(bool isEnd);
	void MakeCube();
	void MakePlayer();
	void MakeButton(int rotaion, int id);
	void MakePortal();
	void MakeBlackWall(bool isEnd);

	void MakeGoal(vector<int> list);

	void MakeTunnel(string dir, string id);

	void Respawn();

	void PushButton();
	void TunnelCheck();
	void BridgeCheck();
	void RedwallCheck();
	void WaterCheck(float );
	void CheckStillObjectalive();
	void MoveToPortal();
	
public:
	void DrawBackGroundView(RenderWindow& window);
	void DrawRenderedBuffer(RenderWindow& window);
	void Input();
	void LightTestInputForDev();
	void ClearRenderBuffer();
	void OpenStage(float dt);
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

	Vector2f temp = { 0,0 };

	Cube* grabbedcube = nullptr;
	Vector2f currgrid = { GRIDSIZE / 2,GRIDSIZE / 2 };
	float wallbunchwidth = GRIDSIZE;
	Vector2f box2dposition={ GRIDSIZE / 2,GRIDSIZE / 2 };

	View backgroundView;
	View endingView;
	RectangleShape background;
	
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
	Texture* bgNormal;

	////////////////////////////////////////////////////
	unique_ptr<b2World> world;

	float dtstack = 0.f;
	int dark = 0;	
	bool isMovingViewCenter;

	//////
	ParticleSystem particle;
	
	int width;
	int height;

	// Front and backbuffer as Pointer for std::swap
	unique_ptr<RenderTexture> front, back;
	RenderTexture pass_normals, pass_diffuse;
	//Texture normal_map, diffuse_map;

	Shader lights_shader;
	Shader normals_shader;

	Light light;

	//float ambient_intensity = 0.0;
	float ambient_intensity = 0.7;
	Vector3f falloff;
	/////
	Sprite crosshair;

	//float openingTime = 1.5f;	
	float openingTime = 0.f;	
	map<int, list<Vector2f>> wireList;
	list<PsceneWire*> wires;
	bool showWire;

	Sprite backtemp;	
	
};

