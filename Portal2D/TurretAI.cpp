#include "TurretAI.h"
#include "Map.h"
#include "Definitions.h"


void game::turretAI(GameInfo* gameInfo, MapCell** map)
{
	bool heroIsSpotted = false;
	heroIsSpotted = spottingHero(gameInfo, map);
	turretMoving(gameInfo, map, heroIsSpotted);
	shootingToHero(gameInfo, map, heroIsSpotted);
}

bool game::spottingHero(GameInfo* gameInfo, MapCell** map)
{
	bool heroIsSpotted = false;
	for (int i = gameInfo->turret.xCoordinate - 10; i < gameInfo->turret.xCoordinate + 10; i++)
	{
		for (int j = gameInfo->turret.yCoordinate + 5; j > gameInfo->turret.yCoordinate - 10; j--)
		{
			if ((gameInfo->hero.xCoordinate == i) && (gameInfo->hero.yCoordinate == j))
			{
				return heroIsSpotted = true;
			}
		}
	}
}

void game::turretMoving(GameInfo* gameInfo, MapCell** map, bool heroIsSpotted)
{
	if (heroIsSpotted == true)
	{
		if (gameInfo->hero.xCoordinate > gameInfo->turret.xCoordinate + 4 &&
			map[gameInfo->turret.yCoordinate][gameInfo->turret.xCoordinate + 1].passable == true)
		{
			moveRight(TURRET, gameInfo, map);
		}
		else if (gameInfo->hero.xCoordinate > gameInfo->turret.xCoordinate + 4 &&
			map[gameInfo->turret.yCoordinate][gameInfo->turret.xCoordinate + 1].passable == false)
		{
			jump(TURRET, gameInfo, map);
			moveRight(TURRET, gameInfo, map);
		}
		else if (gameInfo->hero.xCoordinate < gameInfo->turret.xCoordinate - 4 &&
			map[gameInfo->turret.yCoordinate][gameInfo->turret.xCoordinate - 1].passable == true)
		{
			moveLeft(TURRET, gameInfo, map);
		}
		else if (gameInfo->hero.xCoordinate < gameInfo->turret.xCoordinate - 4 &&
			map[gameInfo->turret.yCoordinate][gameInfo->turret.xCoordinate - 1].passable == false)
		{
			jump(TURRET, gameInfo, map);
			moveLeft(TURRET, gameInfo, map);
		}
	}
}

void game::shootingToHero(GameInfo* gameInfo, MapCell** map, bool heroIsSpotted)
{
	if (gameInfo->hero.xCoordinate > gameInfo->turret.xCoordinate)
	{
		if (gameInfo->hero.yCoordinate == gameInfo->turret.yCoordinate && heroIsSpotted == true &&
			gameInfo->bullet.xCoordinate == 0 &&
			map[gameInfo->turret.yCoordinate][gameInfo->turret.xCoordinate + 1].passable == true)
		{
			gameInfo->bullet.xCoordinate = gameInfo->turret.xCoordinate + 1;
			gameInfo->bullet.yCoordinate = gameInfo->turret.yCoordinate;
			list::addBegin(&map[gameInfo->bullet.yCoordinate][gameInfo->bullet.xCoordinate].types, BULLET);

		}
		else if (gameInfo->hero.yCoordinate == gameInfo->turret.yCoordinate && heroIsSpotted == true &&
			gameInfo->bullet.xCoordinate == 0 &&
			map[gameInfo->turret.yCoordinate][gameInfo->turret.xCoordinate + 1].passable == false)
		{
			turretMoving(gameInfo, map, heroIsSpotted);
		}

		else if ((gameInfo->bullet.xCoordinate != 0) && (heroIsSpotted == true))
		{
			if ((gameInfo->bullet.yCoordinate == gameInfo->hero.yCoordinate) && (gameInfo->bullet.xCoordinate == gameInfo->hero.xCoordinate))
			{
				gameInfo->hero.healthPoints = gameInfo->hero.healthPoints - 33;
				list::deleteCurrentElement(&map[gameInfo->bullet.yCoordinate][gameInfo->bullet.xCoordinate].types, BULLET);
				gameInfo->bullet.xCoordinate = 0;
			}
			else if (map[gameInfo->bullet.yCoordinate][gameInfo->bullet.xCoordinate + 1].passable == true)
			{
				moveRight(BULLET, gameInfo, map);
			}
			else if (map[gameInfo->bullet.yCoordinate][gameInfo->bullet.xCoordinate + 1].passable == false)
			{
				list::deleteCurrentElement(&map[gameInfo->bullet.yCoordinate][gameInfo->bullet.xCoordinate].types, BULLET);
				gameInfo->bullet.xCoordinate = 0;
			}
		}
	}
	else if (gameInfo->hero.xCoordinate < gameInfo->turret.xCoordinate)
	{
		if (gameInfo->hero.yCoordinate == gameInfo->turret.yCoordinate && heroIsSpotted == true &&
			gameInfo->bullet.xCoordinate == 0 &&
			map[gameInfo->turret.yCoordinate][gameInfo->turret.xCoordinate - 1].passable == true)
		{
			gameInfo->bullet.xCoordinate = gameInfo->turret.xCoordinate - 1;
			gameInfo->bullet.yCoordinate = gameInfo->turret.yCoordinate;
			list::addBegin(&map[gameInfo->bullet.yCoordinate][gameInfo->bullet.xCoordinate].types, BULLET);

		}

		else if(gameInfo->hero.yCoordinate == gameInfo->turret.yCoordinate && heroIsSpotted == true &&
			gameInfo->bullet.xCoordinate == 0 &&
			map[gameInfo->turret.yCoordinate][gameInfo->turret.xCoordinate - 1].passable == false)
		{
			turretMoving(gameInfo, map, heroIsSpotted);
		}

		else if ((gameInfo->bullet.xCoordinate != 0) && (heroIsSpotted == true))
		{
			if ((gameInfo->bullet.yCoordinate == gameInfo->hero.yCoordinate) && (gameInfo->bullet.xCoordinate == gameInfo->hero.xCoordinate))
			{
				gameInfo->hero.healthPoints = gameInfo->hero.healthPoints - 33;
				list::deleteCurrentElement(&map[gameInfo->bullet.yCoordinate][gameInfo->bullet.xCoordinate].types, BULLET);
				gameInfo->bullet.xCoordinate = 0;
			}
			else if (map[gameInfo->bullet.yCoordinate][gameInfo->bullet.xCoordinate - 1].passable == true)
			{
				moveLeft(BULLET, gameInfo, map);
			}
			else if (map[gameInfo->bullet.yCoordinate][gameInfo->bullet.xCoordinate - 1].passable == false)
			{
				list::deleteCurrentElement(&map[gameInfo->bullet.yCoordinate][gameInfo->bullet.xCoordinate].types, BULLET);
				gameInfo->bullet.xCoordinate = 0;
			}
		}
	}
	else if ((gameInfo->hero.xCoordinate == gameInfo->turret.xCoordinate) && (gameInfo->hero.yCoordinate == gameInfo->turret.yCoordinate))
	{
		gameInfo->hero.healthPoints = gameInfo->hero.healthPoints - 33;
	}
}