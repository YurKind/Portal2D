#pragma once

#include "DistrOfDefine.h"
#include "Map.h"

namespace game
{
	int findHeroXCoordinate(Map** map);
	int findHeroYCoordinate(Map** map);

	int findAimXCoordinate(Map** map);
	int findAimYCoordinate(Map** map);
}