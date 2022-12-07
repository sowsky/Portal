#pragma once
#include <vector>
#include <nlohmann/json.hpp>
#include <array>

struct Map_Size_Struct
{
	int row;
	int col;
	NLOHMANN_DEFINE_TYPE_INTRUSIVE(Map_Size_Struct, row, col);
};

/////

struct Object_struct
{
	int posX;
	int posY;	
	int rotation = 2;
	char id;
};

struct Player_struct : public Object_struct
{	
	NLOHMANN_DEFINE_TYPE_INTRUSIVE(Player_struct, posX, posY, rotation, id);
};

struct Goal_struct : public Object_struct
{	
	vector<int> buttonList;
	NLOHMANN_DEFINE_TYPE_INTRUSIVE(Goal_struct, posX, posY, rotation, id, buttonList);
};

struct Tile_struct : public Object_struct
{		
	array<bool, 4> sideBool;
	NLOHMANN_DEFINE_TYPE_INTRUSIVE(Tile_struct, posX, posY, rotation, id, sideBool);
};

struct Black_Tile_struct : public Object_struct
{
	array<bool, 4> sideBool;
	NLOHMANN_DEFINE_TYPE_INTRUSIVE(Black_Tile_struct, posX, posY, rotation, id, sideBool);
};

struct Cube_struct : public Object_struct
{	
	NLOHMANN_DEFINE_TYPE_INTRUSIVE(Cube_struct, posX, posY, rotation, id);
};

struct Button_sturct : public Object_struct
{	
	int buttonId;
	NLOHMANN_DEFINE_TYPE_INTRUSIVE(Button_sturct, posX, posY, rotation, id, buttonId);
};

struct Tunnel_sturct : public Object_struct
{

	bool IsBlue;  //false=orange
	bool active;
	vector<int> buttonList;
	NLOHMANN_DEFINE_TYPE_INTRUSIVE(Tunnel_sturct, posX, posY, rotation, id, IsBlue, active, buttonList);
};

struct Bridge_sturct : public Object_struct
{
	bool on;
	vector<int> buttonList;
	NLOHMANN_DEFINE_TYPE_INTRUSIVE(Bridge_sturct, posX, posY, rotation, id, buttonList,on);
};

struct Redwall_struct : public Object_struct
{
	bool on;
	vector<int> buttonList;
	NLOHMANN_DEFINE_TYPE_INTRUSIVE(Redwall_struct, posX, posY, rotation, id, buttonList, on);
};

struct Water_struct : public Object_struct
{	
	NLOHMANN_DEFINE_TYPE_INTRUSIVE(Water_struct, posX, posY, rotation, id);
};

struct JumpPlate_Struct : public Object_struct
{
	float speed;
	vector<pair<float, float>> pos;
	NLOHMANN_DEFINE_TYPE_INTRUSIVE(JumpPlate_Struct, posX, posY, rotation, id, speed, pos);
};

struct JumpGel_struct : public Object_struct
{
	NLOHMANN_DEFINE_TYPE_INTRUSIVE(JumpGel_struct, posX, posY, rotation, id);
};

struct AccelGel_struct : public Object_struct
{
	NLOHMANN_DEFINE_TYPE_INTRUSIVE(AccelGel_struct, posX, posY, rotation, id);
};

struct MovingPlatform_struct : public Object_struct
{	
	bool on;
	float destX;
	float destY;
	NLOHMANN_DEFINE_TYPE_INTRUSIVE(MovingPlatform_struct, posX, posY, rotation, id, on, destX, destY);
};

struct Switch_struct : public Object_struct
{
	int buttonId;
	float time;
	bool type;
	NLOHMANN_DEFINE_TYPE_INTRUSIVE(Switch_struct, posX, posY, rotation, id, buttonId, time, type);
};

struct AngledTile_struct : public Object_struct
{
	bool on;
	NLOHMANN_DEFINE_TYPE_INTRUSIVE(AngledTile_struct, posX, posY, rotation, id, on);
};

struct Dropper_struct : public Object_struct
{
	char contentsId;
	NLOHMANN_DEFINE_TYPE_INTRUSIVE(Dropper_struct, posX, posY, rotation, id, contentsId);
};

struct Dummy_struct1 : public Object_struct
{
	float dummyFloat1;
	float dummyFloat2;
	float dummyFloat3;
	float dummyFloat4;
	float dummyFloat5;
	float dummyFloat6;
	vector<float> dummyVec;	
	NLOHMANN_DEFINE_TYPE_INTRUSIVE(Dummy_struct1, posX, posY, rotation, id, dummyFloat1, dummyFloat2, dummyFloat3, dummyFloat4, dummyFloat5, dummyFloat6, dummyVec);
};

struct Dummy_struct2 : public Object_struct
{
	float dummyFloat1;
	float dummyFloat2;
	float dummyFloat3;
	float dummyFloat4;
	float dummyFloat5;
	float dummyFloat6;
	vector<float> dummyVec;
	NLOHMANN_DEFINE_TYPE_INTRUSIVE(Dummy_struct2, posX, posY, rotation, id, dummyFloat1, dummyFloat2, dummyFloat3, dummyFloat4, dummyFloat5, dummyFloat6, dummyVec);
};

struct Dummy_struct3 : public Object_struct
{
	float dummyFloat1;
	float dummyFloat2;
	float dummyFloat3;
	float dummyFloat4;
	float dummyFloat5;
	float dummyFloat6;
	vector<float> dummyVec;
	NLOHMANN_DEFINE_TYPE_INTRUSIVE(Dummy_struct3, posX, posY, rotation, id, dummyFloat1, dummyFloat2, dummyFloat3, dummyFloat4, dummyFloat5, dummyFloat6, dummyVec);
};


struct Data_struct
{
	Map_Size_Struct map_size;
	Player_struct player;
	Goal_struct goal;
	vector<Tile_struct> tiles;
	vector<Black_Tile_struct> blacktile;
	vector<Cube_struct> cubes;
	vector<Button_sturct> buttons;
	vector<Tunnel_sturct> tunnels;
	vector<Bridge_sturct> bridges;
	vector<Redwall_struct> redwalls;
	vector<Water_struct> waters;
	vector<JumpPlate_Struct> jumpPlates;
	vector<JumpGel_struct> jumpGels;
	vector<AccelGel_struct> accelGels;
	vector<MovingPlatform_struct> movingPlatforms;
	vector<Switch_struct> switches;
	vector<AngledTile_struct> angleTiles;
	vector<Dropper_struct> droppes;
	vector<Dummy_struct1> dummys1;
	vector<Dummy_struct2> dummys2;
	vector<Dummy_struct3> dummys3;

	NLOHMANN_DEFINE_TYPE_INTRUSIVE(Data_struct, map_size, player, goal, tiles, cubes, buttons, tunnels, bridges, blacktile,redwalls, waters, jumpPlates, jumpGels, accelGels, movingPlatforms, switches, angleTiles, droppes, dummys1, dummys2, dummys3);
};