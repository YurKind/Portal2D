#include "TurretsAI.h"
#include "Map.h"
#include "Definitions.h"

void game::TurretAI(char type, GameInfo* gameInfo, MapCell** map)
{
	if (type == STATIONARY_TURRET)
	{
		int step = determinePositionOfHero(STATIONARY_TURRET, gameInfo, map);
		bool turretCanShootingToHero = checkTurretShotConditions(STATIONARY_TURRET, gameInfo, map, step);
		shootingToHero(STATIONARY_TURRET, gameInfo, map, turretCanShootingToHero, step);
	}
	else if (type == PLATFORM_TURRET)
	{
		int step = determinePositionOfHero(PLATFORM_TURRET, gameInfo, map);
		bool turretCanShootingToHero = checkTurretShotConditions(PLATFORM_TURRET, gameInfo, map, step);
		platformTurretPatrol(gameInfo, map, turretCanShootingToHero, step);
		shootingToHero(PLATFORM_TURRET, gameInfo, map, turretCanShootingToHero, step);
	}
	else if (type == TURRET_HUNTER)
	{
		int step = determinePositionOfHero(TURRET_HUNTER, gameInfo, map);
		bool turretCanShootingToHero = checkTurretShotConditions(TURRET_HUNTER, gameInfo, map, step);
		turretHunterMoving(gameInfo, map, turretCanShootingToHero, step);
		shootingToHero(TURRET_HUNTER, gameInfo, map, turretCanShootingToHero, step);
	}
}

int game::determinePositionOfHero(char type, GameInfo* gameInfo, MapCell** map)
{
	if (type == STATIONARY_TURRET)
	{
		if (gameInfo->hero.xCoordinate > gameInfo->stationary_turret.xCoordinate)
		{
			return 1;
		}
		else if (gameInfo->hero.xCoordinate < gameInfo->stationary_turret.xCoordinate)
		{
			return -1;
		}
		else
		{
			return 0;
		}
	}

	else if (type == PLATFORM_TURRET)
	{
		if (gameInfo->hero.xCoordinate > gameInfo->platform_turret.xCoordinate)
		{
			return 1;
		}
		else if (gameInfo->hero.xCoordinate < gameInfo->platform_turret.xCoordinate)
		{
			return -1;
		}
		else
		{
			return 1;
		}
	}

	else if (type == TURRET_HUNTER)
	{
		if (gameInfo->hero.xCoordinate > gameInfo->hunter_turret.xCoordinate)
		{
			return 1;
		}
		else if (gameInfo->hero.xCoordinate < gameInfo->hunter_turret.xCoordinate)
		{
			return -1;
		}
		else
		{
			return 0;
		}
	}
}

bool game::checkTurretShotConditions(char type, GameInfo* gameInfo, MapCell** map, int step)
{
	if (type == STATIONARY_TURRET)
	{
		bool wallIsHere = false;
		int searcher = gameInfo->stationary_turret.xCoordinate;
		if (step != 0 &&
			gameInfo->hero.yCoordinate == gameInfo->stationary_turret.yCoordinate)
		{
			while (gameInfo->hero.xCoordinate != searcher && wallIsHere == false)
			{
				if (map[gameInfo->stationary_turret.yCoordinate][searcher + step].types->value == HERO)
				{
					wallIsHere = false;
					searcher = searcher + step;
				}
				else if (map[gameInfo->stationary_turret.yCoordinate][searcher + step].types->value != BLOCK)
				{
					searcher = searcher + step;
				}
				else if (map[gameInfo->stationary_turret.yCoordinate][searcher + step].types->value == BLOCK)
				{
					wallIsHere = true;
				}
			}
			return !wallIsHere;
		}
		else if (step == 0)
		{
			return wallIsHere;
		}
		else
		{
			return wallIsHere;
		}
	}
	else if (type == PLATFORM_TURRET)
	{
		bool wallIsHere = false;
		int searcher = gameInfo->platform_turret.xCoordinate;
		if (step != 0 &&
			gameInfo->hero.yCoordinate == gameInfo->platform_turret.yCoordinate)
		{
			while (gameInfo->hero.xCoordinate != searcher && wallIsHere == false)
			{
				if (map[gameInfo->platform_turret.yCoordinate][searcher + step].types->value == HERO)
				{
					wallIsHere = false;
					searcher = searcher + step;
				}
				else if (map[gameInfo->platform_turret.yCoordinate][searcher + step].types->value != BLOCK)
				{
					searcher = searcher + step;
				}
				else if (map[gameInfo->platform_turret.yCoordinate][searcher + step].types->value == BLOCK)
				{
					wallIsHere = true;
				}
			}
			return !wallIsHere;
		}
		else if (step == 0)
		{
			return wallIsHere;
		}
		else
		{
			return wallIsHere;
		}
	}
	else if (type == TURRET_HUNTER)
	{
		bool wallIsHere = false;
		int searcher = gameInfo->hunter_turret.xCoordinate;
		if (step != 0 &&
			gameInfo->hero.yCoordinate == gameInfo->hunter_turret.yCoordinate)
		{
			while (gameInfo->hero.xCoordinate != searcher && wallIsHere == false)
			{
				if (map[gameInfo->hunter_turret.yCoordinate][searcher + step].types->value == HERO)
				{
					wallIsHere = false;
					searcher = searcher + step;
				}
				else if (map[gameInfo->hunter_turret.yCoordinate][searcher + step].types->value != BLOCK)
				{
					searcher = searcher + step;
				}
				else if (map[gameInfo->hunter_turret.yCoordinate][searcher + step].types->value == BLOCK)
				{
					wallIsHere = true;
				}
			}
			return !wallIsHere;
		}
		else if (step == 0)
		{
			return wallIsHere;
		}
		else
		{
			return wallIsHere;
		}
	}
}

