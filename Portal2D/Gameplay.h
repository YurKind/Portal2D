#pragma once

#include <iostream>
#include <iomanip>
#include <fstream>
#include <conio.h>

#include "Definitions.h"
#include "Map.h"
#include "Stack.h"

namespace game
{
	struct GameInfo;
	struct MapCell;

	// Выполняя необходимые проверки, совершает прыжок, если он возможен
	void jump(GameInfo* gameInfo, game::MapCell** map);

	// Совершает определенное действие в зависимости от нажатой игроком клавиши
	void performAnAction(GameInfo* gameInfo, MapCell** map);
	
	// Функции для перемещения объектов влево-вправо-вверх-вниз

	void moveLeft(char type, GameInfo* gameInfo, MapCell** map);
	void moveRight(char type, GameInfo* gameInfo, MapCell** map);
	void moveUp(char type, GameInfo* gameInfo, MapCell** map);
	void moveDown(char type, GameInfo* gameInfo, MapCell** map);
	void replaceTheAim(char type, GameInfo* gameInfo, game::MapCell** map);
	// Временная функция для запуска первого уровня
	double startLevel(char* levelName); 

	// Выполняя необходимые проверки, имитирует гравитацию
	void gravity(MapCell** map, GameInfo* gameInfo);

	void setPortal(char type, GameInfo* gameInfo, game::MapCell** map);
	void enterThePortal(char type, GameInfo* gameInfo, MapCell** map);

	void activateTheButton(GameInfo* gameInfo, game::MapCell** map);

	bool checkGameOverConditions(GameInfo* gameInfo, MapCell** map);
}