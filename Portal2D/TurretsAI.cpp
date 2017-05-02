#include "TurretsAI.h"
#include "Map.h"
#include "Definitions.h"

// Главная функция ИИ турелей, запускает их работу
void game::turretAI(char type, GameInfo* gameInfo, MapCell** map)
{
	if (type == STATIONARY_TURRET && gameInfo->stationary_turret.xCoordinate != 0)
	{
		// step - переменная для хранения направления движения с количеством 
		int step = determineMovingDirection(STATIONARY_TURRET, gameInfo, map);
		bool turretCanShootHero = checkTurretShootingConditions(STATIONARY_TURRET, gameInfo, map, step);
		shootHero(STATIONARY_TURRET, gameInfo, map, turretCanShootHero, step);
	}
	else if (type == PLATFORM_TURRET && gameInfo->platform_turret.xCoordinate != 0)
	{
		int step = determineMovingDirection(PLATFORM_TURRET, gameInfo, map);
		bool turretCanShootHero = checkTurretShootingConditions(PLATFORM_TURRET, gameInfo, map, step);
		platformTurretPatrol(gameInfo, map, turretCanShootHero, step);
		shootHero(PLATFORM_TURRET, gameInfo, map, turretCanShootHero, step);
	}
	else if (type == TURRET_HUNTER && gameInfo->hunter_turret.xCoordinate != 0)
	{
		int step = determineMovingDirection(TURRET_HUNTER, gameInfo, map);
		bool turretCanShootHero = checkTurretShootingConditions(TURRET_HUNTER, gameInfo, map, step);
		turretHunterMoving(gameInfo, map, turretCanShootHero, step);
		shootHero(TURRET_HUNTER, gameInfo, map, turretCanShootHero, step);
	}
}

// Определяет направление движения объектов (пуль и турелей), основываясь на положении героя
int game::determineMovingDirection(char type, GameInfo* gameInfo, MapCell** map)
{
	// Переменная для хранения направления движения (изначально турель никуда не двигается)
	int direction = NO_STEP;

	if (type == STATIONARY_TURRET)
	{
		if (gameInfo->hero.xCoordinate > gameInfo->stationary_turret.xCoordinate)
		{
			direction = STEP_RIGHT_DOWN;
		}
		else if (gameInfo->hero.xCoordinate < gameInfo->stationary_turret.xCoordinate)
		{
			direction = STEP_LEFT_UP;
		}
	}

	else if (type == PLATFORM_TURRET)
	{
		if (gameInfo->hero.xCoordinate >= gameInfo->platform_turret.xCoordinate)
		{
			direction = STEP_RIGHT_DOWN;
		}
		else
		{
			direction = STEP_LEFT_UP;
		}
	}

	else if (type == TURRET_HUNTER)
	{
		if (gameInfo->hero.xCoordinate > gameInfo->hunter_turret.xCoordinate)
		{
			direction = STEP_RIGHT_DOWN;
		}
		else if (gameInfo->hero.xCoordinate < gameInfo->hunter_turret.xCoordinate)
		{
			direction = STEP_LEFT_UP;
		}
	}

	return direction;
}

