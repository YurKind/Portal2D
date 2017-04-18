#include "TurretAI.h"
#include "Map.h"
#include "Definitions.h"

void game::stationaryTurret(GameInfo* gameInfo, MapCell** map)
{
	int step = determinePositionOfHero(gameInfo, map);
	bool turretCanShootingToHero = checkTurretShotConditions(gameInfo, map, step);
	shootingToHero(gameInfo, map, turretCanShootingToHero, step);
	//platformTurretPatrol(gameInfo, map, step);
}

int game::determinePositionOfHero(GameInfo* gameInfo, MapCell** map)
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

bool game::checkTurretShotConditions(GameInfo* gameInfo, MapCell** map, int step)
{
	if (step != 0)
	{
		int wallIsHere = false;
		int searcher = gameInfo->stationary_turret.xCoordinate;
		while (gameInfo->hero.xCoordinate != searcher && wallIsHere == false)
		{
			if (map[gameInfo->stationary_turret.yCoordinate][searcher + step].passable == true)
			{
				searcher = searcher + step;
			}
			else
			{
				wallIsHere = true;
			}
		}
		return !wallIsHere;
	}
}

void game::shootingToHero(GameInfo* gameInfo, MapCell** map, bool turretCanShootingToHero, int step)
{
	if (turretCanShootingToHero == true || gameInfo->bullet.xCoordinate != 0)
	{
		if (map[gameInfo->stationary_turret.yCoordinate][gameInfo->stationary_turret.xCoordinate + step].passable == true &&
			gameInfo->bullet.xCoordinate == 0)
		{
			gameInfo->bullet.xCoordinate = gameInfo->stationary_turret.xCoordinate + step;
			gameInfo->bullet.yCoordinate = gameInfo->stationary_turret.yCoordinate;
			list::addBegin(&map[gameInfo->bullet.yCoordinate][gameInfo->bullet.xCoordinate].types, BULLET);
		}

		else if (gameInfo->bullet.xCoordinate != 0)
		{
			if ((gameInfo->bullet.yCoordinate == gameInfo->hero.yCoordinate) &&
				(gameInfo->bullet.xCoordinate == gameInfo->hero.xCoordinate))
			{
				gameInfo->hero.healthPoints -= DAMAGE_TO_HERO; // отнимается здоровье игрока
				// удаляется текстура пули
				list::deleteCurrentElement(&map[gameInfo->bullet.yCoordinate][gameInfo->bullet.xCoordinate].types, BULLET);
				// пуля исчезает
				gameInfo->bullet.xCoordinate = 0;
			}
			else if (map[gameInfo->bullet.yCoordinate][gameInfo->bullet.xCoordinate + step].passable == true)
			{
				moveBullet(gameInfo, map, step);
			}

			else if (map[gameInfo->bullet.yCoordinate][gameInfo->bullet.xCoordinate + step].passable == false)
			{
				// удаляется текстура пули
				list::deleteCurrentElement(&map[gameInfo->bullet.yCoordinate][gameInfo->bullet.xCoordinate].types, BULLET);
				// пуля исчезает
				gameInfo->bullet.xCoordinate = 0;
			}
		}

		else
		{
			gameInfo->hero.healthPoints -= DAMAGE_TO_HERO;	// у героя отнимается здоровье
		}
	}
}

void game::moveBullet(GameInfo* gameInfo, MapCell** map, int step)
{
	// в ячейку слева добавляется символ турели
	list::addBegin(&map[gameInfo->bullet.yCoordinate][gameInfo->bullet.xCoordinate + step].types, BULLET);
	// из текущей ячейки удаляется символ турели
	list::deleteCurrentElement(&map[gameInfo->bullet.yCoordinate][gameInfo->bullet.xCoordinate].types, BULLET);
	gameInfo->bullet.xCoordinate = gameInfo->bullet.xCoordinate + step;
}

//void game::platformTurretPatrol(GameInfo* gameInfo, MapCell** map, int step)
//{
//	if (step == 0)
//	{
//
//	}
//}



































