#include "Gameplay.h"
#include "Map.h"
#include "Instruments.h"

//------Moving_Functions------//
void game::performAnAction(GameInfo* gameInfo, MapCell** map)
{
	bool gameIsRunning = true; // Временно

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
				moveDown(gameInfo, map);
				break;

			case SPACE_JUMP:
				jump(gameInfo, map);
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
		
		gameIsRunning = checkGameOverConditions(gameInfo, map);

		game::clearScreen(); // Очищаем экран
		game::drawFrame(map, gameInfo);
		game::gravity(map, gameInfo); // Имитируем гравитацию
		game::clearScreen(); // Очищаем экран

		double timeAfterAction = clock();
		gameInfo->hero.time = (timeAfterAction - timeBeforeGame) / 1000.0;

		if (gameInfo->hero.score > 0)
		{
			gameInfo->hero.score -= 1;
		}
	}

	double timeAfterGame = clock();

	double requiredTime = (timeAfterGame - timeBeforeGame) / 1000.0;
}

//------Moving_Functions------//

void game::jump(GameInfo* gameInfo, game::MapCell** map)
{
	if (map[gameInfo->hero.yCoordinate + 1][gameInfo->hero.xCoordinate].passable == false)	// если под персонажем есть непроходимый блок
	{
		if ((map[gameInfo->hero.yCoordinate - 1][gameInfo->hero.xCoordinate].passable == true) && // Если обе клетки над героем свободны
			(map[gameInfo->hero.yCoordinate - 2][gameInfo->hero.xCoordinate].passable == true))
		{
			push(pop(map[gameInfo->hero.yCoordinate][gameInfo->hero.xCoordinate].types),
				map[gameInfo->hero.yCoordinate - 1][gameInfo->hero.xCoordinate].types);	// персонаж перемещается на ячеку карты вверх

			gameInfo->hero.yCoordinate = gameInfo->hero.yCoordinate - 1;

			game::drawFrame(map, gameInfo);	// отрисовавается кадр

			push(pop(map[gameInfo->hero.yCoordinate][gameInfo->hero.xCoordinate].types),	// персонаж перемещается на ячеку карты вверх
				map[gameInfo->hero.yCoordinate - 1][gameInfo->hero.xCoordinate].types);

			gameInfo->hero.yCoordinate = gameInfo->hero.yCoordinate - 1;
		}

		else if ((map[gameInfo->hero.yCoordinate - 1][gameInfo->hero.xCoordinate].passable == true) && // Если свободна только одна
			(map[gameInfo->hero.yCoordinate - 2][gameInfo->hero.xCoordinate].passable == false))
		{
			push(pop(map[gameInfo->hero.yCoordinate][gameInfo->hero.xCoordinate].types),	// персонаж перемещается на ячеку карты вверх
				map[gameInfo->hero.yCoordinate - 1][gameInfo->hero.xCoordinate].types);

			gameInfo->hero.yCoordinate = gameInfo->hero.yCoordinate - 1;
		}
	}
}

// функция перемещения влево
// принимает символ персонажа или прицела, структуру с информацией об объекте на карте и массив ячеек карты
void game::moveLeft(char type, GameInfo* gameInfo, game::MapCell** map)
{
	switch (type)
	{
	case AIM_DOT:
		// если слева ячека карты проходима и в ней не герой
		if (map[gameInfo->aim.yCoordinate][gameInfo->aim.xCoordinate - 1].passable == true &&
			peek(map[gameInfo->aim.yCoordinate][gameInfo->aim.xCoordinate - 1].types) != HERO)
		{
			push(pop(map[gameInfo->aim.yCoordinate][gameInfo->aim.xCoordinate].types),	// пересонаж перемещается влево
				map[gameInfo->aim.yCoordinate][gameInfo->aim.xCoordinate - 1].types);

			gameInfo->aim.xCoordinate = gameInfo->aim.xCoordinate - 1;

		}
		break;

	case HERO:
		// если слева ячека карты проходима и в ней не прицел
		if (map[gameInfo->hero.yCoordinate][gameInfo->hero.xCoordinate - 1].passable == true &&
			peek(map[gameInfo->hero.yCoordinate][gameInfo->hero.xCoordinate - 1].types) != AIM_DOT)
		{
			push(pop(map[gameInfo->hero.yCoordinate][gameInfo->hero.xCoordinate].types),	// прицел перемещается влево
				map[gameInfo->hero.yCoordinate][gameInfo->hero.xCoordinate - 1].types);

			gameInfo->hero.xCoordinate = gameInfo->hero.xCoordinate - 1;
		}
		break;
	}
}

