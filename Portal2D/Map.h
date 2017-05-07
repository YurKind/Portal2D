#pragma once

#include "Stack.h"
#include "List.h"

namespace game
{
	struct Coordinates
	{
		int xCoordinate = 0;
		int yCoordinate = 0;
	};

	struct Hero					// Хранит данные о герое (координаты, очки здоровья)
	{
		Coordinates coordinates;
		int healthPoints = 99;
		double score = 4000.0;
		double time = 10000.0;
		bool isPlayerPassedLevel = true;
	};

	struct Objects				// Хранит данные об объектах на карте (прицел, порталы)
	{
		Coordinates coordinates;
	};

	struct Turret				// Хранит данные о турелях
	{
		Coordinates coordinates;
		bool isMovingRight = true;
	};

	struct GameInfo
	{
		Hero hero;
		Objects redPortal, bluePortal, aim, blackWallOne, blackWallTwo, blackWallThree, blackWallFour,
			exitFromLevel, buttonOne, buttonTwo, buttonThree, buttonFour,
			bulletOfStationaryTurret, bulletOfPlatformTurret, bulletOfHunterTurret, wall;
		Turret hunter_turret, stationary_turret, platform_turret;
	};

	struct MapCell					// структура MapCell хранит всебе данные о клетке карты
	{
		list::List<char>* types;	// переменная для хранения текстуры (персонажа, блоков и тд)
		bool passable = true;		// переменная хранит в себе данные о возможности пройти сквозь неё
	};

	// функция считывающая карту из файла в двумерный массив структур, функция принимает в качетсве аргумета имя уровня
	MapCell** createMap(char* levelName, GameInfo* gameInfo);
}
