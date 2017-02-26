#pragma once

#include <iostream>
#include <iomanip>
#include <fstream>
#include <conio.h>

#include "DistrOfDefine.h"
#include "Map.h"

namespace game
{
	void jump(int heroXCoordinate, int heroYCoordinate, Map** map);
	void performAnAction(Map** map);
	void moveLeft(char type, int yCoordinate, int xCoordinate, Map** map);
	void moveRight(char type, int yCoordinate, int xCoordinate, Map** map);
	
	void moveAimRight(char type, int aimXCoordinate, int aimYCoordinate, Map** map);
	void moveAimLeft(char type, int aimXCoordinate, int aimYCoordinate, Map** map);
	void moveAimUp(char type, int aimXCoordinate, int aimYCoordinate, Map** map);
	void moveAimDown(char type, int aimXCoordinate, int aimYCoordinate, Map** map);
}