#include "Queue.h"

void initializeQueueForRandomLevel(queue::Queue<int> **begin)
{
	queue::Queue<int> *add = *begin;
	for (int i = 0; i < NUMBER_OF_LEVELS; i++)
	{
		int counter = 0;
		bool flag = true;
		int temp = rand() % NUMBER_OF_LEVELS + 1;
		for (int j = 0; add->head != NULL && j < NUMBER_OF_LEVELS; j++)
		{
			if (temp == add->head->data)
			{
				flag = false;
			}
			add->head = add->head->next;
			counter++;
		}
		for (int index = 0; index < counter; index++)
		{
			add->head = add->head->previous;
		}

		if (flag)
		{
			queue::pushInQueue(add, temp);
		}
		else
		{
			i--;
		}
	}
}