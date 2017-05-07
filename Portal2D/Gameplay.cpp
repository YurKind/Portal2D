#include "Gameplay.h"
#include "Map.h"
#include "Instruments.h"
#include "Structures.h"
#include "List.h"
#include "TurretsAI.h"

namespace game
{
	//------Moving_Functions------//
	// принимает структуру с информацией об объекте на карте и двумерный массив структур
	void performAnAction(GameInfo* gameInfo, MapCell** map)
	{
		bool gameIsRunning = true;	// условие выполнение цикла
		bool isMovingRight = true;  // переменная для патрулирующей турели (отвечает за направление движения)
		double timeBeforeGame = clock(); // переменная для отображения времени, затраченного на прохождение уровня
		double timeOnPause = 0.0;	// переменная для хранения времени на паузе
		int sideOfMovingOx = 0;		// переменная для хранения направления движения и количество шагов по оси Ох
		int sideOfMovingOy = 0;		// переменная для хранения направления движения и количество шагов по оси Оу

		while (gameIsRunning == true)
		{
			if (_kbhit()) // Если нажата клавиша
			{
				switch (_getch()) // Читаем клавишу
				{
				case A_LOWER_CASE: case A_LOWER_CASE_RU: case A_UPPER_CASE: case A_UPPER_CASE_RU:
					sideOfMovingOx = -1;
					moveOx(sideOfMovingOx, HERO, gameInfo, map);
					break;

				case D_LOWER_CASE: case D_LOWER_CASE_RU: case D_UPPER_CASE: case D_UPPER_CASE_RU:
					sideOfMovingOx = 1;
					moveOx(sideOfMovingOx, HERO, gameInfo, map);
					break;

				case LEFT_ARROW:
					sideOfMovingOx = -1;
					moveOx(sideOfMovingOx, AIM_DOT, gameInfo, map);
					break;

				case RIGHT_ARROW:
					sideOfMovingOx = 1;
					moveOx(sideOfMovingOx, AIM_DOT, gameInfo, map);
					break;

				case UP_ARROW:
					sideOfMovingOy = -1;
					moveOy(sideOfMovingOy, AIM_DOT, gameInfo, map);
					break;

				case DOWN_ARROW:
					sideOfMovingOy = 1;
					moveOy(sideOfMovingOy, AIM_DOT, gameInfo, map);
					break;

				case SPACE_JUMP:
					jump(HERO, gameInfo, map);
					break;

				case E_LOWER_CASE: case E_LOWER_CASE_RU: case E_UPPER_CASE: case E_UPPER_CASE_RU:
					setPortal(BLUE_PORTAL, gameInfo, map);
					break;

				case Q_LOWER_CASE: case Q_LOWER_CASE_RU: case Q_UPPER_CASE: case Q_UPPER_CASE_RU:
					setPortal(RED_PORTAL, gameInfo, map);
					break;

				case ENTER:
					enterThePortal(HERO, gameInfo, map);
					activateTheButton(gameInfo, map);
					break;

				case PAUSE_LOWER_CASE: case PAUSE_LOWER_CASE_RU: // тут что-то не так
					timeOnPause += pause(gameInfo, map);
					break;

				case BACKSPACE:
					gameIsRunning = quitTheLevel(gameInfo, map);
					break;

				default:
					break;
				}
			}

			// Запускает ИИ стационарной турели
			turretAI(STATIONARY_TURRET, gameInfo, map);

			// Запускает ИИ патрулирующей турели
			turretAI(PLATFORM_TURRET, gameInfo, map);

			// Запускает ИИ турели охотника
			turretAI(TURRET_HUNTER, gameInfo, map);

			// Проверяет условия конца игры (кончилось ли здоровье, нашел ли игрок выход)
			gameIsRunning = checkGameOverConditions(gameInfo, map, gameIsRunning);

			clearScreen(); // Очищаем экран
			drawFrame(map, gameInfo); // Отрисовываем кадр
			gravity(map, gameInfo); // Имитируем гравитацию
			clearScreen(); // Очищаем экран

								 // Переменная необходимая для отображения времени, затраченного на прохождение уровня
			double timeAfterAction = clock() - timeOnPause;

			// Вносим информация о затраченном на прохождение уровня времени (в секундах)
			gameInfo->hero.time = (timeAfterAction - timeBeforeGame) / 1000.0;

			if (gameInfo->hero.score > 0)	// если количество очков больше 0, то вычетается одно очко
			{
				gameInfo->hero.score -= 1.02354;
			}
		}
	}

