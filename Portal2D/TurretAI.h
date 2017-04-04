#pragma once
#include "Gameplay.h"
#include "Map.h"

namespace game
{
	void turretAI(GameInfo* gameInfo, MapCell** map);
	void turretMoving(GameInfo* gameInfo, MapCell** map, bool heroIsSpotted);
	bool spottingHero(GameInfo* gameInfo, MapCell** map);
	void shootingToHero(GameInfo* gameInfo, MapCell** map, bool heroIsSpotted);
}
