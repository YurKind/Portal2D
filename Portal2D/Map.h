#pragma once

#include "Definitions.h"
#include "Instruments.h"

namespace game
{
	struct Hero
	{
		//char type = HERO;
		int xCoordinate;
		int yCoordinate;
		int healthPoints = 100;
	};

	struct Aim
	{
		//char type = AIM_DOT;
		int xCoordinate;
		int yCoordinate;
	};

	struct RedPortal
	{
		//char type = RED_PORTAL;
		int xCoordinate;
		int yCoordinate;
	};

	struct BluePotal
	{
		//char type = BLUE_PORTAL;
		int xCoordinate;
		int yCoordinate;
	};

	struct MapCell					// структура MapCell хранит всебе данные о клетке карты
	{
		char type;					// переменная для хранения текстуры (персонажа, блоков и тд)
		int xCoordinate;			// координаты по x ?(оно пригодится в будущем)?
		int yCoordinate;			// координаты по y ???
		bool passable;				// переменная хранит в себе данные о возможности пройти сквозь неё
		//int healthPoints = 100;		// здоровье персонажей
	};

	// функция считывающая карту из файла в двумерный массив структур, функция принимает в качетсве аргумета имя уровня
	MapCell** createMap(char* levelName, Hero* hero, Aim* aim, RedPortal* redPortal, BluePotal* bluePortal);
}
