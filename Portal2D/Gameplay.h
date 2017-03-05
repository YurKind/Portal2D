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
	void jump(Hero* hero, game::MapShell** map);

	// Совершает определенное действие в зависимости от нажатой игроком клавиши
	void performAnAction(MapShell** map, Hero* hero, Aim* aim, RedPotal* redPortal, BluePotal* bluePortal);
	
	// Функции для перемещения объектов влево-вправо-вверх-вниз

	template <class T>
	void moveLeft(char type, T *object, MapShell** map);
	template <class T>
	void moveRight(char type, T *object, MapShell** map);
	template <class T>
	void moveUp(char type, T *object, game::MapShell** map);
	template <class T>
	void moveDown(char type, T *object, game::MapShell** map);
	
	// Функции для перемещения прицела вправо-влево-вверх-вниз
	/*void moveAimRight(char type, int aimYCoordinate, int aimXCoordinate, MapShell** map);
	void moveAimLeft(char type, int aimYCoordinate, int aimXCoordinate, MapShell** map);
	void moveAimUp(char type, int aimYCoordinate, int aimXCoordinate, MapShell** map);
	void moveAimDown(char type, int aimYCoordinate, int aimXCoordinate, MapShell** map);*/

	// Временная функция для запуска первого уровня
	void levelOne(); 

	// Выполняя необходимые проверки, имитирует гравитацию
	template <class T>
	void gravity(MapShell** map, T* object);

	void setPortal(char type, int PortalYCoordinate, int PortalXCoordinate, int aimYCoordinate, int aimXCoordinate, MapShell** map);
	/*void enterThePortal(char type, MapShell** map);*/
}