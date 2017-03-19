#pragma once
#include "Tree.h"
#include "Records.h"
#include "List.h"
#include "Instruments.h"
#include <conio.h>

namespace search
{
	/* В зависимости от введенных параметров руководит процессом поиска */
	template<typename T> void setSearchParametr(int parametr)
	{
		list::List<records::DataAboutTheChampion> *list = NULL;       // список с найденными рекорсдменами 
		tree::BranchForNumber<records::DataAboutTheChampion> *tree = NULL;        // дерево со всеми рекордсменами 
		double numberOfScore = 0.0;
		int numberOfLevel = 0;
		char *name = new char[1000];
		switch (parametr)
		{
		case SCORE:
			createTree(&tree, FILE_NAME_RECORDS, SCORE);     // создаем и инициализируем список по очкам
			std::cout << "\tenter the number of score: ";
			std::cin >> numberOfScore;
			std::cout << "\n";
			list = searchAllElements<double>(tree, numberOfScore, searchByScoreOfOneResult);       // указатель на список с найденными рекорсдменами 
			break;

		case LEVEL:
			createTree(&tree, FILE_NAME_RECORDS, LEVEL);     // создаем и инициализируем список по уровням
			std::cout << "\tenter the number of level: ";
			std::cin >> numberOfLevel;
			std::cout << "\n";
			list = searchAllElements<int>(tree, numberOfLevel, searchByLevelOfOneResult);       // указатель на список с найденными рекорсдменами 
			break;

		case STRING:
			createTree(&tree, FILE_NAME_RECORDS, STRING);     // создаем и инициализируем список по именам
			std::cout << "\tenter the string: ";
			std::cin >> name;
			std::cout << "\n";
			list = searchAllElements<char*>(tree, name, searchByStringOfOneResult);       // указатель на список с найденными рекорсдменами 
			break;
		}
		printFoundChampions(list);        // печатаем список с найденными рекордсменами
		list::freeMemory(list);
		tree::freeMemory(tree);
		delete[] name;
		_getch();
		system("cls");
	}

	void printFoundChampions(list::List<records::DataAboutTheChampion> *list);

	int comparison(char *name, std::string str);

	tree::BranchForNumber<records::DataAboutTheChampion> *searchByLevelOfOneResult(tree::BranchForNumber<records::DataAboutTheChampion> *tree, int level);

	tree::BranchForNumber<records::DataAboutTheChampion> *searchByScoreOfOneResult(tree::BranchForNumber<records::DataAboutTheChampion> *tree, double score);

	tree::BranchForNumber<records::DataAboutTheChampion> *searchByStringOfOneResult(tree::BranchForNumber<records::DataAboutTheChampion> *tree, char *name);

	/* Заполняет список найденными рекордсменами и возвращает указатель на этот список*/
	template<typename T> list::List<records::DataAboutTheChampion> *searchAllElements(
		tree::BranchForNumber<records::DataAboutTheChampion> *tree,
		T data,
		tree::BranchForNumber<records::DataAboutTheChampion>*(*searchFunc)(tree::BranchForNumber<records::DataAboutTheChampion> *, T)
	)
	{
		int counterOfLoop = 0;
		list::List<records::DataAboutTheChampion> *list = NULL;       // список с найденными рекорсдменами 
		tree::BranchForNumber<records::DataAboutTheChampion> **search = &tree;      // основной указатель на указатель для поиска
		tree::BranchForNumber<records::DataAboutTheChampion> *temp = *search;       // указатель, для инициализации списка
		while (temp)
		{
			if (counterOfLoop)     // не первая итерация 
			{
				*search = searchFunc(temp->right, data);    // вызываем функцию, соответствующую параметру заполнения дерева, 
				                                      // от правой ветки текущего положения указателя (чтобы не найти уже найденного рекордсмена)
			}
			else    // первая итерация 
			{
				*search = searchFunc(temp, data);       // вызываем функцию, соответствующую параметру заполнения дерева, от начала дерева
			}
			temp = *search;      // инициализируем указатель 
			if (temp)
			{
				list::addBegin(&list, temp->data);      // если есть что, то добавляем в список найденного рекордсмена
			}
			counterOfLoop++;     // счетчик итераций++
		}
		return list;
	}
}