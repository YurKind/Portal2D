#include "Tree.h"
#include "Records.h"
#include "List.h"
#include <conio.h>

namespace tree
{
	void addTree(BranchForNumber<records::DataAboutTheChampion> **tree, char *fileName, int variant)
	{
		std::ifstream fin(FILE_NAME_RECORDS);
		tree::BranchForNumber<records::DataAboutTheChampion> *add = *tree;
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
				pushInTree(*data, add, STRING);
			}
			delete data;
			delete[] buf;
		}
		*tree = add;
		fin.close();
	}

	void pushInTree(records::DataAboutTheChampion newData, BranchForNumber<records::DataAboutTheChampion> *&tree, int variant)
	{
		if (!tree)
		{
			tree = new tree::BranchForNumber<records::DataAboutTheChampion>;
			tree->data = newData;
		}
		else 
		{
			if (variant == SCORE)
			{
				if (tree->data.score > newData.score)
				{
					tree::pushInTree(newData, tree->left, SCORE);
				}
				else
				{
					tree::pushInTree(newData, tree->right, SCORE);
				}
			}
			else if (variant == LEVEL)
			{
				if (tree->data.level > newData.level)
				{
					tree::pushInTree(newData, tree->left, LEVEL);
				}
				else
				{
					tree::pushInTree(newData, tree->right, LEVEL);
				}
			}
			else if (variant == STRING)
			{
				int size1 = tree->data.name.length() + 1, size2 = newData.name.length() + 1;
				char *str1 = new char[size1], *str2 = new char[size2];
				strcpy_s(str1, size1, tree->data.name.c_str());
				strcpy_s(str2, size2, newData.name.c_str());
				if (strcmp(str1, str2) > 0)
				{
					tree::pushInTree(newData, tree->left, STRING);
				}
				else
				{
					tree::pushInTree(newData, tree->right, STRING);
				}
				delete[] str1;
				delete[] str2;
			}
		}
	}

	records::DataAboutTheChampion getMinimum(BranchForNumber<records::DataAboutTheChampion> *tree)
	{
		while (tree->left)
		{
			tree = tree->left;
		}
		return tree->data;
	}

	records::DataAboutTheChampion getMaximum(BranchForNumber<records::DataAboutTheChampion> *tree)
	{
		while (tree->right)
		{
			tree = tree->right;
		}
		return tree->data;
	}

	void freeMemory(BranchForNumber<records::DataAboutTheChampion> *tree)
	{
		if (tree)
		{
			tree::freeMemory(tree->left);
			tree::freeMemory(tree->right);
			delete tree;
		}
	}
}
