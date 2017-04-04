#include "Gameplay.h"
#include "Map.h"
#include "Instruments.h"
#include "Structures.h"
#include "List.h"
#include "Save.h"
#include "TurretAI.h"


//------Moving_Functions------//
// принимает структуру с информацией об объекте на карте и двумерный массив структур
void game::performAnAction(GameInfo* gameInfo, MapCell** map)
{
	bool gameIsRunning = true;	// условие выполнение цикла

	double timeBeforeGame = clock();

	while (gameIsRunning)
	{

		if (_kbhit()) // Если нажата клавиша
		{
			switch (_getch()) // Читаем клавишу
			{
			case A_LOWER_CASE:
				moveLeft(HERO, gameInfo, map);
				break;

			case D_LOWER_CASE:
				moveRight(HERO, gameInfo, map);
				break;

			case LEFT_ARROW:
				moveLeft(AIM_DOT, gameInfo, map);
				break;

			case RIGHT_ARROW:
				moveRight(AIM_DOT, gameInfo, map);
				break;

			case UP_ARROW:
				moveUp(gameInfo, map);
				break;

			case DOWN_ARROW:
				moveDown(AIM_DOT, gameInfo, map);
				break;

			case SPACE_JUMP:
				jump(HERO, gameInfo, map);
				break;

			case E_LOWER_CASE:
				setPortal(RED_PORTAL, gameInfo, map);
				break;

			case Q_LOWER_CASE:
				setPortal(BLUE_PORTAL, gameInfo, map);
				break;

			case ENTER:
				enterThePortal(HERO, gameInfo, map);
				activateTheButton(gameInfo, map);
				break;

			default:
				break;
			}
		}

		game::turretAI(gameInfo, map);

		// если координаты героя равны координатам выхода, то переменной gameIsRunning присваивается значение false
		gameIsRunning = checkGameOverConditions(gameInfo, map);

		game::clearScreen(); // Очищаем экран
		game::drawFrame(map, gameInfo);
		game::gravity(map, gameInfo); // Имитируем гравитацию
		game::clearScreen(); // Очищаем экран

		double timeAfterAction = clock();

		gameInfo->hero.time = (timeAfterAction - timeBeforeGame) / 1000.0;

		if (gameInfo->hero.score > 0)	// если количество очков больше 0, то вычетается одно очко
		{
			gameInfo->hero.score -= 1.02354;
		}
	}

	double timeAfterGame = clock();

	double requiredTime = (timeAfterGame - timeBeforeGame) / 1000.0;
}

