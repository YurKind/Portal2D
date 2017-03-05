#include "Gameplay.h"
#include "Map.h"
#include "Instruments.h"

//------Moving_Functions------//
void game::performAnAction(game::MapShell** map, Hero* hero, Aim* aim, RedPotal* redPortal, BluePotal* bluePortal)
{
	bool gameIsRunning = true; // Временно

	while (gameIsRunning)
	{
		//int heroXCoordinate = findSomeTypeXCoordinate(HERO, map); //Ищем координату героя на оси X
		//int heroYCoordinate = findSomeTypeYCoordinate(HERO, map); //Ищем координату героя на оси Y

		int PortalXCoordinate = findSomeTypeXCoordinate(RED_PORTAL, map);
		int PortalYCoordinate = findSomeTypeYCoordinate(RED_PORTAL, map);

		//int aimXCoordinate = findSomeTypeXCoordinate(AIM_DOT, map); //Ищем координату прицела на оси X
		//int aimYCoordinate = findSomeTypeYCoordinate(AIM_DOT, map); //Ищем координату прицела на оси Y

		if (_kbhit()) // Если нажата клавиша
		{
			switch (_getch()) // Читаем клавишу
			{
			case A_LOWER_CASE:
				moveLeft(HERO, hero, map);
				break;

			case D_LOWER_CASE:
				moveRight(HERO, hero, map);
				break;

			case LEFT_ARROW:
				//условие ниже вызывает неприязнь и желание его уничтожить, но это временно, пока не появится стек
				if ((map[aim->yCoordinate][aim->xCoordinate - 1].type != RED_PORTAL) && (map[aim->yCoordinate][aim->xCoordinate - 1].type != BLUE_PORTAL))
					moveLeft(AIM_DOT, aim, map);
				break;

			case RIGHT_ARROW:
				//условие ниже вызывает неприязнь и желание его уничтожить, но это временно, пока не появится стек
				if ((map[aim->yCoordinate][aim->xCoordinate + 1].type != RED_PORTAL) && (map[aim->yCoordinate][aim->xCoordinate + 1].type != BLUE_PORTAL))
					moveRight(AIM_DOT, aim, map);
				break;

			case UP_ARROW:
				//условие ниже вызывает неприязнь и желание его уничтожить, но это временно, пока не появится стек
				if ((map[aim->yCoordinate - 1][aim->xCoordinate].type != RED_PORTAL) && (map[aim->yCoordinate - 1][aim->xCoordinate].type != BLUE_PORTAL))
					moveUp(AIM_DOT, aim, map);
				break;

			case DOWN_ARROW:
				//условие ниже вызывает неприязнь и желание его уничтожить, но это временно, пока не появится стек
					if ((map[aim->yCoordinate + 1][aim->xCoordinate].type != RED_PORTAL) && (map[aim->yCoordinate + 1][aim->xCoordinate].type != BLUE_PORTAL))
				moveDown(AIM_DOT, aim, map);
				break;

			case SPACE_JUMP:
				jump(hero, map); // Прыжок
				break;

			case E_LOWER_CASE:
				setPortal(RED_PORTAL, PortalYCoordinate, PortalXCoordinate, aim->yCoordinate, aim->xCoordinate, map);
				break;

			case Q_LOWER_CASE:
				setPortal(BLUE_PORTAL, PortalYCoordinate, PortalXCoordinate, aim->yCoordinate, aim->xCoordinate, map);
				break;

			/*case ENTER:
				
				break;*/

			default:
				break;
			}
		}
		game::clearScreen(); // Очищаем экран
		game::drawFrame(map);
		game::gravity(map, hero); // Имитируем гравитацию
		Sleep(50);
		game::clearScreen(); // Очищаем экран
	}
}

void game::jump(Hero* hero, game::MapShell** map)
{
	if (map[hero->yCoordinate + 1][hero->xCoordinate].passable == false)
	{
		if ((map[hero->yCoordinate - 1][hero->xCoordinate].passable == true) && // Если обе клетки над героем свободны
			(map[hero->yCoordinate - 2][hero->xCoordinate].passable == true))
		{
			map[hero->yCoordinate][hero->xCoordinate].type = EMPTY_SPACE; // В клетку, где был герой заносим пробел, в клетку
			map[hero->yCoordinate - 1][hero->xCoordinate].type = HERO;	  // выше заносим символ героя, а так же переносим инфу о HP
			hero->yCoordinate = hero->yCoordinate - 1;

			game::drawFrame(map);

			map[hero->yCoordinate][hero->xCoordinate].type = EMPTY_SPACE;
			map[hero->yCoordinate - 1][hero->xCoordinate].type = HERO;
			hero->yCoordinate = hero->yCoordinate - 1;
		}

		else if ((map[hero->yCoordinate - 1][hero->xCoordinate].passable == true) && // Если свободна только одна
			(map[hero->yCoordinate - 2][hero->xCoordinate].passable == false))
		{
			map[hero->yCoordinate][hero->xCoordinate].type = EMPTY_SPACE;
			map[hero->yCoordinate - 1][hero->xCoordinate].type = HERO;
			hero->yCoordinate = hero->yCoordinate - 1;
		}
	}
}

template <class T>
void game::moveLeft(char type, T *object, game::MapShell** map)
{
	if (map[object->yCoordinate][object->xCoordinate - 1].passable == true) // Если клетка слева проходима 
	{
		map[object->yCoordinate][object->xCoordinate].type = EMPTY_SPACE; // В клетку, где был объект заносим пробел, в клетку
		map[object->yCoordinate][object->xCoordinate - 1].type = type;	  // слева заносим символ объекта, а так же переносим инфу о HP
		object->xCoordinate = object->xCoordinate - 1;
	}
}

