#include "Gameplay.h"
#include "Map.h"
#include "Instruments.h"

//------Moving_Functions------//
void game::performAnAction(game::Map** map)
{
	int redPortalXCoordinate = 0;
	int redPortalYCoordinate = 0;
	int bluePortalXCoordinate = 0;
	int bluePortalYCoordinate = 0;

	bool gameIsRunning = true; // Временно

	while (gameIsRunning)
	{
		int heroXCoordinate = findHeroXCoordinate(map); //Ищем координату героя на оси X
		int heroYCoordinate = findHeroYCoordinate(map); //Ищем координату героя на оси Y

		int aimXCoordinate = findAimXCoordinate(map); //Ищем координату прицела на оси X
		int aimYCoordinate = findAimYCoordinate(map); //Ищем координату прицела на оси X

		if (_kbhit()) // Если нажата клавиша
		{
			switch (_getch()) // Читаем клавишу
			{
			case A_LOWER_CASE:
				if (map[heroYCoordinate][heroXCoordinate - 1].passable == true) // Если клетка слева проходима
				{
					moveLeft(HERO, heroYCoordinate, heroXCoordinate, map); 
				}
				break;

			case D_LOWER_CASE:
				if (map[heroYCoordinate][heroXCoordinate + 1].passable == true) // Если клетка справа проходима
				{
					moveRight(HERO, heroYCoordinate, heroXCoordinate, map);
				}
				break;

			case LEFT_ARROW:
				if (map[aimYCoordinate][aimXCoordinate - 1].passable == true) 
				{
					moveAimLeft(AIM_DOT, aimYCoordinate, aimXCoordinate, map);
				}
				break;

			case RIGHT_ARROW:
				if (map[aimYCoordinate][aimXCoordinate + 1].passable == true)
				{
					moveAimRight(AIM_DOT, aimYCoordinate, aimXCoordinate, map);
				}
				break;

			case UP_ARROW:
				if (map[aimYCoordinate - 1][aimXCoordinate].passable == true)
				{
					moveAimUp(AIM_DOT, aimYCoordinate, aimXCoordinate, map);
				}
				break;

			case DOWN_ARROW:
				if (map[aimYCoordinate + 1][aimXCoordinate].passable == true)
				{
					moveAimDown(AIM_DOT, aimYCoordinate, aimXCoordinate, map);
				}
				break;

			case SPACE_JUMP: 
				jump(heroYCoordinate, heroXCoordinate, map); // Прыжок
				break;

			/*case E_LOWER_CASE:
				redPortalXCoordinate = aimXCoordinate;
				redPortalYCoordinate = aimYCoordinate;
				setRedPortal(RED_PORTAL, redPortalYCoordinate, redPortalXCoordinate, aimYCoordinate, aimXCoordinate, map);
				break;*/

			/*case Q_LOWER_CASE:
				bluePortalXCoordinate = aimXCoordinate;
				bluePortalYCoordinate = aimYCoordinate;
				setBluePortal(BLUE_PORTAL, redPortalYCoordinate, redPortalXCoordinate, aimYCoordinate, aimXCoordinate, map);
				break;*/

			default:
				break;
			}
		}
		game::clearScreen(); // Очищаем экран
		game::gravitation(HERO, heroYCoordinate, heroXCoordinate, map); // Имитируем гравитацию
		game::drawFrame(map); // Рисуем кадр
		Sleep(200);
	}
}

void game::jump(int heroYCoordinate, int heroXCoordinate, game::Map** map)
{
	if((map[heroYCoordinate - 1][heroXCoordinate].passable == true) && // Если обе клетки над героем свободны
		(map[heroYCoordinate - 2][heroXCoordinate].passable == true))
	{
		map[heroYCoordinate][heroXCoordinate].type = EMPTY_SPACE; // В клетку, где был герой заносим пробел, в клетку
		map[heroYCoordinate - 1][heroXCoordinate].type = HERO;	  // выше заносим символ героя, а так же переносим инфу о HP
		map[heroYCoordinate - 1][heroXCoordinate].healthPoints = 
			map[heroYCoordinate][heroXCoordinate].healthPoints;

		drawFrame(map);

		map[heroYCoordinate - 1][heroXCoordinate].type = EMPTY_SPACE;
		map[heroYCoordinate - 2][heroXCoordinate].type = HERO;
		map[heroYCoordinate - 2][heroXCoordinate].healthPoints = 
			map[heroYCoordinate - 1][heroXCoordinate].healthPoints;
	}

	else if ((map[heroYCoordinate - 1][heroXCoordinate].passable == true) && // Если свободна только одна
		(map[heroYCoordinate - 2][heroXCoordinate].passable == false))
	{
		map[heroYCoordinate][heroXCoordinate].type = EMPTY_SPACE;
		map[heroYCoordinate - 1][heroXCoordinate].type = HERO;
		map[heroYCoordinate - 1][heroXCoordinate].healthPoints =
			map[heroYCoordinate][heroXCoordinate].healthPoints;
	}
}

