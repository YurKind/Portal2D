#pragma once

#include "DistrOfDefine.h"
#include "Map.h"

#include <iostream>
#include <conio.h>

namespace game
{
	int findHeroXCoordinate(Map** map);
	int findHeroYCoordinate(Map** map);

	int findAimXCoordinate(Map** map);
	int findAimYCoordinate(Map** map);

	void drawFrame(Map** map);
}