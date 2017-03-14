#include "Tree.h"
#include "Records.h"
#include "List.h"
#include <conio.h>

namespace tree
{
	void setSearchParametr(int parametr)
	{
		list::List<records::DataAboutTheChampion> *list = NULL;
		BranchForNumber<records::DataAboutTheChampion> *tree = NULL;
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

	BranchForNumber<records::DataAboutTheChampion> *searchByScoreOfOneResult(BranchForNumber<records::DataAboutTheChampion> *begin, double score)
	{
		if (!begin || score == begin->data.score)
		{
			return begin;
		}

		if (score < begin->data.score)
		{
			tree::searchByScoreOfOneResult(begin->left, score);
		}
		else
		{
			tree::searchByScoreOfOneResult(begin->right, score);
		}
	}

	list::List<records::DataAboutTheChampion> *searchByScoreAllElements(BranchForNumber<records::DataAboutTheChampion> *begin, double score)
	{
		int counterOfLoop = 0;
		list::List<records::DataAboutTheChampion> *list = NULL;
		tree::BranchForNumber<records::DataAboutTheChampion> **s = &begin;
		tree::BranchForNumber<records::DataAboutTheChampion> *search = *s;
		while (search)
		{
			if (counterOfLoop)
			{
				*s = tree::searchByScoreOfOneResult(search->right, score);
			}
			else
			{
				*s = tree::searchByScoreOfOneResult(search, score);
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

	BranchForNumber<records::DataAboutTheChampion> *searchByLevelOfOneResult(BranchForNumber<records::DataAboutTheChampion> *begin, int level)
	{
		if (!begin || level == begin->data.level)
		{
			return begin;
		}

		if (level < begin->data.level)
		{
			tree::searchByLevelOfOneResult(begin->left, level);
		}
		else
		{
			tree::searchByLevelOfOneResult(begin->right, level);
		}
	}

	list::List<records::DataAboutTheChampion> *searchByLevelAllElements(BranchForNumber<records::DataAboutTheChampion> *begin, int level)
	{
		int counterOfLoop = 0;
		list::List<records::DataAboutTheChampion> *list = NULL;
		tree::BranchForNumber<records::DataAboutTheChampion> **s = &begin;
		tree::BranchForNumber<records::DataAboutTheChampion> *search = *s;
		while (search)
		{
			if (counterOfLoop)
			{
				*s = tree::searchByLevelOfOneResult(search->right, level);
			}
			else
			{
				*s = tree::searchByLevelOfOneResult(search, level);
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

	void addTree(BranchForNumber<records::DataAboutTheChampion> **begin, char *fileName, int variant)
	{
		std::ifstream fin(FILE_NAME_RECORDS);
		tree::BranchForNumber<records::DataAboutTheChampion> *add = *begin;
		while (!fin.eof())
		{
			char *buf = new char[1024];
			fin.getline(buf, 1024);
			records::DataAboutTheChampion *data = new records::DataAboutTheChampion(records::initializationDataAboutTheChampion(buf));
			if (variant == SCORE)
			{
				pushInTree(*data, add, SCORE);
			}
			else if (variant == LEVEL)
			{
				pushInTree(*data, add, LEVEL);
			}
			else if (variant == STRING)
			{
				
			}
			delete data;
			delete[] buf;
		}
		*begin = add;
		fin.close();
	}

	/*void pushInTreeByScore(records::DataAboutTheChampion newData, BranchForNumber<records::DataAboutTheChampion> *&begin)
	{
		if (!begin)
		{
			begin = new tree::BranchForNumber<records::DataAboutTheChampion>;
			begin->data = newData;
		}
		else
		{
			if (begin->data.score > newData.score)
			{
				tree::pushInTreeByScore(newData, begin->left);
			}
			else
			{
				tree::pushInTreeByScore(newData, begin->right);
			}
		}
	}

	void pushInTreeByLevel(records::DataAboutTheChampion newData, BranchForNumber<records::DataAboutTheChampion> *&begin)
	{
		if (!begin)
		{
			begin = new tree::BranchForNumber<records::DataAboutTheChampion>;
			begin->data = newData;
		}
		else
		{
			if (begin->data.level > newData.level)
			{
				tree::pushInTreeByLevel(newData, begin->left);
			}
			else
			{
				tree::pushInTreeByLevel(newData, begin->right);
			}
		}
	}*/

	void pushInTree(records::DataAboutTheChampion newData, BranchForNumber<records::DataAboutTheChampion> *&begin, int variant)
	{
		if (!begin)
		{
			begin = new tree::BranchForNumber<records::DataAboutTheChampion>;
			begin->data = newData;
		}
		else 
		{
			if (variant == SCORE)
			{
				if (begin->data.score > newData.score)
				{
					tree::pushInTree(newData, begin->left, SCORE);
				}
				else
				{
					tree::pushInTree(newData, begin->right, SCORE);
				}
			}
			else if (variant == LEVEL)
			{
				if (begin->data.level > newData.level)
				{
					tree::pushInTree(newData, begin->left, LEVEL);
				}
				else
				{
					tree::pushInTree(newData, begin->right, LEVEL);
				}
			}
			else if (variant == STRING)
			{
				
			}
		}
	}

	records::DataAboutTheChampion getMinimum(BranchForNumber<records::DataAboutTheChampion> *begin)
	{
		while (begin->left)
		{
			begin = begin->left;
		}
		return begin->data;
	}

	records::DataAboutTheChampion getMaximum(BranchForNumber<records::DataAboutTheChampion> *begin)
	{
		while (begin->right)
		{
			begin = begin->right;
		}
		return begin->data;
	}

	void freeMemory(BranchForNumber<records::DataAboutTheChampion> *begin)
	{
		if (begin)
		{
			tree::freeMemory(begin->left);
			tree::freeMemory(begin->right);
			delete begin;
		}
	}
}