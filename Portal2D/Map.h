#pragma once

#include "Definitions.h"
#include "Instruments.h"

namespace game
{
	struct GameInfo
	{
		struct Hero							// Хранит данные о герое (координаты, очки здоровья)
		{
			int xCoordinate;
			int yCoordinate;
			int healthPoints = 100;
		} hero;

		struct Coordinates                  // Хранит данные об объектах на карте (прицел, порталы)
		{
			int xCoordinate;
			int yCoordinate;
		} redPortal, bluePortal, aim;
	};

	struct MapCell					// структура MapCell хранит всебе данные о клетке карты
	{
		char type;					// переменная для хранения текстуры (персонажа, блоков и тд)
		//int xCoordinate;			// координаты по x ?(оно пригодится в будущем)?
		//int yCoordinate;			// координаты по y ???
		bool passable;				// переменная хранит в себе данные о возможности пройти сквозь неё
	};

	// функция считывающая карту из файла в двумерный массив структур, функция принимает в качетсве аргумета имя уровня
	MapCell** createMap(char* levelName, GameInfo* gameInfo);
}
