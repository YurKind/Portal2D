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