#pragma once

//------TEXTURES------//
#define HERO '\2'			// символ героя в игре '☻'
#define HERO_SYMBOL 'H'		// символ героя в текстовом файле
#define BLOCK_SHARP '#'		// символ блока в текстовом файле
#define BLOCK char(219)		// символ блока в игре '█'
#define EMPTY_SPACE ' '		// символ пустого пространства
#define BUTTON_S '`'		// символ кнопки в текстовом файле
#define BUTTON char(127)	// символ кнопки в игре '⌂'
#define RED_PORTAL 'O'		// символ красного портала
#define BLUE_PORTAL '0'		// символ синего портала
#define AIM '+'				// символ прицела в текстовом файле
#define AIM_DOT '.'			// символ прицела в игре '.'
#define BLACK_WALL (char)176// символ непроходимой стены в игре '░'
#define BLACK_WALL_S 'X'	// символ непроходимой стены в текстовом файле
#define EXIT (char)178		// символ выхода в игре '▓'
#define EXIT_S 'E'			// символ выхода в текстовом файле
#define BULLET_OF_STATIONARY_TURRET char(250)	// символ пули от стационарной турели в игре '·'
#define BULLET_OF_PLATFORM_TURRET char(249)		// символ пули от патрулируещей турели в игре '∙'
#define BULLET_OF_HUNTER_TURRET '~'				// символ пули от турели охотника '~'

//------MAP------//
#define NEW_LINE '\n'		// символ новой строки (для считывания из файла)
#define MAP_HEIGHT 20		// высота карты
#define MAP_WIDTH 35		// ширина карты

//------MOVE_KEYS------//
#define W_UPPER_CASE 87		// клавиша 'W' (в верхнем регистре)
#define A_UPPER_CASE 65		// клавиша 'A' (в верхнем регистре)
#define S_UPPER_CASE 83		// клавиша 'S' (в верхнем регистре)
#define D_UPPER_CASE 68		// клавиша 'D' (в верхнем регистре)

#define W_LOWER_CASE 119	// клавиша 'w' (в нижнем регистре)
#define A_LOWER_CASE 97		// клавиша 'a' (в нижнем регистре)
#define S_LOWER_CASE 115	// клавиша 's' (в нижнем регистре)
#define D_LOWER_CASE 100	// клавиша 'd' (в нижнем регистре)

#define W_UPPER_CASE_RU 150	// клавиша 'Ц' (в верхнем регистре)
#define A_UPPER_CASE_RU 148	// клавиша 'Ф' (в верхнем регистре)
#define S_UPPER_CASE_RU 155	// клавиша 'Ы' (в верхнем регистре)
#define D_UPPER_CASE_RU 130	// клавиша 'В' (в верхнем регистре)

#define W_LOWER_CASE_RU 230	// клавиша 'ц' (в нижнем регистре)
#define A_LOWER_CASE_RU 228	// клавиша 'ф' (в нижнем регистре)
#define S_LOWER_CASE_RU 235	// клавиша 'ы' (в нижнем регистре)
#define D_LOWER_CASE_RU 162	// клавиша 'в' С

#define SPACE_JUMP 32

//------AIM_KEYS------//
#define ARROWS 224
#define UP_ARROW 72		// стерлка вверх
#define LEFT_ARROW 75	// стрелка влево
#define DOWN_ARROW 80	// стрелка вниз
#define RIGHT_ARROW 77	// стрелка вправо

//------PORTAL_GUN_KEYS------//
#define Q_UPPER_CASE 81		// клавиша 'Q' (в верхнем регистре)
#define E_UPPER_CASE 69		// клавиша 'E' (в верхнем регистре)
#define Q_LOWER_CASE 113	// клавиша 'q' (в нижнем регистре)
#define E_LOWER_CASE 101	// клавиша 'e' (в нижнем регистре)
#define Q_UPPER_CASE_RU 137	// клавиша 'Й' (в верхнем регистре)
#define E_UPPER_CASE_RU 147	// клавиша 'У' (в верхнем регистре)
#define Q_LOWER_CASE_RU 169	// клавиша 'й' (в нижнем регистре)
#define E_LOWER_CASE_RU 227	// клавиша 'у' (в нижнем регистре)

//------ACTION_KEYS------//
#define ENTER 13	// клавиша 'Enter'
#define BACKSPACE 8	// клавиша 'backspace'
#define PAUSE 'p'	// клавиша 'p'
#define YES 'y'		// клавиша 'y'
#define NO 'n'		// клавиша 'n'

/* SAVE THE GAME */
#define SAVE 'k'

/* TURRET */
#define DAMAGE_TO_HERO 33			// урон по герою
#define HERO_SPOTTING_RANGE_X 10	// дистанция обнаружения героя турелью по оси Ох
#define HERO_SPOTTING_RANGE_Y 5		// дистанция обнаружения героя турелью по оси Оу
#define TURRET_HUNTER_S '+'			// символ турели-охотника в текстовом файле
#define TURRET_HUNTER char(209)		// символ турели-охотника в игре '╤'
#define STATIONARY_TURRET_S '='		// символ патрулирующей турели в текстовом файле
#define STATIONARY_TURRET char(193)	// символ патрулирующей турели в игре '┴'
#define PLATFORM_TURRET_S '*'		// символ патрулирующей турели в текстовом файле
#define PLATFORM_TURRET char(207)	// символ патрулирующей турели в игре '╧'
#define STEP_RIGHT_DOWN 1				// шаг объекта вправо (турели и пули)
#define STEP_LEFT_UP -1				// шаг объекта влево (турели и пули)
#define NO_STEP 0					// отсутствие шага 