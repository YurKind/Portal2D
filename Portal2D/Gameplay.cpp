#include "Gameplay.h"
#include "Map.h"
#include "Instruments.h"
#include "Structures.h"
#include "List.h"
#include "TurretsAI.h"

namespace game
{
	// принимает структуру с информацией об объекте на карте и двумерный массив структур
	void performAnAction(GameInfo* gameInfo, MapCell** map)
	{
		bool gameIsRunning = true;	// условие выполнение цикла
		double timeBeforeGame = clock(); // переменная для отображения времени, затраченного на прохождение уровня
		double timeOnPause = 0.0;	// переменная для хранения времени на паузе
		int sideOfMovingOx;		// переменная для хранения направления движения и количество шагов по оси Ох
		int sideOfMovingOy;		// переменная для хранения направления движения и количество шагов по оси Оу

		while (gameIsRunning == true)
		{
			if (_kbhit()) // Если нажата клавиша
			{
				switch (_getch()) // Читаем клавишу
				{
				case A_LOWER_CASE: case A_LOWER_CASE_RU: case A_UPPER_CASE: case A_UPPER_CASE_RU:
					sideOfMovingOx = STEP_LEFT_OR_UP;
					moveOx(sideOfMovingOx, HERO, gameInfo, map);
					break;

				case D_LOWER_CASE: case D_LOWER_CASE_RU: case D_UPPER_CASE: case D_UPPER_CASE_RU:
					sideOfMovingOx = STEP_RIGHT_OR_DOWN;
					moveOx(sideOfMovingOx, HERO, gameInfo, map);
					break;

				case LEFT_ARROW:
					sideOfMovingOx = STEP_LEFT_OR_UP;
					moveOx(sideOfMovingOx, AIM_DOT, gameInfo, map);
					break;

				case RIGHT_ARROW:
					sideOfMovingOx = STEP_RIGHT_OR_DOWN;
					moveOx(sideOfMovingOx, AIM_DOT, gameInfo, map);
					break;

				case UP_ARROW:
					sideOfMovingOy = STEP_LEFT_OR_UP;
					moveOy(sideOfMovingOy, AIM_DOT, gameInfo, map);
					break;

				case DOWN_ARROW:
					sideOfMovingOy = STEP_RIGHT_OR_DOWN;
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
					enterThePortal(gameInfo, map);
					activateTheButton(gameInfo, map);
					break;

				case PAUSE_LOWER_CASE: case PAUSE_LOWER_CASE_RU:
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
				gameInfo->hero.score -= SCORE_PER_SECOND;
			}
		}
	}

	//------Moving_Functions------//

	// функция перемещения объектов по оси Ox
	void moveOx(int sideOfMovingOx, char type, GameInfo* gameInfo, MapCell** map)
	{
		// если перемещение по оси Ox возможно
		if (isMovingPossibleOx(getCoordinates(gameInfo, type), map, sideOfMovingOx, type))
		{
			// удаляем символ объекта из текущей ячейки карты
			list::deleteCurrentElement(&map[getCoordinates(gameInfo, type).yCoordinate][getCoordinates(gameInfo, type).xCoordinate].types, type);
			// добавляем в соседнюю ячейку карты символ объекта
			list::addBegin(&map[getCoordinates(gameInfo, type).yCoordinate][getCoordinates(gameInfo, type).xCoordinate + sideOfMovingOx].types, type);
			// изменяем координаты объекта по Ox
			changeOXCoordinates(gameInfo, type, sideOfMovingOx);

		}
	}

	// функция перемещения объектов по оси Oy
	void moveOy(int sideOfMovingOy, char type, GameInfo* gameInfo, MapCell** map)
	{
		// если перемещение по оси Oy возможно
		if (isMovingPossibleOy(getCoordinates(gameInfo, type), map, sideOfMovingOy, type))
		{
			// удаляем символ объекта из текущей ячейки карты
			list::deleteCurrentElement(&map[getCoordinates(gameInfo, type).yCoordinate][getCoordinates(gameInfo, type).xCoordinate].types, type);
			// добавляем в соседнюю ячейку карты символ объекта
			list::addBegin(&map[getCoordinates(gameInfo, type).yCoordinate + sideOfMovingOy][getCoordinates(gameInfo, type).xCoordinate].types, type);
			// изменяем координаты объекта по Oy
			changeOYCoordinates(gameInfo, type, sideOfMovingOy);
		}
	}

	// принимает структуру с информацией об объекте на карте и двумерный массив структур
	void jump(char type, GameInfo* gameInfo, MapCell** map)
	{
		// если под объектом есть непроходимый блок
		if (isObjectStandingOnTheFloor(getCoordinates(gameInfo, type), map))
		{
			// Если обе клетки над объектом проходимы
			if (bothCellsAboveTheObjectAreFree(getCoordinates(gameInfo, type), map))
			{
				// удаляем символ объекта из текущей ячейки
				list::deleteCurrentElement(&map[getCoordinates(gameInfo, type).yCoordinate][getCoordinates(gameInfo, type).xCoordinate].types, type);
				// добавляем в ячейку выше символ объекта
				list::addBegin(&map[getCoordinates(gameInfo, type).yCoordinate + JUMP_HEIGHT][getCoordinates(gameInfo, type).xCoordinate].types, type);

				// координата объекта по оси Оу уменьшается на один
				changeOYCoordinates(gameInfo, type, STEP_LEFT_OR_UP);
				// отрисовавается кадр
				drawFrame(map, gameInfo);

				// удаляем символ объекта из текущей ячейки
				list::deleteCurrentElement(&map[getCoordinates(gameInfo, type).yCoordinate][getCoordinates(gameInfo, type).xCoordinate].types, type);
				// добавляем в ячейку выше символ объекта
				list::addBegin(&map[getCoordinates(gameInfo, type).yCoordinate + JUMP_HEIGHT][getCoordinates(gameInfo, type).xCoordinate].types, type);
				// координата объекта по оси Оу уменьшается на один
				changeOYCoordinates(gameInfo, type, JUMP_HEIGHT);
			}
			// Если над объектом проходима только одна клетка
			else if (oneCellAboveTheObjectIsFree(getCoordinates(gameInfo, type), map))
			{
				// удаляем символ объкта из текущей ячейки
				list::deleteCurrentElement(&map[getCoordinates(gameInfo, type).yCoordinate][getCoordinates(gameInfo, type).xCoordinate].types, type);
				// добавляем в ячейку выше символ объекта
				list::addBegin(&map[getCoordinates(gameInfo, type).yCoordinate + JUMP_HEIGHT][getCoordinates(gameInfo, type).xCoordinate].types, type);
				// координата объекта по оси Оу уменьшается на один
				changeOYCoordinates(gameInfo, type, JUMP_HEIGHT);
			}

		}
	}

	// Выполняя необходимые проверки, имитирует гравитацию
	void gravity(MapCell** map, GameInfo* gameInfo)
	{
		// если в ячейке карты ниже героя проходимое пространство
		if (map[getCoordinates(gameInfo, HERO).yCoordinate + STEP_RIGHT_OR_DOWN][getCoordinates(gameInfo, HERO).xCoordinate].passable == true)
		{
			// перемещение героя вниз на одну ячейку карты
			moveOy(STEP_RIGHT_OR_DOWN, HERO, gameInfo, map);
		}
		// если в ячейке карты ниже турели-охотника проходимое пространство
		if (map[getCoordinates(gameInfo, TURRET_HUNTER).yCoordinate + STEP_RIGHT_OR_DOWN][getCoordinates(gameInfo, TURRET_HUNTER).xCoordinate].passable == true)
		{
			// перемещение турели-охотника вниз на одну ячейку карты
			moveOy(STEP_RIGHT_OR_DOWN, TURRET_HUNTER, gameInfo, map);
		}
		// если в ячейке карты ниже стационарной турели проходимое пространство
		if (map[getCoordinates(gameInfo, STATIONARY_TURRET).yCoordinate + STEP_RIGHT_OR_DOWN][getCoordinates(gameInfo, STATIONARY_TURRET).xCoordinate].passable == true)
		{
			// перемещение стационарной турели вниз на одну ячейку карты
			moveOy(STEP_RIGHT_OR_DOWN, STATIONARY_TURRET, gameInfo, map);
		}
		// если в ячейке карты ниже патрулирующей турели проходимое пространство
		if (map[getCoordinates(gameInfo, PLATFORM_TURRET).yCoordinate + STEP_RIGHT_OR_DOWN][getCoordinates(gameInfo, PLATFORM_TURRET).xCoordinate].passable == true)
		{
			// перемещение патрулирующей турели вниз на одну ячейку карты
			moveOy(STEP_RIGHT_OR_DOWN, PLATFORM_TURRET, gameInfo, map);
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
		// если портал существует
		if (getCoordinates(gameInfo, type).yCoordinate != 0)
		{
			// удаляем символ объекта
			list::deleteCurrentElement(&map[getCoordinates(gameInfo, type).yCoordinate][getCoordinates(gameInfo, type).xCoordinate].types, type);
		}
		// устанавливаем координаты портала на оси Ox
		setOXCoordinates(gameInfo, type, NO_STEP);
		// устанавливаем координаты портала на оси Oy
		setOYCoordinates(gameInfo, type);
		// добавляем символ портала
		list::addBegin(&map[getCoordinates(gameInfo, type).yCoordinate][getCoordinates(gameInfo, type).xCoordinate].types, type);
	}

	// функция перехода по порталам, принимает структуру с информацией об объекте на карте и двумерный массив структур
	void enterThePortal(GameInfo* gameInfo, MapCell** map)
	{
		// переменная для хранения типа портала
		char typeOfPortal = findTypeOfPortal(gameInfo);
		// если герой стоит в портале
		if (typeOfPortal != NULL)
		{
			// добавляем символ героя по координатом второго портала
			list::addBegin(&map[getCoordinates(gameInfo, typeOfPortal).yCoordinate][getCoordinates(gameInfo, typeOfPortal).xCoordinate].types, HERO);
			// удаляем символ героя из предыдущего положения
			list::deleteCurrentElement(&map[getCoordinates(gameInfo, HERO).yCoordinate][getCoordinates(gameInfo, HERO).xCoordinate].types, HERO);

			// устанавливаем координаты героя по координатам второго портала
			gameInfo->hero.coordinates.xCoordinate = getCoordinates(gameInfo, typeOfPortal).xCoordinate;
			gameInfo->hero.coordinates.yCoordinate = getCoordinates(gameInfo, typeOfPortal).yCoordinate;
		}
	}

	// функция определяет тип портала, в который будет совершено перемещение
	char findTypeOfPortal(GameInfo* gameInfo)
	{
		// переменная для хранения типа портала, в который будет совершено перемещение
		char typeOfPortal = NULL;
		// если герой в красном портале
		if (getCoordinates(gameInfo, HERO).xCoordinate == getCoordinates(gameInfo, RED_PORTAL).xCoordinate &&
			getCoordinates(gameInfo, HERO).yCoordinate == getCoordinates(gameInfo, RED_PORTAL).yCoordinate &&
			getCoordinates(gameInfo, BLUE_PORTAL).yCoordinate != 0 && getCoordinates(gameInfo, BLUE_PORTAL).xCoordinate != 0)
		{
			typeOfPortal = BLUE_PORTAL;
		}
		// если герой в синем портале
		else if (getCoordinates(gameInfo, HERO).xCoordinate == getCoordinates(gameInfo, BLUE_PORTAL).xCoordinate &&
			getCoordinates(gameInfo, HERO).yCoordinate == getCoordinates(gameInfo, BLUE_PORTAL).yCoordinate &&
			getCoordinates(gameInfo, RED_PORTAL).yCoordinate != 0 && getCoordinates(gameInfo, RED_PORTAL).xCoordinate != 0)
		{
			typeOfPortal = RED_PORTAL;
		}

		return typeOfPortal;
	}

	//------Button_Functions------//

	// функция активации клавиши, принимает структуру с информацией об объекте на карте и двумерный массив структур
	void activateTheButton(GameInfo* gameInfo, MapCell** map)
	{
		// переменная для хранения типа двери
		char typeOfDoor = findTypeOfDoor(gameInfo, map);
		// переменная для хранения типа кнопки
		char typeOfButton = findTypeOfButton(typeOfDoor);
		// если кнопка существует и герой стоит на кнопке
		if (typeOfDoor != NULL)
		{
			// ячейка карты по координатам двери становится проходимой
			map[getCoordinates(gameInfo, typeOfDoor).yCoordinate][getCoordinates(gameInfo, typeOfDoor).xCoordinate].passable = true;
			// удаляем символ двери
			list::deleteCurrentElement(&map[getCoordinates(gameInfo, typeOfDoor).yCoordinate][getCoordinates(gameInfo, typeOfDoor).xCoordinate].types, typeOfDoor);
			// удаляем символ кномки
			list::deleteCurrentElement(&map[getCoordinates(gameInfo, typeOfButton).yCoordinate][getCoordinates(gameInfo, typeOfButton).xCoordinate].types, typeOfButton);
		}
	}

	// функция определяет тип двери
	char findTypeOfDoor(GameInfo* gameInfo, MapCell** map)
	{
		// переменная для хранения типа двери
		char typeOfDoor = NULL;
		// если герой стоит на кнопке, которая открывает первую дверь
		if (gameInfo->hero.coordinates.xCoordinate == gameInfo->buttonOne.coordinates.xCoordinate &&
			gameInfo->hero.coordinates.yCoordinate == gameInfo->buttonOne.coordinates.yCoordinate &&
			map[gameInfo->blackWallOne.coordinates.yCoordinate][gameInfo->blackWallOne.coordinates.xCoordinate].types->value == BLACK_WALL_ONE_S)
		{
			typeOfDoor = BLACK_WALL_ONE_S;
		}
		// если герой стоит на кнопке, которая открывает вторую дверь
		else if (gameInfo->hero.coordinates.xCoordinate == gameInfo->buttonTwo.coordinates.xCoordinate &&
			gameInfo->hero.coordinates.yCoordinate == gameInfo->buttonTwo.coordinates.yCoordinate &&
			map[gameInfo->blackWallTwo.coordinates.yCoordinate][gameInfo->blackWallTwo.coordinates.xCoordinate].types->value == BLACK_WALL_TWO_S)
		{
			typeOfDoor = BLACK_WALL_TWO_S;
		}
		// если герой стоит на кнопке, которая открывает третью дверь
		else if (gameInfo->hero.coordinates.xCoordinate == gameInfo->buttonThree.coordinates.xCoordinate &&
			gameInfo->hero.coordinates.yCoordinate == gameInfo->buttonThree.coordinates.yCoordinate &&
			map[gameInfo->blackWallThree.coordinates.yCoordinate][gameInfo->blackWallThree.coordinates.xCoordinate].types->value == BLACK_WALL_THREE_S)
		{
			typeOfDoor = BLACK_WALL_THREE_S;

		}
		// если герой стоит на кнопке, которая открывает четвёртую дверь
		else if (gameInfo->hero.coordinates.xCoordinate == gameInfo->buttonFour.coordinates.xCoordinate &&
			gameInfo->hero.coordinates.yCoordinate == gameInfo->buttonFour.coordinates.yCoordinate &&
			map[gameInfo->blackWallFour.coordinates.yCoordinate][gameInfo->blackWallFour.coordinates.xCoordinate].types->value == BLACK_WALL_FOUR_S)
		{
			typeOfDoor = BLACK_WALL_FOUR_S;
		}
		return typeOfDoor;
	}

	// функция определяет тип кнопки
	char findTypeOfButton(char typeOfDoor)
	{
		// переменная для хранения типа кнопки
		char typeOfButton = NULL;
		switch (typeOfDoor)
		{
		case BLACK_WALL_ONE_S:
			typeOfButton = BUTTON_ONE_S;
			break;

		case BLACK_WALL_TWO_S:
			typeOfButton = BUTTON_TWO_S;
			break;

		case BLACK_WALL_THREE_S:
			typeOfButton = BUTTON_THREE_S;
			break;

		case BLACK_WALL_FOUR_S:
			typeOfButton = BUTTON_FOUR_S;
			break;
		}

		return typeOfButton;
	}

	//------Auxiliary_Functions------//

	// Функция проверяет, наступило ли событие, при котором игра должна закончиться
	bool checkGameOverConditions(GameInfo* gameInfo, MapCell** map, bool gameIsRunning)
	{
		// если персонаж находится в одной клетке с выходом
		if ((getCoordinates(gameInfo, HERO).xCoordinate == getCoordinates(gameInfo, EXIT).xCoordinate) &&
			(getCoordinates(gameInfo, HERO).yCoordinate == getCoordinates(gameInfo, EXIT).yCoordinate))
		{
			return false;
		}
		// если здоровье игрока ниже или равно 0
		else if (gameInfo->hero.healthPoints <= 0)
		{
			gameInfo->hero.isPlayerPassedLevel = false;
			return false;
		}
		// если был произведён выход из игры
		else if (gameIsRunning == false)
		{
			return false;
		}
		else
		{
			return true;
		}
	}

	// функция прерывает процесс игры
	bool quitTheLevel(GameInfo* gameInfo, MapCell** map)
	{
		std::cout << "\n\n\n\n\n\n\n\n\t   Quit the level?\n\n\t   Press 'y' or 'n'" << std::endl;
		// переменная для хранения выбора игрока (выйти или нет из игры)
		bool isPlayerWantsToQuitLevel = false;
		switch (_getch())
		{
			// если игрок подтверждает выход
		case YES_LOWER_CASE: case YES_LOWER_CASE_RU: case YES_UPPER_CASE: case YES_UPPER_CASE_RU:
			gameInfo->hero.isPlayerPassedLevel = false;
			isPlayerWantsToQuitLevel = true;
			break;
			// если игрок отменяет выход
		case NO_LOWER_CASE: case NO_LOWER_CASE_RU: case NO_UPPER_CASE: case NO_UPPER_CASE_RU:
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

	// функция проверяет стоит ли объект на непроходимой поверхности
	bool isObjectStandingOnTheFloor(Coordinates coordinates, MapCell** map)
	{
		// если под объектом свободно
		if (map[coordinates.yCoordinate + STEP_RIGHT_OR_DOWN][coordinates.xCoordinate].passable == false)
		{
			return true;
		}
		else
		{
			return false;
		}
	}

	// функция проверяет есть ли над объектом две свободных клетки
	bool bothCellsAboveTheObjectAreFree(Coordinates coordinates, MapCell** map)
	{
		// если две ячейки над объектом проходимы
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

	// функция проверяет есть ли над объектом одна свободная клетка
	bool oneCellAboveTheObjectIsFree(Coordinates coordinates, MapCell** map)
	{
		// если одна ячейка над объектом проходимы
		if ((map[coordinates.yCoordinate - 1][coordinates.xCoordinate].passable == true) &&
			(map[coordinates.yCoordinate - 2][coordinates.xCoordinate].passable == false))
		{
			return true;
		}
		else
		{
			return false;
		}
	}

	// функция проверяет возможность проходимости по оси Ox
	bool isMovingPossibleOx(Coordinates coordinates, MapCell** map, int sideOfMovingOx, char type)
	{
		// если по оси Ox проходимое пространство
		// если слева(справа) от прицела нет кнопки или стены (в случае перемещения прицела) 
		if ((type == AIM_DOT && map[coordinates.yCoordinate][coordinates.xCoordinate + sideOfMovingOx].passable == true &&
			map[coordinates.yCoordinate][coordinates.xCoordinate + sideOfMovingOx].types->value != BUTTON &&
			map[coordinates.yCoordinate][coordinates.xCoordinate + sideOfMovingOx].types->value != WALL) ||
			(type != AIM_DOT && map[coordinates.yCoordinate][coordinates.xCoordinate + sideOfMovingOx].passable == true))
		{
			return true;
		}
		else
		{
			return false;
		}
	}

	// функция проверяет возможность проходимости по оси Oy
	bool isMovingPossibleOy(Coordinates coordinates, MapCell** map, int sideOfMovingOy, char type)
	{
		// если по оси Oy проходимое пространство
		// если сверху(снизу) от прицела нет кнопки или стены (в случае перемещения прицела) 
		if ((type == AIM_DOT && map[coordinates.yCoordinate + sideOfMovingOy][coordinates.xCoordinate].passable == true &&
			map[coordinates.yCoordinate + sideOfMovingOy][coordinates.xCoordinate].types->value != BUTTON &&
			map[coordinates.yCoordinate + sideOfMovingOy][coordinates.xCoordinate].types->value != WALL) ||
			(type != AIM_DOT && map[coordinates.yCoordinate + sideOfMovingOy][coordinates.xCoordinate].passable == true))
		{
			return true;
		}
		else
		{
			return false;
		}
	}

	// функция возвращает координаты объекта
	Coordinates getCoordinates(GameInfo* gameInfo, char type)
	{
		// переменная для хранения текущих координат объекта
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

		case BULLET_OF_STATIONARY_TURRET:
			requiredCoords = gameInfo->bulletOfStationaryTurret.coordinates;
			break;

		case BULLET_OF_PLATFORM_TURRET:
			requiredCoords = gameInfo->bulletOfPlatformTurret.coordinates;
			break;

		case BULLET_OF_HUNTER_TURRET:
			requiredCoords = gameInfo->bulletOfHunterTurret.coordinates;
			break;

		case BLACK_WALL_ONE_S:
			requiredCoords = gameInfo->blackWallOne.coordinates;
			break;

		case BLACK_WALL_TWO_S:
			requiredCoords = gameInfo->blackWallTwo.coordinates;
			break;

		case BLACK_WALL_THREE_S:
			requiredCoords = gameInfo->blackWallThree.coordinates;
			break;

		case BLACK_WALL_FOUR_S:
			requiredCoords = gameInfo->blackWallFour.coordinates;
			break;

		case BUTTON_ONE_S:
			requiredCoords = gameInfo->buttonOne.coordinates;
			break;

		case BUTTON_TWO_S:
			requiredCoords = gameInfo->buttonTwo.coordinates;
			break;

		case BUTTON_THREE_S:
			requiredCoords = gameInfo->buttonThree.coordinates;
			break;

		case BUTTON_FOUR_S:
			requiredCoords = gameInfo->buttonFour.coordinates;
			break;

		case EXIT:
			requiredCoords = gameInfo->exitFromLevel.coordinates;
			break;

		default:
			break;
		}

		return requiredCoords;
	}

	// функция изменяет координаты объекта по оси Ox
	void changeOXCoordinates(GameInfo* gameInfo, char type, int sideOfMovingOx)
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

		case BULLET_OF_STATIONARY_TURRET:
			gameInfo->bulletOfStationaryTurret.coordinates.xCoordinate += sideOfMovingOx;
			break;

		case BULLET_OF_PLATFORM_TURRET:
			gameInfo->bulletOfPlatformTurret.coordinates.xCoordinate += sideOfMovingOx;
			break;

		case BULLET_OF_HUNTER_TURRET:
			gameInfo->bulletOfHunterTurret.coordinates.xCoordinate += sideOfMovingOx;
			break;

		default:
			break;
		}
	}

	// функция изменяет координаты объекта по оси Oy
	void changeOYCoordinates(GameInfo* gameInfo, char type, int sideOfMovingOy)
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

		default:
			break;
		}
	}

