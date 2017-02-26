#include "DistrOfDefine.h"
#include "Map.h"
#include "Instruments.h"

int game::findHeroYCoordinate(game::Map** map)
{
	for (int i = 0; i < MAP_HEIGHT; i++)
	{
		for (int j = 0; j < MAP_WIDTH; j++)
		{
			if (map[i][j].type == HERO) return i;
		}
	}
}

int game::findHeroXCoordinate(game::Map** map)
{
	for (int i = 0; i < MAP_HEIGHT; i++)
	{
		for (int j = 0; j < MAP_WIDTH; j++)
		{
			if (map[i][j].type == HERO) return j;
		}
	}
}

int game::findAimXCoordinate(game::Map** map)
{
	{
		for (int i = 0; i < MAP_HEIGHT; i++)
		{
			for (int j = 0; j < MAP_WIDTH; j++)
			{
				if (map[i][j].type == AIM_DOT) return j;
			}
		}
	}
}

int game::findAimYCoordinate(game::Map** map)
{
	{
		for (int i = 0; i < MAP_HEIGHT; i++)
		{
			for (int j = 0; j < MAP_WIDTH; j++)
			{
				if (map[i][j].type == AIM_DOT) return i;
			}
		}
	}
}


void game::drawFrame(game::Map** map)
{
	for (int i = 0; i < MAP_HEIGHT; i++)
	{
		for (int j = 0; j < MAP_WIDTH; j++)
		{
			switch (map[i][j].type)
			{
			case HERO:
				std::cout << HERO;
				break;

			case BLOCK:
				std::cout << BLOCK;
				break;

			case EMPTY_SPACE:
				std::cout << EMPTY_SPACE;
				break;

			case AIM_DOT:
				std::cout << AIM;
				break;

			default:
				break;
			}
		}
		std::cout << std::endl;
	}
}

void game::clearScreen() {
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