//------Moving_Functions------//
// принимает структуру с информацией об объекте на карте и двумерный массив структур
void game::jump(char type, GameInfo* gameInfo, game::MapCell** map)
{
	switch (type)
	{
	case HERO:
		if (map[gameInfo->hero.yCoordinate + 1][gameInfo->hero.xCoordinate].passable == false)	// если под персонажем есть непроходимый блок
		{
			//replaceTheAimMovement(gameInfo, map);

			// Если обе клетки над героем свободны
			if ((map[gameInfo->hero.yCoordinate - 1][gameInfo->hero.xCoordinate].passable == true) &&
				(map[gameInfo->hero.yCoordinate - 2][gameInfo->hero.xCoordinate].passable == true))
			{
				//удаляем символ героя из текущей ячейки
				list::deleteCurrentElement(&map[gameInfo->hero.yCoordinate][gameInfo->hero.xCoordinate].types, HERO);
				//добавляем в ячейку выше символ героя
				list::addBegin(&map[gameInfo->hero.yCoordinate - 1][gameInfo->hero.xCoordinate].types, HERO);

				gameInfo->hero.yCoordinate = gameInfo->hero.yCoordinate - 1;

				game::drawFrame(map, gameInfo);	// отрисовавается кадр

				//удаляем символ героя из текущей ячейки
				list::deleteCurrentElement(&map[gameInfo->hero.yCoordinate][gameInfo->hero.xCoordinate].types, HERO);
				//добавляем в ячейку выше символ героя
				list::addBegin(&map[gameInfo->hero.yCoordinate - 1][gameInfo->hero.xCoordinate].types, HERO);

				gameInfo->hero.yCoordinate = gameInfo->hero.yCoordinate - 1;
			}

			else if ((map[gameInfo->hero.yCoordinate - 1][gameInfo->hero.xCoordinate].passable == true) && // Если свободна только одна
				(map[gameInfo->hero.yCoordinate - 2][gameInfo->hero.xCoordinate].passable == false))
			{
				//удаляем символ героя из текущей ячейки
				list::deleteCurrentElement(&map[gameInfo->hero.yCoordinate][gameInfo->hero.xCoordinate].types, HERO);
				//добавляем в ячейку выше символ героя
				list::addBegin(&map[gameInfo->hero.yCoordinate - 1][gameInfo->hero.xCoordinate].types, HERO);

				gameInfo->hero.yCoordinate = gameInfo->hero.yCoordinate - 1;
			}
		}
		break;

	case TURRET:
		if (map[gameInfo->turret.yCoordinate + 1][gameInfo->turret.xCoordinate].passable == false)	// если под персонажем есть непроходимый блок
		{
			//replaceTheAimMovement(gameInfo, map);

			// Если обе клетки над героем свободны
			if ((map[gameInfo->turret.yCoordinate - 1][gameInfo->turret.xCoordinate].passable == true) &&
				(map[gameInfo->turret.yCoordinate - 2][gameInfo->turret.xCoordinate].passable == true))
			{
				//удаляем символ героя из текущей ячейки
				list::deleteCurrentElement(&map[gameInfo->turret.yCoordinate][gameInfo->turret.xCoordinate].types, TURRET);
				//добавляем в ячейку выше символ героя
				list::addBegin(&map[gameInfo->turret.yCoordinate - 1][gameInfo->turret.xCoordinate].types, TURRET);

				gameInfo->turret.yCoordinate = gameInfo->turret.yCoordinate - 1;

				game::drawFrame(map, gameInfo);	// отрисовавается кадр

												//удаляем символ героя из текущей ячейки
				list::deleteCurrentElement(&map[gameInfo->turret.yCoordinate][gameInfo->turret.xCoordinate].types, TURRET);
				//добавляем в ячейку выше символ героя
				list::addBegin(&map[gameInfo->turret.yCoordinate - 1][gameInfo->turret.xCoordinate].types, TURRET);

				gameInfo->turret.yCoordinate = gameInfo->turret.yCoordinate - 1;
			}

			else if ((map[gameInfo->turret.yCoordinate - 1][gameInfo->turret.xCoordinate].passable == true) && // Если свободна только одна
				(map[gameInfo->turret.yCoordinate - 2][gameInfo->turret.xCoordinate].passable == false))
			{
				//удаляем символ героя из текущей ячейки
				list::deleteCurrentElement(&map[gameInfo->turret.yCoordinate][gameInfo->turret.xCoordinate].types, TURRET);
				//добавляем в ячейку выше символ героя
				list::addBegin(&map[gameInfo->turret.yCoordinate - 1][gameInfo->turret.xCoordinate].types, TURRET);

				gameInfo->turret.yCoordinate = gameInfo->turret.yCoordinate - 1;
			}
		}
		break;
	}
}

