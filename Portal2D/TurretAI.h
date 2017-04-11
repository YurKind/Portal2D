#pragma once
#include "Gameplay.h"
#include "Map.h"

namespace game
{
	//void turretAI(GameInfo* gameInfo, MapCell** map);
	void turretPatrolAI(GameInfo* gameInfo, MapCell** map, bool *isMovingRight);
	void turretMoving(GameInfo* gameInfo, MapCell** map, bool heroIsSpotted);
	void turretPatrol(GameInfo* gameInfo, MapCell** map, bool heroIsSpotted, bool *isMovingRight);
	//bool spottingHero(GameInfo* gameInfo, MapCell** map);
	bool spottingHeroPatrol(GameInfo* gameInfo, MapCell** map);
	//void shootingToHero(GameInfo* gameInfo, MapCell** map, bool heroIsSpotted);
	void shootingToHeroPatrol(GameInfo* gameInfo, MapCell** map, bool heroIsSpotted);
}
