#pragma once
#include "Gameplay.h"
#include "Map.h"

namespace game
{
	void turretAI(char type, GameInfo* gameInfo, MapCell** map);
	void turretMoving(GameInfo* gameInfo, MapCell** map, bool heroIsSpotted);
	void turretPatrol(GameInfo* gameInfo, MapCell** map, bool heroIsSpotted);
	bool spottingHero(GameInfo* gameInfo, MapCell** map);
	void shootingToHero(GameInfo* gameInfo, MapCell** map, bool heroIsSpotted);
}
