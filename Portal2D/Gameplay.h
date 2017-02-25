#pragma once

#define HERO static_cast<char>(2)
#define HERO_SYMBOL 'H'
#define BLOCK_SHARP '#'
#define BLOCK static_cast<char>(219)
#define EMPTY_SPACE ' '
//#define TURRET ''
//#define TIMER_BUTTON ''
#define RED_PORTAL 'O'
#define BLUE_PORTAL 'O'
#define NEW_LINE '\n'

#define MAP_HEIGHT 20
#define MAP_WIDTH 35

//--------KEYS---------//
#define W_LOWER_CASE 119
#define A_LOWER_CASE 97
#define S_LOWER_CASE 115
#define D_LOWER_CASE 100
#define W_UPPER_CASE 87
#define A_UPPER_CASE 65
#define S_UPPER_CASE 83
#define D_UPPER_CASE 68

namespace game
{
	/*struct Hero
	{
		char symbol = HERO;
		int xCoordinate;
		int yCoordinate;
		int healthPoints = 100;
	};

	struct Turret
	{
		int xCoordinate;
		int yCoordinate;
		bool passable = true;
	};

	struct TimerButton
	{
		int xCoordinate;
		int yCoordinate;
		int timer;
		bool passable = true;
	};

	struct Block
	{
		char symbol = BLOCK;
		int xCoordinate;
		int yCoordinate;
		bool passable = false;
	};

	struct RedPortal
	{
		char symbol = RED_PORTAL;
		int xCoordinate;
		int yCoordinate;
		bool passable = true;
	};

	struct BluePortal
	{
		char symbol = BLUE_PORTAL;
		int xCoordinate;
		int yCoordinate;
		bool passable = true;
	};

	struct EmptySpace
	{
		char symbol = EMPTY_SPACE;
		int xCoordinate;
		int yCoordinate;
		bool passable = true;
	};*/

	struct Map
	{
		char type;
		int xCoordinate;
		int yCoordinate;
		bool passable;
		int healthPoints = 100;
	};

	Map** createMap(int sizeOfMapHeight, int sizeOfMapWidth, char* levelName);
	void drawFrame(int sizeOfMapHeight, int sizeOfMapWidth, Map** map);
	
}