	//------Moving_Functions------//
	// принимает структуру с информацией об объекте на карте и двумерный массив структур
	void jump(char type, GameInfo* gameInfo, MapCell** map)
	{
		// если под персонажем есть непроходимый блок
		if (objectIsStandingOnTheFloor(getCoordinates(gameInfo, type), map))
		{
			// Если обе клетки над объектом проходимы
			if (bothCellsAboveTheObjectAreFree(getCoordinates(gameInfo, type), map))
			{
				//удаляем символ героя из текущей ячейки
				list::deleteCurrentElement(&map[getCoordinates(gameInfo, type).yCoordinate][getCoordinates(gameInfo, type).xCoordinate].types, type);
				//добавляем в ячейку выше символ героя
				list::addBegin(&map[getCoordinates(gameInfo, type).yCoordinate - 1][getCoordinates(gameInfo, type).xCoordinate].types, type);

				// координата героя по оси Оу уменьшается на один
				setOYCoordinates(gameInfo, type, -1); // TODO: -1 расхардкодить

				drawFrame(map, gameInfo);	// отрисовавается кадр

												//удаляем символ героя из текущей ячейки
				list::deleteCurrentElement(&map[getCoordinates(gameInfo, type).yCoordinate][getCoordinates(gameInfo, type).xCoordinate].types, type);
				//добавляем в ячейку выше символ героя
				list::addBegin(&map[getCoordinates(gameInfo, type).yCoordinate - 1][getCoordinates(gameInfo, type).xCoordinate].types, type);
				// координата героя по оси Оу уменьшается на один
				setOYCoordinates(gameInfo, type, -1); // TODO: -1 расхардкодить
			}
			// Если проходима только одна клетка
			else if ((map[getCoordinates(gameInfo, type).yCoordinate - 1][getCoordinates(gameInfo, type).xCoordinate].passable == true) &&
				(map[getCoordinates(gameInfo, type).yCoordinate - 2][getCoordinates(gameInfo, type).xCoordinate].passable == false))
			{
				//удаляем символ героя из текущей ячейки
				list::deleteCurrentElement(&map[getCoordinates(gameInfo, type).yCoordinate][getCoordinates(gameInfo, type).xCoordinate].types, type);
				//добавляем в ячейку выше символ героя
				list::addBegin(&map[getCoordinates(gameInfo, type).yCoordinate - 1][getCoordinates(gameInfo, type).xCoordinate].types, type);
				// координата героя по оси Оу уменьшается на один
				setOYCoordinates(gameInfo, type, -1); // TODO: -1 расхардкодить
			}

		}
	}

	// функция перемещения объектов по оси Ox
	void moveOx(int sideOfMovingOx, char type, GameInfo* gameInfo, MapCell** map)
	{
		if (type == AIM_DOT)
		{
			// если в соседней клетке проходимое пространство
			if (map[gameInfo->aim.coordinates.yCoordinate][gameInfo->aim.coordinates.xCoordinate + sideOfMovingOx].passable == true &&
				map[gameInfo->aim.coordinates.yCoordinate][gameInfo->aim.coordinates.xCoordinate + sideOfMovingOx].types->value != BUTTON &&
				map[gameInfo->aim.coordinates.yCoordinate][gameInfo->aim.coordinates.xCoordinate + sideOfMovingOx].types->value != WALL)
			{
				// удаляем символ прицела из текущей ячейки карты
				list::deleteCurrentElement(&map[getCoordinates(gameInfo, type).yCoordinate][getCoordinates(gameInfo, type).xCoordinate].types, type);
				//добавляем в соседнюю ячейку карты символ прицела
				list::addBegin(&map[gameInfo->aim.coordinates.yCoordinate][gameInfo->aim.coordinates.xCoordinate + sideOfMovingOx].types, type);
				setOXCoordinates(gameInfo, type, sideOfMovingOx);
			}
		}

		else
		{
			if (map[getCoordinates(gameInfo, type).yCoordinate][getCoordinates(gameInfo, type).xCoordinate + sideOfMovingOx].passable == true)
			{
				//удаляем символ героя из текущей ячейки карты
				list::deleteCurrentElement(&map[getCoordinates(gameInfo, type).yCoordinate][getCoordinates(gameInfo, type).xCoordinate].types, type);
				//добавляем в соседнюю ячейку карты символ героя
				list::addBegin(&map[getCoordinates(gameInfo, type).yCoordinate][getCoordinates(gameInfo, type).xCoordinate + sideOfMovingOx].types, type);
				setOXCoordinates(gameInfo, type, sideOfMovingOx);
			}
		}
	
	}


