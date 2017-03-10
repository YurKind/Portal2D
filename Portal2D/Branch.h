#pragma once
#include "Structures.h"

namespace branch
{
	template <class T> void addTree(T newData, Branch<T> *&begin)
	{
		if (!begin)
		{
			begin = new Branch<T>;
			begin->data = newData;
			begin->left = NULL;
			begin->right = NULL;
		}
		else
		{
			if (begin->data > newData)
			{
				addTree(newData, begin->left);
			}
			else
			{
				addTree(newData, begin->right);
			}
		}
	}

	template <class T> void freeMemory(Branch<T> *begin)
	{
		if (begin)
		{
			freeMemory(begin->left);
			freeMemory(begin->right);
			delete begin;
		}
	}
}