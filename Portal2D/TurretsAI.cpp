#include "TurretsAI.h"
#include "Map.h"
#include "Definitions.h"

// √лавна€ функци€ »» турелей, запускает их работу
void game::turretAI(char type, GameInfo* gameInfo, MapCell** map)
{
	if (type == STATIONARY_TURRET && gameInfo->stationary_turret.xCoordinate != 0)
	{
		// step - переменна€ дл€ хранени€ направлени€ движени€
		int step = determineMovingDirection(STATIONARY_TURRET, gameInfo, map);
		bool turretCanShootHero = checkTurretShootingConditions(STATIONARY_TURRET, gameInfo, map, step);
		shootHero(STATIONARY_TURRET, gameInfo, map, turretCanShootHero, step);
	}
	else if (type == PLATFORM_TURRET && gameInfo->platform_turret.xCoordinate != 0)
	{
		int step = determineMovingDirection(PLATFORM_TURRET, gameInfo, map);
		bool turretCatShootHero = checkTurretShootingConditions(PLATFORM_TURRET, gameInfo, map, step);
		platformTurretPatrol(gameInfo, map, turretCatShootHero, step);
		shootHero(PLATFORM_TURRET, gameInfo, map, turretCatShootHero, step);
	}
	else if (type == TURRET_HUNTER && gameInfo->hunter_turret.xCoordinate != 0)
	{
		int step = determineMovingDirection(TURRET_HUNTER, gameInfo, map);
		bool turretCanShootHero = checkTurretShootingConditions(TURRET_HUNTER, gameInfo, map, step);
		turretHunterMoving(gameInfo, map, turretCanShootHero, step);
		shootHero(TURRET_HUNTER, gameInfo, map, turretCanShootHero, step);
	}
}

// ќпредел€ет направление движени€ объектов (пуль и турелей), основыва€сь на положении геро€
int game::determineMovingDirection(char type, GameInfo* gameInfo, MapCell** map)
{
	// ѕеременна€ дл€ хранени€ направлени€ движени€ (изначально турель никуда не двигаетс€)
	int direction = NO_STEP;

	if (type == STATIONARY_TURRET)
	{
		if (gameInfo->hero.xCoordinate > gameInfo->stationary_turret.xCoordinate)
		{
			direction = STEP_RIGHT;
		}
		else if (gameInfo->hero.xCoordinate < gameInfo->stationary_turret.xCoordinate)
		{
			direction = STEP_LEFT;
		}
	}

	else if (type == PLATFORM_TURRET)
	{
		if (gameInfo->hero.xCoordinate >= gameInfo->platform_turret.xCoordinate)
		{
			direction = STEP_RIGHT;
		}
		else
		{
			direction = STEP_LEFT;
		}
	}

	else if (type == TURRET_HUNTER)
	{
		if (gameInfo->hero.xCoordinate > gameInfo->hunter_turret.xCoordinate)
		{
			direction = STEP_RIGHT;
		}
		else if (gameInfo->hero.xCoordinate < gameInfo->hunter_turret.xCoordinate)
		{
			direction = STEP_LEFT;
		}
	}

	return direction;
}

