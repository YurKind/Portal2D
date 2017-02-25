#define _CRT_SECURE_NO_WARNINGS

#include "Menu.h"
#include "Gameplay.h"
#include <fstream>

using namespace std;
/*
	¬Ќ»ћјЌ»≈! (кто не будет соблюдать правила - того ебЄм в жопу стулом)

	1)	»мена, представл€ющие типы, должны быть об€зательно написаны в смешанном регистре, начина€ с верхнего.
	Line, SavingsAccount

	2)	»мена переменных должны быть записаны в смешанном регистре, начина€ с нижнего.
	line, savingsAccount

	3)	»менованные константы (включа€ значени€ перечислений) должны быть записаны в верхнем регистре с нижним подчЄркиванием в качестве разделител€.
	MAX_ITERATIONS, COLOR_RED, PI

	4)	Ќазвани€ методов и функций должны быть глаголами, быть записанными в смешанном регистре и начинатьс€ с нижнего.
	getName(), computeTotalWidth()

	5)	Ќазвани€ пространств имЄн следует записывать в нижнем регистре.
	model::analyzer, io::iomanager, common::math::geometry            !!!!!!!!!!!(при написание своего модул€ все ваши авторские функции заключайте в пространства имЄн (namespace) в хедере)

	6)	—ледует называть имена типов в шаблонах одной заглавной буквой.
	template<class T> 

	7)	јббревиатуры и сокращени€ в именах должны записыватьс€ в нижнем регистре.
	exportHtmlSource(); // Ќ≈Ћ№«я: exportHTMLSource();

	8)	Ќастраиваемым (в нашем случае - структурным) переменным следует давать то же им€, что и у их типа.
	void setTopic(Topic* topic)      // Ќ≈Ћ№«я: void setTopic(Topic* value)
		                             // Ќ≈Ћ№«я: void setTopic(Topic* aTopic)
			                         // Ќ≈Ћ№«я: void setTopic(Topic* t)
	9)	¬се имена следует записывать по-английски.
	fileName;   // Ќ≈ –≈ ќћ≈Ќƒ”≈“—я: imyaFayla

	10)	ѕеременные, имеющие большую область видимости, следует называть длинными именами, имеющие небольшую область видимости Ч короткими.

	11)	»мена объектов не указываютс€ €вно, следует избегать указани€ названий объектов в именах методов.  (проводим параллель со структурами)
	line.getLength();   // Ќ≈ –≈ ќћ≈Ќƒ”≈“—я: line.getLineLength();

	12)	—лово find может быть использовано в функци€х, осуществл€ющих какой-либо поиск.
	findMinElement();

	13)	ѕрефикс n следует использовать дл€ представлени€ числа объектов.
	nPoints, nLines

	14) —уффикс No следует использовать дл€ обозначени€ номера сущности.
	tableNo, employeeNo

	15)	—ледует избегать сокращений в именах.
	computeAverage();   // Ќ≈Ћ№«я: compAvg();

	16)	—ледует избегать дополнительного именовани€ указателей.
	Line* line; // Ќ≈ –≈ ќћ≈Ќƒ”≈“—я: Line* pLine;
		        // Ќ≈ –≈ ќћ≈Ќƒ”≈“—я: Line* linePtr;

	17)  Ќельз€ давать булевым (логическим) переменным имена, содержащие отрицание.
	bool isError; // Ќ≈Ћ№«я: isNoError
	bool isFound; // Ќ≈Ћ№«я: isNotFound

	18)	 онстанты в перечислени€х ћќ√”“ иметь (могут не иметь) префикс Ч общее им€ типа.
	enum Color {
	COLOR_RED,
	COLOR_GREEN,
	COLOR_BLUE
	};
*/

int main()
{
	const int sizeOfMapHeight = 20;
	const int sizeOfMapWidth = 35;
	//menu::functionCaller(menu::menu());


	game::Map** map = game::createMap(sizeOfMapHeight, sizeOfMapWidth);

	char currentSymbol;
	ifstream fin("Lvl_1.txt", ios_base::in);

	for (int i = 0; i < sizeOfMapHeight; i++)
	{
		for (int j = 0; j < sizeOfMapWidth; j++)
		{
			currentSymbol = fin.get();
			if (currentSymbol == NEW_LINE)
				currentSymbol = fin.get();

			switch (currentSymbol)
			{
			case BLOCK_SHARP:
				map[i][j].type = BLOCK;
				map[i][j].block.xCoordinate = i;
				map[i][j].block.yCoordinate = j;
				break;
			case EMPTY_SPACE:
				map[i][j].type = EMPTY_SPACE;
				map[i][j].emptySpace.xCoordinate = i;
				map[i][j].emptySpace.yCoordinate = j;
				break;
			default:
				break;
			}
		}
	}
	fin.close();

	for (int i = 0; i < sizeOfMapHeight; i++)
	{
		for (int j = 0; j < sizeOfMapWidth; j++)
		{
			switch (map[i][j].type)
			{
			case BLOCK:
				cout << BLOCK;
				break;
			case EMPTY_SPACE:
				cout << EMPTY_SPACE;
				break;
			}
		}
		cout << endl;
	}

	system("pause");

	return 0;
}
