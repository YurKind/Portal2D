#include "Instruments.h"
#include "Gameplay.h"
#include "Menu.h"

void game::drawFrame(game::MapCell** map, game::GameInfo* gameInfo)		// отрисовка карты, функция принимает в качетсве аргумета двумерный массив структур
{
	HANDLE consoleHandler = GetStdHandle(STD_OUTPUT_HANDLE);

	for (int i = 0; i < MAP_HEIGHT; i++)
	{
		for (int j = 0; j < MAP_WIDTH; j++)
		{
			switch (map[i][j].types->value)			// выражением служит тип текущего элемента массива (персонаж, блок и тд)
			{
			case HERO:						// если встречен тип "герой", то отрисовывается герой
				game::printSpecialSymbol(consoleHandler, i, j, LightGrey, HERO);
				break;

			case BLOCK:						// если встречен тип "блок", то отрисовывается блок
				game::printSpecialSymbol(consoleHandler, i, j, LightGrey, BLOCK);
				break;

			case EMPTY_SPACE:				// если встречен тип "_", то отрисовывается пустое пространство
				game::printSpecialSymbol(consoleHandler, i, j, Black, EMPTY_SPACE);
				break;

			case AIM_DOT:					// если встречен тип "прицел_точка", то отрисовывается прицел
				game::printSpecialSymbol(consoleHandler, i, j, LightGrey, AIM);
				break;

			case BLACK_WALL:				// если встречен тип "непроходимая стена", то отрисовывается непроходимая стена
				game::printSpecialSymbol(consoleHandler, i, j, Yellow, BLACK_WALL);
				break;

			case EXIT:					// если встречен тип "выход", то отрисовывается выход
				game::printSpecialSymbol(consoleHandler, i, j, LightGrey, EXIT);
				break;

			case RED_PORTAL:			// если встречен тип "красный портал", то отрисовывается красный портал
				game::printSpecialSymbol(consoleHandler, i, j, LightRed, RED_PORTAL);
				break;

			case BLUE_PORTAL:			// если встречен тип "синий портал", то отрисовывается синий портал 
				game::printSpecialSymbol(consoleHandler, i, j, LightBlue, BLUE_PORTAL);
				break;

			case BUTTON:				// если встречен тип "кнопка", то отрисовывается кнопка 
				game::printSpecialSymbol(consoleHandler, i, j, Yellow, BUTTON);
				break;

			case BULLET_OF_STATIONARY_TURRET:			// если встречен тип "пуля стационарной турели", то отрисовывается пуля стационарной турели
				game::printSpecialSymbol(consoleHandler, i, j, LightRed, BULLET_OF_STATIONARY_TURRET);
				break;

			case BULLET_OF_PLATFORM_TURRET:				// если встречен тип "пуля патрулирующей турели", то отрисовывается пуля стационарной турели
				game::printSpecialSymbol(consoleHandler, i, j, LightRed, BULLET_OF_STATIONARY_TURRET);
				break;

			case BULLET_OF_HUNTER_TURRET:				// если встречен тип "пуля турели-охотника", то отрисовывается пуля стационарной турели
				game::printSpecialSymbol(consoleHandler, i, j, LightRed, BULLET_OF_STATIONARY_TURRET);
				break;

			case STATIONARY_TURRET:		// если встречен тип "стационарная турель", то отрисовывается стационарная турель турель
				game::printSpecialSymbol(consoleHandler, i, j, LightGrey, STATIONARY_TURRET);
				break;

			case PLATFORM_TURRET:		// если встречен тип "турель на платформе", то отрисовывается турель на платформе 
				game::printSpecialSymbol(consoleHandler, i, j, LightGrey, PLATFORM_TURRET);
				break;

			case TURRET_HUNTER:			// если встречен тип "турель", то отрисовывается обычная турель 
				game::printSpecialSymbol(consoleHandler, i, j, LightGrey, TURRET_HUNTER);
				break;

			default:
				break;
			}
		}
		std::cout << std::endl;
	}
	// Вывод на экран информации о текущем здоровии и времени, затраченном на прохождение уровня
	std::cout << std::endl << "HP: " << gameInfo->hero.healthPoints << "\t\t\tTIME: " << gameInfo->hero.time;
}

// функция очистки экрана (позволяет избежать мерцания, как в случае с system("cls"))
void game::clearScreen()
{
	HANDLE Handle = nullptr;
	Handle = GetStdHandle(STD_OUTPUT_HANDLE);
	COORD Cursor;
	Cursor.X = 0;
	Cursor.Y = 0;
	SetConsoleCursorPosition(Handle, Cursor);
	CONSOLE_CURSOR_INFO structCursorInfo;
	GetConsoleCursorInfo(Handle, &structCursorInfo);
	structCursorInfo.bVisible = FALSE;
	SetConsoleCursorInfo(Handle, &structCursorInfo);
}

// Функция освобождения памяти
void game::freeMemory(game::MapCell** map, game::GameInfo* gameInfo)
{
	delete gameInfo; // Очищаем память, занятую информацией об игре

	// Очищаем память, занятую картой игры
	for (int i = 0; i < MAP_HEIGHT; i++)
	{
		delete map[i];
	}
	delete map;
}

// Функция отвечает за вывод на экран определенного символа с заданными цветом и позицией 
void game::printSpecialSymbol(HANDLE consoleHandler, int yCoordinate, int xCoordinate, int color, char symbol)
{
	CONSOLE_CURSOR_INFO cursorInfo;
	cursorInfo.bVisible = 0;
	cursorInfo.dwSize = 100;
	SetConsoleCursorInfo(consoleHandler, &cursorInfo);
	COORD coordinates;
	coordinates.X = xCoordinate;
	coordinates.Y = yCoordinate;
	SetConsoleCursorPosition(consoleHandler, coordinates);
	SetConsoleTextAttribute(consoleHandler, color);

	cout << symbol;
}

// Функция вычисляет счет игрока
double game::computeTheScore(GameInfo* gameInfo)
{
	double score = 1000 / gameInfo->hero.time;
	return score;
}

// Фукнция, отвечающая за вывод инструкции на экран
void game::showInstruction()
{
	char currentSymbol;
	ifstream fout("Instruction.txt", std::ios_base::in);
	while (!fout.eof())
	{
		currentSymbol = fout.get();

		switch (currentSymbol)
		{
		case HERO_SYMBOL:
			cout << HERO;
			break;

		case AIM_DOT:
			cout << AIM_DOT;
			break;

		case BLACK_WALL_S:
			cout << BLACK_WALL;
			break;

		case EXIT_S:
			std::cout << EXIT;
			break;

		case RED_PORTAL:
			cout << RED_PORTAL;
			break;

		case BUTTON_S:
			cout << BUTTON;
			break;

		case TURRET_HUNTER_S:
			cout << TURRET_HUNTER;
			break;

		case STATIONARY_TURRET_S:
			cout << STATIONARY_TURRET;
			break;

		case PLATFORM_TURRET_S:
			cout << PLATFORM_TURRET;
			break;

		case BULLET_OF_STATIONARY_TURRET:
			cout << BULLET_OF_STATIONARY_TURRET;
			break;

		case BULLET_OF_PLATFORM_TURRET:
			cout << BULLET_OF_PLATFORM_TURRET;
			break;

		default:
			cout << currentSymbol;
			break;
		}

	}
	fout.close();

	cout << endl << " PRESS ANY KEY TO CONTINUE" << endl;
	_getch();
}