//// функция перемещения влево
// принимает символ персонажа или прицела, структуру с информацией об объекте на карте и двумерный массив структур
void game::moveLeft(char type, GameInfo* gameInfo, game::MapCell** map)
{
	switch (type)
	{

	case AIM_DOT:
		if (map[gameInfo->aim.yCoordinate][gameInfo->aim.xCoordinate - 1].passable == true)
		{
			// удаляем символ прицела из текущей ячейки карты
			list::deleteCurrentElement(&map[gameInfo->aim.yCoordinate][gameInfo->aim.xCoordinate].types, AIM_DOT);
			//добавляем в ячейку карты слева символ прицела
			list::addBegin(&map[gameInfo->aim.yCoordinate][gameInfo->aim.xCoordinate - 1].types, AIM_DOT);
			gameInfo->aim.xCoordinate = gameInfo->aim.xCoordinate - 1;
		}
		break;

	case HERO:
		if (map[gameInfo->hero.yCoordinate][gameInfo->hero.xCoordinate - 1].passable == true)
		{
			//удаляем символ героя из текущей ячейки карты
			list::deleteCurrentElement(&map[gameInfo->hero.yCoordinate][gameInfo->hero.xCoordinate].types, HERO);
			//добавляем в ячейку карты слева символ героя
			list::addBegin(&map[gameInfo->hero.yCoordinate][gameInfo->hero.xCoordinate - 1].types, HERO);
			gameInfo->hero.xCoordinate = gameInfo->hero.xCoordinate - 1;
		}
		break;

	case TURRET:
		if (map[gameInfo->turret.yCoordinate][gameInfo->turret.xCoordinate - 1].passable == true)
		{
			list::deleteCurrentElement(&map[gameInfo->turret.yCoordinate][gameInfo->turret.xCoordinate].types, TURRET);
			list::addBegin(&map[gameInfo->turret.yCoordinate][gameInfo->turret.xCoordinate - 1].types, TURRET);
			gameInfo->turret.xCoordinate = gameInfo->turret.xCoordinate - 1;
		}
		break;

	case BULLET:
		if (map[gameInfo->bullet.yCoordinate][gameInfo->bullet.xCoordinate - 1].passable == true)
		{
			list::addBegin(&map[gameInfo->bullet.yCoordinate][gameInfo->bullet.xCoordinate - 1].types, BULLET);
			list::deleteCurrentElement(&map[gameInfo->bullet.yCoordinate][gameInfo->bullet.xCoordinate].types, BULLET);
			gameInfo->bullet.xCoordinate = gameInfo->bullet.xCoordinate - 1;
		}
		break;
	}
}

// функция перемещения вниз
// принимает символ персонажа или прицела, структуру с информацией об объекте на карте и двумерный массив структур
void game::moveRight(char type, GameInfo* gameInfo, game::MapCell** map)
{

	switch (type)
	{
	case AIM_DOT:
		if (map[gameInfo->aim.yCoordinate][gameInfo->aim.xCoordinate + 1].passable == true)
		{
			//удаляем символ прицела из текущей ячейки карты
			list::deleteCurrentElement(&map[gameInfo->aim.yCoordinate][gameInfo->aim.xCoordinate].types, AIM_DOT);
			//добавляем в ячейку карты справа символ прицела
			list::addBegin(&map[gameInfo->aim.yCoordinate][gameInfo->aim.xCoordinate + 1].types, AIM_DOT);
			gameInfo->aim.xCoordinate = gameInfo->aim.xCoordinate + 1;
		}
		break;

	case HERO:
		if (map[gameInfo->hero.yCoordinate][gameInfo->hero.xCoordinate + 1].passable == true)
		{
			//удаляем символ героя из текущей ячейки карты
			list::deleteCurrentElement(&map[gameInfo->hero.yCoordinate][gameInfo->hero.xCoordinate].types, HERO);
			//добавляем в ячейку карты справа символ героя
			list::addBegin(&map[gameInfo->hero.yCoordinate][gameInfo->hero.xCoordinate + 1].types, HERO);
			gameInfo->hero.xCoordinate = gameInfo->hero.xCoordinate + 1;
		}
		break;

	case TURRET:
		if (map[gameInfo->turret.yCoordinate][gameInfo->turret.xCoordinate + 1].passable == true)
		{
			list::deleteCurrentElement(&map[gameInfo->turret.yCoordinate][gameInfo->turret.xCoordinate].types, TURRET);
			list::addBegin(&map[gameInfo->turret.yCoordinate][gameInfo->turret.xCoordinate + 1].types, TURRET);
			gameInfo->turret.xCoordinate = gameInfo->turret.xCoordinate + 1;
		}
		break;

	case BULLET:
		if (map[gameInfo->bullet.yCoordinate][gameInfo->bullet.xCoordinate + 1].passable == true)
		{
			list::addBegin(&map[gameInfo->bullet.yCoordinate][gameInfo->bullet.xCoordinate + 1].types, BULLET);
			list::deleteCurrentElement(&map[gameInfo->bullet.yCoordinate][gameInfo->bullet.xCoordinate].types, BULLET);
			gameInfo->bullet.xCoordinate = gameInfo->bullet.xCoordinate + 1;
		}
		break;
	}
}