void game::shootingToHero(char type, GameInfo* gameInfo, MapCell** map, bool turretCanShootingToHero, int step)
{
	if (type == STATIONARY_TURRET)
	{
		if (map[gameInfo->stationary_turret.yCoordinate][gameInfo->stationary_turret.xCoordinate + step].passable == true &&
			gameInfo->bulletOfStationaryTurret.xCoordinate == 0 && turretCanShootingToHero == true)
		{
			gameInfo->bulletOfStationaryTurret.xCoordinate = gameInfo->stationary_turret.xCoordinate + step;
			gameInfo->bulletOfStationaryTurret.yCoordinate = gameInfo->stationary_turret.yCoordinate;
			list::addBegin(&map[gameInfo->bulletOfStationaryTurret.yCoordinate][gameInfo->bulletOfStationaryTurret.xCoordinate].types, BULLET_OF_STATIONARY_TURRET);
		}

		else if (gameInfo->bulletOfStationaryTurret.xCoordinate != 0 && step != 0)
		{
			if ((gameInfo->bulletOfStationaryTurret.yCoordinate == gameInfo->hero.yCoordinate) &&
				(gameInfo->bulletOfStationaryTurret.xCoordinate == gameInfo->hero.xCoordinate))
			{
				gameInfo->hero.healthPoints -= DAMAGE_TO_HERO; // отнимается здоровье игрока
				// удаляется текстура пули
				list::deleteCurrentElement(&map[gameInfo->bulletOfStationaryTurret.yCoordinate][gameInfo->bulletOfStationaryTurret.xCoordinate].types, BULLET_OF_STATIONARY_TURRET);
				// пуля исчезает
				gameInfo->bulletOfStationaryTurret.xCoordinate = 0;
			}
			else if (map[gameInfo->bulletOfStationaryTurret.yCoordinate][gameInfo->bulletOfStationaryTurret.xCoordinate + step].passable == true)
			{
				moveBullet(BULLET_OF_STATIONARY_TURRET, gameInfo, map, step);
			}

			else if (map[gameInfo->bulletOfStationaryTurret.yCoordinate][gameInfo->bulletOfStationaryTurret.xCoordinate + step].passable == false)
			{
				// удаляется текстура пули
				list::deleteCurrentElement(&map[gameInfo->bulletOfStationaryTurret.yCoordinate][gameInfo->bulletOfStationaryTurret.xCoordinate].types, BULLET_OF_STATIONARY_TURRET);
				// пуля исчезает
				gameInfo->bulletOfStationaryTurret.xCoordinate = 0;
			}
		}

		else if (step == 0 && gameInfo->hero.yCoordinate == gameInfo->stationary_turret.yCoordinate)
		{
			gameInfo->hero.healthPoints -= DAMAGE_TO_HERO;	// у героя отнимается здоровье
		}

		else if (turretCanShootingToHero == false && gameInfo->bulletOfStationaryTurret.xCoordinate != 0)
		{
			moveBullet(BULLET_OF_STATIONARY_TURRET, gameInfo, map, step);
		}
	}
	else if (type == PLATFORM_TURRET)
	{

		if (map[gameInfo->platform_turret.yCoordinate][gameInfo->platform_turret.xCoordinate + step].passable == true &&
			gameInfo->bulletOfPlatformTurret.xCoordinate == 0 && turretCanShootingToHero == true)
		{
			gameInfo->bulletOfPlatformTurret.xCoordinate = gameInfo->platform_turret.xCoordinate + step;
			gameInfo->bulletOfPlatformTurret.yCoordinate = gameInfo->platform_turret.yCoordinate;
			list::addBegin(&map[gameInfo->bulletOfPlatformTurret.yCoordinate][gameInfo->bulletOfPlatformTurret.xCoordinate].types, BULLET_OF_PLATFORM_TURRET);
		}

		else if (gameInfo->bulletOfPlatformTurret.xCoordinate != 0 && step != 0)
		{
			if ((gameInfo->bulletOfPlatformTurret.yCoordinate == gameInfo->hero.yCoordinate) &&
				(gameInfo->bulletOfPlatformTurret.xCoordinate == gameInfo->hero.xCoordinate))
			{
				gameInfo->hero.healthPoints -= DAMAGE_TO_HERO; // отнимается здоровье игрока
				// удаляется текстура пули
				list::deleteCurrentElement(&map[gameInfo->bulletOfPlatformTurret.yCoordinate][gameInfo->bulletOfPlatformTurret.xCoordinate].types, BULLET_OF_PLATFORM_TURRET);
				// пуля исчезает
				gameInfo->bulletOfPlatformTurret.xCoordinate = 0;
			}
			else if (map[gameInfo->bulletOfPlatformTurret.yCoordinate][gameInfo->bulletOfPlatformTurret.xCoordinate + step].passable == true)
			{
				moveBullet(BULLET_OF_PLATFORM_TURRET, gameInfo, map, step);
			}

			else if (map[gameInfo->bulletOfPlatformTurret.yCoordinate][gameInfo->bulletOfPlatformTurret.xCoordinate + step].passable == false)
			{
				// удаляется текстура пули
				list::deleteCurrentElement(&map[gameInfo->bulletOfPlatformTurret.yCoordinate][gameInfo->bulletOfPlatformTurret.xCoordinate].types, BULLET_OF_PLATFORM_TURRET);
				// пуля исчезает
				gameInfo->bulletOfPlatformTurret.xCoordinate = 0;
			}
		}
		else if (gameInfo->hero.xCoordinate == gameInfo->platform_turret.xCoordinate &&
			gameInfo->hero.yCoordinate == gameInfo->platform_turret.yCoordinate)
		{
			gameInfo->hero.healthPoints -= DAMAGE_TO_HERO;	// у героя отнимается здоровье
		}

		else if (turretCanShootingToHero == false && gameInfo->bulletOfPlatformTurret.xCoordinate != 0)
		{
			moveBullet(BULLET_OF_PLATFORM_TURRET, gameInfo, map, step);
		}
	}

	else if (type == TURRET_HUNTER)
	{

		if (map[gameInfo->hunter_turret.yCoordinate][gameInfo->hunter_turret.xCoordinate + step].passable == true &&
			gameInfo->bulletOfHunterTurret.xCoordinate == 0 && turretCanShootingToHero == true)
		{
			gameInfo->bulletOfHunterTurret.xCoordinate = gameInfo->hunter_turret.xCoordinate + step;
			gameInfo->bulletOfHunterTurret.yCoordinate = gameInfo->hunter_turret.yCoordinate;
			list::addBegin(&map[gameInfo->bulletOfHunterTurret.yCoordinate][gameInfo->bulletOfHunterTurret.xCoordinate].types, BULLET_OF_HUNTER_TURRET);
		}

		else if (gameInfo->bulletOfHunterTurret.xCoordinate != 0 && step != 0)
		{
			if ((gameInfo->bulletOfHunterTurret.yCoordinate == gameInfo->hero.yCoordinate) &&
				(gameInfo->bulletOfHunterTurret.xCoordinate == gameInfo->hero.xCoordinate))
			{
				gameInfo->hero.healthPoints -= DAMAGE_TO_HERO; // отнимается здоровье игрока
															   // удаляется текстура пули
				list::deleteCurrentElement(&map[gameInfo->bulletOfHunterTurret.yCoordinate][gameInfo->bulletOfHunterTurret.xCoordinate].types, BULLET_OF_HUNTER_TURRET);
				// пуля исчезает
				gameInfo->bulletOfHunterTurret.xCoordinate = 0;
			}
			else if (map[gameInfo->bulletOfHunterTurret.yCoordinate][gameInfo->bulletOfHunterTurret.xCoordinate + step].passable == true)
			{
				moveBullet(BULLET_OF_HUNTER_TURRET, gameInfo, map, step);
			}

			else if (map[gameInfo->bulletOfHunterTurret.yCoordinate][gameInfo->bulletOfHunterTurret.xCoordinate + step].passable == false)
			{
				// удаляется текстура пули
				list::deleteCurrentElement(&map[gameInfo->bulletOfHunterTurret.yCoordinate][gameInfo->bulletOfHunterTurret.xCoordinate].types, BULLET_OF_HUNTER_TURRET);
				// пуля исчезает
				gameInfo->bulletOfHunterTurret.xCoordinate = 0;
			}
		}
		else if (gameInfo->hero.xCoordinate == gameInfo->hunter_turret.xCoordinate &&
			gameInfo->hero.yCoordinate == gameInfo->hunter_turret.yCoordinate)
		{
			gameInfo->hero.healthPoints -= DAMAGE_TO_HERO;	// у героя отнимается здоровье
		}

		else if (turretCanShootingToHero == false && gameInfo->bulletOfHunterTurret.xCoordinate != 0)
		{
			moveBullet(BULLET_OF_HUNTER_TURRET, gameInfo, map, step);
		}
	}
}

