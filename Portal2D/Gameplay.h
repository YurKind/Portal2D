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
	void jump(Hero* hero, game::MapCell** map);

	// Совершает определенное действие в зависимости от нажатой игроком клавиши
	void performAnAction(MapCell** map, Hero* hero, Object* aim, Object* redPortal, Object* bluePortal);
	
	// Функции для перемещения объектов влево-вправо-вверх-вниз

	template <class T>
	void moveLeft(char type, T *object, MapCell** map);

	template <class T>
	void moveRight(char type, T *object, MapCell** map);

	template <class T>
	void moveUp(char type, T *object, game::MapCell** map);

	template <class T>
	void moveDown(char type, T *object, game::MapCell** map);

	// Временная функция для запуска первого уровня
	void levelOne(); 

	// Выполняя необходимые проверки, имитирует гравитацию
	template <class T>
	void gravity(MapCell** map, T* object);

	template <class T>
	void setPortal(char type, T* object, Object* aim, game::MapCell** map);
	/*void enterThePortal(char type, MapCell** map);*/
}