#pragma once
#include "RandomLevel.h"
#include "Queue.h"

namespace random
{
	/*   «аполнение массива разными числами   */
	void initializesArrayWithUnmatchedNumbers(int *arr);

	/*   »нициализирует очередь из массива со случайными числами и возвращает элемент очереди   */
	template <typename T> T initializeQueueAndReturnHead(queue::Queue<T> *queue)
	{
		int *arr = new int[NUMBER_OF_LEVELS];
		if (!queue->head)
		{
			random::initializesArrayWithUnmatchedNumbers(arr);
			queue::addQueue(queue, arr, NUMBER_OF_LEVELS);
		}
		else
		{
			std::cout << " ";
		}

		return queue::deQueue(queue);
	}
}