void game::moveBullet(char type, GameInfo* gameInfo, MapCell** map, int step)
{
	if (type == BULLET_OF_STATIONARY_TURRET)
	{

		list::addBegin(&map[gameInfo->bulletOfStationaryTurret.yCoordinate][gameInfo->bulletOfStationaryTurret.xCoordinate + step].types, BULLET_OF_STATIONARY_TURRET);

		list::deleteCurrentElement(&map[gameInfo->bulletOfStationaryTurret.yCoordinate][gameInfo->bulletOfStationaryTurret.xCoordinate].types, BULLET_OF_STATIONARY_TURRET);
		gameInfo->bulletOfStationaryTurret.xCoordinate = gameInfo->bulletOfStationaryTurret.xCoordinate + step;
	}

	else if (type == BULLET_OF_PLATFORM_TURRET)
	{
		list::addBegin(&map[gameInfo->bulletOfPlatformTurret.yCoordinate][gameInfo->bulletOfPlatformTurret.xCoordinate + step].types, BULLET_OF_PLATFORM_TURRET);

		list::deleteCurrentElement(&map[gameInfo->bulletOfPlatformTurret.yCoordinate][gameInfo->bulletOfPlatformTurret.xCoordinate].types, BULLET_OF_PLATFORM_TURRET);
		gameInfo->bulletOfPlatformTurret.xCoordinate = gameInfo->bulletOfPlatformTurret.xCoordinate + step;
	}

	else if (type == BULLET_OF_HUNTER_TURRET)
	{
		list::addBegin(&map[gameInfo->bulletOfHunterTurret.yCoordinate][gameInfo->bulletOfHunterTurret.xCoordinate + step].types, BULLET_OF_HUNTER_TURRET);

		list::deleteCurrentElement(&map[gameInfo->bulletOfHunterTurret.yCoordinate][gameInfo->bulletOfHunterTurret.xCoordinate].types, BULLET_OF_HUNTER_TURRET);
		gameInfo->bulletOfHunterTurret.xCoordinate = gameInfo->bulletOfHunterTurret.xCoordinate + step;
	}
}