	// функция перемещения объектов по оси Oy
	void moveOy(int sideOfMovingOy, char type, GameInfo* gameInfo, MapCell** map)
	{
		if (type == AIM_DOT)
		{
			// если в соседней клетке проходимое пространство
			if (map[gameInfo->aim.coordinates.yCoordinate + sideOfMovingOy][gameInfo->aim.coordinates.xCoordinate].passable == true &&
				map[gameInfo->aim.coordinates.yCoordinate + sideOfMovingOy][gameInfo->aim.coordinates.xCoordinate].types->value != BUTTON &&
				map[gameInfo->aim.coordinates.yCoordinate + sideOfMovingOy][gameInfo->aim.coordinates.xCoordinate].types->value != WALL)
			{
				// удаляем символ прицела из текущей ячейки карты
				list::deleteCurrentElement(&map[getCoordinates(gameInfo, type).yCoordinate][getCoordinates(gameInfo, type).xCoordinate].types, type);
				// добавляем в соседнюю ячейку карты символ прицела
				list::addBegin(&map[getCoordinates(gameInfo, type).yCoordinate + sideOfMovingOy][getCoordinates(gameInfo, type).xCoordinate].types, type);

				setOYCoordinates(gameInfo, type, sideOfMovingOy);
			}
		}
		
		else
		{
			if (map[getCoordinates(gameInfo, type).yCoordinate + sideOfMovingOy][getCoordinates(gameInfo, type).xCoordinate].passable == true)
			{
				// удаляем символ прицела из текущей ячейки карты
				list::deleteCurrentElement(&map[getCoordinates(gameInfo, type).yCoordinate][getCoordinates(gameInfo, type).xCoordinate].types, type);
				// добавляем в соседнюю ячейку карты символ прицела
				list::addBegin(&map[getCoordinates(gameInfo, type).yCoordinate + sideOfMovingOy][getCoordinates(gameInfo, type).xCoordinate].types, type);

				setOYCoordinates(gameInfo, type, sideOfMovingOy);
			}
		}	
	}

	void gravity(MapCell** map, GameInfo* gameInfo)
	{
		int step = 1;
		// если в ячейке карты ниже героя проходимое пространство
		if (map[gameInfo->hero.coordinates.yCoordinate][gameInfo->hero.coordinates.xCoordinate].types->value == HERO &&
			map[gameInfo->hero.coordinates.yCoordinate + 1][gameInfo->hero.coordinates.xCoordinate].passable == true)
		{
			// перемещение героя вниз на одну ячейку карты
			moveOy(step, HERO, gameInfo, map);
		}
		// если в ячейке карты ниже турели проходимое пространство
		if (map[gameInfo->hunter_turret.coordinates.yCoordinate][gameInfo->hunter_turret.coordinates.xCoordinate].types->value == TURRET_HUNTER &&
			map[gameInfo->hunter_turret.coordinates.yCoordinate + 1][gameInfo->hunter_turret.coordinates.xCoordinate].passable == true)
		{
			// перемещение турели вниз на одну ячейку карты
			moveOy(step, TURRET_HUNTER, gameInfo, map);
		}
		// если в ячейке карты ниже турели проходимое пространство
		if (map[gameInfo->stationary_turret.coordinates.yCoordinate][gameInfo->stationary_turret.coordinates.xCoordinate].types->value == STATIONARY_TURRET &&
			map[gameInfo->stationary_turret.coordinates.yCoordinate + 1][gameInfo->stationary_turret.coordinates.xCoordinate].passable == true)
		{
			// перемещение турели вниз на одну ячейку карты
			moveOy(step, STATIONARY_TURRET, gameInfo, map);
		}

		if (map[gameInfo->platform_turret.coordinates.yCoordinate][gameInfo->platform_turret.coordinates.xCoordinate].types->value == PLATFORM_TURRET &&
			map[gameInfo->platform_turret.coordinates.yCoordinate + 1][gameInfo->platform_turret.coordinates.xCoordinate].passable == true)
		{
			// перемещение турели вниз на одну ячейку карты
			moveOy(step, PLATFORM_TURRET, gameInfo, map);
		}
	}