//// Фукнция отвечает за работу ИИ турели
//void game::turretPatrolAI(GameInfo* gameInfo, MapCell** map, bool *isMovingRight)
//{
//	//bool heroIsSpotted = spottingHeroPatrol(gameInfo, map);
//	// переменная хранит в себе информацию о наличии стены между турелью и героем
//	// true - стена есть, false - стены нет
//	bool wallIsHere = checkTheWall(gameInfo, map);
//	//запускается функция патрулирования турели
//	turretPatrol(gameInfo, map, isMovingRight, &wallIsHere);
//	// запускается функция стрельбы турели
//	shootingToHeroPatrol(gameInfo, map, &wallIsHere);
//}
//
//// Функция проверяет, есть ли между героем и турелью стены
//bool game::checkTheWall(GameInfo* gameInfo, MapCell** map)
//{
//	// если герой и турель находятся на одной высоте, и герой находится правее
//	if (gameInfo->hero.yCoordinate == gameInfo->platform_turret.yCoordinate &&
//		gameInfo->hero.xCoordinate > gameInfo->platform_turret.xCoordinate)
//	{
//		// поиск стен между героем и турелью
//		for (int i = gameInfo->platform_turret.xCoordinate; i < gameInfo->hero.xCoordinate; i++)
//		{
//			if (map[gameInfo->platform_turret.yCoordinate][i].passable == false)
//			{
//				return true; // если стена найдена - возвращается зачение true
//			}
//		}
//	}
//	// если герой и турель находятся на одной высоте, и герой находится левее
//	else if (gameInfo->hero.yCoordinate == gameInfo->platform_turret.yCoordinate &&
//		gameInfo->hero.xCoordinate < gameInfo->platform_turret.xCoordinate)
//	{
//		// поиск стен между героем и турель
//		for (int i = gameInfo->platform_turret.xCoordinate; i > gameInfo->hero.xCoordinate; i--)
//		{
//			if (map[gameInfo->platform_turret.yCoordinate][i].passable == false)
//			{
//				return true; // если стена найдена - возвращается зачение true
//			}
//		}
//	}
//	return false;	// если стена не найдена - возвращается зачение false
//}
//
//// Фукнция отвечает за стрельбу по герою
//void game::shootingToHeroPatrol(GameInfo* gameInfo, MapCell** map, bool *wallIsHere)
//{
//	// Начинает стрельбу только если между героем и турелью отсутствуют стены
//	if (*wallIsHere == false && gameInfo->hero.yCoordinate == gameInfo->platform_turret.yCoordinate)
//	{
//		// если герой правее турели
//		if (gameInfo->hero.xCoordinate > gameInfo->platform_turret.xCoordinate)
//		{
//			// если пуля существует и справа от турели проходимое пространство
//			if (gameInfo->bullet.xCoordinate == 0 &&
//				map[gameInfo->platform_turret.yCoordinate][gameInfo->platform_turret.xCoordinate + 1].passable == true)
//			{
//				// справа от турели появляется пуля
//				gameInfo->bullet.xCoordinate = gameInfo->platform_turret.xCoordinate + 1;
//				gameInfo->bullet.yCoordinate = gameInfo->platform_turret.yCoordinate;
//				// справа от турели появляется текстура пули
//				list::addBegin(&map[gameInfo->bullet.yCoordinate][gameInfo->bullet.xCoordinate].types, BULLET);
//			}
//		}
//		// если герой левее турели
//		else if (gameInfo->hero.xCoordinate < gameInfo->platform_turret.xCoordinate)
//		{
//			// если пули не существует и слева от турели проходимое пространство
//			if (gameInfo->bullet.xCoordinate == 0 &&
//				map[gameInfo->platform_turret.yCoordinate][gameInfo->platform_turret.xCoordinate - 1].passable == true)
//			{
//				// слева от турели появляется пуля
//				gameInfo->bullet.xCoordinate = gameInfo->platform_turret.xCoordinate - 1;
//				gameInfo->bullet.yCoordinate = gameInfo->platform_turret.yCoordinate;
//				// слева от турели появояется текстура пули
//				list::addBegin(&map[gameInfo->bullet.yCoordinate][gameInfo->bullet.xCoordinate].types, BULLET);
//			}
//		}
//		// если герой и турель в одной клетке
//		else if ((gameInfo->hero.xCoordinate == gameInfo->platform_turret.xCoordinate) &&
//			(gameInfo->hero.yCoordinate == gameInfo->platform_turret.yCoordinate))
//		{
//			gameInfo->hero.healthPoints -= DAMAGE_TO_HERO;	// у героя отнимается здоровье
//		}
//	}
//	// Если герой находится справа
//	if (gameInfo->hero.xCoordinate > gameInfo->platform_turret.xCoordinate)
//	{
//		shootingRight(gameInfo, map);	// турель стреляет вправо
//	}
//
//	// Если герой находится слева
//	else if (gameInfo->hero.xCoordinate < gameInfo->platform_turret.xCoordinate)
//	{
//		shootingLeft(gameInfo, map);	// турель стреляет влево
//	}
//}
//
//// Отвечает за стрельбу вправо
//void game::shootingRight(GameInfo* gameInfo, MapCell** map)
//{
//	// если пуля существует
//	if (gameInfo->bullet.xCoordinate != 0)
//	{
//		// если координаты пули и игрока совпадают
//		if ((gameInfo->bullet.yCoordinate == gameInfo->hero.yCoordinate) &&
//			(gameInfo->bullet.xCoordinate == gameInfo->hero.xCoordinate))
//		{
//			gameInfo->hero.healthPoints -= DAMAGE_TO_HERO; // отнимается здоровье игрока
//			// удаляется текстура пули
//			list::deleteCurrentElement(&map[gameInfo->bullet.yCoordinate][gameInfo->bullet.xCoordinate].types, BULLET);
//			// пуля исчезает
//			gameInfo->bullet.xCoordinate = 0;
//		}
//		// если справа от пули проходимое пространство
//		else if (map[gameInfo->bullet.yCoordinate][gameInfo->bullet.xCoordinate + 1].passable == true)
//		{
//			moveRight(BULLET, gameInfo, map);	//пуля перемещается вправо
//		}
//		// если справа от пули непроходимое пространство
//		else if (map[gameInfo->bullet.yCoordinate][gameInfo->bullet.xCoordinate + 1].passable == false)
//		{
//			// текстура пули исчезает
//			list::deleteCurrentElement(&map[gameInfo->bullet.yCoordinate][gameInfo->bullet.xCoordinate].types, BULLET);
//			// пуля исчезает
//			gameInfo->bullet.xCoordinate = 0;
//		}
//	}
//}
//
//// Отвечает за стрельбу влево
//void game::shootingLeft(GameInfo* gameInfo, MapCell** map)
//{
//	// если пуля существует
//	if (gameInfo->bullet.xCoordinate != 0)
//	{
//		// если координаты пули и игрока совпадают
//		if ((gameInfo->bullet.yCoordinate == gameInfo->hero.yCoordinate) &&
//			(gameInfo->bullet.xCoordinate == gameInfo->hero.xCoordinate))
//		{
//			gameInfo->hero.healthPoints -= DAMAGE_TO_HERO; // отнимается здоровье игрока
//			// удаляется текстура пули
//			list::deleteCurrentElement(&map[gameInfo->bullet.yCoordinate][gameInfo->bullet.xCoordinate].types, BULLET);
//			// пуля исчезает
//			gameInfo->bullet.xCoordinate = 0;
//		}
//		// если слева от пули проходимое пространство
//		else if (map[gameInfo->bullet.yCoordinate][gameInfo->bullet.xCoordinate - 1].passable == true)
//		{
//			moveLeft(BULLET, gameInfo, map); // пуля перемещается влево
//		}
//		// если слева от пули непроходимое пространство
//		else if (map[gameInfo->bullet.yCoordinate][gameInfo->bullet.xCoordinate - 1].passable == false)
//		{
//			// удаляется текстура пули
//			list::deleteCurrentElement(&map[gameInfo->bullet.yCoordinate][gameInfo->bullet.xCoordinate].types, BULLET);
//			// пуля исчезает
//			gameInfo->bullet.xCoordinate = 0;
//		}
//	}
//}
//
//// Отвечает за патрулирование местности турелью
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



















/*


			TURRET HUNTER BELOW


*/

//void game::turretAI(GameInfo* gameInfo, MapCell** map)
//{
//	bool heroIsSpotted = false;
//	heroIsSpotted = spottingHero(gameInfo, map);
//	turretMoving(gameInfo, map, heroIsSpotted);
//	shootingToHero(gameInfo, map, heroIsSpotted);
//}

//// Функция проверяет, находится ли герой в зоне видимости турели
//bool game::spottingHeroPatrol(GameInfo* gameInfo, MapCell** map)
//{
//	bool heroIsSpotted = false;
//	if (gameInfo->hero.yCoordinate == gameInfo->platform_turret.yCoordinate)
//	{
//		return true;
//	}
//	return false;
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