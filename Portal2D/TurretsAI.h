#pragma once
#include "Gameplay.h"
#include "Map.h"

namespace game
{
	void TurretAI(char type, GameInfo* gameInfo, MapCell** map);
	int determinePositionOfHero(char type, GameInfo* gameInfo, MapCell** map);
	bool checkTurretShotConditions(char type, GameInfo* gameInfo, MapCell** map, int step);
	void shootingToHero(char type, GameInfo* gameInfo, MapCell** map, bool turretCanShootingToHero, int step);
	void moveBullet(char type, GameInfo* gameInfo, MapCell** map, int step);
	void platformTurretPatrol(GameInfo* gameInfo, MapCell** map, bool turretCanShootingToHero, int step);


	//// Фукнция отвечает за работу ИИ турели
	//void turretPatrolAI(GameInfo* gameInfo, MapCell** map, bool *isMovingRight);
	//// Отвечает за патрулирование местности турелью
	//void turretPatrol(GameInfo* gameInfo, MapCell** map, bool *isMovingRight, bool *wallIsHere);
	//// Фукнция отвечает за стрельбу по герою
	//void shootingToHeroPatrol(GameInfo* gameInfo, MapCell** map, bool *wallIsHere);
	//// Отвечает за стрельбу вправо
	//void shootingRight(GameInfo* gameInfo, MapCell** map);
	//// Отвечает за стрельбу влево
	//void shootingLeft(GameInfo* gameInfo, MapCell** map);
	//// Функция проверяет, есть ли между героем и турелью стены
	//bool checkTheWall(GameInfo* gameInfo, MapCell** map);

	//void turretAI(GameInfo* gameInfo, MapCell** map);
	//void turretMoving(GameInfo* gameInfo, MapCell** map, bool heroIsSpotted);
	//bool spottingHero(GameInfo* gameInfo, MapCell** map);
	//bool spottingHeroPatrol(GameInfo* gameInfo, MapCell** map);
	//void shootingToHero(GameInfo* gameInfo, MapCell** map, bool heroIsSpotted);
}
