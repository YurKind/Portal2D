#pragma once

#include <iostream>
#include <iomanip>
#include <fstream>
#include <conio.h>

#include "DistrOfDefine.h"

namespace game
{
	struct Map
	{
		char type;
		int xCoordinate;
		int yCoordinate;
		bool passable;
		int healthPoints = 100;
	};

	Map** createMap(char* levelName);
	void drawFrame(Map** map);
	void jump(int heroXCoordinate, int heroYCoordinate, Map** map);
	void moving(Map** map);
	int findHeroXCoordinate(Map** map);
	int findHeroYCoordinate(Map** map);
	void moveLeft(char type, int yCoordinate, int xCoordinate, Map** map);
	void moveRight(char type, int yCoordinate, int xCoordinate, Map** map);
	
	int findAimXCoordinate(Map** map);
	int findAimYCoordinate(Map** map);
	void moveAimRight(char type, int aimXCoordinate, int aimYCoordinate, Map** map);
	void moveAimLeft(char type, int aimXCoordinate, int aimYCoordinate, Map** map);
	void moveAimUp(char type, int aimXCoordinate, int aimYCoordinate, Map** map);
	void moveAimDown(char type, int aimXCoordinate, int aimYCoordinate, Map** map);
}