// ѕровер€ет, должна ли турель стрел€ть
bool game::checkTurretShootingConditions(char type, GameInfo* gameInfo, MapCell** map, int step)
{
	bool turretCanShoot = false;
	bool wallIsHere = false;
	if (type == STATIONARY_TURRET)
	{
		// ѕеременна€ дл€ поиска геро€ 
		int searcher = gameInfo->stationary_turret.xCoordinate;
		if (step != NO_STEP &&
			gameInfo->hero.yCoordinate == gameInfo->stationary_turret.yCoordinate)
		{
			// ѕока координаты геро€ не равны координатам поиска и нет стены
			while (gameInfo->hero.xCoordinate != searcher && wallIsHere == false)
			{
				// ≈сли по координатам поиска находитс€ герой
				if (map[gameInfo->stationary_turret.yCoordinate][searcher + step].types->value == HERO)
				{
					wallIsHere = false;
					//   координатам поиска прибал€етс€ шаг
					searcher = searcher + step;
				}
				// ≈сли по координатам поиска нет стены
				else if (map[gameInfo->stationary_turret.yCoordinate][searcher + step].types->value != BLOCK)
				{
					searcher = searcher + step;
				}
				// ≈сли по координатам поиска есть стена
				else if (map[gameInfo->stationary_turret.yCoordinate][searcher + step].types->value == BLOCK)
				{
					wallIsHere = true;
				}
			}

			turretCanShoot = !wallIsHere;
		}
		else if (step == NO_STEP)
		{
			turretCanShoot = wallIsHere;
		}
	}
	else if (type == PLATFORM_TURRET)
	{
		int searcher = gameInfo->platform_turret.xCoordinate;
		if (step != NO_STEP &&
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
			turretCanShoot = !wallIsHere;
		}
		else if (step == NO_STEP)
		{
			turretCanShoot = wallIsHere;
		}
	}
	else if (type == TURRET_HUNTER)
	{
		int searcher = gameInfo->hunter_turret.xCoordinate;
		if (step != NO_STEP &&
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
			turretCanShoot = !wallIsHere;
		}
		else if (step == NO_STEP)
		{
			turretCanShoot = wallIsHere;
		}
	}

	return turretCanShoot;
}

