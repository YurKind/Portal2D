#include "DistrOfDefine.h"

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
	void jump(int heroXCoordinate, int heroYCoordinate, Map** map);
	void moving(int heroXCoordinate, int heroYCoordinate, Map** map);
	
}