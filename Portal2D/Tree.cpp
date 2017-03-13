#include "Tree.h"
#include "Records.h"
#include "List.h"
#include <conio.h>

namespace tree
{
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
				pushInTreeByScore(*data, add);
			}
			else if (variant == LEVEL)
			{
				pushInTreeByLevel(*data, add);
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

	void pushInTreeByScore(records::DataAboutTheChampion newData, BranchForNumber<records::DataAboutTheChampion> *&begin)
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