	// функция устанавливает координаты объекта на оси Ox
	void setOXCoordinates(GameInfo* gameInfo, char type, int step)
	{
		switch (type)
		{
		case RED_PORTAL:
			gameInfo->redPortal.coordinates.xCoordinate = gameInfo->aim.coordinates.xCoordinate;
			break;

		case BLUE_PORTAL:
			gameInfo->bluePortal.coordinates.xCoordinate = gameInfo->aim.coordinates.xCoordinate;
			break;

		case BULLET_OF_STATIONARY_TURRET:
			// если стационарная турель стреляет
			if (step != NO_STEP)
			{
				gameInfo->bulletOfStationaryTurret.coordinates.xCoordinate = gameInfo->stationary_turret.coordinates.xCoordinate + step;
			}
			// если стационарная турель не стреляет
			else
			{
				gameInfo->bulletOfStationaryTurret.coordinates.xCoordinate = NO_STEP;
			}
			break;

		case BULLET_OF_PLATFORM_TURRET:
			// если патрулирующая турель стреляет
			if (step != NO_STEP)
			{
				gameInfo->bulletOfPlatformTurret.coordinates.xCoordinate = gameInfo->platform_turret.coordinates.xCoordinate + step;
			}
			// если патрулирующая турель не стреляет
			else
			{
				gameInfo->bulletOfPlatformTurret.coordinates.xCoordinate = NO_STEP;
			}
			break;

		case BULLET_OF_HUNTER_TURRET:
			// если турель-охотник стреляет
			if (step != NO_STEP)
			{
				gameInfo->bulletOfHunterTurret.coordinates.xCoordinate = gameInfo->hunter_turret.coordinates.xCoordinate + step;
			}
			// если турель-охотник не стреляет
			else
			{
				gameInfo->bulletOfHunterTurret.coordinates.xCoordinate = NO_STEP;
			}
			break;

		default:
			break;
		}
	}

	// функция устанавливает координаты объекта на оси Oy
	void setOYCoordinates(GameInfo* gameInfo, char type)
	{
		switch (type)
		{
		case RED_PORTAL:
			gameInfo->redPortal.coordinates.yCoordinate = gameInfo->aim.coordinates.yCoordinate;
			break;

		case BLUE_PORTAL:
			gameInfo->bluePortal.coordinates.yCoordinate = gameInfo->aim.coordinates.yCoordinate;
			break;

		case BULLET_OF_STATIONARY_TURRET:
			gameInfo->bulletOfStationaryTurret.coordinates.yCoordinate = gameInfo->stationary_turret.coordinates.yCoordinate;
			break;

		case BULLET_OF_PLATFORM_TURRET:
			gameInfo->bulletOfPlatformTurret.coordinates.yCoordinate = gameInfo->platform_turret.coordinates.yCoordinate;
			break;

		case BULLET_OF_HUNTER_TURRET:
			gameInfo->bulletOfHunterTurret.coordinates.yCoordinate = gameInfo->hunter_turret.coordinates.yCoordinate;
			break;

		default:
			break;
		}
	}
}