// Проверяет, должна ли турель стрелять
bool game::checkTurretShootingConditions(char type, GameInfo* gameInfo, MapCell** map, int step)
{
	bool turretCanShoot = false;
	bool wallIsHere = false;
	if (type == STATIONARY_TURRET)
	{
		// Переменная для поиска героя 
		int searcher = gameInfo->stationary_turret.xCoordinate;
		if (step != NO_STEP &&
			gameInfo->hero.yCoordinate == gameInfo->stationary_turret.yCoordinate)
		{
			// Пока координаты героя не равны координатам поиска и нет стены
			while (gameInfo->hero.xCoordinate != searcher && wallIsHere == false)
			{
				// Если по координатам поиска находится герой
				if (map[gameInfo->stationary_turret.yCoordinate][searcher + step].types->value == HERO)
				{
					wallIsHere = false;
					// К координатам поиска прибаляется шаг
					searcher = searcher + step;
				}
				// Если по координатам поиска нет стены
				else if (map[gameInfo->stationary_turret.yCoordinate][searcher + step].types->value != BLOCK)
				{
					searcher = searcher + step;
				}
				// Если по координатам поиска есть стена
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

// Функция определяет поведение пули (ее появление, исчезновение)
void game::shootHero(char type, GameInfo* gameInfo, MapCell** map, bool turretCanShootHero, int step)
{
	if (type == STATIONARY_TURRET)
	{
		// если с слева(справа) проходимое пространство и не существует пули и турель может стрелять
		if (map[gameInfo->stationary_turret.yCoordinate][gameInfo->stationary_turret.xCoordinate + step].passable == true &&
			gameInfo->bulletOfStationaryTurret.xCoordinate == 0 && turretCanShootHero == true)
		{
			// справа(слева) создаётся пуля
			gameInfo->bulletOfStationaryTurret.xCoordinate = gameInfo->stationary_turret.xCoordinate + step;
			gameInfo->bulletOfStationaryTurret.yCoordinate = gameInfo->stationary_turret.yCoordinate;
			// справа(слева) создаётся текстура пули
			list::addBegin(&map[gameInfo->bulletOfStationaryTurret.yCoordinate][gameInfo->bulletOfStationaryTurret.xCoordinate].types, BULLET_OF_STATIONARY_TURRET);
		}

		// если пуля существует и возможно перемещение
		else if (gameInfo->bulletOfStationaryTurret.xCoordinate != 0 && step != NO_STEP)
		{
			// если координаты пули и героя совпадают
			if ((gameInfo->bulletOfStationaryTurret.yCoordinate == gameInfo->hero.yCoordinate) &&
				(gameInfo->bulletOfStationaryTurret.xCoordinate == gameInfo->hero.xCoordinate))
			{
				gameInfo->hero.healthPoints -= DAMAGE_TO_HERO; // отнимается здоровье игрока
				// удаляется текстура пули
				list::deleteCurrentElement(&map[gameInfo->bulletOfStationaryTurret.yCoordinate][gameInfo->bulletOfStationaryTurret.xCoordinate].types, BULLET_OF_STATIONARY_TURRET);
				// пуля исчезает
				gameInfo->bulletOfStationaryTurret.xCoordinate = 0;
			}
			// если справа(слева) от пули проходимое пространство
			else if (map[gameInfo->bulletOfStationaryTurret.yCoordinate][gameInfo->bulletOfStationaryTurret.xCoordinate + step].passable == true)
			{
				// пуля перемещается
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
		// если перемещение не требуется и герой на одном уровне с турелью
		else if (step == NO_STEP && gameInfo->hero.yCoordinate == gameInfo->stationary_turret.yCoordinate)
		{
			gameInfo->hero.healthPoints -= DAMAGE_TO_HERO;	// у героя отнимается здоровье
		}
		// если героя нет на линии огня и пуля существует
		else if (turretCanShootHero == false && gameInfo->bulletOfStationaryTurret.xCoordinate != 0)
		{
			// пуля перемещается
			moveBullet(BULLET_OF_STATIONARY_TURRET, gameInfo, map, step);
		}
	}
	else if (type == PLATFORM_TURRET)
	{
		// если с слева(справа) проходимое пространство и не существует пули и турель может стрелять
		if (map[gameInfo->platform_turret.yCoordinate][gameInfo->platform_turret.xCoordinate + step].passable == true &&
			gameInfo->bulletOfPlatformTurret.xCoordinate == 0 && turretCanShootHero == true)
		{
			// справа(слева) создаётся пуля
			gameInfo->bulletOfPlatformTurret.xCoordinate = gameInfo->platform_turret.xCoordinate + step;
			gameInfo->bulletOfPlatformTurret.yCoordinate = gameInfo->platform_turret.yCoordinate;
			// справа(слева) создаётся текстура пули
			list::addBegin(&map[gameInfo->bulletOfPlatformTurret.yCoordinate][gameInfo->bulletOfPlatformTurret.xCoordinate].types, BULLET_OF_PLATFORM_TURRET);
		}
		
		// если пуля существует и возможно перемещение
		else if (gameInfo->bulletOfPlatformTurret.xCoordinate != 0 && step != NO_STEP)
		{
			// если координаты пули и героя совпадают
			if ((gameInfo->bulletOfPlatformTurret.yCoordinate == gameInfo->hero.yCoordinate) &&
				(gameInfo->bulletOfPlatformTurret.xCoordinate == gameInfo->hero.xCoordinate))
			{
				gameInfo->hero.healthPoints -= DAMAGE_TO_HERO; // отнимается здоровье игрока
				// удаляется текстура пули
				list::deleteCurrentElement(&map[gameInfo->bulletOfPlatformTurret.yCoordinate][gameInfo->bulletOfPlatformTurret.xCoordinate].types, BULLET_OF_PLATFORM_TURRET);
				// пуля исчезает
				gameInfo->bulletOfPlatformTurret.xCoordinate = 0;
			}
			// если справа(слева) от пули проходимое пространство
			else if (map[gameInfo->bulletOfPlatformTurret.yCoordinate][gameInfo->bulletOfPlatformTurret.xCoordinate + step].passable == true)
			{
				// пуля перемещается
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
		// если перемещение не требуется и герой на одном уровне с турелью
		else if (gameInfo->hero.xCoordinate == gameInfo->platform_turret.xCoordinate &&
			gameInfo->hero.yCoordinate == gameInfo->platform_turret.yCoordinate)
		{
			gameInfo->hero.healthPoints -= DAMAGE_TO_HERO;	// у героя отнимается здоровье
		}
		// если героя нет на линии огня и пуля существует
		else if (turretCanShootHero == false && gameInfo->bulletOfPlatformTurret.xCoordinate != 0)
		{
			// пуля перемещается
			moveBullet(BULLET_OF_PLATFORM_TURRET, gameInfo, map, step);
		}
	}

	else if (type == TURRET_HUNTER)
	{
		// если с слева(справа) проходимое пространство и не существует пули и турель может стрелять
		if (map[gameInfo->hunter_turret.yCoordinate][gameInfo->hunter_turret.xCoordinate + step].passable == true &&
			gameInfo->bulletOfHunterTurret.xCoordinate == 0 && turretCanShootHero == true)
		{
			// справа(слева) создаётся пуля
			gameInfo->bulletOfHunterTurret.xCoordinate = gameInfo->hunter_turret.xCoordinate + step;
			gameInfo->bulletOfHunterTurret.yCoordinate = gameInfo->hunter_turret.yCoordinate;
			// справа(слева) создаётся текстура пули
			list::addBegin(&map[gameInfo->bulletOfHunterTurret.yCoordinate][gameInfo->bulletOfHunterTurret.xCoordinate].types, BULLET_OF_HUNTER_TURRET);
		}
		// если пуля существует и возможно перемещение
		else if (gameInfo->bulletOfHunterTurret.xCoordinate != 0 && step != NO_STEP)
		{
			// если координаты пули и героя совпадают
			if ((gameInfo->bulletOfHunterTurret.yCoordinate == gameInfo->hero.yCoordinate) &&
				(gameInfo->bulletOfHunterTurret.xCoordinate == gameInfo->hero.xCoordinate))
			{
				gameInfo->hero.healthPoints -= DAMAGE_TO_HERO; // отнимается здоровье игрока
				 // удаляется текстура пули
				list::deleteCurrentElement(&map[gameInfo->bulletOfHunterTurret.yCoordinate][gameInfo->bulletOfHunterTurret.xCoordinate].types, BULLET_OF_HUNTER_TURRET);
				// пуля исчезает
				gameInfo->bulletOfHunterTurret.xCoordinate = 0;
			}
			// если справа(слева) от пули проходимое пространство
			else if (map[gameInfo->bulletOfHunterTurret.yCoordinate][gameInfo->bulletOfHunterTurret.xCoordinate + step].passable == true)
			{
				// пуля перемещается
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
		// если перемещение не требуется и герой на одном уровне с турелью
		else if (gameInfo->hero.xCoordinate == gameInfo->hunter_turret.xCoordinate &&
			gameInfo->hero.yCoordinate == gameInfo->hunter_turret.yCoordinate)
		{
			gameInfo->hero.healthPoints -= DAMAGE_TO_HERO;	// у героя отнимается здоровье
		}
		// если героя нет на линии огня и пуля существует
		else if (turretCanShootHero == false && gameInfo->bulletOfHunterTurret.xCoordinate != 0)
		{
			// пуля перемещается
			moveBullet(BULLET_OF_HUNTER_TURRET, gameInfo, map, step);
		}
	}
}

// Функция отвечает за перемещение пули по карте
void game::moveBullet(char type, GameInfo* gameInfo, MapCell** map, int step)
{
	if (type == BULLET_OF_STATIONARY_TURRET)
	{
		// слева(справа) создаётся текстура пули
		list::addBegin(&map[gameInfo->bulletOfStationaryTurret.yCoordinate][gameInfo->bulletOfStationaryTurret.xCoordinate + step].types, BULLET_OF_STATIONARY_TURRET);
		// существующая текстура удаляется
		list::deleteCurrentElement(&map[gameInfo->bulletOfStationaryTurret.yCoordinate][gameInfo->bulletOfStationaryTurret.xCoordinate].types, BULLET_OF_STATIONARY_TURRET);
		// координата по Ox увеличивается(уменьшается) на step(на один)
		gameInfo->bulletOfStationaryTurret.xCoordinate = gameInfo->bulletOfStationaryTurret.xCoordinate + step;
	}

	else if (type == BULLET_OF_PLATFORM_TURRET)
	{	
		// слева(справа) создаётся текстура пули
		list::addBegin(&map[gameInfo->bulletOfPlatformTurret.yCoordinate][gameInfo->bulletOfPlatformTurret.xCoordinate + step].types, BULLET_OF_PLATFORM_TURRET);
		// существующая текстура удаляется
		list::deleteCurrentElement(&map[gameInfo->bulletOfPlatformTurret.yCoordinate][gameInfo->bulletOfPlatformTurret.xCoordinate].types, BULLET_OF_PLATFORM_TURRET);
		// координата по Ox увеличивается(уменьшается) на step(на один)
		gameInfo->bulletOfPlatformTurret.xCoordinate = gameInfo->bulletOfPlatformTurret.xCoordinate + step;
	}

	else if (type == BULLET_OF_HUNTER_TURRET)
	{
		// слева(справа) создаётся текстура пули
		list::addBegin(&map[gameInfo->bulletOfHunterTurret.yCoordinate][gameInfo->bulletOfHunterTurret.xCoordinate + step].types, BULLET_OF_HUNTER_TURRET);
		// существующая текстура удаляется
		list::deleteCurrentElement(&map[gameInfo->bulletOfHunterTurret.yCoordinate][gameInfo->bulletOfHunterTurret.xCoordinate].types, BULLET_OF_HUNTER_TURRET);
		// координата по Ox увеличивается(уменьшается) на step(на один)
		gameInfo->bulletOfHunterTurret.xCoordinate = gameInfo->bulletOfHunterTurret.xCoordinate + step;
	}
}

// Функция отвечает за перемещение патрулирующей турели
void game::platformTurretPatrol(GameInfo* gameInfo, MapCell** map, bool turretCanShootHero, int step)
{
	// sideOfMoving - переменная для хранения направления передвижения и размера одного шага
	int sideOfMoving = step;
	// если турель не может стрелять или если герой и турель на разной высоте
	if (turretCanShootHero == false ||
		gameInfo->hero.yCoordinate != gameInfo->platform_turret.yCoordinate)
	{
		// если справа проходимое пространство и турель двигалась вправо
		if (map[gameInfo->platform_turret.yCoordinate][gameInfo->platform_turret.xCoordinate + 1].passable == true && 
			gameInfo->platform_turret.isMovingRight == true)
		{
			sideOfMoving = 1;
			moveOx(sideOfMoving, PLATFORM_TURRET, gameInfo, map);
		}
		// если слева проходимое пространство и турель двигалась влево
		else if (map[gameInfo->platform_turret.yCoordinate][gameInfo->platform_turret.xCoordinate - 1].passable == true && 
			gameInfo->platform_turret.isMovingRight == false)
		{
			sideOfMoving = -1;
			moveOx(sideOfMoving, PLATFORM_TURRET, gameInfo, map);
		}
		// если справа непроходимое пространство
		else if (map[gameInfo->platform_turret.yCoordinate][gameInfo->platform_turret.xCoordinate + 1].passable == false)
		{
			sideOfMoving = -1;
			gameInfo->platform_turret.isMovingRight = false;
			moveOx(sideOfMoving, PLATFORM_TURRET, gameInfo, map);
		}
		// если слева непроходимое пространство
		else if (map[gameInfo->platform_turret.yCoordinate][gameInfo->platform_turret.xCoordinate - 1].passable == false)
		{
			sideOfMoving = 1;
			gameInfo->platform_turret.isMovingRight = true;
			moveOx(sideOfMoving, PLATFORM_TURRET, gameInfo, map);
		}
	}
}

// Функция отвечает за перемещение турели-охотника
void game::turretHunterMoving(GameInfo* gameInfo, MapCell** map, bool turretCanShootHero, int step)
{
	// если турель не может стрелять
	if (turretCanShootHero == false)
	{
		// если герой правее турели на четыре клетки карты и справа от турели проходимое пространство
		if (gameInfo->hero.xCoordinate > gameInfo->hunter_turret.xCoordinate + 4 &&
			map[gameInfo->hunter_turret.yCoordinate][gameInfo->hunter_turret.xCoordinate + step].passable == true)
		{
			// турель перемещается по Ox
			moveOx(step, TURRET_HUNTER, gameInfo, map);
		}
		// если герой левее турели на четыре клетки карты и слева от турели проходимое пространство
		else if (gameInfo->hero.xCoordinate < gameInfo->hunter_turret.xCoordinate - 4 &&
			map[gameInfo->hunter_turret.yCoordinate][gameInfo->hunter_turret.xCoordinate + step].passable == true)
		{
			// турель перемещается по Ox
			moveOx(step, TURRET_HUNTER, gameInfo, map);
		}
		// если герой правее турели на четыре клетки карты и справа от турели непроходимое пространство
		else if (gameInfo->hero.xCoordinate > gameInfo->hunter_turret.xCoordinate + 4 &&
			map[gameInfo->hunter_turret.yCoordinate][gameInfo->hunter_turret.xCoordinate + step].passable == false)
		{
			// турель прыгает
			jump(TURRET_HUNTER, gameInfo, map);
			// турель перемещается по Ox
			moveOx(step, TURRET_HUNTER, gameInfo, map);
		}
		// если герой левее турели на четыре клетки карты и слева от турели непроходимое пространство
		else if (gameInfo->hero.xCoordinate < gameInfo->hunter_turret.xCoordinate - 4 &&
			map[gameInfo->hunter_turret.yCoordinate][gameInfo->hunter_turret.xCoordinate + step].passable == false)
		{
			// турель прыгает
			jump(TURRET_HUNTER, gameInfo, map);
			// турель перемещается по Ox
			moveOx(step, TURRET_HUNTER, gameInfo, map);
		}
	}
}