#pragma once 
#include "Structures.h" 

#define NUMBER_OF_LEVELS 10 

namespace queue
{
	void initializeArrayWithDifferentData(int *arr)
	{
		for (int i = 0; i < NUMBER_OF_LEVELS; i++)
		{
			bool flag = true;
			int temp = rand() % NUMBER_OF_LEVELS + 1;
			for (int j = 0; j < NUMBER_OF_LEVELS; j++)
			{
				if (temp == arr[j])
				{
					i--;
					flag = false;
				}
			}
			if (flag)
			{
				arr[i] = temp;
			}
		}
	}

	template <typename T> int checkCurrentSizeOfQueue(queue::Queue<T> *begin)
	{
		int resultOfCount = 0;
		queue::Queue<T> *counter = begin;
		while (counter->head)
		{
			resultOfCount++;
			counter->head = counter->head->next;
		}
		return resultOfCount;
	}

	template <typename T> T generatingRandomLevelNumber(queue::Queue<T> *begin)
	{
		int *arr = new int[NUMBER_OF_LEVELS];
		if (!begin->head)
		{
			queue::initializeArrayWithDifferentData(arr);
			queue::addQueue(begin, arr, NUMBER_OF_LEVELS);
		}
		else
		{
			std::cout << " ";
		}	
		return queue::pullElement(begin);
	}

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

	template <typename T> T pullElement(queue::Queue<T> *begin)
	{
		T element = NULL;
		queue::Node<T> *clean = begin->head;
		if (begin->head)
		{
			element = begin->head->data;
		}
		clean = begin->head;
		begin->head = begin->head->next;
		delete clean;

		return element;
	}
}
