#pragma once

#include <iostream>
#include <iomanip>
#include <fstream>
#include <conio.h>

#include "Definitions.h"
#include "Map.h"

namespace game
{
	// Выполняя необходимые проверки, совершает прыжок, если он возможен
	void jump(int heroYCoordinate, int heroXCoordinate, MapShell** map);

	// Совершает определенное действие в зависимости от нажатой игроком клавиши
	void performAnAction(MapShell** map);
	
	// Функции для перемещения объектов влево-вправо-вверх-вниз
	void moveLeft(char type, int yCoordinate, int xCoordinate, MapShell** map);
	void moveRight(char type, int yCoordinate, int xCoordinate, MapShell** map);
	void moveUp(char type, int yCoordinate, int xCoordinate, MapShell** map);
	void moveDown(char type, int yCoordinate, int xCoordinate, MapShell** map);
	
	// Функции для перемещения прицела вправо-влево-вверх-вниз
	/*void moveAimRight(char type, int aimYCoordinate, int aimXCoordinate, MapShell** map);
	void moveAimLeft(char type, int aimYCoordinate, int aimXCoordinate, MapShell** map);
	void moveAimUp(char type, int aimYCoordinate, int aimXCoordinate, MapShell** map);
	void moveAimDown(char type, int aimYCoordinate, int aimXCoordinate, MapShell** map);*/

	// Временная функция для запуска первого уровня
	void levelOne(); 

	// Выполняя необходимые проверки, имитирует гравитацию
	void gravity(MapShell** map);

	//void setRedPortal(char type, int redPortalYCoordinate, int redPortalXCoordinate, int aimYCoordinate, int aimXCoordinate, game::Map** map);
	//void setBluePortal(char type, int bluePortalYCoordinate, int bluePortalXCoordinate, int aimYCoordinate, int aimXCoordinate, game::Map** map);
}