#include "Gameplay.h"
#include "Map.h"
#include "Instruments.h"
#include "Structures.h"
#include "List.h"
#include "TurretAI.h"

// функция паузы
double game::pause(GameInfo* gameInfo, MapCell** map)
{
	double startTime = clock();
	std::cout << "\n\n\n\n\n\n\n\n\t       Pause\n\n\t   Press any key" << std::endl;
	_getch();
	system("cls");
	double endTime = clock();
	return endTime - startTime;
}

//------Moving_Functions------//
// принимает структуру с информацией об объекте на карте и двумерный массив структур
void game::performAnAction(GameInfo* gameInfo, MapCell** map)
{
	bool gameIsRunning = true;	// условие выполнение цикла
	bool isMovingRight = true;  // переменная для патрулирующей турели (отвечает за направление движения)
	double timeBeforeGame = clock(); // переменная для отображения времени, затраченного на прохождение уровня
	double timeOnPause = 0.0; // переменная для хранения времени на паузе
	while (gameIsRunning)
	{
		if (_kbhit()) // Если нажата клавиша
		{
			switch (_getch()) // Читаем клавишу
			{
			case 'p':
				timeOnPause += pause(gameInfo, map);
				break;

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

		//game::turretAI(gameInfo, map);
		// Запускает ИИ патрулирующей турели
		game::turretPatrolAI(gameInfo, map, &isMovingRight);
		// Проверяет условия конца игры (кончилось ли здоровье, нашел ли игрок выход)
		gameIsRunning = checkGameOverConditions(gameInfo, map);

		game::clearScreen(); // Очищаем экран
		game::drawFrame(map, gameInfo); // Отрисовываем кадр
		game::gravity(map, gameInfo); // Имитируем гравитацию
		game::clearScreen(); // Очищаем экран

		// Переменная необходимая для отображения времени, затраченного на прохождение уровня
		double timeAfterAction = clock() - timeOnPause;

		// Вносим информация о затраченном на прохождение уровня времени (в секундах)
		gameInfo->hero.time = (timeAfterAction - timeBeforeGame) / 1000.0;

		if (gameInfo->hero.score > 0)	// если количество очков больше 0, то вычетается одно очко
		{
			gameInfo->hero.score -= 1.02354;
		}
	}

	/*double timeAfterGame = clock();
	double requiredTime = (timeAfterGame - timeBeforeGame) / 1000.0;*/
}

//------Moving_Functions------//
// принимает структуру с информацией об объекте на карте и двумерный массив структур
void game::jump(char type, GameInfo* gameInfo, game::MapCell** map)
{
	switch (type)
	{
	case HERO:
		// если под персонажем есть непроходимый блок
		if (map[gameInfo->hero.yCoordinate + 1][gameInfo->hero.xCoordinate].passable == false)
		{
			// Если обе клетки над героем проходимы
			if ((map[gameInfo->hero.yCoordinate - 1][gameInfo->hero.xCoordinate].passable == true) &&
				(map[gameInfo->hero.yCoordinate - 2][gameInfo->hero.xCoordinate].passable == true))
			{
				//удаляем символ героя из текущей ячейки
				list::deleteCurrentElement(&map[gameInfo->hero.yCoordinate][gameInfo->hero.xCoordinate].types, HERO);
				//добавляем в ячейку выше символ героя
				list::addBegin(&map[gameInfo->hero.yCoordinate - 1][gameInfo->hero.xCoordinate].types, HERO);

				// координата героя по оси Оу уменьшается на один
				gameInfo->hero.yCoordinate = gameInfo->hero.yCoordinate - 1;

				game::drawFrame(map, gameInfo);	// отрисовавается кадр

				//удаляем символ героя из текущей ячейки
				list::deleteCurrentElement(&map[gameInfo->hero.yCoordinate][gameInfo->hero.xCoordinate].types, HERO);
				//добавляем в ячейку выше символ героя
				list::addBegin(&map[gameInfo->hero.yCoordinate - 1][gameInfo->hero.xCoordinate].types, HERO);
				// координата героя по оси Оу уменьшается на один
				gameInfo->hero.yCoordinate = gameInfo->hero.yCoordinate - 1;
			}
			// Если проходима только одна клетка
			else if ((map[gameInfo->hero.yCoordinate - 1][gameInfo->hero.xCoordinate].passable == true) &&
				(map[gameInfo->hero.yCoordinate - 2][gameInfo->hero.xCoordinate].passable == false))
			{
				//удаляем символ героя из текущей ячейки
				list::deleteCurrentElement(&map[gameInfo->hero.yCoordinate][gameInfo->hero.xCoordinate].types, HERO);
				//добавляем в ячейку выше символ героя
				list::addBegin(&map[gameInfo->hero.yCoordinate - 1][gameInfo->hero.xCoordinate].types, HERO);
				// координата героя по оси Оу уменьшается на один
				gameInfo->hero.yCoordinate = gameInfo->hero.yCoordinate - 1;
			}

		}
		break;

	case TURRET:
		// если под турелью есть непроходимый блок
		if (map[gameInfo->turret.yCoordinate + 1][gameInfo->turret.xCoordinate].passable == false)
		{
			// Если обе клетки над турелью проходимы
			if ((map[gameInfo->turret.yCoordinate - 1][gameInfo->turret.xCoordinate].passable == true) &&
				(map[gameInfo->turret.yCoordinate - 2][gameInfo->turret.xCoordinate].passable == true))
			{
				//удаляем символ турели из текущей ячейки
				list::deleteCurrentElement(&map[gameInfo->turret.yCoordinate][gameInfo->turret.xCoordinate].types, TURRET);
				//добавляем в ячейку выше символ турели
				list::addBegin(&map[gameInfo->turret.yCoordinate - 1][gameInfo->turret.xCoordinate].types, TURRET);

				// координата турели по оси Оу уменьшается на один
				gameInfo->turret.yCoordinate = gameInfo->turret.yCoordinate - 1;

				game::drawFrame(map, gameInfo);	// отрисовавается кадр

				//удаляем символ турели из текущей ячейки
				list::deleteCurrentElement(&map[gameInfo->turret.yCoordinate][gameInfo->turret.xCoordinate].types, TURRET);
				//добавляем в ячейку выше символ турели
				list::addBegin(&map[gameInfo->turret.yCoordinate - 1][gameInfo->turret.xCoordinate].types, TURRET);
				// координата турели по оси Оу уменьшается на один
				gameInfo->turret.yCoordinate = gameInfo->turret.yCoordinate - 1;
			}
			// если проходима только одна клетка
			else if ((map[gameInfo->turret.yCoordinate - 1][gameInfo->turret.xCoordinate].passable == true) &&
				(map[gameInfo->turret.yCoordinate - 2][gameInfo->turret.xCoordinate].passable == false))
			{
				//удаляем символ турели из текущей ячейки
				list::deleteCurrentElement(&map[gameInfo->turret.yCoordinate][gameInfo->turret.xCoordinate].types, TURRET);
				//добавляем в ячейку выше символ турели
				list::addBegin(&map[gameInfo->turret.yCoordinate - 1][gameInfo->turret.xCoordinate].types, TURRET);
				// координата турели по оси Оу уменьшается на один
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
		// если слева от турели прохоидмое пространство
		if (map[gameInfo->turret.yCoordinate][gameInfo->turret.xCoordinate - 1].passable == true)
		{
			// из текущей ячейки удаляется символ турели
			list::deleteCurrentElement(&map[gameInfo->turret.yCoordinate][gameInfo->turret.xCoordinate].types, TURRET);
			// в ячейку слева добавляется символ турели
			list::addBegin(&map[gameInfo->turret.yCoordinate][gameInfo->turret.xCoordinate - 1].types, TURRET);
			gameInfo->turret.xCoordinate = gameInfo->turret.xCoordinate - 1;
		}
		break;

	case PLATFORM_TURRET:
		// если слева от турели прохоидмое пространство
		if (map[gameInfo->platform_turret.yCoordinate][gameInfo->platform_turret.xCoordinate - 1].passable == true)
		{
			// из текущей ячейки удаляется символ турели
			list::deleteCurrentElement(&map[gameInfo->platform_turret.yCoordinate][gameInfo->platform_turret.xCoordinate].types, PLATFORM_TURRET);
			// в ячейку слева добавляется символ турели
			list::addBegin(&map[gameInfo->platform_turret.yCoordinate][gameInfo->platform_turret.xCoordinate - 1].types, PLATFORM_TURRET);
			gameInfo->platform_turret.xCoordinate = gameInfo->platform_turret.xCoordinate - 1;
		}
		break;

	case BULLET:
		// если слева от пули прохоидмое пространство
		if (map[gameInfo->bullet.yCoordinate][gameInfo->bullet.xCoordinate - 1].passable == true)
		{
			// в ячейку слева добавляется символ турели
			list::addBegin(&map[gameInfo->bullet.yCoordinate][gameInfo->bullet.xCoordinate - 1].types, BULLET);
			// из текущей ячейки удаляется символ турели
			list::deleteCurrentElement(&map[gameInfo->bullet.yCoordinate][gameInfo->bullet.xCoordinate].types, BULLET);
			gameInfo->bullet.xCoordinate = gameInfo->bullet.xCoordinate - 1;
		}
		break;
	}
}

// функция перемещения вправо
// использует информацию обо всех объектах на карте, символ, подаваемый на вход отвечает за то, какой именно символ нужно переместить
void game::moveRight(char type, GameInfo* gameInfo, game::MapCell** map)
{
	switch (type)
	{
	case AIM_DOT:
		// если справа от прицела проходимое пространство
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
		// если справа от героя проходимое пространство
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
		// если справа от турели проходимое пространство
		if (map[gameInfo->turret.yCoordinate][gameInfo->turret.xCoordinate + 1].passable == true)
		{
			// удаляется символ турели из текущей ячеки
			list::deleteCurrentElement(&map[gameInfo->turret.yCoordinate][gameInfo->turret.xCoordinate].types, TURRET);
			// добавляется в ячейку карты справа символ турели
			list::addBegin(&map[gameInfo->turret.yCoordinate][gameInfo->turret.xCoordinate + 1].types, TURRET);
			gameInfo->turret.xCoordinate = gameInfo->turret.xCoordinate + 1;
		}
		break;

	case PLATFORM_TURRET:
		// если справа от турели проходимое пространство
		if (map[gameInfo->platform_turret.yCoordinate][gameInfo->platform_turret.xCoordinate + 1].passable == true)
		{
			// удаляется символ турели из текущей ячейки
			list::deleteCurrentElement(&map[gameInfo->platform_turret.yCoordinate][gameInfo->platform_turret.xCoordinate].types, PLATFORM_TURRET);
			// добавляется в ячейку карты справа символ турели
			list::addBegin(&map[gameInfo->platform_turret.yCoordinate][gameInfo->platform_turret.xCoordinate + 1].types, PLATFORM_TURRET);
			gameInfo->platform_turret.xCoordinate = gameInfo->platform_turret.xCoordinate + 1;
		}
		break;

	case BULLET:
		// если справа от пули проходимое пространство
		if (map[gameInfo->bullet.yCoordinate][gameInfo->bullet.xCoordinate + 1].passable == true)
		{
			// добавляется в ячейку карты справа символ турели
			list::addBegin(&map[gameInfo->bullet.yCoordinate][gameInfo->bullet.xCoordinate + 1].types, BULLET);
			// удаляется символ турели из текущей ячейки карты
			list::deleteCurrentElement(&map[gameInfo->bullet.yCoordinate][gameInfo->bullet.xCoordinate].types, BULLET);
			gameInfo->bullet.xCoordinate = gameInfo->bullet.xCoordinate + 1;
		}
		break;
	}
}

// функция перемещения вверх
// использует информацию обо всех объектах на карте, символ, подаваемый на вход отвечает за то, какой именно символ нужно переместить
void game::moveUp(GameInfo* gameInfo, game::MapCell** map)
{
	// если сверху ячека карты проходима
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
// использует информацию обо всех объектах на карте, символ, подаваемый на вход отвечает за то, какой именно символ нужно переместить
void game::moveDown(char type, GameInfo* gameInfo, game::MapCell** map)
{
	switch (type)
	{
	case AIM_DOT:
		// если ячейка карты ниже героя проходима
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
		// если ячейка карты ниже героя проходима
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
		// если ячейка карты ниже турели проходима
		if (map[gameInfo->turret.yCoordinate + 1][gameInfo->turret.xCoordinate].passable == true)
		{
			//удаляем символ турели из текущей ячейки карты
			list::deleteCurrentElement(&map[gameInfo->turret.yCoordinate][gameInfo->turret.xCoordinate].types, TURRET);
			//добавляем в ячейку карты ниже символ турели
			list::addBegin(&map[gameInfo->turret.yCoordinate + 1][gameInfo->turret.xCoordinate].types, TURRET);

			gameInfo->turret.yCoordinate = gameInfo->turret.yCoordinate + 1;
		}
		break;

	case PLATFORM_TURRET:
		// если ячейка карты ниже турели проходима
		if (map[gameInfo->platform_turret.yCoordinate + 1][gameInfo->platform_turret.xCoordinate].passable == true)
		{
			//удаляем символ турели из текущей ячейки карты
			list::deleteCurrentElement(&map[gameInfo->platform_turret.yCoordinate][gameInfo->platform_turret.xCoordinate].types, PLATFORM_TURRET);
			//добавляем в ячейку карты ниже символ турели
			list::addBegin(&map[gameInfo->platform_turret.yCoordinate + 1][gameInfo->platform_turret.xCoordinate].types, PLATFORM_TURRET);

			gameInfo->platform_turret.yCoordinate = gameInfo->platform_turret.yCoordinate + 1;
		}
		break;
	}
}

//// функция переставляет прицел, при установке портала
//// принимает структуру с информацией об объекте на карте и двумерный массив структур
//void game::replaceTheAim(GameInfo* gameInfo, game::MapCell** map)
//{
//	// если ячека карты справа пуста
//	if (map[gameInfo->aim.yCoordinate][gameInfo->aim.xCoordinate + 1].types->value == EMPTY_SPACE)
//	{
//		moveRight(AIM_DOT, gameInfo, map);	// прицел перемещаяется влево на одну ячейку карты
//	}
//
//	// если ячека карты слева пуста
//	else if (map[gameInfo->aim.yCoordinate][gameInfo->aim.xCoordinate - 1].types->value == EMPTY_SPACE)
//	{
//		moveLeft(AIM_DOT, gameInfo, map);	// прицел перемещаяется вправо на одну ячейку карты
//	}
//
//	// если ячека карты сверху пуста
//	else if (map[gameInfo->aim.yCoordinate - 1][gameInfo->aim.xCoordinate].types->value == EMPTY_SPACE)
//	{
//		moveUp(gameInfo, map);	// прицел перемещаяется вверх на одну ячейку карты
//	}
//
//	// если ячека карты снизу пуста
//	else if (map[gameInfo->aim.yCoordinate + 1][gameInfo->aim.xCoordinate].types->value == EMPTY_SPACE)
//	{
//		moveDown(AIM_DOT, gameInfo, map);	// прицел перемещаяется вниз на одну ячейку карты
//	}
//}

void game::gravity(game::MapCell** map, GameInfo* gameInfo)
{
	// если в ячейке карты ниже героя проходимое пространство
	if (map[gameInfo->hero.yCoordinate][gameInfo->hero.xCoordinate].types->value == HERO &&
		map[gameInfo->hero.yCoordinate + 1][gameInfo->hero.xCoordinate].passable == true)
	{
		// перемещение героя вниз на одну ячейку карты
		moveDown(HERO, gameInfo, map);
	}
	// если в ячейке карты ниже турели проходимое пространство
	if (map[gameInfo->turret.yCoordinate][gameInfo->turret.xCoordinate].types->value == TURRET &&
		map[gameInfo->turret.yCoordinate + 1][gameInfo->turret.xCoordinate].passable == true)
	{
		// перемещение турели вниз на одну ячейку карты
		moveDown(TURRET, gameInfo, map);
	}
	// если в ячейке карты ниже турели проходимое пространство
	if (map[gameInfo->platform_turret.yCoordinate][gameInfo->platform_turret.xCoordinate].types->value == PLATFORM_TURRET &&
		map[gameInfo->platform_turret.yCoordinate + 1][gameInfo->platform_turret.xCoordinate].passable == true)
	{
		// перемещение турели вниз на одну ячейку карты
		moveDown(PLATFORM_TURRET, gameInfo, map);
	}
}

// функция запуска уровня, отвчает за работу всей игры, принимает на вход название файла с уровнем
// возвращает структуру с данными о уровне, количестве очков и времени, затраченном на прохождение
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

	player->level = atoi(&levelName[4]); // Номер уровня находится в названии на пятом месте

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
		// если красный портал существует
		if (gameInfo->redPortal.yCoordinate != 0)
			// удаляется символ существующего красного портала
			list::deleteCurrentElement(&map[gameInfo->redPortal.yCoordinate][gameInfo->redPortal.xCoordinate].types, RED_PORTAL);
		// координаты нового портала приравниваются координатам прицела
		gameInfo->redPortal.xCoordinate = gameInfo->aim.xCoordinate;
		gameInfo->redPortal.yCoordinate = gameInfo->aim.yCoordinate;

		// в ячейку карты, в которой находится прицел, добавляется символ красного портала
		list::addBegin(&map[gameInfo->aim.yCoordinate][gameInfo->aim.xCoordinate].types, RED_PORTAL);
	}

	else if (type == BLUE_PORTAL) // если устанавливется синий портал
	{
		// если синий портал уже существует
		if (gameInfo->bluePortal.yCoordinate != 0)
			// удаляется символ существующего красного портала
			list::deleteCurrentElement(&map[gameInfo->bluePortal.yCoordinate][gameInfo->bluePortal.xCoordinate].types, BLUE_PORTAL);
		// координаты нового портала приравниваются координатам прицела
		gameInfo->bluePortal.xCoordinate = gameInfo->aim.xCoordinate;
		gameInfo->bluePortal.yCoordinate = gameInfo->aim.yCoordinate;
		// в ячейку карты, в которой находится прицел, добавляется символ синего портала
		list::addBegin(&map[gameInfo->aim.yCoordinate][gameInfo->aim.xCoordinate].types, BLUE_PORTAL);
	}
}

// функция перехода по порталам, принимает структуру с информацией об объекте на карте и двумерный массив структур
void game::enterThePortal(char type, GameInfo* gameInfo, MapCell** map)
{
	// если персонаж и красный портал в одной клетке карты и существует синий портал
	if (gameInfo->hero.xCoordinate == gameInfo->redPortal.xCoordinate &&
		gameInfo->hero.yCoordinate == gameInfo->redPortal.yCoordinate &&
		gameInfo->bluePortal.yCoordinate != 0 && gameInfo->bluePortal.xCoordinate != 0)
	{
		// в ячейку карты по координатам синего портала добавляется символ героя
		list::addBegin(&map[gameInfo->bluePortal.yCoordinate][gameInfo->bluePortal.xCoordinate].types, HERO);
		// из ячейки карты по текущим координатам героя удаляется символ героя
		list::deleteCurrentElement(&map[gameInfo->hero.yCoordinate][gameInfo->hero.xCoordinate].types, HERO);
		// координаты героя приравниваются к координатам синего портала
		gameInfo->hero.xCoordinate = gameInfo->bluePortal.xCoordinate;
		gameInfo->hero.yCoordinate = gameInfo->bluePortal.yCoordinate;
	}
	// если персонаж и синий портал в одной клетке карты и существует красный портал
	else if (gameInfo->hero.xCoordinate == gameInfo->bluePortal.xCoordinate &&
		gameInfo->hero.yCoordinate == gameInfo->bluePortal.yCoordinate &&
		gameInfo->redPortal.yCoordinate != 0 && gameInfo->redPortal.xCoordinate != 0)
	{
		// в ячейку карты по координатам красного портала добавляется символ героя
		list::addBegin(&map[gameInfo->redPortal.yCoordinate][gameInfo->redPortal.xCoordinate].types, HERO);
		// из ячейки карты по текущим координатам героя удаляется символ героя
		list::deleteCurrentElement(&map[gameInfo->hero.yCoordinate][gameInfo->hero.xCoordinate].types, HERO);
		// координаты героя приравниваются к координатам синего портала
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
		// ячейка карты, в которой была непроходимая стена, становится проходимой
		map[gameInfo->blackWall.yCoordinate][gameInfo->blackWall.xCoordinate].passable = true;
		// на месте непроходимой стены отображается проходимая
		list::deleteCurrentElement(&map[gameInfo->blackWall.yCoordinate][gameInfo->blackWall.xCoordinate].types, BLACK_WALL);
	}
}

// Функция проверяет, наступило ли событие, при котором игра должна закончиться
bool game::checkGameOverConditions(GameInfo* gameInfo, MapCell** map)
{
	if ((gameInfo->hero.xCoordinate == gameInfo->exitFromLevel.xCoordinate &&	// если персонаж находится в одной клетке с выходом
		gameInfo->hero.yCoordinate == gameInfo->exitFromLevel.yCoordinate))
	{
		return false;
	}
	else if (gameInfo->hero.healthPoints <= 0) // если здоровье игрока ниже или равно 0
	{
		return false;
	}
	else
	{
		return true;
	}
}