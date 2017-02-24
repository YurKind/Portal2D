#pragma once

#define HERO static_cast<char>(2)
#define BLOCK '#'
#define EMPTY_SPACE ' '
//#define TURRET ''
//#define TIMER_BUTTON ''
#define RED_PORTAL 'O'
#define BLUE_PORTAL 'O'


namespace game
{
	struct Hero
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
	};

	struct Map
	{
		Hero hero;
		Turret turret;
		TimerButton timeButton;
		Block block;
		BluePortal bluePortal;
		RedPortal redPortal;
		EmptySpace emptySpace;
		char type;
	};

	Map** createMap(int, int);
	//void printMap(char** map);
}