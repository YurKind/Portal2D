#pragma once

#include <iostream>

#include <Windows.h>
#include <conio.h>

#include "DistrOfDefine.h"
#include "Map.h"

namespace game
{
	int findHeroXCoordinate(Map** map);
	int findHeroYCoordinate(Map** map);

	int findAimXCoordinate(Map** map);
	int findAimYCoordinate(Map** map);

	void drawFrame(Map** map);
	void clearScreen();
}