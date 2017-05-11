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
		shootHero(STATIONARY_TURRET, BULLET_OF_STATIONARY_TURRET, gameInfo, map, turretCanShootHero, step);
	}
	else if (type == PLATFORM_TURRET && gameInfo->platform_turret.coordinates.xCoordinate != 0)
	{
		int step = determineMovingDirection(PLATFORM_TURRET, gameInfo, map);
		bool turretCanShootHero = checkTurretShootingConditions(PLATFORM_TURRET, gameInfo, map, step);
		platformTurretPatrol(gameInfo, map, turretCanShootHero, step);
		shootHero(PLATFORM_TURRET, BULLET_OF_PLATFORM_TURRET, gameInfo, map, turretCanShootHero, step);
	}
	else if (type == TURRET_HUNTER && gameInfo->hunter_turret.coordinates.xCoordinate != 0)
	{
		int step = determineMovingDirection(TURRET_HUNTER, gameInfo, map);
		bool turretCanShootHero = checkTurretShootingConditions(TURRET_HUNTER, gameInfo, map, step);
		turretHunterMoving(gameInfo, map, turretCanShootHero, step);
		shootHero(TURRET_HUNTER, BULLET_OF_HUNTER_TURRET, gameInfo, map, turretCanShootHero, step);
	}
}

// Определяет направление движения объектов (пуль и турелей), основываясь на положении героя
int game::determineMovingDirection(char type, GameInfo* gameInfo, MapCell** map)
{
	int direction = NO_STEP;
	if (getCoordinates(gameInfo, HERO).xCoordinate > getCoordinates(gameInfo, type).xCoordinate)
	{
		direction = STEP_RIGHT_OR_DOWN;
	}
	else if (getCoordinates(gameInfo, HERO).xCoordinate < getCoordinates(gameInfo, type).xCoordinate)
	{
		direction = STEP_LEFT_OR_UP;
	}
	return direction;
}