// функция перемещения вниз
// принимает символ персонажа или прицела, структуру с информацией об объекте на карте и массив ячеек карты
void game::moveRight(char type, GameInfo* gameInfo, game::MapCell** map)
{
	switch (type)
	{
	case AIM_DOT:
		// если справа ячека карты проходима и в ней не герой
		if (map[gameInfo->aim.yCoordinate][gameInfo->aim.xCoordinate + 1].passable == true &&
			peek(map[gameInfo->aim.yCoordinate][gameInfo->aim.xCoordinate + 1].types) != HERO)
		{
			push(pop(map[gameInfo->aim.yCoordinate][gameInfo->aim.xCoordinate].types),	// прицел перемещается вправо
				map[gameInfo->aim.yCoordinate][gameInfo->aim.xCoordinate + 1].types);

			gameInfo->aim.xCoordinate = gameInfo->aim.xCoordinate + 1;

		}
		break;

	case HERO:
		// если справа ячека карты проходима и в ней не прицел
		if (map[gameInfo->hero.yCoordinate][gameInfo->hero.xCoordinate + 1].passable == true &&
			peek(map[gameInfo->hero.yCoordinate][gameInfo->hero.xCoordinate + 1].types) != AIM_DOT)
		{
			push(pop(map[gameInfo->hero.yCoordinate][gameInfo->hero.xCoordinate].types),	// персонаж перемещается вправо
				map[gameInfo->hero.yCoordinate][gameInfo->hero.xCoordinate + 1].types);

			gameInfo->hero.xCoordinate = gameInfo->hero.xCoordinate + 1;
		}
		break;
	}
}

// функция перемещения вниз
// структуру с информацией об объекте на карте и массив ячеек карты
void game::moveUp(GameInfo* gameInfo, game::MapCell** map)
{
	// если сверху ячека карты проходима и в ней не герой
	if (map[gameInfo->aim.yCoordinate - 1][gameInfo->aim.xCoordinate].passable == true &&
		peek(map[gameInfo->aim.yCoordinate - 1][gameInfo->aim.xCoordinate].types) != HERO)
	{
		push(pop(map[gameInfo->aim.yCoordinate][gameInfo->aim.xCoordinate].types),	// прицел перемещается вверх
			map[gameInfo->aim.yCoordinate - 1][gameInfo->aim.xCoordinate].types);

		gameInfo->aim.yCoordinate = gameInfo->aim.yCoordinate - 1;
	}
}

// функция перемещения вниз
// структуру с информацией об объекте на карте и массив ячеек карты
void game::moveDown(GameInfo* gameInfo, game::MapCell** map)
{
	// если снизу ячека карты проходима и в ней не герой
	if (map[gameInfo->aim.yCoordinate + 1][gameInfo->aim.xCoordinate].passable == true &&
		peek(map[gameInfo->aim.yCoordinate + 1][gameInfo->aim.xCoordinate].types) != HERO)
	{
		push(pop(map[gameInfo->aim.yCoordinate][gameInfo->aim.xCoordinate].types),	// прицел перемещается вниз
			map[gameInfo->aim.yCoordinate + 1][gameInfo->aim.xCoordinate].types);

		gameInfo->aim.yCoordinate = gameInfo->aim.yCoordinate + 1;

	}
}

