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
				/*std::cout << HERO;*/
				break;

			case BLOCK:						// если встречен тип "блок", то отрисовывается блок
				game::printSpecialSymbol(consoleHandler, i, j, LightGrey, BLOCK);
				/*std::cout << BLOCK;*/
				break;

			case EMPTY_SPACE:				// если встречен тип "_", то отрисовывается пустое пространство
				game::printSpecialSymbol(consoleHandler, i, j, Black, EMPTY_SPACE);
				/*std::cout << EMPTY_SPACE;*/
				break;

			case AIM_DOT:					// если встречен тип "прицел_точка", то отрисовывается прицел
				game::printSpecialSymbol(consoleHandler, i, j, LightGrey, AIM);
				/*std::cout << AIM;*/
				break;

			case BLACK_WALL:				// если встречен тип "непроходимая стена", то отрисовывается непроходимая стена
				game::printSpecialSymbol(consoleHandler, i, j, Yellow, BLACK_WALL);
				/*std::cout << BLACK_WALL;*/
				break;

			case EXIT:					// если встречен тип "выход", то отрисовывается выход
				game::printSpecialSymbol(consoleHandler, i, j, LightGrey, EXIT);
				/*std::cout << EXIT;*/
				break;

			case RED_PORTAL:			// если встречен тип "красный портал", то отрисовывается красный портал
				game::printSpecialSymbol(consoleHandler, i, j, LightRed, RED_PORTAL);
				/*std::cout << RED_PORTAL;*/
				break;

			case BLUE_PORTAL:			// если встречен тип "синий портал", то отрисовывается синий портал 
				game::printSpecialSymbol(consoleHandler, i, j, LightBlue, BLUE_PORTAL);
				/*std::cout << BLUE_PORTAL;*/
				break;

			case BUTTON:
				game::printSpecialSymbol(consoleHandler, i, j, Yellow, BUTTON);
				/*std::cout << BUTTON;*/
				break;
			case TURRET:
				game::printSpecialSymbol(consoleHandler, i, j, LightGrey, TURRET);
				break;

			default:
				break;
			}
		}
		std::cout << std::endl;
	}
	std::cout << std::endl << "HP: " << gameInfo->hero.healthPoints << "\t\t\tTIME: " << gameInfo->hero.time;
}

void game::clearScreen()		// функция очистки консоли (без мерцания)
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

void game::freeMemory(game::MapCell** map, game::GameInfo* gameInfo)
{
	delete gameInfo;
	
	for(int i = 0; i < MAP_HEIGHT; i++)
	{
		delete map[i];
	}
	
	delete map;
}

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

double game::computeTheScore(GameInfo* gameInfo)
{
	double score = 1000 / gameInfo->hero.time;
	return score;
}

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
			std::cout << AIM;
			break;

		case BLACK_WALL_S:
			std::cout << BLACK_WALL;
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

		default:
			cout << currentSymbol;
			break;
		}

	}
	fout.close();

	cout << endl << " PRESS ANY KEY TO CONTINUE" << endl;
	_getch();
}