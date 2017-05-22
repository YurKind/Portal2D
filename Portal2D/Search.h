#pragma once
#include "Tree.h"
#include "HighScores.h"
#include "List.h"
#include "Instruments.h"
#include "SortingMethods.h"
#include <conio.h>

namespace search
{
	void printFoundChampions(list::List<records::DataAboutTheChampion> *list, int key);

	int comparison(char *name, std::string str);

	tree::BranchForNumber<records::DataAboutTheChampion> *searchByLevelOfOneResult(tree::BranchForNumber<records::DataAboutTheChampion> *tree, int level);

	tree::BranchForNumber<records::DataAboutTheChampion> *searchByScoreOfOneResult(tree::BranchForNumber<records::DataAboutTheChampion> *tree, double score);

	tree::BranchForNumber<records::DataAboutTheChampion> *searchByStringOfOneResult(tree::BranchForNumber<records::DataAboutTheChampion> *tree, char *name);

	/* Заполняет список найденными рекордсменами и возвращает указатель на этот список */
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
														   //  от правой ветки текущего положения указателя (чтобы не найти уже найденного рекордсмена)
			}
			else     // первая итерация 
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

	records::DataAboutTheChampion searchBySubstringOfOneResult(records::DataAboutTheChampion subjectOfSearch, char *substring);

	list::List<records::DataAboutTheChampion> *searchBySubstringAllResults(list::List<records::DataAboutTheChampion> *result, char *substring);
}