// функция перестановки прицела
// принимает структуру с информацией об объекте на карте и массив ячеек карты
void game::replaceTheAim(GameInfo* gameInfo, game::MapCell** map)
{
	// если ячека карты сверху пуста
	if (peek(map[gameInfo->aim.yCoordinate - 1][gameInfo->aim.xCoordinate].types) == EMPTY_SPACE)
	{
		moveUp(gameInfo, map);	// прицел перемещаяется вверх на одну ячейку карты
	}

	// если ячека карты снизу пуста
	else if (peek(map[gameInfo->aim.yCoordinate + 1][gameInfo->aim.xCoordinate].types) == EMPTY_SPACE)
	{
		moveDown(gameInfo, map);	// прицел перемещаяется вниз на одну ячейку карты
	}

	// если ячека карты слева пуста
	else if (peek(map[gameInfo->aim.yCoordinate][gameInfo->aim.xCoordinate - 1].types) == EMPTY_SPACE)
	{
		moveLeft(AIM_DOT, gameInfo, map);	// прицел перемещаяется влево на одну ячейку карты
	}

	// если ячека карты справа пуста
	else if (peek(map[gameInfo->aim.yCoordinate][gameInfo->aim.xCoordinate + 1].types) == EMPTY_SPACE)
	{
		moveRight(AIM_DOT, gameInfo, map);	// прицел перемещаяется вправо на одну ячейку карты
	}
}

//------Gravitation_Functions------//
// функция гравитации, принимает структуру с информацией об объекте на карте и массив ячеек карты
void game::gravity(game::MapCell** map, GameInfo* gameInfo)
{
	// если под персонажем нет непроходимого блока/объекта
	if (game::peek(map[gameInfo->hero.yCoordinate][gameInfo->hero.xCoordinate].types) == HERO &&
		map[gameInfo->hero.yCoordinate + 1][gameInfo->hero.xCoordinate].passable == true)
	{
		push(pop(map[gameInfo->hero.yCoordinate][gameInfo->hero.xCoordinate].types),
			map[gameInfo->hero.yCoordinate + 1][gameInfo->hero.xCoordinate].types);	// перемещение игрока вниз на одну ячейку карты

		gameInfo->hero.yCoordinate = gameInfo->hero.yCoordinate + 1;
	}
}

// функция запуска уровня, принимает на вход название файла с уровнем
// возвращает количество очков, набранное игроком
double game::startLevel(char* levelName)
{
	game::GameInfo* gameInfo = new GameInfo;

	game::MapCell** map = game::createMap(levelName, gameInfo); // Создаем двумерный массив структур, используя текстовый документ

	game::clearScreen(); // Чистим экран

	game::drawFrame(map, gameInfo); // Рисуем первый кадр

	game::performAnAction(gameInfo, map); // Выполняем далее в зависимости от действий игрока
	
	double score = gameInfo->hero.score;

	game::freeMemory(map, gameInfo); // Очищаем занятую память

	game::clearScreen(); // Чистим экран

	return score;
}

//-----Portals_Functions------//
// функция установки второго портала
// принимает на вход символ портала, структуру с информацией об объекте на карте и массив ячеек карты
void game::setPortal(char type, GameInfo* gameInfo, game::MapCell** map)
{
	if (type == RED_PORTAL)	// если устанавливется красный портал
	{
		if ((gameInfo->hero.xCoordinate != gameInfo->redPortal.xCoordinate) ||	// если персонаж и красный портал не находятся в одной клетке
			(gameInfo->hero.yCoordinate != gameInfo->redPortal.yCoordinate))
		{
			if (gameInfo->redPortal.yCoordinate != 0)	// если красный портал уже есть, то существующий красный портал исчезает
				pop(map[gameInfo->redPortal.yCoordinate][gameInfo->redPortal.xCoordinate].types);

			gameInfo->redPortal.xCoordinate = gameInfo->aim.xCoordinate; // координаты нового порталы приравниваются координатам прицела
			gameInfo->redPortal.yCoordinate = gameInfo->aim.yCoordinate;

			pop(map[gameInfo->aim.yCoordinate][gameInfo->aim.xCoordinate].types);
			push(RED_PORTAL, map[gameInfo->redPortal.yCoordinate][gameInfo->redPortal.xCoordinate].types);	// в стек последовательно записываются типы (текстуры объектов)
			push(AIM_DOT, map[gameInfo->aim.yCoordinate][gameInfo->aim.xCoordinate].types);
			replaceTheAim(gameInfo, map);	// прицел смещается с портала
		}
	}

	else if (type == BLUE_PORTAL) // если устанавливется синий портал
	{
		if ((gameInfo->hero.xCoordinate != gameInfo->bluePortal.xCoordinate) ||	// если персонаж и синий портал не находятся в одной клетке
			(gameInfo->hero.yCoordinate != gameInfo->bluePortal.yCoordinate))
		{
			if (gameInfo->bluePortal.yCoordinate != 0)	// если синий портал уже есть, то существующий синий портал исчезает
				pop(map[gameInfo->bluePortal.yCoordinate][gameInfo->bluePortal.xCoordinate].types);

			gameInfo->bluePortal.xCoordinate = gameInfo->aim.xCoordinate;	// координаты нового порталы приравниваются координатам прицела
			gameInfo->bluePortal.yCoordinate = gameInfo->aim.yCoordinate;

			pop(map[gameInfo->aim.yCoordinate][gameInfo->aim.xCoordinate].types);
			push(BLUE_PORTAL, map[gameInfo->bluePortal.yCoordinate][gameInfo->bluePortal.xCoordinate].types);	// в стек последовательно записываются типы (текстуры объектов)
			push(AIM_DOT, map[gameInfo->aim.yCoordinate][gameInfo->aim.xCoordinate].types);
			replaceTheAim(gameInfo, map);	// прицел смещается с портала
		}
	}
}