// ‘ункци€ определ€ет поведение пули (ее по€вление, исчезновение)
void game::shootHero(char type, GameInfo* gameInfo, MapCell** map, bool turretCanShootHero, int step)
{
	if (type == STATIONARY_TURRET)
	{
		if (map[gameInfo->stationary_turret.yCoordinate][gameInfo->stationary_turret.xCoordinate + step].passable == true &&
			gameInfo->bulletOfStationaryTurret.xCoordinate == 0 && turretCanShootHero == true)
		{
			gameInfo->bulletOfStationaryTurret.xCoordinate = gameInfo->stationary_turret.xCoordinate + step;
			gameInfo->bulletOfStationaryTurret.yCoordinate = gameInfo->stationary_turret.yCoordinate;
			list::addBegin(&map[gameInfo->bulletOfStationaryTurret.yCoordinate][gameInfo->bulletOfStationaryTurret.xCoordinate].types, BULLET_OF_STATIONARY_TURRET);
		}

		else if (gameInfo->bulletOfStationaryTurret.xCoordinate != 0 && step != NO_STEP)
		{
			if ((gameInfo->bulletOfStationaryTurret.yCoordinate == gameInfo->hero.yCoordinate) &&
				(gameInfo->bulletOfStationaryTurret.xCoordinate == gameInfo->hero.xCoordinate))
			{
				gameInfo->hero.healthPoints -= DAMAGE_TO_HERO; // отнимаетс€ здоровье игрока
				// удал€етс€ текстура пули
				list::deleteCurrentElement(&map[gameInfo->bulletOfStationaryTurret.yCoordinate][gameInfo->bulletOfStationaryTurret.xCoordinate].types, BULLET_OF_STATIONARY_TURRET);
				// пул€ исчезает
				gameInfo->bulletOfStationaryTurret.xCoordinate = 0;
			}
			else if (map[gameInfo->bulletOfStationaryTurret.yCoordinate][gameInfo->bulletOfStationaryTurret.xCoordinate + step].passable == true)
			{
				moveBullet(BULLET_OF_STATIONARY_TURRET, gameInfo, map, step);
			}

			else if (map[gameInfo->bulletOfStationaryTurret.yCoordinate][gameInfo->bulletOfStationaryTurret.xCoordinate + step].passable == false)
			{
				// удал€етс€ текстура пули
				list::deleteCurrentElement(&map[gameInfo->bulletOfStationaryTurret.yCoordinate][gameInfo->bulletOfStationaryTurret.xCoordinate].types, BULLET_OF_STATIONARY_TURRET);
				// пул€ исчезает
				gameInfo->bulletOfStationaryTurret.xCoordinate = 0;
			}
		}

		else if (step == NO_STEP && gameInfo->hero.yCoordinate == gameInfo->stationary_turret.yCoordinate)
		{
			gameInfo->hero.healthPoints -= DAMAGE_TO_HERO;	// у геро€ отнимаетс€ здоровье
		}

		else if (turretCanShootHero == false && gameInfo->bulletOfStationaryTurret.xCoordinate != 0)
		{
			moveBullet(BULLET_OF_STATIONARY_TURRET, gameInfo, map, step);
		}
	}
	else if (type == PLATFORM_TURRET)
	{

		if (map[gameInfo->platform_turret.yCoordinate][gameInfo->platform_turret.xCoordinate + step].passable == true &&
			gameInfo->bulletOfPlatformTurret.xCoordinate == 0 && turretCanShootHero == true)
		{
			gameInfo->bulletOfPlatformTurret.xCoordinate = gameInfo->platform_turret.xCoordinate + step;
			gameInfo->bulletOfPlatformTurret.yCoordinate = gameInfo->platform_turret.yCoordinate;
			list::addBegin(&map[gameInfo->bulletOfPlatformTurret.yCoordinate][gameInfo->bulletOfPlatformTurret.xCoordinate].types, BULLET_OF_PLATFORM_TURRET);
		}

		else if (gameInfo->bulletOfPlatformTurret.xCoordinate != 0 && step != NO_STEP)
		{
			if ((gameInfo->bulletOfPlatformTurret.yCoordinate == gameInfo->hero.yCoordinate) &&
				(gameInfo->bulletOfPlatformTurret.xCoordinate == gameInfo->hero.xCoordinate))
			{
				gameInfo->hero.healthPoints -= DAMAGE_TO_HERO; // отнимаетс€ здоровье игрока
				// удал€етс€ текстура пули
				list::deleteCurrentElement(&map[gameInfo->bulletOfPlatformTurret.yCoordinate][gameInfo->bulletOfPlatformTurret.xCoordinate].types, BULLET_OF_PLATFORM_TURRET);
				// пул€ исчезает
				gameInfo->bulletOfPlatformTurret.xCoordinate = 0;
			}
			else if (map[gameInfo->bulletOfPlatformTurret.yCoordinate][gameInfo->bulletOfPlatformTurret.xCoordinate + step].passable == true)
			{
				moveBullet(BULLET_OF_PLATFORM_TURRET, gameInfo, map, step);
			}

			else if (map[gameInfo->bulletOfPlatformTurret.yCoordinate][gameInfo->bulletOfPlatformTurret.xCoordinate + step].passable == false)
			{
				// удал€етс€ текстура пули
				list::deleteCurrentElement(&map[gameInfo->bulletOfPlatformTurret.yCoordinate][gameInfo->bulletOfPlatformTurret.xCoordinate].types, BULLET_OF_PLATFORM_TURRET);
				// пул€ исчезает
				gameInfo->bulletOfPlatformTurret.xCoordinate = 0;
			}
		}
		else if (gameInfo->hero.xCoordinate == gameInfo->platform_turret.xCoordinate &&
			gameInfo->hero.yCoordinate == gameInfo->platform_turret.yCoordinate)
		{
			gameInfo->hero.healthPoints -= DAMAGE_TO_HERO;	// у геро€ отнимаетс€ здоровье
		}

		else if (turretCanShootHero == false && gameInfo->bulletOfPlatformTurret.xCoordinate != 0)
		{
			moveBullet(BULLET_OF_PLATFORM_TURRET, gameInfo, map, step);
		}
	}

	else if (type == TURRET_HUNTER)
	{

		if (map[gameInfo->hunter_turret.yCoordinate][gameInfo->hunter_turret.xCoordinate + step].passable == true &&
			gameInfo->bulletOfHunterTurret.xCoordinate == 0 && turretCanShootHero == true)
		{
			gameInfo->bulletOfHunterTurret.xCoordinate = gameInfo->hunter_turret.xCoordinate + step;
			gameInfo->bulletOfHunterTurret.yCoordinate = gameInfo->hunter_turret.yCoordinate;
			list::addBegin(&map[gameInfo->bulletOfHunterTurret.yCoordinate][gameInfo->bulletOfHunterTurret.xCoordinate].types, BULLET_OF_HUNTER_TURRET);
		}

		else if (gameInfo->bulletOfHunterTurret.xCoordinate != 0 && step != NO_STEP)
		{
			if ((gameInfo->bulletOfHunterTurret.yCoordinate == gameInfo->hero.yCoordinate) &&
				(gameInfo->bulletOfHunterTurret.xCoordinate == gameInfo->hero.xCoordinate))
			{
				gameInfo->hero.healthPoints -= DAMAGE_TO_HERO; // отнимаетс€ здоровье игрока
															   // удал€етс€ текстура пули
				list::deleteCurrentElement(&map[gameInfo->bulletOfHunterTurret.yCoordinate][gameInfo->bulletOfHunterTurret.xCoordinate].types, BULLET_OF_HUNTER_TURRET);
				// пул€ исчезает
				gameInfo->bulletOfHunterTurret.xCoordinate = 0;
			}
			else if (map[gameInfo->bulletOfHunterTurret.yCoordinate][gameInfo->bulletOfHunterTurret.xCoordinate + step].passable == true)
			{
				moveBullet(BULLET_OF_HUNTER_TURRET, gameInfo, map, step);
			}

			else if (map[gameInfo->bulletOfHunterTurret.yCoordinate][gameInfo->bulletOfHunterTurret.xCoordinate + step].passable == false)
			{
				// удал€етс€ текстура пули
				list::deleteCurrentElement(&map[gameInfo->bulletOfHunterTurret.yCoordinate][gameInfo->bulletOfHunterTurret.xCoordinate].types, BULLET_OF_HUNTER_TURRET);
				// пул€ исчезает
				gameInfo->bulletOfHunterTurret.xCoordinate = 0;
			}
		}
		else if (gameInfo->hero.xCoordinate == gameInfo->hunter_turret.xCoordinate &&
			gameInfo->hero.yCoordinate == gameInfo->hunter_turret.yCoordinate)
		{
			gameInfo->hero.healthPoints -= DAMAGE_TO_HERO;	// у геро€ отнимаетс€ здоровье
		}

		else if (turretCanShootHero == false && gameInfo->bulletOfHunterTurret.xCoordinate != 0)
		{
			moveBullet(BULLET_OF_HUNTER_TURRET, gameInfo, map, step);
		}
	}
}

