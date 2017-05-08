#pragma once

#include <iostream>
#include <iomanip>
#include <fstream>

#include <string>
#include <conio.h>

#include "Definitions.h"
#include "Structures.h"
#include "Map.h"
#include "Stack.h"

namespace game
{
	/* Останавливает процесс игры и возвращает кол-во миллисекунд, проведенных на паузе*/
	double pause(GameInfo* gameInfo, MapCell** map);

	// Выполняя необходимые проверки, совершает прыжок, если он возможен
	void jump(char type, GameInfo* gameInfo, MapCell** map);

	// Совершает определенное действие в зависимости от нажатой игроком клавиши
	void performAnAction(GameInfo* gameInfo, MapCell** map);

	// Функции для перемещения объектов влево-вправо-вверх-вниз
	void moveOx(int sideOfMovingOx, char type, GameInfo* gameInfo, game::MapCell** map);
	void moveOy(int sideOfMovingOy, char type, GameInfo* gameInfo, game::MapCell** map);

	// Временная функция для запуска первого уровня
	records::DataAboutTheChampion* startLevel(char* levelName);

	// Выполняя необходимые проверки, имитирует гравитацию
	void gravity(MapCell** map, GameInfo* gameInfo);

	// функуция установки портала
	void setPortal(char type, GameInfo* gameInfo, MapCell** map);

	// функуция перехода по порталам
	void enterThePortal(char type, GameInfo* gameInfo, MapCell** map);	

	// функция активации кнопки
	void activateTheButton(GameInfo* gameInfo, MapCell** map);

	// функция перемещения прицела к герою
	void replayceTheAimToHero(GameInfo* gameInfo, MapCell** map);

	// Функция проверяет, не настали ли условия, приводящие к концу игры (нашел ли игрок выход, кончилось ли у игрока здоровье)
	bool checkGameOverConditions(GameInfo* gameInfo, MapCell** map, bool gameIsRunning);
	
	// функция выхода из уровня
	bool quitTheLevel(GameInfo* gameInfo, MapCell** map);

	bool objectIsStandingOnTheFloor(Coordinates coordinates, MapCell** map);

	bool movingPossableOx(Coordinates coordinates, GameInfo* gameInfo, MapCell** map, int sideOfMovingOx, char type);

	bool movingPossableOy(Coordinates coordinates, GameInfo* gameInfo, MapCell** map, int sideOfMovingOx, char type);

	bool oneCellAboveTheObjectIsFree(Coordinates coordinates, MapCell** map);

	bool bothCellsAboveTheObjectAreFree(Coordinates coordinates, MapCell** map);

	Coordinates getCoordinates(GameInfo* gameInfo, char type);

	void setOXCoordinates(GameInfo* gameInfo, char type);

	void setOYCoordinates(GameInfo* gameInfo, char type);

	void changeOXCoordinates(GameInfo* gameInfo, char type, int sideOfMovingOx);

	void changeOYCoordinates(GameInfo* gameInfo, char type, int sideOfMovingOy);
}