// функция перемещения вниз
// структуру с информацией об объекте на карте и двумерный массив структур
void game::moveUp(GameInfo* gameInfo, game::MapCell** map)
{
	// если сверху ячека карты проходима и в ней не герой
	if (map[gameInfo->aim.yCoordinate - 1][gameInfo->aim.xCoordinate].passable == true)
	{
		//удаляем символ прицела из текущей ячейки карты
		list::deleteCurrentElement(&map[gameInfo->aim.yCoordinate][gameInfo->aim.xCoordinate].types, AIM_DOT);
		//добавляем в ячейку карты выше символ прицела
		list::addBegin(&map[gameInfo->aim.yCoordinate - 1][gameInfo->aim.xCoordinate].types, AIM_DOT);

		gameInfo->aim.yCoordinate = gameInfo->aim.yCoordinate - 1;
	}
}

// функция перемещения вниз
// принимает структуру с информацией об объекте на карте и двумерный массив структур
void game::moveDown(char type, GameInfo* gameInfo, game::MapCell** map)
{
	switch (type)
	{
	case AIM_DOT:
		// если снизу ячейка карты проходима и в ней не герой
		if (map[gameInfo->aim.yCoordinate + 1][gameInfo->aim.xCoordinate].passable == true)
		{
			//удаляем символ прицела из текущей ячейки карты
			list::deleteCurrentElement(&map[gameInfo->aim.yCoordinate][gameInfo->aim.xCoordinate].types, AIM_DOT);
			//добавляем в ячейку карты ниже символ прицела
			list::addBegin(&map[gameInfo->aim.yCoordinate + 1][gameInfo->aim.xCoordinate].types, AIM_DOT);

			gameInfo->aim.yCoordinate = gameInfo->aim.yCoordinate + 1;
		}
		break;

	case HERO:
		if (map[gameInfo->hero.yCoordinate + 1][gameInfo->hero.xCoordinate].passable == true)
		{
			//удаляем символ героя из текущей ячейки карты
			list::deleteCurrentElement(&map[gameInfo->hero.yCoordinate][gameInfo->hero.xCoordinate].types, HERO);
			//добавляем в ячейку карты ниже символ героя
			list::addBegin(&map[gameInfo->hero.yCoordinate + 1][gameInfo->hero.xCoordinate].types, HERO);

			gameInfo->hero.yCoordinate = gameInfo->hero.yCoordinate + 1;
		}
		break;

	case TURRET:
		if (map[gameInfo->turret.yCoordinate + 1][gameInfo->turret.xCoordinate].passable == true)
		{
			//удаляем символ турели из текущей ячейки карты
			list::deleteCurrentElement(&map[gameInfo->turret.yCoordinate][gameInfo->turret.xCoordinate].types, TURRET);
			//добавляем в ячейку карты ниже символ турели
			list::addBegin(&map[gameInfo->turret.yCoordinate + 1][gameInfo->turret.xCoordinate].types, TURRET);

			gameInfo->turret.yCoordinate = gameInfo->turret.yCoordinate + 1;
		}
		break;
	}
}

