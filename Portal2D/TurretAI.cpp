#include "TurretAI.h"
#include "Map.h"
#include "Definitions.h"

//void game::turretAI(GameInfo* gameInfo, MapCell** map)
//{
//	bool heroIsSpotted = false;
//	heroIsSpotted = spottingHero(gameInfo, map);
//	turretMoving(gameInfo, map, heroIsSpotted);
//	shootingToHero(gameInfo, map, heroIsSpotted);
//}

void game::turretPatrolAI(GameInfo* gameInfo, MapCell** map, bool *isMovingRight)
{
	bool heroIsSpotted = spottingHeroPatrol(gameInfo, map);
	bool isWallHere = checkTheWall(gameInfo, map);
	turretPatrol(gameInfo, map, heroIsSpotted, isMovingRight, &isWallHere);
	shootingToHeroPatrol(gameInfo, map, heroIsSpotted, &isWallHere);
}

bool game::spottingHeroPatrol(GameInfo* gameInfo, MapCell** map)
{
	bool heroIsSpotted = false;
	if (gameInfo->hero.yCoordinate == gameInfo->platform_turret.yCoordinate)
	{
		return true;
	}
	return false;
}

bool game::checkTheWall(GameInfo* gameInfo, MapCell** map)
{
	if (gameInfo->hero.yCoordinate == gameInfo->platform_turret.yCoordinate &&
		gameInfo->hero.xCoordinate > gameInfo->platform_turret.xCoordinate)
	{
		for (int i = gameInfo->platform_turret.xCoordinate; i < gameInfo->hero.xCoordinate; i++)
		{
			if (map[gameInfo->platform_turret.yCoordinate][i].passable == false)
			{
				return true;
			}
		}
	}
	else if (gameInfo->hero.yCoordinate == gameInfo->platform_turret.yCoordinate &&
		gameInfo->hero.xCoordinate < gameInfo->platform_turret.xCoordinate)
	{
		for (int i = gameInfo->platform_turret.xCoordinate; i > gameInfo->hero.xCoordinate; i--)
		{
			if (map[gameInfo->platform_turret.yCoordinate][i].passable == false)
			{
				return true;
			}
		}
	}
	return false;
}

void game::shootingToHeroPatrol(GameInfo* gameInfo, MapCell** map, bool heroIsSpotted, bool *isWallHere)
{
	if (*isWallHere == false)
	{
		if (gameInfo->hero.xCoordinate > gameInfo->platform_turret.xCoordinate)
		{
			if (heroIsSpotted == true && gameInfo->bullet.xCoordinate == 0 &&
				map[gameInfo->platform_turret.yCoordinate][gameInfo->platform_turret.xCoordinate + 1].passable == true)
			{
				gameInfo->bullet.xCoordinate = gameInfo->platform_turret.xCoordinate + 1;
				gameInfo->bullet.yCoordinate = gameInfo->platform_turret.yCoordinate;
				list::addBegin(&map[gameInfo->bullet.yCoordinate][gameInfo->bullet.xCoordinate].types, BULLET);
			}
		}
		else if (gameInfo->hero.xCoordinate < gameInfo->platform_turret.xCoordinate)
		{
			if (heroIsSpotted == true && gameInfo->bullet.xCoordinate == 0 &&
				map[gameInfo->platform_turret.yCoordinate][gameInfo->platform_turret.xCoordinate - 1].passable == true)
			{
				gameInfo->bullet.xCoordinate = gameInfo->platform_turret.xCoordinate - 1;
				gameInfo->bullet.yCoordinate = gameInfo->platform_turret.yCoordinate;
				list::addBegin(&map[gameInfo->bullet.yCoordinate][gameInfo->bullet.xCoordinate].types, BULLET);
			}
		}
		else if ((gameInfo->hero.xCoordinate == gameInfo->platform_turret.xCoordinate) &&
			(gameInfo->hero.yCoordinate == gameInfo->platform_turret.yCoordinate))
		{
			gameInfo->hero.healthPoints -= DAMAGE_TO_HERO;
		}
	}
	if (gameInfo->hero.xCoordinate > gameInfo->platform_turret.xCoordinate)
	{
		shootingToRight(gameInfo, map);
	}
	else if (gameInfo->hero.xCoordinate < gameInfo->platform_turret.xCoordinate)
	{
		shootingToLeft(gameInfo, map);
	}
}


