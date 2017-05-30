#pragma once
#include "Tree.h"
#include "HighScores.h"
#include "List.h"
#include "Instruments.h"
#include "Algorithms.h"
#include <conio.h>

namespace search
{
	/**
	 * ¬ыводит на печать лучший результат на уровне. 
	 */
	void printFoundChampion(list::List<records::DataAboutTheChampion> *list, int key);

	/**
	 * —равнивает строки вне зависимости от регистра.
	 */
	int comparison(char *name, std::string str);

	/**
	 * ѕоиск по уровню до первого результата.
	 */
	tree::BranchForNumber<records::DataAboutTheChampion> *searchByLevelOfOneResult(tree::BranchForNumber<records::DataAboutTheChampion> *tree, int level);

	/**
	 * ѕоиск по очкам до первого результата.
	 */
	tree::BranchForNumber<records::DataAboutTheChampion> *searchByScoreOfOneResult(tree::BranchForNumber<records::DataAboutTheChampion> *tree, double score);

	/**
	 * ѕоиск по имени до первого результата.
	 */
	tree::BranchForNumber<records::DataAboutTheChampion> *searchByNameOfOneResult(tree::BranchForNumber<records::DataAboutTheChampion> *tree, char *name);

	/**
	 * «аполн€ет список найденными рекордсменами и возвращает указатель на этот список 
	 */
	template<typename T> list::List<records::DataAboutTheChampion> *searchAllElements(
		tree::BranchForNumber<records::DataAboutTheChampion> *tree,
		T data,
		tree::BranchForNumber<records::DataAboutTheChampion> *(*searchFunc)(tree::BranchForNumber<records::DataAboutTheChampion> *, T))
	{
		int counterOfLoop = 0;
		list::List<records::DataAboutTheChampion> *list = NULL;       // список с найденными рекорсдменами 
		tree::BranchForNumber<records::DataAboutTheChampion> **search = &tree;      // основной указатель на указатель дл€ поиска
		tree::BranchForNumber<records::DataAboutTheChampion> *temp = *search;       // указатель, дл€ инициализации списка

		while (temp)
		{
			if (counterOfLoop)     // не перва€ итераци€ 
			{
				*search = searchFunc(temp->right, data);    // вызываем функцию, соответствующую параметру заполнени€ дерева, 
														   //  от правой ветки текущего положени€ указател€ (чтобы не найти уже найденного рекордсмена)
			}
			else     // перва€ итераци€ 
			{
				*search = searchFunc(temp, data);       // вызываем функцию, соответствующую параметру заполнени€ дерева, от начала дерева
			}

			temp = *search;      // инициализируем указатель 
			if (temp)
			{
				list::addBegin(&list, temp->data);      // если есть что, то добавл€ем в список найденного рекордсмена
			}
			counterOfLoop++;     // счетчик итераций++
		}

		return list;
	}

	/**
	 * ѕоиск по подстроке в строке.
	 */
	records::DataAboutTheChampion searchBySubstringOfOneResult(records::DataAboutTheChampion subjectOfSearch, char *substring);

	/**
	 * ѕоиск по подстроке всех элементов из файла с рекордами.
	 */
	list::List<records::DataAboutTheChampion> *searchBySubstringAllResults(char *substring);
}