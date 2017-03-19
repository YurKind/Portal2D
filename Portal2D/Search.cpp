#include "Search.h"

namespace search
{
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

	tree::BranchForNumber<records::DataAboutTheChampion> *searchByStringOfOneResult(tree::BranchForNumber<records::DataAboutTheChampion> *begin, char *name)
	{
		if (!begin || comparison(name, begin->data.name) == 0)
		{
			return begin;
		}

		if (comparison(name, begin->data.name) < 0)
		{
			search::searchByStringOfOneResult(begin->left, name);
		}
		else
		{
			search::searchByStringOfOneResult(begin->right, name);
		}
	}

	int comparison(char *name, std::string str)
	{
		char *checking = new char[str.length() + 1];
		strcpy_s(checking, str.length() + 1, str.c_str());
		return _stricmp(name, checking);
	}
}
/*list::List<records::DataAboutTheChampion> *searchByScoreAllElements(tree::BranchForNumber<records::DataAboutTheChampion> *begin, double score)
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
	}*/
/*
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
	}*/