#pragma once

#include "Definitions.h"
#include "Instruments.h"
#include "Stack.h"

namespace game
{
	struct Hero							// Хранит данные о герое (координаты, очки здоровья)
	{
		int xCoordinate;
		int yCoordinate;
		int healthPoints = 100;
		double score = 10000;
	};

	struct Objects                  // Хранит данные об объектах на карте (прицел, порталы)
	{
		int xCoordinate = 0;
		int yCoordinate = 0;
	};

	struct GameInfo
	{
		Hero hero;
		Objects redPortal, bluePortal, aim, blackWall, exitFromLevel, button;
	};

	struct MapCell					// структура MapCell хранит всебе данные о клетке карты
	{
		Stack<char>* types;			// переменная для хранения текстуры (персонажа, блоков и тд)
		bool passable;				// переменная хранит в себе данные о возможности пройти сквозь неё
	};

	// функция считывающая карту из файла в двумерный массив структур, функция принимает в качетсве аргумета имя уровня
	MapCell** createMap(char* levelName, GameInfo* gameInfo);
}