	// функция запуска уровня, отвчает за работу всей игры, принимает на вход название файла с уровнем
	// возвращает структуру с данными о уровне, количестве очков и времени, затраченном на прохождение
	records::DataAboutTheChampion* startLevel(char* levelName)
	{
		GameInfo* gameInfo = new GameInfo;
		MapCell** map = createMap(levelName, gameInfo); // Создаем двумерный массив структур, используя текстовый документ
		records::DataAboutTheChampion* player = new records::DataAboutTheChampion;
		clearScreen(); // Чистим экран
		drawFrame(map, gameInfo); // Рисуем первый кадр
		performAnAction(gameInfo, map); // Выполняем далее в зависимости от действий игрока
		system("cls");


		if (gameInfo->hero.isPlayerPassedLevel == true)
		{
			std::cout << "Please enter your name" << std::endl;

			std::cin >> player->name;

			player->score = gameInfo->hero.score;

			player->level = atoi(&levelName[4]); // Номер уровня находится в названии на пятом месте

			double score = gameInfo->hero.score;

			std::cout << "\n\n\t\t\tSCORE: " << score << std::endl;
			std::cout << "\t\t\tTIME: " << gameInfo->hero.time << std::endl;
			std::cout << "\n\n\t\t\tPRESS ANY KEY TO CONTINUE" << std::endl;
		}
		else
		{
			player->isPlayerPassedLevel = false;
			std::cout << "\n\n\t\t\tEND OF GAME" << std::endl;
		}

		_getch();

		freeMemory(map, gameInfo); // Очищаем занятую память

		clearScreen(); // Чистим экран

		return player;
	}

	//-----Portals_Functions------//
	// функция установки второго портала
	// принимает на вход символ портала, структуру с информацией об объекте на карте и двумерный массив структур
	void setPortal(char type, GameInfo* gameInfo, MapCell** map)
	{
		if (type == RED_PORTAL)	// если устанавливется красный портал
		{
			// если красный портал существует
			if (gameInfo->redPortal.coordinates.yCoordinate != 0)
				// удаляется символ существующего красного портала
				list::deleteCurrentElement(&map[gameInfo->redPortal.coordinates.yCoordinate][gameInfo->redPortal.coordinates.xCoordinate].types, RED_PORTAL);
			// координаты нового портала приравниваются координатам прицела
			gameInfo->redPortal.coordinates.xCoordinate = gameInfo->aim.coordinates.xCoordinate;
			gameInfo->redPortal.coordinates.yCoordinate = gameInfo->aim.coordinates.yCoordinate;

			// в ячейку карты, в которой находится прицел, добавляется символ красного портала
			list::addBegin(&map[gameInfo->aim.coordinates.yCoordinate][gameInfo->aim.coordinates.xCoordinate].types, RED_PORTAL);
		}

		else if (type == BLUE_PORTAL) // если устанавливется синий портал
		{
			// если синий портал уже существует
			if (gameInfo->bluePortal.coordinates.yCoordinate != 0)
				// удаляется символ существующего красного портала
				list::deleteCurrentElement(&map[gameInfo->bluePortal.coordinates.yCoordinate][gameInfo->bluePortal.coordinates.xCoordinate].types, BLUE_PORTAL);
			// координаты нового портала приравниваются координатам прицела
			gameInfo->bluePortal.coordinates.xCoordinate = gameInfo->aim.coordinates.xCoordinate;
			gameInfo->bluePortal.coordinates.yCoordinate = gameInfo->aim.coordinates.yCoordinate;
			// в ячейку карты, в которой находится прицел, добавляется символ синего портала
			list::addBegin(&map[gameInfo->aim.coordinates.yCoordinate][gameInfo->aim.coordinates.xCoordinate].types, BLUE_PORTAL);
		}
	}