// функция перехода по порталам, принимает структуру с информацией об объекте на карте и массив ячеек карты
void game::enterThePortal(char type, GameInfo* gameInfo, MapCell** map)
{
	if (gameInfo->hero.xCoordinate == gameInfo->redPortal.xCoordinate &&	// если персонаж и красный портал в одной клетке
		gameInfo->hero.yCoordinate == gameInfo->redPortal.yCoordinate &&
		gameInfo->bluePortal.yCoordinate != 0 && gameInfo->bluePortal.xCoordinate != 0) // и второй портал существует
	{
		push(pop(map[gameInfo->hero.yCoordinate][gameInfo->hero.xCoordinate].types),
			map[gameInfo->bluePortal.yCoordinate][gameInfo->bluePortal.xCoordinate].types);	// герой перемещается по координатам второго портала
		gameInfo->hero.xCoordinate = gameInfo->bluePortal.xCoordinate;
		gameInfo->hero.yCoordinate = gameInfo->bluePortal.yCoordinate;
	}

	else if (gameInfo->hero.xCoordinate == gameInfo->bluePortal.xCoordinate && // если персонаж и синий портал в одной клетке
		gameInfo->hero.yCoordinate == gameInfo->bluePortal.yCoordinate &&
		gameInfo->bluePortal.yCoordinate != 0 && gameInfo->bluePortal.xCoordinate != 0)	// и второй портал существует
	{
		push(pop(map[gameInfo->hero.yCoordinate][gameInfo->hero.xCoordinate].types),
			map[gameInfo->redPortal.yCoordinate][gameInfo->redPortal.xCoordinate].types);	// герой перемещается по координатам второго портала
		gameInfo->hero.xCoordinate = gameInfo->redPortal.xCoordinate;
		gameInfo->hero.yCoordinate = gameInfo->redPortal.yCoordinate;
	}
}

//------Button_Functions------//
// функция активации клавиши, принимает структуру с информацией об объекте на карте и массив ячеек карты
void game::activateTheButton(GameInfo* gameInfo, MapCell** map)
{
	if (gameInfo->hero.xCoordinate == gameInfo->button.xCoordinate &&	// если персонаж и кнопка находятся в одной клетке
		gameInfo->hero.yCoordinate == gameInfo->button.yCoordinate)
	{
		map[gameInfo->blackWall.yCoordinate][gameInfo->blackWall.xCoordinate].passable = true;// непроходимая стена становится проходимой
		pop(map[gameInfo->blackWall.yCoordinate][gameInfo->blackWall.xCoordinate].types);	// на месте непроходимой стены отображается проходимая
	}
}

bool game::checkGameOverConditions(GameInfo* gameInfo, MapCell** map)
{
	if (gameInfo->hero.xCoordinate == gameInfo->exitFromLevel.xCoordinate &&	// если персонаж находится в одной клетке с выходом
		gameInfo->hero.yCoordinate == gameInfo->exitFromLevel.yCoordinate)
	{
		return false;
	}
	else
	{
		return true;
	}
}