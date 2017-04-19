#pragma once
#include "Gameplay.h"
#include "Map.h"

namespace game
{
	void turretAI(char type, GameInfo* gameInfo, MapCell** map);
	//int determineMovingDirection(char type, GameInfo* gameInfo, MapCell** map);
	//bool checkTurretShootingConditions(char type, GameInfo* gameInfo, MapCell** map, int step);
	//void shootHero(char type, GameInfo* gameInfo, MapCell** map, bool turretCanShootingToHero, int step);
	//void moveBullet(char type, GameInfo* gameInfo, MapCell** map, int step);
	//void platformTurretPatrol(GameInfo* gameInfo, MapCell** map, bool turretCanShootingToHero, int step);

	////-----TURRET_HUNTER------//
	//void turretHunterMoving(GameInfo* gameInfo, MapCell** map, bool turretCanShootingToHero, int step);
}
