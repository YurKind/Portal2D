#pragma once
#include "Tree.h"
#include "Records.h"
#include "List.h"
#include "Instruments.h"
#include <conio.h>

namespace search
{
	template<typename T> void setSearchParametr(int parametr)
	{
		list::List<records::DataAboutTheChampion> *list = NULL;
		tree::BranchForNumber<records::DataAboutTheChampion> *tree = NULL;
		double numberOfScore = 0.0;
		int numberOfLevel = 0;
		char *name = new char[1000];
		switch (parametr)
		{
		case SCORE:
			addTree(&tree, FILE_NAME_RECORDS, SCORE);
			std::cout << "\tenter the number of score: ";
			std::cin >> numberOfScore;
			std::cout << "\n";
			list = searchAllElements<double>(tree, numberOfScore, searchByScoreOfOneResult);
			break;

		case LEVEL:
			addTree(&tree, FILE_NAME_RECORDS, LEVEL);
			std::cout << "\tenter the number of level: ";
			std::cin >> numberOfLevel;
			std::cout << "\n";
			list = searchAllElements<int>(tree, numberOfLevel, searchByLevelOfOneResult);
			break;

		case STRING:
			addTree(&tree, FILE_NAME_RECORDS, STRING);
			std::cout << "\tenter the string: ";
			std::cin >> name;
			std::cout << "\n";
			list = searchAllElements<char *>(tree, name, searchByStringOfOneResult);
			break;
		}
		printFoundChampions(list);
		list::freeMemory(list);
		tree::freeMemory(tree);
		_getch();
		system("cls");
	}

	void printFoundChampions(list::List<records::DataAboutTheChampion> *list);

	int comparison(char *name, std::string str);

	tree::BranchForNumber<records::DataAboutTheChampion> *searchByLevelOfOneResult(tree::BranchForNumber<records::DataAboutTheChampion> *begin, int level);

	tree::BranchForNumber<records::DataAboutTheChampion> *searchByScoreOfOneResult(tree::BranchForNumber<records::DataAboutTheChampion> *begin, double score);

	tree::BranchForNumber<records::DataAboutTheChampion> *searchByStringOfOneResult(tree::BranchForNumber<records::DataAboutTheChampion> *begin, char *name);

	template<typename T> list::List<records::DataAboutTheChampion> *searchAllElements(
		tree::BranchForNumber<records::DataAboutTheChampion> *tree,
		T data,
		tree::BranchForNumber<records::DataAboutTheChampion>*(*searchFunc)(tree::BranchForNumber<records::DataAboutTheChampion> *, T)
	)
	{
		int counterOfLoop = 0;
		list::List<records::DataAboutTheChampion> *list = NULL;
		tree::BranchForNumber<records::DataAboutTheChampion> **s = &tree;
		tree::BranchForNumber<records::DataAboutTheChampion> *search = *s;
		while (search)
		{
			if (counterOfLoop)
			{
				*s = searchFunc(search->right, data);
			}
			else
			{
				*s = searchFunc(search, data);
			}
			search = *s;
			if (search)
			{
				list::addBegin(&list, search->data);
			}
			counterOfLoop++;
		}
		return list;
	}
}