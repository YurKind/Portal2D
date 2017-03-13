#include "Search.h"

namespace search
{
	void setSearchParametr(int parametr)
	{
		list::List<records::DataAboutTheChampion> *list = NULL;
		tree::BranchForNumber<records::DataAboutTheChampion> *tree = NULL;
		double numberOfScore = 0.0;
		int numberOfLevel = 0;
		switch (parametr)
		{
		case SCORE:
			addTree(&tree, FILE_NAME_RECORDS, SCORE);
			std::cout << "\tenter the number of score: ";
			std::cin >> numberOfScore;
			std::cout << "\n";
			list = searchByScoreAllElements(tree, numberOfScore);
			break;

		case LEVEL:
			addTree(&tree, FILE_NAME_RECORDS, LEVEL);
			std::cout << "\tenter the number of level: ";
			std::cin >> numberOfLevel;
			std::cout << "\n";
			list = searchByLevelAllElements(tree, numberOfLevel);
			break;

		case STRING:
			break;
		}
		printFoundChampions(list);
		list::freeMemory(list);
		tree::freeMemory(tree);
		_getch();
	}

	void printFoundChampions(list::List<records::DataAboutTheChampion> *list)
	{
		if (!list)
		{
			std::cout << "\t\tNoone here, be the first!" << std::endl;
		}
		else
		{
			while (list)
			{
				std::cout << "\t\t\tname: " << list->value.name
					<< " level: " << list->value.level
					<< " score: " << list->value.score
					<< std::endl;

				list = list->next;
			}
		}
	}

	tree::BranchForNumber<records::DataAboutTheChampion> *searchByScoreOfOneResult(tree::BranchForNumber<records::DataAboutTheChampion> *begin, double score)
	{
		if (!begin || score == begin->data.score)
		{
			return begin;
		}

		if (score < begin->data.score)
		{
			search::searchByScoreOfOneResult(begin->left, score);
		}
		else
		{
			search::searchByScoreOfOneResult(begin->right, score);
		}
	}

	list::List<records::DataAboutTheChampion> *searchByScoreAllElements(tree::BranchForNumber<records::DataAboutTheChampion> *begin, double score)
	{
		int counterOfLoop = 0;
		list::List<records::DataAboutTheChampion> *list = NULL;
		tree::BranchForNumber<records::DataAboutTheChampion> **s = &begin;
		tree::BranchForNumber<records::DataAboutTheChampion> *search = *s;
		while (search)
		{
			if (counterOfLoop)
			{
				*s = search::searchByScoreOfOneResult(search->right, score);
			}
			else
			{
				*s = search::searchByScoreOfOneResult(search, score);
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

	tree::BranchForNumber<records::DataAboutTheChampion> *searchByLevelOfOneResult(tree::BranchForNumber<records::DataAboutTheChampion> *begin, int level)
	{
		if (!begin || level == begin->data.level)
		{
			return begin;
		}

		if (level < begin->data.level)
		{
			search::searchByLevelOfOneResult(begin->left, level);
		}
		else
		{
			search::searchByLevelOfOneResult(begin->right, level);
		}
	}

	list::List<records::DataAboutTheChampion> *searchByLevelAllElements(tree::BranchForNumber<records::DataAboutTheChampion> *begin, int level)
	{
		int counterOfLoop = 0;
		list::List<records::DataAboutTheChampion> *list = NULL;
		tree::BranchForNumber<records::DataAboutTheChampion> **s = &begin;
		tree::BranchForNumber<records::DataAboutTheChampion> *search = *s;
		while (search)
		{
			if (counterOfLoop)
			{
				*s = search::searchByLevelOfOneResult(search->right, level);
			}
			else
			{
				*s = search::searchByLevelOfOneResult(search, level);
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