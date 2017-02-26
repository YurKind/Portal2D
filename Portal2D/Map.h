#pragma once

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
}