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

// За модуль отвечают: Меньшиков Юрий и Наговицин Максим
namespace game
{
	// Останавливает процесс игры и возвращает кол-во миллисекунд, проведенных на паузе
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
	void enterThePortal(GameInfo* gameInfo, MapCell** map);	

	// функция активации кнопки
	void activateTheButton(GameInfo* gameInfo, MapCell** map);

	// Функция проверяет, не настали ли условия, приводящие к концу игры (нашел ли игрок выход, кончилось ли у игрока здоровье)
	bool checkGameOverConditions(GameInfo* gameInfo, MapCell** map, bool gameIsRunning);
	
	// функция прерывает процесс игры
	bool quitTheLevel(GameInfo* gameInfo, MapCell** map);

	// функция проверяет стоит ли объект на непроходимой поверхности
	bool objectIsStandingOnTheFloor(Coordinates coordinates, MapCell** map);

	// функция проверяет возможность проходимости по оси Ox
	bool movingPossibleOx(Coordinates coordinates, MapCell** map, int sideOfMovingOx, char type);

	// функция проверяет возможность проходимости по оси Oy
	bool movingPossibleOy(Coordinates coordinates, MapCell** map, int sideOfMovingOx, char type);

	// функция проверяет есть ли над объектом одна свободная клетка
	bool oneCellAboveTheObjectIsFree(Coordinates coordinates, MapCell** map);

	// функция проверяет есть ли над объектом две свободных клетки
	bool bothCellsAboveTheObjectAreFree(Coordinates coordinates, MapCell** map);

	// функция возвращает координаты объекта
	Coordinates getCoordinates(GameInfo* gameInfo, char type);

	// функция устанавливает координаты объекта на оси Ox
	void setOXCoordinates(GameInfo* gameInfo, char type, int step);

	// функция устанавливает координаты объекта на оси Oy
	void setOYCoordinates(GameInfo* gameInfo, char type);

	// функция изменяет координаты объекта по оси Ox
	void changeOXCoordinates(GameInfo* gameInfo, char type, int sideOfMovingOx);

	// функция изменяет координаты объекта по оси Oy
	void changeOYCoordinates(GameInfo* gameInfo, char type, int sideOfMovingOy);

	// функция определяет тип портала, в который будет совершено перемещение
	char findTypeOfPortal(GameInfo* gameInfo);

	// функция определяет тип двери
	char findTypeOfDoor(GameInfo* gameInfo, MapCell** map);

	// функция определяет тип кнопки
	char findTypeOfButton(char typeOfDoor);
}