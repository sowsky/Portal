#pragma once

//enum class Origins
//{
//	TL,	// 0
//	TC,
//	TR,
//	ML,
//	MC,
//	MR,
//	BL,
//	BC,
//	BR,	// 8
//};

enum class Scenes
{
	GAMESTART,
	MAPEDITER,
	MAPSELECTER,
};

enum class TileTypes
{
	None = -1,
	Stand = 0,
	Water,
	Mountain,
	Building1,
	Building2,
	Rail,
};

enum class Squd
{
	None = -1,
	RiftWalkers,
};

enum class MechClass
{
	None = -1,
	Prime,
	Brute,
	Range,
};

enum class ActorType
{
	None = -1,
	Mech = 0,
	Veck = 1,
};


enum class GamePhase
{
	None = -1,
	Start,
	Deploy,
	Player,
	Move,
	Enemy,
	End,
};

enum class AnimationType
{
	None = -1,
	Projectile,
	Actor,	
	Background,
};