bool isMovingRight = true; // пока так, нужен фикс
void game::platformTurretPatrol(GameInfo* gameInfo, MapCell** map, bool turretCanShootingToHero, int step)
{
	int sideOfMoving = step;
	if (turretCanShootingToHero == false ||
		gameInfo->hero.yCoordinate != gameInfo->platform_turret.yCoordinate)
	{
		if (map[gameInfo->platform_turret.yCoordinate][gameInfo->platform_turret.xCoordinate + 1].passable == true && isMovingRight == true)
		{
			sideOfMoving = 1;
			moveOx(sideOfMoving, PLATFORM_TURRET, gameInfo, map);
		}
		else if (map[gameInfo->platform_turret.yCoordinate][gameInfo->platform_turret.xCoordinate - 1].passable == true && isMovingRight == false)
		{
			sideOfMoving = -1;
			moveOx(sideOfMoving, PLATFORM_TURRET, gameInfo, map);
		}
		else if (map[gameInfo->platform_turret.yCoordinate][gameInfo->platform_turret.xCoordinate + 1].passable == false)
		{
			sideOfMoving = -1;
			isMovingRight = false;
			moveOx(sideOfMoving, PLATFORM_TURRET, gameInfo, map);
		}
		else if (map[gameInfo->platform_turret.yCoordinate][gameInfo->platform_turret.xCoordinate - 1].passable == false)
		{
			sideOfMoving = 1;
			isMovingRight = true;
			moveOx(sideOfMoving, PLATFORM_TURRET, gameInfo, map);
		}
	}
}