// функция переставляет прицел, при установке портала
// принимает структуру с информацией об объекте на карте и двумерный массив структур
void game::replaceTheAim(GameInfo* gameInfo, game::MapCell** map)
{
	// если ячека карты справа пуста
	if (map[gameInfo->aim.yCoordinate][gameInfo->aim.xCoordinate + 1].types->value == EMPTY_SPACE)
	{
		moveRight(AIM_DOT, gameInfo, map);	// прицел перемещаяется влево на одну ячейку карты
	}

	// если ячека карты слева пуста
	else if (map[gameInfo->aim.yCoordinate][gameInfo->aim.xCoordinate - 1].types->value == EMPTY_SPACE)
	{
		moveLeft(AIM_DOT, gameInfo, map);	// прицел перемещаяется вправо на одну ячейку карты
	}

	// если ячека карты сверху пуста
	else if (map[gameInfo->aim.yCoordinate - 1][gameInfo->aim.xCoordinate].types->value == EMPTY_SPACE)
	{
		moveUp(gameInfo, map);	// прицел перемещаяется вверх на одну ячейку карты
	}

	// если ячека карты снизу пуста
	else if (map[gameInfo->aim.yCoordinate + 1][gameInfo->aim.xCoordinate].types->value == EMPTY_SPACE)
	{
		moveDown(AIM_DOT, gameInfo, map);	// прицел перемещаяется вниз на одну ячейку карты
	}
}

//// функция переставляет прицел, если герой падает на прицел
//// принимает структуру с информацией об объекте на карте и двумерный массив структур
//void game::replaceTheAimMovement(GameInfo* gameInfo, game::MapCell** map)
//{
//	if (peek(map[gameInfo->hero.yCoordinate + 1][gameInfo->hero.xCoordinate].types) == AIM_DOT)
//	{
//		replaceTheAim(gameInfo, map);
//	}
//
//	else if (peek(map[gameInfo->hero.yCoordinate - 1][gameInfo->hero.xCoordinate].types) == AIM_DOT)
//	{
//		replaceTheAim(gameInfo, map);
//	}
//}
//
//------Gravitation_Functions------//
// функция гравитации, принимает структуру с информацией об объекте на карте и двумерный массив структур
//void game::gravity(game::MapCell** map, GameInfo* gameInfo)
//{
//	// если под персонажем нет непроходимого блока/объекта
//	if (map[gameInfo->hero.yCoordinate][gameInfo->hero.xCoordinate].types->value == HERO &&
//		map[gameInfo->hero.yCoordinate + 1][gameInfo->hero.xCoordinate].passable == true)
//	{
//		//replaceTheAimMovement(gameInfo, map);
//		Sleep(50);
//		// перемещение героя вниз на одну ячейку карты
//		list::addBegin(&map[gameInfo->hero.yCoordinate + 1][gameInfo->hero.xCoordinate].types, HERO);
//		list::deleteCurrentElement(&map[gameInfo->hero.yCoordinate][gameInfo->hero.xCoordinate].types, HERO);
//
//		gameInfo->hero.yCoordinate = gameInfo->hero.yCoordinate + 1;
//	}
//
//	if (map[gameInfo->turret.yCoordinate][gameInfo->turret.xCoordinate].types->value == TURRET &&
//		map[gameInfo->turret.yCoordinate + 1][gameInfo->turret.xCoordinate].passable == true)
//	{
//		Sleep(50);
//		// перемещение турели вниз на одну ячейку карты
//		list::addBegin(&map[gameInfo->turret.yCoordinate + 1][gameInfo->turret.xCoordinate].types, TURRET);
//		list::deleteCurrentElement(&map[gameInfo->turret.yCoordinate][gameInfo->turret.xCoordinate].types, TURRET);
//
//		gameInfo->turret.yCoordinate = gameInfo->turret.yCoordinate + 1;
//	}
//}

