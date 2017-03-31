#pragma once
#include <iostream>
#include "Map.h"

namespace game
{
	void turretAI(MapCell** map, GameInfo* gameInfo);
	bool heroIsNear(MapCell** map);
}