	// функция перехода по порталам, принимает структуру с информацией об объекте на карте и двумерный массив структур
	void enterThePortal(char type, GameInfo* gameInfo, MapCell** map)
	{
		// если персонаж и красный портал в одной клетке карты и существует синий портал
		if (gameInfo->hero.coordinates.xCoordinate == gameInfo->redPortal.coordinates.xCoordinate &&
			gameInfo->hero.coordinates.yCoordinate == gameInfo->redPortal.coordinates.yCoordinate &&
			gameInfo->bluePortal.coordinates.yCoordinate != 0 && gameInfo->bluePortal.coordinates.xCoordinate != 0)
		{
			// в ячейку карты по координатам синего портала добавляется символ героя
			list::addBegin(&map[gameInfo->bluePortal.coordinates.yCoordinate][gameInfo->bluePortal.coordinates.xCoordinate].types, HERO);
			// из ячейки карты по текущим координатам героя удаляется символ героя
			list::deleteCurrentElement(&map[gameInfo->hero.coordinates.yCoordinate][gameInfo->hero.coordinates.xCoordinate].types, HERO);
			// координаты героя приравниваются к координатам синего портала
			gameInfo->hero.coordinates.xCoordinate = gameInfo->bluePortal.coordinates.xCoordinate;
			gameInfo->hero.coordinates.yCoordinate = gameInfo->bluePortal.coordinates.yCoordinate;
		}
		// если персонаж и синий портал в одной клетке карты и существует красный портал
		else if (gameInfo->hero.coordinates.xCoordinate == gameInfo->bluePortal.coordinates.xCoordinate &&
			gameInfo->hero.coordinates.yCoordinate == gameInfo->bluePortal.coordinates.yCoordinate &&
			gameInfo->redPortal.coordinates.yCoordinate != 0 && gameInfo->redPortal.coordinates.xCoordinate != 0)
		{
			// в ячейку карты по координатам красного портала добавляется символ героя
			list::addBegin(&map[gameInfo->redPortal.coordinates.yCoordinate][gameInfo->redPortal.coordinates.xCoordinate].types, HERO);
			// из ячейки карты по текущим координатам героя удаляется символ героя
			list::deleteCurrentElement(&map[gameInfo->hero.coordinates.yCoordinate][gameInfo->hero.coordinates.xCoordinate].types, HERO);
			// координаты героя приравниваются к координатам синего портала
			gameInfo->hero.coordinates.xCoordinate = gameInfo->redPortal.coordinates.xCoordinate;
			gameInfo->hero.coordinates.yCoordinate = gameInfo->redPortal.coordinates.yCoordinate;
		}
	}

