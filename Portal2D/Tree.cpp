#include "Tree.h"
#include "Records.h"
#include "List.h"

namespace tree
{
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

	/*BranchForNumber<records::DataAboutTheChampion> *searchByLevelOfOneResult(BranchForNumber<records::DataAboutTheChampion> *begin, double level)
	{
		if (!begin || level == begin->data.level)
		{
			return begin;
		}

		if (level < begin->data.level)
		{
			tree::searchByScoreOfOneResult(begin->left, level);
		}
		else
		{
			tree::searchByScoreOfOneResult(begin->right, level);
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
	}*/

	void addTree(BranchForNumber<records::DataAboutTheChampion> **begin, char *fileName)
	{
		std::ifstream fin(FILE_NAME_RECORDS);
		tree::BranchForNumber<records::DataAboutTheChampion> *add = *begin;
		while (!fin.eof())
		{
			char *buf = new char[1024];
			fin.getline(buf, 1024);
			records::DataAboutTheChampion *data = new records::DataAboutTheChampion(records::initializationDataAboutTheChampion(buf));
			pushInTree(*data, add);
			delete data;
		}
		*begin = add;
	}

	void pushInTree(records::DataAboutTheChampion newData, BranchForNumber<records::DataAboutTheChampion> *&begin)
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
				tree::pushInTree(newData, begin->left);
			}
			else
			{
				tree::pushInTree(newData, begin->right);
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