// Проверяет, должна ли турель стрелять
bool game::checkTurretShootingConditions(char type, GameInfo* gameInfo, MapCell** map, int step)
{
	bool turretCanShoot = false;
	bool wallIsHere = false;
	int searcher = getCoordinates(gameInfo, type).xCoordinate;
	if (step != NO_STEP &&
		getCoordinates(gameInfo, HERO).yCoordinate == getCoordinates(gameInfo, type).yCoordinate)
	{
		while (getCoordinates(gameInfo, HERO).xCoordinate != searcher && wallIsHere == false)
		{
			if (map[getCoordinates(gameInfo, type).yCoordinate][searcher + step].types->value == HERO)
			{
				wallIsHere = false;
				// К координатам поиска прибаляется шаг
				searcher = searcher + step;
			}
			// Если по координатам поиска нет стены
			else if (map[getCoordinates(gameInfo, type).yCoordinate][searcher + step].types->value != BLOCK)
			{
				searcher = searcher + step;
			}
			// Если по координатам поиска есть стена
			else if (map[getCoordinates(gameInfo, type).yCoordinate][searcher + step].types->value == BLOCK)
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
	return turretCanShoot;
}

// Функция определяет поведение пули (ее появление, исчезновение)
void game::shootHero(char type, char bullet, GameInfo* gameInfo, MapCell** map, bool turretCanShootHero, int step)
{
	// если с слева(справа) проходимое пространство и не существует пули и турель может стрелять
	if (map[getCoordinates(gameInfo, type).yCoordinate][getCoordinates(gameInfo, type).xCoordinate + step].passable == true &&
	getCoordinates(gameInfo, bullet).xCoordinate == 0 && turretCanShootHero == true)
	{
		// справа(слева) создаётся пуля
		setOXCoordinates(gameInfo, bullet, step);
		setOYCoordinates(gameInfo, bullet);
		// справа(слева) создаётся текстура пули
		list::addBegin(&map[getCoordinates(gameInfo, bullet).yCoordinate][getCoordinates(gameInfo, bullet).xCoordinate].types, bullet);
	}

// если пуля существует и возможно перемещение
	else if (getCoordinates(gameInfo, bullet).xCoordinate != 0 && step != NO_STEP)
	{
		// если координаты пули и героя совпадают
		if ((getCoordinates(gameInfo, bullet).yCoordinate == getCoordinates(gameInfo, HERO).yCoordinate) &&
			(getCoordinates(gameInfo, bullet).xCoordinate == getCoordinates(gameInfo, HERO).xCoordinate))
		{
			gameInfo->hero.healthPoints -= DAMAGE_TO_HERO; // отнимается здоровье игрока
														   // удаляется текстура пули
			list::deleteCurrentElement(&map[getCoordinates(gameInfo, bullet).yCoordinate][getCoordinates(gameInfo, bullet).xCoordinate].types, bullet);
			// пуля исчезает
			setOXCoordinates(gameInfo, bullet, NO_STEP);
		}
		// если справа(слева) от пули проходимое пространство
		else if (map[getCoordinates(gameInfo, bullet).yCoordinate][getCoordinates(gameInfo, bullet).xCoordinate + step].passable == true)
		{
			// пуля перемещается
			moveBullet(bullet, gameInfo, map, step);
		}

		else if (map[getCoordinates(gameInfo, bullet).yCoordinate][getCoordinates(gameInfo, bullet).xCoordinate + step].passable == false)
		{
			// удаляется текстура пули
			list::deleteCurrentElement(&map[getCoordinates(gameInfo, bullet).yCoordinate][getCoordinates(gameInfo, bullet).xCoordinate].types, bullet);
			// пуля исчезает
			setOXCoordinates(gameInfo, bullet, NO_STEP);
		}
	}
// если перемещение не требуется и герой на одном уровне с турелью
	else if (step == NO_STEP && getCoordinates(gameInfo, HERO).yCoordinate == getCoordinates(gameInfo, type).yCoordinate)
	{
		gameInfo->hero.healthPoints -= DAMAGE_TO_HERO;	// у героя отнимается здоровье
	}
// если героя нет на линии огня и пуля существует
	else if (turretCanShootHero == false && getCoordinates(gameInfo, bullet).xCoordinate != 0)
	{
		// пуля перемещается
		moveBullet(bullet, gameInfo, map, step);
	}
}

// Функция отвечает за перемещение пули по карте
void game::moveBullet(char bullet, GameInfo* gameInfo, MapCell** map, int step)
{
	// слева(справа) создаётся текстура пули
	list::addBegin(&map[getCoordinates(gameInfo, bullet).yCoordinate][getCoordinates(gameInfo, bullet).xCoordinate + step].types, bullet);
	// существующая текстура удаляется
	list::deleteCurrentElement(&map[getCoordinates(gameInfo, bullet).yCoordinate][getCoordinates(gameInfo, bullet).xCoordinate].types, bullet);
	// координата по Ox увеличивается(уменьшается) на step(на один)
	changeOXCoordinates(gameInfo, bullet, step);
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
		if (map[gameInfo->platform_turret.coordinates.yCoordinate][gameInfo->platform_turret.coordinates.xCoordinate + STEP_RIGHT_OR_DOWN].passable == true && 
			gameInfo->platform_turret.isMovingRight == true)
		{
			sideOfMoving = 1;
			moveOx(sideOfMoving, PLATFORM_TURRET, gameInfo, map);
		}
		// если слева проходимое пространство и турель двигалась влево
		else if (map[gameInfo->platform_turret.coordinates.yCoordinate][gameInfo->platform_turret.coordinates.xCoordinate + STEP_LEFT_OR_UP].passable == true && 
			gameInfo->platform_turret.isMovingRight == false)
		{
			sideOfMoving = -1;
			moveOx(sideOfMoving, PLATFORM_TURRET, gameInfo, map);
		}
		// если справа непроходимое пространство
		else if (map[gameInfo->platform_turret.coordinates.yCoordinate][gameInfo->platform_turret.coordinates.xCoordinate + STEP_RIGHT_OR_DOWN].passable == false)
		{
			sideOfMoving = -1;
			gameInfo->platform_turret.isMovingRight = false;
			moveOx(sideOfMoving, PLATFORM_TURRET, gameInfo, map);
		}
		// если слева непроходимое пространство
		else if (map[gameInfo->platform_turret.coordinates.yCoordinate][gameInfo->platform_turret.coordinates.xCoordinate + STEP_LEFT_OR_UP].passable == false)
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
		if (gameInfo->hero.coordinates.xCoordinate > gameInfo->hunter_turret.coordinates.xCoordinate + RANGE_BETWEEN_HERO_AND_HUNTER_TURRET &&
			map[gameInfo->hunter_turret.coordinates.yCoordinate][gameInfo->hunter_turret.coordinates.xCoordinate + step].passable == true)
		{
			// турель перемещается по Ox
			moveOx(step, TURRET_HUNTER, gameInfo, map);
		}
		// если герой левее турели на четыре клетки карты и слева от турели проходимое пространство
		else if (gameInfo->hero.coordinates.xCoordinate < gameInfo->hunter_turret.coordinates.xCoordinate - RANGE_BETWEEN_HERO_AND_HUNTER_TURRET &&
			map[gameInfo->hunter_turret.coordinates.yCoordinate][gameInfo->hunter_turret.coordinates.xCoordinate + step].passable == true)
		{
			// турель перемещается по Ox
			moveOx(step, TURRET_HUNTER, gameInfo, map);
		}
		// если герой правее турели на четыре клетки карты и справа от турели непроходимое пространство
		else if (gameInfo->hero.coordinates.xCoordinate > gameInfo->hunter_turret.coordinates.xCoordinate + RANGE_BETWEEN_HERO_AND_HUNTER_TURRET &&
			map[gameInfo->hunter_turret.coordinates.yCoordinate][gameInfo->hunter_turret.coordinates.xCoordinate + step].passable == false)
		{
			// турель прыгает
			jump(TURRET_HUNTER, gameInfo, map);
			// турель перемещается по Ox
			moveOx(step, TURRET_HUNTER, gameInfo, map);
		}
		// если герой левее турели на четыре клетки карты и слева от турели непроходимое пространство
		else if (gameInfo->hero.coordinates.xCoordinate < gameInfo->hunter_turret.coordinates.xCoordinate - RANGE_BETWEEN_HERO_AND_HUNTER_TURRET &&
			map[gameInfo->hunter_turret.coordinates.yCoordinate][gameInfo->hunter_turret.coordinates.xCoordinate + step].passable == false)
		{
			// турель прыгает
			jump(TURRET_HUNTER, gameInfo, map);
			// турель перемещается по Ox
			moveOx(step, TURRET_HUNTER, gameInfo, map);
		}
	}
}