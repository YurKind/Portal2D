#pragma once 
#include "Structures.h" 

#define NUMBER_OF_LEVELS 10 

namespace queue
{
	template <typename T> void pushInQueue(queue::Queue<T> *begin, T newData)
	{
		queue::Node<T> *node = new queue::Node<T>;
		node->data = newData;
		node->next = NULL;

		if (begin->head != NULL)
		{
			node->previous = begin->tail;
			begin->tail->next = node;
			begin->tail = node;
		}
		else
		{
			node->previous = NULL;
			begin->tail = begin->head = node;
		}
	}

	template <typename T> void freeMemory(queue::Queue<T> *begin)
	{
		queue::Node<T> *cleaner;
		while (begin->head)
		{
			cleaner = begin->tail;
			begin->tail = begin->tail->previous;
			if (begin->head->next)
			{
				begin->tail->next = NULL;
			}
			else
			{
				begin->head = NULL;
			}
			delete cleaner;
		}
	}

	template <typename T> void addQueue(queue::Queue<T> *begin, T *dataArray, int numberOfElements)
	{
		for (int i = 0; i < numberOfElements; i++)
		{
			pushInQueue(begin, dataArray[i]);
		}
	}

	/*template <typename T> T pullElement(queue::Queue<T> *begin)
	{
	if (begin->head)
	T element = begin->head->data;

	return element;
	}*/
}