void game::turretHunterMoving(GameInfo* gameInfo, MapCell** map, bool turretCanShootingToHero, int step)
{
	if (turretCanShootingToHero == false)
	{
		if (gameInfo->hero.xCoordinate > gameInfo->hunter_turret.xCoordinate + 4 &&
			map[gameInfo->hunter_turret.yCoordinate][gameInfo->hunter_turret.xCoordinate + step].passable == true)
		{
			moveOx(step, TURRET_HUNTER, gameInfo, map);
		}
		else if (gameInfo->hero.xCoordinate < gameInfo->hunter_turret.xCoordinate - 4 &&
			map[gameInfo->hunter_turret.yCoordinate][gameInfo->hunter_turret.xCoordinate + step].passable == true)
		{
			moveOx(step, TURRET_HUNTER, gameInfo, map);
		}
		else if (gameInfo->hero.xCoordinate > gameInfo->hunter_turret.xCoordinate + 4 &&
			map[gameInfo->hunter_turret.yCoordinate][gameInfo->hunter_turret.xCoordinate + step].passable == false)
		{
			jump(TURRET_HUNTER, gameInfo, map);
			moveOx(step, TURRET_HUNTER, gameInfo, map);
		}
		else if (gameInfo->hero.xCoordinate < gameInfo->hunter_turret.xCoordinate - 4 &&
			map[gameInfo->hunter_turret.yCoordinate][gameInfo->hunter_turret.xCoordinate + step].passable == false)
		{
			jump(TURRET_HUNTER, gameInfo, map);
			moveOx(step, TURRET_HUNTER, gameInfo, map);
		}
	}
}





//void game::turretAI(GameInfo* gameInfo, MapCell** map)
//{
//	bool heroIsSpotted = false;
//	heroIsSpotted = spottingHero(gameInfo, map);
//	turretMoving(gameInfo, map, heroIsSpotted);
//	shootingToHero(gameInfo, map, heroIsSpotted);
//}


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


//void game::turretPatrol(GameInfo* gameInfo, MapCell** map, bool *isMovingRight, bool *isWallHere)
//{
//	// если между игроком и турелью есть стена или турель и игрок находятся на разной высоте
//	if (*isWallHere == true ||
//		gameInfo->hero.yCoordinate != gameInfo->platform_turret.yCoordinate)
//	{
//		// если справа от турели проходмое пространство и турель двигалась вправо
//		if (map[gameInfo->platform_turret.yCoordinate][gameInfo->platform_turret.xCoordinate + 1].passable == true && *isMovingRight == true)
//		{
//			moveRight(PLATFORM_TURRET, gameInfo, map); // турель перемещается вправо
//			*isMovingRight = true; // текущее направление движения - вправо
//		}
//		// если справа от турели проходмое пространство и турель двигалась влево 
//		else if (map[gameInfo->platform_turret.yCoordinate][gameInfo->platform_turret.xCoordinate - 1].passable == true && *isMovingRight == false)
//		{
//			moveLeft(PLATFORM_TURRET, gameInfo, map); // турель перемещается влево
//			*isMovingRight = false; // текущее направление движения - влево
//		}
//		// если справа от турели непроходимое пространство
//		else if (map[gameInfo->platform_turret.yCoordinate][gameInfo->platform_turret.xCoordinate + 1].passable == false)
//		{
//			*isMovingRight = false;	// текущее направление движения - влево
//			moveLeft(PLATFORM_TURRET, gameInfo, map);	//турель перемещается влево
//		}
//		// если слева от турели непроходимое пространство
//		else if (map[gameInfo->platform_turret.yCoordinate][gameInfo->platform_turret.xCoordinate - 1].passable == false)
//		{
//			*isMovingRight = true;	// текущее направление движения - вправо
//			moveRight(PLATFORM_TURRET, gameInfo, map);
//		}
//	}
//}