void game::shootingToRight(GameInfo* gameInfo, MapCell** map)
{
	if (gameInfo->bullet.xCoordinate != 0)
	{
		if ((gameInfo->bullet.yCoordinate == gameInfo->hero.yCoordinate) && (gameInfo->bullet.xCoordinate == gameInfo->hero.xCoordinate))
		{
			gameInfo->hero.healthPoints -= DAMAGE_TO_HERO;
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

void game::shootingToLeft(GameInfo* gameInfo, MapCell** map)
{
	if (gameInfo->bullet.xCoordinate != 0)
	{
		if ((gameInfo->bullet.yCoordinate == gameInfo->hero.yCoordinate) && (gameInfo->bullet.xCoordinate == gameInfo->hero.xCoordinate))
		{
			gameInfo->hero.healthPoints -= DAMAGE_TO_HERO;
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

//void game::turretMoving(GameInfo* gameInfo, MapCell** map, bool heroIsSpotted)
//{
//	if (heroIsSpotted == true)
//	{
//		if (gameInfo->hero.xCoordinate > gameInfo->turret.xCoordinate + 4 &&
//			map[gameInfo->turret.yCoordinate][gameInfo->turret.xCoordinate + 1].passable == true)
//		{
//			moveRight(TURRET_EASY, gameInfo, map);
//		}
//		else if (gameInfo->hero.xCoordinate > gameInfo->turret.xCoordinate + 4 &&
//			map[gameInfo->turret.yCoordinate][gameInfo->turret.xCoordinate + 1].passable == false)
//		{
//			//jump(TURRET_EASY, gameInfo, map);
//			moveRight(TURRET_EASY, gameInfo, map);
//		}
//		else if (gameInfo->hero.xCoordinate < gameInfo->turret.xCoordinate - 4 &&
//			map[gameInfo->turret.yCoordinate][gameInfo->turret.xCoordinate - 1].passable == true)
//		{
//			moveLeft(TURRET_EASY, gameInfo, map);
//		}
//		else if (gameInfo->hero.xCoordinate < gameInfo->turret.xCoordinate - 4 &&
//			map[gameInfo->turret.yCoordinate][gameInfo->turret.xCoordinate - 1].passable == false)
//		{
//			//jump(TURRET_EASY, gameInfo, map);
//			moveLeft(TURRET_EASY, gameInfo, map);
//		}
//	}
//}

void game::turretPatrol(GameInfo* gameInfo, MapCell** map, bool heroIsSpotted, bool *isMovingRight, bool *isWallHere)
{
	if (heroIsSpotted == false || *isWallHere == true)
	{
		if (map[gameInfo->platform_turret.yCoordinate][gameInfo->platform_turret.xCoordinate + 1].passable == true && *isMovingRight == true)
		{
			moveRight(PLATFORM_TURRET, gameInfo, map);
			*isMovingRight = true;
		}
		else if (map[gameInfo->platform_turret.yCoordinate][gameInfo->platform_turret.xCoordinate - 1].passable == true && *isMovingRight == false)
		{
			moveLeft(PLATFORM_TURRET, gameInfo, map);
			*isMovingRight = false;
		}
		else if (map[gameInfo->platform_turret.yCoordinate][gameInfo->platform_turret.xCoordinate + 1].passable == false)
		{
			*isMovingRight = false;
			moveLeft(PLATFORM_TURRET, gameInfo, map);
		}
		else if (map[gameInfo->platform_turret.yCoordinate][gameInfo->platform_turret.xCoordinate - 1].passable == false)
		{
			*isMovingRight = true;
			moveRight(PLATFORM_TURRET, gameInfo, map);
		}
	}
}

//bool game::spottingHero(GameInfo* gameInfo, MapCell** map)
//{
//	bool heroIsSpotted = false;
//	for (int i = gameInfo->turret.xCoordinate - HERO_SPOTTING_RANGE_X; i < gameInfo->turret.xCoordinate + HERO_SPOTTING_RANGE_X; i++)
//	{
//		for (int j = gameInfo->turret.yCoordinate + HERO_SPOTTING_RANGE_Y; j > gameInfo->turret.yCoordinate - HERO_SPOTTING_RANGE_Y; j--)
//		{
//			if ((gameInfo->hero.xCoordinate == i) && (gameInfo->hero.yCoordinate == j))
//			{
//				return heroIsSpotted = true;
//			}
//		}
//	}
//	return false;
//}

//void game::shootingToHero(GameInfo* gameInfo, MapCell** map, bool heroIsSpotted)
//{
//	if (gameInfo->hero.xCoordinate > gameInfo->turret.xCoordinate)
//	{
//		if (gameInfo->hero.yCoordinate == gameInfo->turret.yCoordinate && heroIsSpotted == true &&
//			gameInfo->bullet.xCoordinate == 0 &&
//			map[gameInfo->turret.yCoordinate][gameInfo->turret.xCoordinate + 1].passable == true)
//		{
//			gameInfo->bullet.xCoordinate = gameInfo->turret.xCoordinate + 1;
//			gameInfo->bullet.yCoordinate = gameInfo->turret.yCoordinate;
//			list::addBegin(&map[gameInfo->bullet.yCoordinate][gameInfo->bullet.xCoordinate].types, BULLET);
//
//		}
//		else if (gameInfo->hero.yCoordinate == gameInfo->turret.yCoordinate && heroIsSpotted == true &&
//			gameInfo->bullet.xCoordinate == 0 &&
//			map[gameInfo->turret.yCoordinate][gameInfo->turret.xCoordinate + 1].passable == false)
//		{
//			turretMoving(gameInfo, map, heroIsSpotted);
//		}
//
//		else if ((gameInfo->bullet.xCoordinate != 0) && (heroIsSpotted == true))
//		{
//			if ((gameInfo->bullet.yCoordinate == gameInfo->hero.yCoordinate) && (gameInfo->bullet.xCoordinate == gameInfo->hero.xCoordinate))
//			{
//				gameInfo->hero.healthPoints -= DAMAGE_TO_HERO;
//				list::deleteCurrentElement(&map[gameInfo->bullet.yCoordinate][gameInfo->bullet.xCoordinate].types, BULLET);
//				gameInfo->bullet.xCoordinate = 0;
//			}
//			else if (map[gameInfo->bullet.yCoordinate][gameInfo->bullet.xCoordinate + 1].passable == true)
//			{
//				moveRight(BULLET, gameInfo, map);
//			}
//			else if (map[gameInfo->bullet.yCoordinate][gameInfo->bullet.xCoordinate + 1].passable == false)
//			{
//				list::deleteCurrentElement(&map[gameInfo->bullet.yCoordinate][gameInfo->bullet.xCoordinate].types, BULLET);
//				gameInfo->bullet.xCoordinate = 0;
//			}
//		}
//	}
//	else if (gameInfo->hero.xCoordinate < gameInfo->turret.xCoordinate)
//	{
//		if (gameInfo->hero.yCoordinate == gameInfo->turret.yCoordinate && heroIsSpotted == true &&
//			gameInfo->bullet.xCoordinate == 0 &&
//			map[gameInfo->turret.yCoordinate][gameInfo->turret.xCoordinate - 1].passable == true)
//		{
//			gameInfo->bullet.xCoordinate = gameInfo->turret.xCoordinate - 1;
//			gameInfo->bullet.yCoordinate = gameInfo->turret.yCoordinate;
//			list::addBegin(&map[gameInfo->bullet.yCoordinate][gameInfo->bullet.xCoordinate].types, BULLET);
//
//		}
//
//		else if (gameInfo->hero.yCoordinate == gameInfo->turret.yCoordinate && heroIsSpotted == true &&
//			gameInfo->bullet.xCoordinate == 0 &&
//			map[gameInfo->turret.yCoordinate][gameInfo->turret.xCoordinate - 1].passable == false)
//		{
//			turretMoving(gameInfo, map, heroIsSpotted);
//		}
//
//		else if ((gameInfo->bullet.xCoordinate != 0) && (heroIsSpotted == true))
//		{
//			if ((gameInfo->bullet.yCoordinate == gameInfo->hero.yCoordinate) && (gameInfo->bullet.xCoordinate == gameInfo->hero.xCoordinate))
//			{
//				gameInfo->hero.healthPoints -= DAMAGE_TO_HERO;
//				list::deleteCurrentElement(&map[gameInfo->bullet.yCoordinate][gameInfo->bullet.xCoordinate].types, BULLET);
//				gameInfo->bullet.xCoordinate = 0;
//			}
//			else if (map[gameInfo->bullet.yCoordinate][gameInfo->bullet.xCoordinate - 1].passable == true)
//			{
//				moveLeft(BULLET, gameInfo, map);
//			}
//			else if (map[gameInfo->bullet.yCoordinate][gameInfo->bullet.xCoordinate - 1].passable == false)
//			{
//				list::deleteCurrentElement(&map[gameInfo->bullet.yCoordinate][gameInfo->bullet.xCoordinate].types, BULLET);
//				gameInfo->bullet.xCoordinate = 0;
//			}
//		}
//	}
//	else if ((gameInfo->hero.xCoordinate == gameInfo->turret.xCoordinate) && (gameInfo->hero.yCoordinate == gameInfo->turret.yCoordinate))
//	{
//		gameInfo->hero.healthPoints -= DAMAGE_TO_HERO;
//	}
//}