void game::moveLeft(char type, int yCoordinate, int xCoordinate, game::Map** map)
{
	map[yCoordinate][xCoordinate].type = EMPTY_SPACE; // В клетку, где был герой заносим пробел, в клетку
	map[yCoordinate][xCoordinate - 1].type = type;	  // слева заносим символ героя, а так же переносим инфу о HP
	map[yCoordinate][xCoordinate - 1].healthPoints = 
		map[yCoordinate][xCoordinate].healthPoints;
}

void game::moveRight(char type, int yCoordinate, int xCoordinate, game::Map** map)
{
	map[yCoordinate][xCoordinate].type = EMPTY_SPACE; // В клетку, где был герой заносим пробел, в клетку
	map[yCoordinate][xCoordinate + 1].type = type;    // справа заносим символ героя, а так же переносим инфу о HP
	map[yCoordinate][xCoordinate + 1].healthPoints =
		map[yCoordinate][xCoordinate].healthPoints;
}


//------Aim_Functions------//
void game::moveAimLeft(char type, int aimYCoordinate, int aimXCoordinate, game::Map** map)
{
	map[aimYCoordinate][aimXCoordinate].type = EMPTY_SPACE; // В клетку, где был прицел заносим пробел, в клетку
	map[aimYCoordinate][aimXCoordinate - 1].type = type;    // слева заносим символ прицела
}

void game::moveAimRight(char type, int aimYCoordinate, int aimXCoordinate, game::Map** map)
{
	map[aimYCoordinate][aimXCoordinate].type = EMPTY_SPACE; // В клетку, где был прицел заносим пробел, в клетку
	map[aimYCoordinate][aimXCoordinate + 1].type = type;	// справа заносим символ прицела
}

void game::moveAimUp(char type, int aimYCoordinate, int aimXCoordinate, game::Map** map)
{
	map[aimYCoordinate][aimXCoordinate].type = EMPTY_SPACE; // В клетку, где был прицел заносим пробел, в клетку
	map[aimYCoordinate - 1][aimXCoordinate].type = type;	// вверху заносим символ прицела
}

void game::moveAimDown(char type, int aimYCoordinate, int aimXCoordinate, game::Map** map)
{
	map[aimYCoordinate][aimXCoordinate].type = EMPTY_SPACE; // В клетку, где был прицел заносим пробел, в клетку
	map[aimYCoordinate + 1][aimXCoordinate].type = type;	// внизу заносим символ прицела
}


//------Gravitation_Functions------//
void game::gravitation(char type, int yCoordinate, int xCoordinate, game::Map** map)
{
	if(map[yCoordinate + 1][xCoordinate].passable == true) // Если клетка под объектом - проходима
	{
		map[yCoordinate][xCoordinate].type = EMPTY_SPACE; // В клетку, где был объект заносим пробел, в клетку
		map[yCoordinate + 1][xCoordinate].type = type;    // внизу заносим символ объекта, а так же переносим инфу о HP
		map[yCoordinate + 1][xCoordinate].healthPoints = 
			map[yCoordinate][xCoordinate].healthPoints;
	}
}

void game::levelOne() 
{
	game::clearScreen(); // Чистим экран

	game::Map** map = game::createMap("Lvl_1.txt"); // Создаем двумерный массив структур, используя текстовый документ

	game::drawFrame(map); // Рисуем первый кадр

	game::performAnAction(map); // Выполняем далее в зависимости от действий игрока
}

//-----Portals_Functions------//
/*void game::setRedPortal(char type, int redPortalYCoordinate, int redPortalXCoordinate, int aimYCoordinate, int aimXCoordinate, game::Map** map)
{
	map[aimYCoordinate][aimXCoordinate].type = RED_PORTAL;
	map[redPortalYCoordinate][redPortalXCoordinate].type = EMPTY_SPACE;

	if (map[aimYCoordinate][aimXCoordinate - 1].type = EMPTY_SPACE)
	{
		aimXCoordinate = aimXCoordinate - 1;
		map[aimYCoordinate][aimXCoordinate].type = AIM_DOT;
	}

	else if (map[aimYCoordinate][aimXCoordinate + 1].type = EMPTY_SPACE)
	{
		aimXCoordinate = aimXCoordinate + 1;
		map[aimYCoordinate][aimXCoordinate].type = AIM_DOT;
	}
	redPortalXCoordinate = aimXCoordinate;
	redPortalYCoordinate = aimYCoordinate;
}
void game::setBluePortal(char type, int bluePortalYCoordinate, int bluePortalXCoordinate, int aimYCoordinate, int aimXCoordinate, game::Map** map)
{
	map[aimYCoordinate][aimXCoordinate].type = BLUE_PORTAL;
	map[bluePortalYCoordinate][bluePortalXCoordinate].type = EMPTY_SPACE;

	if (map[aimYCoordinate][aimXCoordinate - 1].type = EMPTY_SPACE)
	{
		aimXCoordinate = aimXCoordinate - 1;
		map[aimYCoordinate][aimXCoordinate].type = AIM_DOT;
	}

	else if (map[aimYCoordinate][aimXCoordinate + 1].type = EMPTY_SPACE)
	{
		aimXCoordinate = aimXCoordinate + 1;
		map[aimYCoordinate][aimXCoordinate].type = AIM_DOT;
	}
	bluePortalXCoordinate = aimXCoordinate;
	bluePortalYCoordinate = aimYCoordinate;
}*/