// ‘ункци€ отвечает за перемещение пули по карте
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

// ‘ункци€ отвечает за перемещение патрулирующей турели
void game::platformTurretPatrol(GameInfo* gameInfo, MapCell** map, bool turretCanShootHero, int step)
{
	int sideOfMoving = step;
	if (turretCanShootHero == false ||
		gameInfo->hero.yCoordinate != gameInfo->platform_turret.yCoordinate)
	{
		if (map[gameInfo->platform_turret.yCoordinate][gameInfo->platform_turret.xCoordinate + 1].passable == true && 
			gameInfo->platform_turret.isMovingRight == true)
		{
			sideOfMoving = 1;
			moveOx(sideOfMoving, PLATFORM_TURRET, gameInfo, map);
		}
		else if (map[gameInfo->platform_turret.yCoordinate][gameInfo->platform_turret.xCoordinate - 1].passable == true && 
			gameInfo->platform_turret.isMovingRight == false)
		{
			sideOfMoving = -1;
			moveOx(sideOfMoving, PLATFORM_TURRET, gameInfo, map);
		}
		else if (map[gameInfo->platform_turret.yCoordinate][gameInfo->platform_turret.xCoordinate + 1].passable == false)
		{
			sideOfMoving = -1;
			gameInfo->platform_turret.isMovingRight = false;
			moveOx(sideOfMoving, PLATFORM_TURRET, gameInfo, map);
		}
		else if (map[gameInfo->platform_turret.yCoordinate][gameInfo->platform_turret.xCoordinate - 1].passable == false)
		{
			sideOfMoving = 1;
			gameInfo->platform_turret.isMovingRight = true;
			moveOx(sideOfMoving, PLATFORM_TURRET, gameInfo, map);
		}
	}
}

// ‘ункци€ отвечает за перемещение турели-охотника
void game::turretHunterMoving(GameInfo* gameInfo, MapCell** map, bool turretCanShootHero, int step)
{
	if (turretCanShootHero == false)
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