template <class T>
void game::moveRight(char type, T *object, game::MapShell** map)
{
	if (map[object->yCoordinate][object->xCoordinate + 1].passable == true) // Если клетка слева проходима 
	{
		map[object->yCoordinate][object->xCoordinate].type = EMPTY_SPACE; // В клетку, где был объект заносим пробел, в клетку
		map[object->yCoordinate][object->xCoordinate + 1].type = type;	  // слева заносим символ объекта, а так же переносим инфу о HP
		object->xCoordinate = object->xCoordinate + 1;
	}
}
template <class T>
void game::moveUp(char type, T *object, game::MapShell** map)
{
	if (map[object->yCoordinate - 1][object->xCoordinate].passable == true) // Если клетка сверху проходима
	{
		map[object->yCoordinate][object->xCoordinate].type = EMPTY_SPACE; // В клетку, где был объект заносим пробел, в клетку
		map[object->yCoordinate - 1][object->xCoordinate].type = type;    // справа заносим символ объекта, а так же переносим инфу о HP
		object->yCoordinate = object->yCoordinate - 1;
	}
}

template <class T>
void game::moveDown(char type, T *object, game::MapShell** map)
{
	if (map[object->yCoordinate + 1][object->xCoordinate].passable == true) // Если клетка снизу проходима 
	{
		map[object->yCoordinate][object->xCoordinate].type = EMPTY_SPACE; // В клетку, где был объект заносим пробел, в клетку
		map[object->yCoordinate + 1][object->xCoordinate].type = type;    // справа заносим символ объекта, а так же переносим инфу о HP
		object->yCoordinate = object->yCoordinate + 1;
	}
}

//------Gravitation_Functions------//
template <class T>
void game::gravity(game::MapShell** map, T *object)
{
	if (map[object->yCoordinate][object->xCoordinate].type == HERO && map[object->yCoordinate + 1][object->xCoordinate].passable == true)
	{
		map[object->yCoordinate][object->xCoordinate].type = EMPTY_SPACE;
		map[object->yCoordinate + 1][object->xCoordinate].type = HERO;
		object->yCoordinate = object->yCoordinate + 1;
	}
}

//void game::gravity(game::MapShell** map)
//{
//	for (int i = 0; i < MAP_HEIGHT; i++)
//	{
//		for (int j = 0; j < MAP_WIDTH; j++)
//		{
//			//Если в клетке герой и клетка под ним - проходима
//			if(map[i][j].type == HERO && map[i + 1][j].passable == true) 
//			{
//					map[i][j].type = EMPTY_SPACE; // В клетку, где был объект заносим пробел, в клетку
//					map[i + 1][j].type = HERO;    // внизу заносим символ объекта, а так же переносим инфу о HP
//					map[i + 1][j].healthPoints =
//						map[i][j].healthPoints;
//					return;
//			}
//		}
//	}
//}

void game::levelOne()
{
	game::Hero* hero = new Hero;
	game::Aim* aim = new Aim;
	game::RedPotal* redPortal = new RedPotal;
	game::BluePotal* bluePortal = new BluePotal;

	game::clearScreen(); // Чистим экран

	game::MapShell** map = game::createMap("Lvl_1.txt", hero, aim, redPortal, bluePortal); // Создаем двумерный массив структур, используя текстовый документ

	game::drawFrame(map); // Рисуем первый кадр

	game::performAnAction(map, hero, aim, redPortal, bluePortal); // Выполняем далее в зависимости от действий игрока
}

//-----Portals_Functions------//
void game::setPortal(char type, int PortalYCoordinate, int PortalXCoordinate, int aimYCoordinate, int aimXCoordinate, game::MapShell** map)
{
	if (type == RED_PORTAL)
	{
		PortalXCoordinate = findSomeTypeXCoordinate(RED_PORTAL, map);
		PortalYCoordinate = findSomeTypeYCoordinate(RED_PORTAL, map);

		map[PortalYCoordinate][PortalXCoordinate].type = EMPTY_SPACE;

		map[aimYCoordinate][aimXCoordinate].type = type;

		if (map[aimYCoordinate][aimXCoordinate - 1].type == EMPTY_SPACE)
		{
			aimXCoordinate = aimXCoordinate - 1;
			map[aimYCoordinate][aimXCoordinate].type = AIM_DOT;
		}

		else if (map[aimYCoordinate][aimXCoordinate + 1].type == EMPTY_SPACE)
		{
			aimXCoordinate = aimXCoordinate + 1;
			map[aimYCoordinate][aimXCoordinate].type = AIM_DOT;
		}
	}

	else if (type == BLUE_PORTAL)
	{
		PortalXCoordinate = findSomeTypeXCoordinate(BLUE_PORTAL, map);
		PortalYCoordinate = findSomeTypeYCoordinate(BLUE_PORTAL, map);

		map[PortalYCoordinate][PortalXCoordinate].type = EMPTY_SPACE;

		map[aimYCoordinate][aimXCoordinate].type = type;

		if (map[aimYCoordinate][aimXCoordinate - 1].type == EMPTY_SPACE)
		{
			aimXCoordinate = aimXCoordinate - 1;
			map[aimYCoordinate][aimXCoordinate].type = AIM_DOT;
		}

		else if (map[aimYCoordinate][aimXCoordinate + 1].type == EMPTY_SPACE)
		{
			aimXCoordinate = aimXCoordinate + 1;
			map[aimYCoordinate][aimXCoordinate].type = AIM_DOT;
		}
	}
}

//void game::enterThePortal(char type, MapShell** map)
//{
//	
//}