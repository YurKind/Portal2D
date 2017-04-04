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
	struct GameInfo;
	struct MapCell;

	// Выполняя необходимые проверки, совершает прыжок, если он возможен
	void jump(char type, GameInfo* gameInfo, MapCell** map);

	// Совершает определенное действие в зависимости от нажатой игроком клавиши
	void performAnAction(GameInfo* gameInfo, MapCell** map);
	
	// Функции для перемещения объектов влево-вправо-вверх-вниз
	void moveLeft(char type, GameInfo* gameInfo, MapCell** map);
	void moveRight(char type, GameInfo* gameInfo, MapCell** map);
	void moveUp(GameInfo* gameInfo, MapCell** map);
	void moveDown(char type, GameInfo* gameInfo, MapCell** map);

	// функция переставляет прицел, при установке портала
	void replaceTheAim(GameInfo* gameInfo, MapCell** map);
	//void replaceTheAimMovement(GameInfo* gameInfo, MapCell** map);

	// Временная функция для запуска первого уровня
	records::DataAboutTheChampion* startLevel(char* levelName); 

	// Выполняя необходимые проверки, имитирует гравитацию
	void gravity(MapCell** map, GameInfo* gameInfo);


	void setPortal(char type, GameInfo* gameInfo, MapCell** map);	// функуция установки портала
	void enterThePortal(char type, GameInfo* gameInfo, MapCell** map);	// функуция перехода по порталам

	void activateTheButton(GameInfo* gameInfo, MapCell** map);	// функция активации кнопки

	void turretAI(GameInfo* gameInfo, MapCell** map);

	bool checkGameOverConditions(GameInfo* gameInfo, MapCell** map);
}