	//------Button_Functions------//
	// функция активации клавиши, принимает структуру с информацией об объекте на карте и двумерный массив структур
	void activateTheButton(GameInfo* gameInfo, MapCell** map)
	{
		if (gameInfo->hero.coordinates.xCoordinate == gameInfo->buttonOne.coordinates.xCoordinate &&	// если персонаж и кнопка находятся в одной клетке
			gameInfo->hero.coordinates.yCoordinate == gameInfo->buttonOne.coordinates.yCoordinate &&	// и существует непроходимая стена
			map[gameInfo->blackWallOne.coordinates.yCoordinate][gameInfo->blackWallOne.coordinates.xCoordinate].types->value == BLACK_WALL)
		{
			// ячейка карты, в которой была непроходимая стена, становится проходимой
			map[gameInfo->blackWallOne.coordinates.yCoordinate][gameInfo->blackWallOne.coordinates.xCoordinate].passable = true;
			// на месте непроходимой стены отображается проходимая
			list::deleteCurrentElement(&map[gameInfo->blackWallOne.coordinates.yCoordinate][gameInfo->blackWallOne.coordinates.xCoordinate].types, BLACK_WALL);
			list::deleteCurrentElement(&map[gameInfo->buttonOne.coordinates.yCoordinate][gameInfo->buttonOne.coordinates.xCoordinate].types, BUTTON);
		}
		else if (gameInfo->hero.coordinates.xCoordinate == gameInfo->buttonTwo.coordinates.xCoordinate &&	// если персонаж и кнопка находятся в одной клетке
			gameInfo->hero.coordinates.yCoordinate == gameInfo->buttonTwo.coordinates.yCoordinate &&	// и существует непроходимая стена
			map[gameInfo->blackWallTwo.coordinates.yCoordinate][gameInfo->blackWallTwo.coordinates.xCoordinate].types->value == BLACK_WALL)
		{
			// ячейка карты, в которой была непроходимая стена, становится проходимой
			map[gameInfo->blackWallTwo.coordinates.yCoordinate][gameInfo->blackWallTwo.coordinates.xCoordinate].passable = true;
			// на месте непроходимой стены отображается проходимая
			list::deleteCurrentElement(&map[gameInfo->blackWallTwo.coordinates.yCoordinate][gameInfo->blackWallTwo.coordinates.xCoordinate].types, BLACK_WALL);
			list::deleteCurrentElement(&map[gameInfo->buttonTwo.coordinates.yCoordinate][gameInfo->buttonTwo.coordinates.xCoordinate].types, BUTTON);
		}
		else if (gameInfo->hero.coordinates.xCoordinate == gameInfo->buttonThree.coordinates.xCoordinate &&	// если персонаж и кнопка находятся в одной клетке
			gameInfo->hero.coordinates.yCoordinate == gameInfo->buttonThree.coordinates.yCoordinate &&	// и существует непроходимая стена
			map[gameInfo->blackWallThree.coordinates.yCoordinate][gameInfo->blackWallThree.coordinates.xCoordinate].types->value == BLACK_WALL)
		{
			// ячейка карты, в которой была непроходимая стена, становится проходимой
			map[gameInfo->blackWallThree.coordinates.yCoordinate][gameInfo->blackWallThree.coordinates.xCoordinate].passable = true;
			// на месте непроходимой стены отображается проходимая
			list::deleteCurrentElement(&map[gameInfo->blackWallThree.coordinates.yCoordinate][gameInfo->blackWallThree.coordinates.xCoordinate].types, BLACK_WALL);
			list::deleteCurrentElement(&map[gameInfo->buttonThree.coordinates.yCoordinate][gameInfo->buttonThree.coordinates.xCoordinate].types, BUTTON);
		}
		else if (gameInfo->hero.coordinates.xCoordinate == gameInfo->buttonFour.coordinates.xCoordinate &&	// если персонаж и кнопка находятся в одной клетке
			gameInfo->hero.coordinates.yCoordinate == gameInfo->buttonFour.coordinates.yCoordinate &&	// и существует непроходимая стена
			map[gameInfo->blackWallFour.coordinates.yCoordinate][gameInfo->blackWallFour.coordinates.xCoordinate].types->value == BLACK_WALL)
		{
			// ячейка карты, в которой была непроходимая стена, становится проходимой
			map[gameInfo->blackWallFour.coordinates.yCoordinate][gameInfo->blackWallFour.coordinates.xCoordinate].passable = true;
			// на месте непроходимой стены отображается проходимая
			list::deleteCurrentElement(&map[gameInfo->blackWallFour.coordinates.yCoordinate][gameInfo->blackWallFour.coordinates.xCoordinate].types, BLACK_WALL);
			list::deleteCurrentElement(&map[gameInfo->buttonFour.coordinates.yCoordinate][gameInfo->buttonFour.coordinates.xCoordinate].types, BUTTON);
		}
	}

	// функция перемещения прицела к герою
	void replayceTheAimToHero(GameInfo* gameInfo, MapCell** map)
	{
		// добавляется текстура прицела по координатам героя
		list::addBegin(&map[gameInfo->hero.coordinates.yCoordinate][gameInfo->hero.coordinates.xCoordinate].types, AIM_DOT);
		// удаляется текущая текстура прицела
		list::deleteCurrentElement(&map[gameInfo->aim.coordinates.yCoordinate][gameInfo->aim.coordinates.xCoordinate].types, AIM_DOT);

		// координатам прицела присваиваются координаты героя
		gameInfo->aim.coordinates.xCoordinate = gameInfo->hero.coordinates.xCoordinate;
		gameInfo->aim.coordinates.yCoordinate = gameInfo->hero.coordinates.yCoordinate;
	}

	// Функция проверяет, наступило ли событие, при котором игра должна закончиться
	bool checkGameOverConditions(GameInfo* gameInfo, MapCell** map, bool gameIsRunning)
	{
		if ((gameInfo->hero.coordinates.xCoordinate == gameInfo->exitFromLevel.coordinates.xCoordinate &&	// если персонаж находится в одной клетке с выходом
			gameInfo->hero.coordinates.yCoordinate == gameInfo->exitFromLevel.coordinates.yCoordinate))
		{
			return false;
		}
		else if (gameInfo->hero.healthPoints <= 0) // если здоровье игрока ниже или равно 0
		{
			gameInfo->hero.isPlayerPassedLevel = false;
			return false;
		}
		else if (gameIsRunning == false)
		{
			return false;
		}
		else
		{
			return true;
		}
	}

