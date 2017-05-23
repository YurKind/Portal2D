#pragma once
#include "Gameplay.h"
#include "Map.h"


// За модуль отвечают: Лебедев Никита, Меньшиков Юрий и Наговицин Максим
namespace game
{	// Главная функция ИИ турелей, запускает их работу
	void turretAI(char type, GameInfo* gameInfo, MapCell** map);
	
	// Определяет направление движения объектов (пуль и турелей), основываясь на положении героя
	int determineMovingDirection(char type, GameInfo* gameInfo, MapCell** map);
	
	// Проверяет, должна ли турель стрелять
	bool checkTurretShootingConditions(char type, GameInfo* gameInfo, MapCell** map, int step);
	
	// Функция определяет поведение пули (ее появление, исчезновение)
	void shootHero(char type, char bullet, GameInfo* gameInfo, MapCell** map, bool turretCanShootingToHero, int step);
	
	// Функция отвечает за перемещение пули по карте
	void moveBullet(char bullet, GameInfo* gameInfo, MapCell** map, int step);
	
	// Функция отвечает за перемещение патрулирующей турели
	void platformTurretPatrol(GameInfo* gameInfo, MapCell** map, bool turretCanShootingToHero, int step);

	// Функция отвечает за перемещение турели-охотника
	void turretHunterMoving(GameInfo* gameInfo, MapCell** map, bool turretCanShootingToHero, int step);
}