void game::gravity(game::MapCell** map, GameInfo* gameInfo)
{
	// если под персонажем нет непроходимого блока/объекта
	if (map[gameInfo->hero.yCoordinate][gameInfo->hero.xCoordinate].types->value == HERO &&
		map[gameInfo->hero.yCoordinate + 1][gameInfo->hero.xCoordinate].passable == true)
	{
		//replaceTheAimMovement(gameInfo, map);
		Sleep(50);
		// перемещение героя вниз на одну ячейку карты
		moveDown(HERO, gameInfo, map);
	}

	if (map[gameInfo->turret.yCoordinate][gameInfo->turret.xCoordinate].types->value == TURRET &&
		map[gameInfo->turret.yCoordinate + 1][gameInfo->turret.xCoordinate].passable == true)
	{
		Sleep(50);
		// перемещение турели вниз на одну ячейку карты
		moveDown(TURRET, gameInfo, map);
	}
}

// функция запуска уровня, принимает на вход название файла с уровнем
// возвращает количество очков, набранное игроком
records::DataAboutTheChampion* game::startLevel(char* levelName)
{
	game::GameInfo* gameInfo = new GameInfo;

	game::MapCell** map = game::createMap(levelName, gameInfo); // Создаем двумерный массив структур, используя текстовый документ

	records::DataAboutTheChampion* player = new records::DataAboutTheChampion;

	game::clearScreen(); // Чистим экран

	game::drawFrame(map, gameInfo); // Рисуем первый кадр

	game::performAnAction(gameInfo, map); // Выполняем далее в зависимости от действий игрока

	system("cls");

	std::cout << "Please enter your name" << std::endl;

	std::cin >> player->name;

	player->score = gameInfo->hero.score;

	player->level = atoi(&levelName[4]);

	double score = gameInfo->hero.score;

	std::cout << "\n\n\t\t\tSCORE: " << score << std::endl;
	std::cout << "\t\t\tTIME: " << gameInfo->hero.time << std::endl;
	std::cout << "\n\n\t\t\tPRESS ANY KEY TO CONTINUE" << std::endl;

	_getch();

	game::freeMemory(map, gameInfo); // Очищаем занятую память

	game::clearScreen(); // Чистим экран

	return player;
}

//-----Portals_Functions------//
// функция установки второго портала
// принимает на вход символ портала, структуру с информацией об объекте на карте и двумерный массив структур
void game::setPortal(char type, GameInfo* gameInfo, game::MapCell** map)
{
	if (type == RED_PORTAL)	// если устанавливется красный портал
	{
		if ((gameInfo->aim.xCoordinate != gameInfo->bluePortal.xCoordinate) ||
			(gameInfo->aim.yCoordinate != gameInfo->bluePortal.yCoordinate))
		{
			if (gameInfo->redPortal.yCoordinate != 0)	// если красный портал уже есть, то существующий красный портал исчезает
				list::deleteCurrentElement(&map[gameInfo->redPortal.yCoordinate][gameInfo->redPortal.xCoordinate].types, RED_PORTAL);

			gameInfo->redPortal.xCoordinate = gameInfo->aim.xCoordinate; // координаты нового портала приравниваются координатам прицела
			gameInfo->redPortal.yCoordinate = gameInfo->aim.yCoordinate;

			list::addBegin(&map[gameInfo->aim.yCoordinate][gameInfo->aim.xCoordinate].types, RED_PORTAL);
			//replaceTheAim(gameInfo, map);	// прицел смещается с портала
		}
	}

	else if (type == BLUE_PORTAL) // если устанавливется синий портал
	{
		if ((gameInfo->aim.xCoordinate != gameInfo->bluePortal.xCoordinate) ||
			(gameInfo->aim.yCoordinate != gameInfo->bluePortal.yCoordinate))
		{
			if (gameInfo->bluePortal.yCoordinate != 0)	// если синий портал уже есть, то существующий синий портал исчезает
				list::deleteCurrentElement(&map[gameInfo->bluePortal.yCoordinate][gameInfo->bluePortal.xCoordinate].types, BLUE_PORTAL);

			gameInfo->bluePortal.xCoordinate = gameInfo->aim.xCoordinate;	// координаты нового портала приравниваются координатам прицела
			gameInfo->bluePortal.yCoordinate = gameInfo->aim.yCoordinate;

			list::addBegin(&map[gameInfo->aim.yCoordinate][gameInfo->aim.xCoordinate].types, BLUE_PORTAL);
			//replaceTheAim(gameInfo, map);	// прицел смещается с портала
		}
	}
}