	bool quitTheLevel(GameInfo* gameInfo, MapCell** map)
	{
		std::cout << "\n\n\n\n\n\n\n\n\t   Quit the level?\n\n\t   Press 'y' or 'n'" << std::endl;
		bool isPlayerWantsToQuitLevel = false;
		switch (_getch())
		{
		case YES_LOWER_CASE:
			gameInfo->hero.isPlayerPassedLevel = false;
			isPlayerWantsToQuitLevel = true;
			break;

		case NO_LOWER_CASE:
			drawFrame(map, gameInfo);
			isPlayerWantsToQuitLevel = false;
			break;

		}
		return !isPlayerWantsToQuitLevel;
	}

	// функция паузы
	double pause(GameInfo* gameInfo, MapCell** map)
	{
		double startTime = clock();
		std::cout << "\n\n\n\n\n\n\n\n\t       Pause\n\n\t   Press any key" << std::endl;
		_getch();
		system("cls");
		double endTime = clock();
		return endTime - startTime;
	}

	bool objectIsStandingOnTheFloor(Coordinates coordinates, MapCell** map)
	{
		if (map[coordinates.yCoordinate + 1][coordinates.xCoordinate].passable == false)
		{
			return true;
		}
		else
		{
			return false;
		}
	}

	bool bothCellsAboveTheObjectAreFree(Coordinates coordinates, MapCell** map)
	{
		if ((map[coordinates.yCoordinate - 1][coordinates.xCoordinate].passable == true) &&
			(map[coordinates.yCoordinate - 2][coordinates.xCoordinate].passable == true))
		{
			return true;
		}
		else
		{
			return false;
		}
	}

	Coordinates getCoordinates(GameInfo* gameInfo, char type)
	{
		Coordinates requiredCoords;

		switch (type)
		{
		case HERO:
			requiredCoords = gameInfo->hero.coordinates;
			break;
		case AIM_DOT:
			requiredCoords = gameInfo->aim.coordinates;
			break;
		case TURRET_HUNTER:
			requiredCoords = gameInfo->hunter_turret.coordinates;
			break;
		case STATIONARY_TURRET:
			requiredCoords = gameInfo->stationary_turret.coordinates;
			break;
		case PLATFORM_TURRET:
			requiredCoords = gameInfo->platform_turret.coordinates;
			break;
		case RED_PORTAL:
			requiredCoords = gameInfo->redPortal.coordinates;
			break;
		case BLUE_PORTAL:
			requiredCoords = gameInfo->bluePortal.coordinates;
			break;
		default:
			break;
		}

		return requiredCoords;
	}

	void setOXCoordinates(GameInfo* gameInfo, char type, int sideOfMovingOx)
	{
		switch (type)
		{
		case HERO:
			gameInfo->hero.coordinates.xCoordinate += sideOfMovingOx;
			break;
		case AIM_DOT:
			gameInfo->aim.coordinates.xCoordinate += sideOfMovingOx;
			break;
		case TURRET_HUNTER:
			gameInfo->hunter_turret.coordinates.xCoordinate += sideOfMovingOx;
			break;
		case PLATFORM_TURRET:
			gameInfo->platform_turret.coordinates.xCoordinate += sideOfMovingOx;
			break;
		case RED_PORTAL:
			gameInfo->redPortal.coordinates.xCoordinate += sideOfMovingOx;
			break;
		case BLUE_PORTAL:
			gameInfo->bluePortal.coordinates.xCoordinate += sideOfMovingOx;
			break;
		default:
			break;
		}
	}

	void setOYCoordinates(GameInfo* gameInfo, char type, int sideOfMovingOy)
	{
		switch (type)
		{
		case HERO:
			gameInfo->hero.coordinates.yCoordinate += sideOfMovingOy;
			break;
		case AIM_DOT:
			gameInfo->aim.coordinates.yCoordinate += sideOfMovingOy;
			break;
		case TURRET_HUNTER:
			gameInfo->hunter_turret.coordinates.yCoordinate += sideOfMovingOy;
			break;
		case PLATFORM_TURRET:
			gameInfo->platform_turret.coordinates.yCoordinate += sideOfMovingOy;
			break;
		case RED_PORTAL:
			gameInfo->redPortal.coordinates.yCoordinate += sideOfMovingOy;
			break;
		case BLUE_PORTAL:
			gameInfo->bluePortal.coordinates.yCoordinate += sideOfMovingOy;
			break;
		default:
			break;
		}
	}
}