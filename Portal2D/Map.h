#pragma once

#include "Definitions.h"
#include "Instruments.h"

namespace game
{
	struct Hero							// Хранит данные о герое (координаты, очки здоровья)
	{
		int xCoordinate;
		int yCoordinate;
		int healthPoints = 100;
	};

	struct Object                  // Хранит данные об объектах на карте (прицел, порталы)
	{
		int xCoordinate;
		int yCoordinate;
	};

	struct MapCell					// структура MapCell хранит всебе данные о клетке карты
	{
		char type;					// переменная для хранения текстуры (персонажа, блоков и тд)
		//int xCoordinate;			// координаты по x ?(оно пригодится в будущем)?
		//int yCoordinate;			// координаты по y ???
		bool passable;				// переменная хранит в себе данные о возможности пройти сквозь неё
	};

	// функция считывающая карту из файла в двумерный массив структур, функция принимает в качетсве аргумета имя уровня
	MapCell** createMap(char* levelName, Hero* hero, Object* aim, Object* redPortal, Object* bluePortal);
}
