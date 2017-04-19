#pragma once

#include "Stack.h"
#include "List.h"

namespace game
{
	struct Hero					// Хранит данные о герое (координаты, очки здоровья)
	{
		int xCoordinate;
		int yCoordinate;
		int healthPoints = 99;
		double score = 4000.0;
		double time = 10000.0;
	};

	struct Objects				// Хранит данные об объектах на карте (прицел, порталы)
	{
		int xCoordinate = 0;
		int yCoordinate = 0;
	};

	struct Turret				// Хранит данные о турелях
	{
		int xCoordinate = 0;
		int yCoordinate = 0;
		bool isMovingRight = true;
	};

	struct GameInfo
	{
		Hero hero;
		Objects redPortal, bluePortal, aim, blackWall, exitFromLevel, button,
			bulletOfStationaryTurret, bulletOfPlatformTurret, bulletOfHunterTurret;
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
