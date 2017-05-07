#include "TurretsAI.h"
#include "Map.h"
#include "Definitions.h"

// Главная функция ИИ турелей, запускает их работу
void game::turretAI(char type, GameInfo* gameInfo, MapCell** map)
{
	if (type == STATIONARY_TURRET && gameInfo->stationary_turret.coordinates.xCoordinate != 0)
	{
		// step - переменная для хранения направления движения с количеством 
		int step = determineMovingDirection(STATIONARY_TURRET, gameInfo, map);
		bool turretCanShootHero = checkTurretShootingConditions(STATIONARY_TURRET, gameInfo, map, step);
		shootHero(STATIONARY_TURRET, gameInfo, map, turretCanShootHero, step);
	}
	else if (type == PLATFORM_TURRET && gameInfo->platform_turret.coordinates.xCoordinate != 0)
	{
		int step = determineMovingDirection(PLATFORM_TURRET, gameInfo, map);
		bool turretCanShootHero = checkTurretShootingConditions(PLATFORM_TURRET, gameInfo, map, step);
		platformTurretPatrol(gameInfo, map, turretCanShootHero, step);
		shootHero(PLATFORM_TURRET, gameInfo, map, turretCanShootHero, step);
	}
	else if (type == TURRET_HUNTER && gameInfo->hunter_turret.coordinates.xCoordinate != 0)
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
		if (gameInfo->hero.coordinates.xCoordinate > gameInfo->stationary_turret.coordinates.xCoordinate)
		{
			direction = STEP_RIGHT_DOWN;
		}
		else if (gameInfo->hero.coordinates.xCoordinate < gameInfo->stationary_turret.coordinates.xCoordinate)
		{
			direction = STEP_LEFT_UP;
		}
	}

	else if (type == PLATFORM_TURRET)
	{
		if (gameInfo->hero.coordinates.xCoordinate >= gameInfo->platform_turret.coordinates.xCoordinate)
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
		if (gameInfo->hero.coordinates.xCoordinate > gameInfo->hunter_turret.coordinates.xCoordinate)
		{
			direction = STEP_RIGHT_DOWN;
		}
		else if (gameInfo->hero.coordinates.xCoordinate < gameInfo->hunter_turret.coordinates.xCoordinate)
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
		int searcher = gameInfo->stationary_turret.coordinates.xCoordinate;
		if (step != NO_STEP &&
			gameInfo->hero.coordinates.yCoordinate == gameInfo->stationary_turret.coordinates.yCoordinate)
		{
			// Пока координаты героя не равны координатам поиска и нет стены
			while (gameInfo->hero.coordinates.xCoordinate != searcher && wallIsHere == false)
			{
				// Если по координатам поиска находится герой
				if (map[gameInfo->stationary_turret.coordinates.yCoordinate][searcher + step].types->value == HERO)
				{
					wallIsHere = false;
					// К координатам поиска прибаляется шаг
					searcher = searcher + step;
				}
				// Если по координатам поиска нет стены
				else if (map[gameInfo->stationary_turret.coordinates.yCoordinate][searcher + step].types->value != BLOCK)
				{
					searcher = searcher + step;
				}
				// Если по координатам поиска есть стена
				else if (map[gameInfo->stationary_turret.coordinates.yCoordinate][searcher + step].types->value == BLOCK)
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
		int searcher = gameInfo->platform_turret.coordinates.xCoordinate;
		if (step != NO_STEP &&
			gameInfo->hero.coordinates.yCoordinate == gameInfo->platform_turret.coordinates.yCoordinate)
		{
			while (gameInfo->hero.coordinates.xCoordinate != searcher && wallIsHere == false)
			{
				if (map[gameInfo->platform_turret.coordinates.yCoordinate][searcher + step].types->value == HERO)
				{
					wallIsHere = false;
					searcher = searcher + step;
				}
				else if (map[gameInfo->platform_turret.coordinates.yCoordinate][searcher + step].types->value != BLOCK)
				{
					searcher = searcher + step;
				}
				else if (map[gameInfo->platform_turret.coordinates.yCoordinate][searcher + step].types->value == BLOCK)
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
		int searcher = gameInfo->hunter_turret.coordinates.xCoordinate;
		if (step != NO_STEP &&
			gameInfo->hero.coordinates.yCoordinate == gameInfo->hunter_turret.coordinates.yCoordinate)
		{
			while (gameInfo->hero.coordinates.xCoordinate != searcher && wallIsHere == false)
			{
				if (map[gameInfo->hunter_turret.coordinates.yCoordinate][searcher + step].types->value == HERO)
				{
					wallIsHere = false;
					searcher = searcher + step;
				}
				else if (map[gameInfo->hunter_turret.coordinates.yCoordinate][searcher + step].types->value != BLOCK)
				{
					searcher = searcher + step;
				}
				else if (map[gameInfo->hunter_turret.coordinates.yCoordinate][searcher + step].types->value == BLOCK)
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
		if (map[gameInfo->stationary_turret.coordinates.yCoordinate][gameInfo->stationary_turret.coordinates.xCoordinate + step].passable == true &&
			gameInfo->bulletOfStationaryTurret.coordinates.xCoordinate == 0 && turretCanShootHero == true)
		{
			// справа(слева) создаётся пуля
			gameInfo->bulletOfStationaryTurret.coordinates.xCoordinate = gameInfo->stationary_turret.coordinates.xCoordinate + step;
			gameInfo->bulletOfStationaryTurret.coordinates.yCoordinate = gameInfo->stationary_turret.coordinates.yCoordinate;
			// справа(слева) создаётся текстура пули
			list::addBegin(&map[gameInfo->bulletOfStationaryTurret.coordinates.yCoordinate][gameInfo->bulletOfStationaryTurret.coordinates.xCoordinate].types, BULLET_OF_STATIONARY_TURRET);
		}

		// если пуля существует и возможно перемещение
		else if (gameInfo->bulletOfStationaryTurret.coordinates.xCoordinate != 0 && step != NO_STEP)
		{
			// если координаты пули и героя совпадают
			if ((gameInfo->bulletOfStationaryTurret.coordinates.yCoordinate == gameInfo->hero.coordinates.yCoordinate) &&
				(gameInfo->bulletOfStationaryTurret.coordinates.xCoordinate == gameInfo->hero.coordinates.xCoordinate))
			{
				gameInfo->hero.healthPoints -= DAMAGE_TO_HERO; // отнимается здоровье игрока
				// удаляется текстура пули
				list::deleteCurrentElement(&map[gameInfo->bulletOfStationaryTurret.coordinates.yCoordinate][gameInfo->bulletOfStationaryTurret.coordinates.xCoordinate].types, BULLET_OF_STATIONARY_TURRET);
				// пуля исчезает
				gameInfo->bulletOfStationaryTurret.coordinates.xCoordinate = 0;
			}
			// если справа(слева) от пули проходимое пространство
			else if (map[gameInfo->bulletOfStationaryTurret.coordinates.yCoordinate][gameInfo->bulletOfStationaryTurret.coordinates.xCoordinate + step].passable == true)
			{
				// пуля перемещается
				moveBullet(BULLET_OF_STATIONARY_TURRET, gameInfo, map, step);
			}

			else if (map[gameInfo->bulletOfStationaryTurret.coordinates.yCoordinate][gameInfo->bulletOfStationaryTurret.coordinates.xCoordinate + step].passable == false)
			{
				// удаляется текстура пули
				list::deleteCurrentElement(&map[gameInfo->bulletOfStationaryTurret.coordinates.yCoordinate][gameInfo->bulletOfStationaryTurret.coordinates.xCoordinate].types, BULLET_OF_STATIONARY_TURRET);
				// пуля исчезает
				gameInfo->bulletOfStationaryTurret.coordinates.xCoordinate = 0;
			}
		}
		// если перемещение не требуется и герой на одном уровне с турелью
		else if (step == NO_STEP && gameInfo->hero.coordinates.yCoordinate == gameInfo->stationary_turret.coordinates.yCoordinate)
		{
			gameInfo->hero.healthPoints -= DAMAGE_TO_HERO;	// у героя отнимается здоровье
		}
		// если героя нет на линии огня и пуля существует
		else if (turretCanShootHero == false && gameInfo->bulletOfStationaryTurret.coordinates.xCoordinate != 0)
		{
			// пуля перемещается
			moveBullet(BULLET_OF_STATIONARY_TURRET, gameInfo, map, step);
		}
	}
	else if (type == PLATFORM_TURRET)
	{
		// если с слева(справа) проходимое пространство и не существует пули и турель может стрелять
		if (map[gameInfo->platform_turret.coordinates.yCoordinate][gameInfo->platform_turret.coordinates.xCoordinate + step].passable == true &&
			gameInfo->bulletOfPlatformTurret.coordinates.xCoordinate == 0 && turretCanShootHero == true)
		{
			// справа(слева) создаётся пуля
			gameInfo->bulletOfPlatformTurret.coordinates.xCoordinate = gameInfo->platform_turret.coordinates.xCoordinate + step;
			gameInfo->bulletOfPlatformTurret.coordinates.yCoordinate = gameInfo->platform_turret.coordinates.yCoordinate;
			// справа(слева) создаётся текстура пули
			list::addBegin(&map[gameInfo->bulletOfPlatformTurret.coordinates.yCoordinate][gameInfo->bulletOfPlatformTurret.coordinates.xCoordinate].types, BULLET_OF_PLATFORM_TURRET);
		}
		
		// если пуля существует и возможно перемещение
		else if (gameInfo->bulletOfPlatformTurret.coordinates.xCoordinate != 0 && step != NO_STEP)
		{
			// если координаты пули и героя совпадают
			if ((gameInfo->bulletOfPlatformTurret.coordinates.yCoordinate == gameInfo->hero.coordinates.yCoordinate) &&
				(gameInfo->bulletOfPlatformTurret.coordinates.xCoordinate == gameInfo->hero.coordinates.xCoordinate))
			{
				gameInfo->hero.healthPoints -= DAMAGE_TO_HERO; // отнимается здоровье игрока
				// удаляется текстура пули
				list::deleteCurrentElement(&map[gameInfo->bulletOfPlatformTurret.coordinates.yCoordinate][gameInfo->bulletOfPlatformTurret.coordinates.xCoordinate].types, BULLET_OF_PLATFORM_TURRET);
				// пуля исчезает
				gameInfo->bulletOfPlatformTurret.coordinates.xCoordinate = 0;
			}
			// если справа(слева) от пули проходимое пространство
			else if (map[gameInfo->bulletOfPlatformTurret.coordinates.yCoordinate][gameInfo->bulletOfPlatformTurret.coordinates.xCoordinate + step].passable == true)
			{
				// пуля перемещается
				moveBullet(BULLET_OF_PLATFORM_TURRET, gameInfo, map, step);
			}

			else if (map[gameInfo->bulletOfPlatformTurret.coordinates.yCoordinate][gameInfo->bulletOfPlatformTurret.coordinates.xCoordinate + step].passable == false)
			{
				// удаляется текстура пули
				list::deleteCurrentElement(&map[gameInfo->bulletOfPlatformTurret.coordinates.yCoordinate][gameInfo->bulletOfPlatformTurret.coordinates.xCoordinate].types, BULLET_OF_PLATFORM_TURRET);
				// пуля исчезает
				gameInfo->bulletOfPlatformTurret.coordinates.xCoordinate = 0;
			}
		}
		// если перемещение не требуется и герой на одном уровне с турелью
		else if (gameInfo->hero.coordinates.xCoordinate == gameInfo->platform_turret.coordinates.xCoordinate &&
			gameInfo->hero.coordinates.yCoordinate == gameInfo->platform_turret.coordinates.yCoordinate)
		{
			gameInfo->hero.healthPoints -= DAMAGE_TO_HERO;	// у героя отнимается здоровье
		}
		// если героя нет на линии огня и пуля существует
		else if (turretCanShootHero == false && gameInfo->bulletOfPlatformTurret.coordinates.xCoordinate != 0)
		{
			// пуля перемещается
			moveBullet(BULLET_OF_PLATFORM_TURRET, gameInfo, map, step);
		}
	}

	else if (type == TURRET_HUNTER)
	{
		// если с слева(справа) проходимое пространство и не существует пули и турель может стрелять
		if (map[gameInfo->hunter_turret.coordinates.yCoordinate][gameInfo->hunter_turret.coordinates.xCoordinate + step].passable == true &&
			gameInfo->bulletOfHunterTurret.coordinates.xCoordinate == 0 && turretCanShootHero == true)
		{
			// справа(слева) создаётся пуля
			gameInfo->bulletOfHunterTurret.coordinates.xCoordinate = gameInfo->hunter_turret.coordinates.xCoordinate + step;
			gameInfo->bulletOfHunterTurret.coordinates.yCoordinate = gameInfo->hunter_turret.coordinates.yCoordinate;
			// справа(слева) создаётся текстура пули
			list::addBegin(&map[gameInfo->bulletOfHunterTurret.coordinates.yCoordinate][gameInfo->bulletOfHunterTurret.coordinates.xCoordinate].types, BULLET_OF_HUNTER_TURRET);
		}
		// если пуля существует и возможно перемещение
		else if (gameInfo->bulletOfHunterTurret.coordinates.xCoordinate != 0 && step != NO_STEP)
		{
			// если координаты пули и героя совпадают
			if ((gameInfo->bulletOfHunterTurret.coordinates.yCoordinate == gameInfo->hero.coordinates.yCoordinate) &&
				(gameInfo->bulletOfHunterTurret.coordinates.xCoordinate == gameInfo->hero.coordinates.xCoordinate))
			{
				gameInfo->hero.healthPoints -= DAMAGE_TO_HERO; // отнимается здоровье игрока
				 // удаляется текстура пули
				list::deleteCurrentElement(&map[gameInfo->bulletOfHunterTurret.coordinates.yCoordinate][gameInfo->bulletOfHunterTurret.coordinates.xCoordinate].types, BULLET_OF_HUNTER_TURRET);
				// пуля исчезает
				gameInfo->bulletOfHunterTurret.coordinates.xCoordinate = 0;
			}
			// если справа(слева) от пули проходимое пространство
			else if (map[gameInfo->bulletOfHunterTurret.coordinates.yCoordinate][gameInfo->bulletOfHunterTurret.coordinates.xCoordinate + step].passable == true)
			{
				// пуля перемещается
				moveBullet(BULLET_OF_HUNTER_TURRET, gameInfo, map, step);
			}

			else if (map[gameInfo->bulletOfHunterTurret.coordinates.yCoordinate][gameInfo->bulletOfHunterTurret.coordinates.xCoordinate + step].passable == false)
			{
				// удаляется текстура пули
				list::deleteCurrentElement(&map[gameInfo->bulletOfHunterTurret.coordinates.yCoordinate][gameInfo->bulletOfHunterTurret.coordinates.xCoordinate].types, BULLET_OF_HUNTER_TURRET);
				// пуля исчезает
				gameInfo->bulletOfHunterTurret.coordinates.xCoordinate = 0;
			}
		}
		// если перемещение не требуется и герой на одном уровне с турелью
		else if (gameInfo->hero.coordinates.xCoordinate == gameInfo->hunter_turret.coordinates.xCoordinate &&
			gameInfo->hero.coordinates.yCoordinate == gameInfo->hunter_turret.coordinates.yCoordinate)
		{
			gameInfo->hero.healthPoints -= DAMAGE_TO_HERO;	// у героя отнимается здоровье
		}
		// если героя нет на линии огня и пуля существует
		else if (turretCanShootHero == false && gameInfo->bulletOfHunterTurret.coordinates.xCoordinate != 0)
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
		list::addBegin(&map[gameInfo->bulletOfStationaryTurret.coordinates.yCoordinate][gameInfo->bulletOfStationaryTurret.coordinates.xCoordinate + step].types, BULLET_OF_STATIONARY_TURRET);
		// существующая текстура удаляется
		list::deleteCurrentElement(&map[gameInfo->bulletOfStationaryTurret.coordinates.yCoordinate][gameInfo->bulletOfStationaryTurret.coordinates.xCoordinate].types, BULLET_OF_STATIONARY_TURRET);
		// координата по Ox увеличивается(уменьшается) на step(на один)
		gameInfo->bulletOfStationaryTurret.coordinates.xCoordinate = gameInfo->bulletOfStationaryTurret.coordinates.xCoordinate + step;
	}

	else if (type == BULLET_OF_PLATFORM_TURRET)
	{	
		// слева(справа) создаётся текстура пули
		list::addBegin(&map[gameInfo->bulletOfPlatformTurret.coordinates.yCoordinate][gameInfo->bulletOfPlatformTurret.coordinates.xCoordinate + step].types, BULLET_OF_PLATFORM_TURRET);
		// существующая текстура удаляется
		list::deleteCurrentElement(&map[gameInfo->bulletOfPlatformTurret.coordinates.yCoordinate][gameInfo->bulletOfPlatformTurret.coordinates.xCoordinate].types, BULLET_OF_PLATFORM_TURRET);
		// координата по Ox увеличивается(уменьшается) на step(на один)
		gameInfo->bulletOfPlatformTurret.coordinates.xCoordinate = gameInfo->bulletOfPlatformTurret.coordinates.xCoordinate + step;
	}

	else if (type == BULLET_OF_HUNTER_TURRET)
	{
		// слева(справа) создаётся текстура пули
		list::addBegin(&map[gameInfo->bulletOfHunterTurret.coordinates.yCoordinate][gameInfo->bulletOfHunterTurret.coordinates.xCoordinate + step].types, BULLET_OF_HUNTER_TURRET);
		// существующая текстура удаляется
		list::deleteCurrentElement(&map[gameInfo->bulletOfHunterTurret.coordinates.yCoordinate][gameInfo->bulletOfHunterTurret.coordinates.xCoordinate].types, BULLET_OF_HUNTER_TURRET);
		// координата по Ox увеличивается(уменьшается) на step(на один)
		gameInfo->bulletOfHunterTurret.coordinates.xCoordinate = gameInfo->bulletOfHunterTurret.coordinates.xCoordinate + step;
	}
}

// Функция отвечает за перемещение патрулирующей турели
void game::platformTurretPatrol(GameInfo* gameInfo, MapCell** map, bool turretCanShootHero, int step)
{
	// sideOfMoving - переменная для хранения направления передвижения и размера одного шага
	int sideOfMoving = step;
	// если турель не может стрелять или если герой и турель на разной высоте
	if (turretCanShootHero == false ||
		gameInfo->hero.coordinates.yCoordinate != gameInfo->platform_turret.coordinates.yCoordinate)
	{
		// если справа проходимое пространство и турель двигалась вправо
		if (map[gameInfo->platform_turret.coordinates.yCoordinate][gameInfo->platform_turret.coordinates.xCoordinate + 1].passable == true && 
			gameInfo->platform_turret.isMovingRight == true)
		{
			sideOfMoving = 1;
			moveOx(sideOfMoving, PLATFORM_TURRET, gameInfo, map);
		}
		// если слева проходимое пространство и турель двигалась влево
		else if (map[gameInfo->platform_turret.coordinates.yCoordinate][gameInfo->platform_turret.coordinates.xCoordinate - 1].passable == true && 
			gameInfo->platform_turret.isMovingRight == false)
		{
			sideOfMoving = -1;
			moveOx(sideOfMoving, PLATFORM_TURRET, gameInfo, map);
		}
		// если справа непроходимое пространство
		else if (map[gameInfo->platform_turret.coordinates.yCoordinate][gameInfo->platform_turret.coordinates.xCoordinate + 1].passable == false)
		{
			sideOfMoving = -1;
			gameInfo->platform_turret.isMovingRight = false;
			moveOx(sideOfMoving, PLATFORM_TURRET, gameInfo, map);
		}
		// если слева непроходимое пространство
		else if (map[gameInfo->platform_turret.coordinates.yCoordinate][gameInfo->platform_turret.coordinates.xCoordinate - 1].passable == false)
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
		if (gameInfo->hero.coordinates.xCoordinate > gameInfo->hunter_turret.coordinates.xCoordinate + 4 &&
			map[gameInfo->hunter_turret.coordinates.yCoordinate][gameInfo->hunter_turret.coordinates.xCoordinate + step].passable == true)
		{
			// турель перемещается по Ox
			moveOx(step, TURRET_HUNTER, gameInfo, map);
		}
		// если герой левее турели на четыре клетки карты и слева от турели проходимое пространство
		else if (gameInfo->hero.coordinates.xCoordinate < gameInfo->hunter_turret.coordinates.xCoordinate - 4 &&
			map[gameInfo->hunter_turret.coordinates.yCoordinate][gameInfo->hunter_turret.coordinates.xCoordinate + step].passable == true)
		{
			// турель перемещается по Ox
			moveOx(step, TURRET_HUNTER, gameInfo, map);
		}
		// если герой правее турели на четыре клетки карты и справа от турели непроходимое пространство
		else if (gameInfo->hero.coordinates.xCoordinate > gameInfo->hunter_turret.coordinates.xCoordinate + 4 &&
			map[gameInfo->hunter_turret.coordinates.yCoordinate][gameInfo->hunter_turret.coordinates.xCoordinate + step].passable == false)
		{
			// турель прыгает
			jump(TURRET_HUNTER, gameInfo, map);
			// турель перемещается по Ox
			moveOx(step, TURRET_HUNTER, gameInfo, map);
		}
		// если герой левее турели на четыре клетки карты и слева от турели непроходимое пространство
		else if (gameInfo->hero.coordinates.xCoordinate < gameInfo->hunter_turret.coordinates.xCoordinate - 4 &&
			map[gameInfo->hunter_turret.coordinates.yCoordinate][gameInfo->hunter_turret.coordinates.xCoordinate + step].passable == false)
		{
			// турель прыгает
			jump(TURRET_HUNTER, gameInfo, map);
			// турель перемещается по Ox
			moveOx(step, TURRET_HUNTER, gameInfo, map);
		}
	}
}