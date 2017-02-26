#pragma once

#include <iostream>
#include <iomanip>
#include <fstream>
#include <conio.h>

#include "DistrOfDefine.h"
#include "Map.h"

namespace game
{
	// Выполняя необходимые проверки, совершает прыжок, если он возможен
	void jump(int heroYCoordinate, int heroXCoordinate, Map** map); 

	// Совершает определенное действие в зависимости от нажатой игроком клавиши
	void performAnAction(Map** map);
	
	// Функции для перемещения героя влево-вправо
	void moveLeft(char type, int yCoordinate, int xCoordinate, Map** map);
	void moveRight(char type, int yCoordinate, int xCoordinate, Map** map);
	
	// Функции для перемещения прицела вправо-влево-вверх-вниз
	void moveAimRight(char type, int aimYCoordinate, int aimXCoordinate, Map** map);
	void moveAimLeft(char type, int aimYCoordinate, int aimXCoordinate, Map** map);
	void moveAimUp(char type, int aimYCoordinate, int aimXCoordinate, Map** map);
	void moveAimDown(char type, int aimYCoordinate, int aimXCoordinate, Map** map);

	// Временная функция для запуска первого уровня
	void levelOne(); 

	// Выполняя необходимые проверки, имитирует гравитацию
	void gravitation(char type, int yCoordinate, int xCoordinate, Map** map); 

	//void setRedPortal(char type, int redPortalYCoordinate, int redPortalXCoordinate, int aimYCoordinate, int aimXCoordinate, game::Map** map);
	//void setBluePortal(char type, int bluePortalYCoordinate, int bluePortalXCoordinate, int aimYCoordinate, int aimXCoordinate, game::Map** map);
}