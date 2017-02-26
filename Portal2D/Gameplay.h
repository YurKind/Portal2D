#pragma once

#include <iostream>
#include <iomanip>
#include <fstream>
#include <conio.h>

#include "DistrOfDefine.h"
#include "Map.h"

namespace game
{
	void jump(int heroYCoordinate, int heroXCoordinate, Map** map);
	void performAnAction(Map** map);
	void moveLeft(char type, int yCoordinate, int xCoordinate, Map** map);
	void moveRight(char type, int yCoordinate, int xCoordinate, Map** map);
	
	void moveAimRight(char type, int aimYCoordinate, int aimXCoordinate, Map** map);
	void moveAimLeft(char type, int aimYCoordinate, int aimXCoordinate, Map** map);
	void moveAimUp(char type, int aimYCoordinate, int aimXCoordinate, Map** map);
	void moveAimDown(char type, int aimYCoordinate, int aimXCoordinate, Map** map);

	void gravitation(char type, int yCoordinate, int xCoordinate, Map** map);
}