// функция перехода по порталам, принимает структуру с информацией об объекте на карте и двумерный массив структур
void game::enterThePortal(char type, GameInfo* gameInfo, MapCell** map)
{
	if (gameInfo->hero.xCoordinate == gameInfo->redPortal.xCoordinate &&	// если персонаж и красный портал в одной клетке
		gameInfo->hero.yCoordinate == gameInfo->redPortal.yCoordinate &&
		gameInfo->bluePortal.yCoordinate != 0 && gameInfo->bluePortal.xCoordinate != 0) // и второй портал существует
	{
		list::addBegin(&map[gameInfo->bluePortal.yCoordinate][gameInfo->bluePortal.xCoordinate].types, HERO);
		list::deleteCurrentElement(&map[gameInfo->hero.yCoordinate][gameInfo->hero.xCoordinate].types, HERO);

		gameInfo->hero.xCoordinate = gameInfo->bluePortal.xCoordinate;
		gameInfo->hero.yCoordinate = gameInfo->bluePortal.yCoordinate;
	}
	else if (gameInfo->hero.xCoordinate == gameInfo->bluePortal.xCoordinate && // если персонаж и синий портал в одной клетке
		gameInfo->hero.yCoordinate == gameInfo->bluePortal.yCoordinate &&
		gameInfo->redPortal.yCoordinate != 0 && gameInfo->redPortal.xCoordinate != 0)	// и второй портал существует
	{
		list::addBegin(&map[gameInfo->redPortal.yCoordinate][gameInfo->redPortal.xCoordinate].types, HERO);
		list::deleteCurrentElement(&map[gameInfo->hero.yCoordinate][gameInfo->hero.xCoordinate].types, HERO);	// герой перемещается по координатам второго портала
		gameInfo->hero.xCoordinate = gameInfo->redPortal.xCoordinate;
		gameInfo->hero.yCoordinate = gameInfo->redPortal.yCoordinate;
	}
}

//------Button_Functions------//
// функция активации клавиши, принимает структуру с информацией об объекте на карте и двумерный массив структур
void game::activateTheButton(GameInfo* gameInfo, MapCell** map)
{
	if (gameInfo->hero.xCoordinate == gameInfo->button.xCoordinate &&	// если персонаж и кнопка находятся в одной клетке
		gameInfo->hero.yCoordinate == gameInfo->button.yCoordinate)
	{
		map[gameInfo->blackWall.yCoordinate][gameInfo->blackWall.xCoordinate].passable = true;// непроходимая стена становится проходимой
		list::deleteCurrentElement(&map[gameInfo->blackWall.yCoordinate][gameInfo->blackWall.xCoordinate].types, BLACK_WALL);	// на месте непроходимой стены отображается проходимая
	}
}

bool game::checkGameOverConditions(GameInfo* gameInfo, MapCell** map)
{
	if ((gameInfo->hero.xCoordinate == gameInfo->exitFromLevel.xCoordinate &&	// если персонаж находится в одной клетке с выходом
		gameInfo->hero.yCoordinate == gameInfo->exitFromLevel.yCoordinate) ||
		(gameInfo->hero.healthPoints <= 0))
	{
		return false;
	}
	else
	{
		return true;
	}
}