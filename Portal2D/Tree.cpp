#include "Tree.h"
#include "Records.h"
#include "List.h"
#include <conio.h>

namespace tree
{
	/* Создает дерево и заполняет в зависимости от параметра "varaint" */
	void createTree(BranchForNumber<records::DataAboutTheChampion> **tree, char *fileName, int variant)
	{
		std::ifstream fin(FILE_NAME_RECORDS);
		tree::BranchForNumber<records::DataAboutTheChampion> *add = *tree;
		while (!fin.eof())
		{
			char *buf = new char[1024];
			fin.getline(buf, 1024);      // заполняем буфер из файла данными об одном рекордсмене 

			records::DataAboutTheChampion *data = new records::DataAboutTheChampion(
				records::initializationDataAboutTheChampion(buf)
			);   // объявление и инициализация переменной из буфера

			if (variant == SCORE)     // добавление элемента в зависимости от очков 
			{
				addInTree(*data, add, SCORE); 
			}
			else if (variant == LEVEL)     // добавление элемента в зависимости от уровня 
			{
				addInTree(*data, add, LEVEL);
			}
			else if (variant == STRING)
			{
				addInTree(*data, add, STRING);     // добавление элемента в зависимости от имени 
			}
			delete data;
			delete[] buf;
		}
		*tree = add;
		fin.close();
	}

	/* Добавляет элемент в дерево */
	void addInTree(records::DataAboutTheChampion newData, BranchForNumber<records::DataAboutTheChampion> *&tree, int variant)
	{
		if (!tree)       // если дерево пустое или конец ветки, то создаем элемент и инициализируем новым значением 
		{
			tree = new tree::BranchForNumber<records::DataAboutTheChampion>;
			tree->data = newData;
		}
		else 
		{
			if (variant == SCORE)        // если инициализация по очкам
			{
				if (tree->data.score > newData.score)
				{
					tree::addInTree(newData, tree->left, SCORE);
				}
				else
				{
					tree::addInTree(newData, tree->right, SCORE);
				}
			}
			else if (variant == LEVEL)        // если инициализация по уровню
			{
				if (tree->data.level > newData.level)
				{
					tree::addInTree(newData, tree->left, LEVEL);
				}
				else
				{
					tree::addInTree(newData, tree->right, LEVEL);
				}
			}
			else if (variant == STRING)        // если инициализация по имени
			{
				int size1 = tree->data.name.length() + 1, size2 = newData.name.length() + 1;
				char *str1 = new char[size1], *str2 = new char[size2];
				strcpy_s(str1, size1, tree->data.name.c_str());
				strcpy_s(str2, size2, newData.name.c_str());

				if (strcmp(str1, str2) > 0)
				{
					tree::addInTree(newData, tree->left, STRING);
				}
				else
				{
					tree::addInTree(newData, tree->right, STRING);
				}
				delete[] str1;
				delete[] str2;
			}
		}
	}

	/* Возвращает минимальный элемент */
	records::DataAboutTheChampion getMinimum(BranchForNumber<records::DataAboutTheChampion> *tree)
	{
		while (tree->left)
		{
			tree = tree->left;
		}
		return tree->data;
	}

	/* Возвращает максимальный элемент */
	records::DataAboutTheChampion getMaximum(BranchForNumber<records::DataAboutTheChampion> *tree)
	{
		while (tree->right)      
		{
			tree = tree->right;
		}
		return tree->data;
	}

	/* Освобождает память */
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
