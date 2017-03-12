#pragma once

#include <iostream>

namespace game
{
	template <typename T> struct Stack
	{
		T element;
		Stack<T> *next;
	};
}

namespace records
{
	struct DataAboutTheChampion
	{
		std::string name;
		double score;
		int level;
	};
}

namespace list
{
	template <class T> struct List
	{
		T value;
		List<T> *next;
	};
}

namespace queue
{
	template <class T> struct Node
	{
		T data;
		Node *next;
		Node *previous;
	};

	template <class T> struct Queue
	{
		Node<T> *head = NULL;
		Node<T> *tail = NULL;
	};
}

namespace tree
{
	template <typename T> struct BranchForNumber
	{
		T data;
		BranchForNumber<T> *left = NULL;
		BranchForNumber<T> *right = NULL;
	};
}