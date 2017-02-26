#include "Gameplay.h"
#include "Map.h"
#include "Instruments.h"

//------Moving_Functions------//
void game::performAnAction(game::Map** map)
{
	while (true)
	{
		if (_kbhit())
		{
			int heroXCoordinate = findHeroXCoordinate(map);
			int heroYCoordinate = findHeroYCoordinate(map);
			int aimXCoordinate = findAimXCoordinate(map);
			int aimYCoordinate = findAimYCoordinate(map);
			switch (_getch())
			{
			case A_LOWER_CASE:
				if (map[heroYCoordinate][heroXCoordinate - 1].passable == true)
				{
					moveLeft(HERO, heroYCoordinate, heroXCoordinate, map);
				}
				break;

			case D_LOWER_CASE:
				if (map[heroYCoordinate][heroXCoordinate + 1].passable == true)
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
				jump(heroYCoordinate, heroXCoordinate, map);
				break;

			default:
				break;
			}
		}
		game::clearScreen();
		game::drawFrame(map);
	}
}

void game::jump(int heroYCoordinate, int heroXCoordinate, game::Map** map)
{
	if((map[heroYCoordinate - 1][heroXCoordinate].passable == true) && 
		(map[heroYCoordinate - 2][heroXCoordinate].passable == true))
	{
		map[heroYCoordinate][heroXCoordinate].type = EMPTY_SPACE;
		map[heroYCoordinate - 1][heroXCoordinate].type = HERO;
		map[heroYCoordinate - 1][heroXCoordinate].healthPoints = 
			map[heroXCoordinate][heroYCoordinate].healthPoints;

		drawFrame(map);

		map[heroYCoordinate - 1][heroXCoordinate].type = EMPTY_SPACE;
		map[heroYCoordinate - 2][heroXCoordinate].type = HERO;
		map[heroYCoordinate - 2][heroXCoordinate].healthPoints = 
			map[heroXCoordinate - 1][heroYCoordinate].healthPoints;
	}

	else if ((map[heroYCoordinate - 1][heroXCoordinate].passable == true) &&
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
	map[yCoordinate][xCoordinate].type = EMPTY_SPACE;
	map[yCoordinate][xCoordinate - 1].type = type;
}

void game::moveRight(char type, int yCoordinate, int xCoordinate, game::Map** map)
{
	map[yCoordinate][xCoordinate].type = EMPTY_SPACE;
	map[yCoordinate][xCoordinate + 1].type = type;
}


//------Aim_Functions------//
void game::moveAimLeft(char type, int aimYCoordinate, int aimXCoordinate, game::Map** map)
{
	map[aimYCoordinate][aimXCoordinate].type = EMPTY_SPACE;
	map[aimYCoordinate][aimXCoordinate - 1].type = type;
}

void game::moveAimRight(char type, int aimYCoordinate, int aimXCoordinate, game::Map** map)
{
	map[aimYCoordinate][aimXCoordinate].type = EMPTY_SPACE;
	map[aimYCoordinate][aimXCoordinate + 1].type = type;
}

void game::moveAimUp(char type, int aimYCoordinate, int aimXCoordinate, game::Map** map)
{
	map[aimYCoordinate][aimXCoordinate].type = EMPTY_SPACE;
	map[aimYCoordinate - 1][aimXCoordinate].type = type;
}

void game::moveAimDown(char type, int aimYCoordinate, int aimXCoordinate, game::Map** map)
{
	map[aimYCoordinate][aimXCoordinate].type = EMPTY_SPACE;
	map[aimYCoordinate + 1][aimXCoordinate].type = type;
}


//------Gravitation_Functions------//