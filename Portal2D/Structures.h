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
		int score;
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
