#pragma once 
#include "Structures.h" 

namespace queue
{
	/** 
	 * ¬озвращает текущий размер очереди.
	 */
	template <typename T> int checkCurrentSizeOfQueue(queue::Queue<T> queue)
	{
		int resultOfCount = 0;
		while (queue.head)
		{
			resultOfCount++;
			queue.head = queue.head->next;
		}

		return resultOfCount;
	}

	/**
	 * »нициализирует очередь из массива данных dataArray.
	 */
	template <typename T> void addQueue(queue::Queue<T> *queue, T *dataArray, int numberOfElements)
	{
		for (int i = 0; i < numberOfElements; i++)
		{
			enQueue(queue, dataArray[i]);
		}
	}

	/**
	 * ƒобавл€ет элемент в очередь.
	 */
	template <typename T> void enQueue(queue::Queue<T> *queue, T newData)
	{
		queue::Node<T> *node = new queue::Node<T>;
		node->data = newData;
		node->next = NULL;

		if (queue->head != NULL)
		{
			node->previous = queue->tail;   // "задний" указатель узла на хвост очереди
			queue->tail->next = node;        
			queue->tail = node;             // хвост приравниваем узлу
		}
		else   // если очередь пуста€, то инициализируем 
		{
			node->previous = NULL;
			queue->tail = queue->head = node;
		}
	}

	/**
	 * ”дал€ет элемент из очереди и возвращает его. (с головы)
	 */
	template <typename T> T deQueue(queue::Queue<T> *queue)
	{
		T result = NULL;
		queue::Node<T> *clean = queue->head;
		if (queue->head)
		{
			result = queue->head->data;    // результат приравниваем голове очереди
		}

		clean = queue->head;              
		queue->head = queue->head->next;
		delete clean;        // удал€ем голову

		return result;       // возвращаем значение удаленной головы
	}

	/**
	 * ќсвобождает пам€ть, выделенную дл€ данной очереди.
	 */
	template <typename T> void freeMemory(queue::Queue<T> *queue)
	{
		queue::Node<T> *cleaner;
		while (queue->head)            // пока есть голова удал€ем элемента с хвоста
		{
			cleaner = queue->tail;
			queue->tail = queue->tail->previous;

			if (queue->head->next)
			{
				queue->tail->next = NULL;
			}
			else
			{
				queue->head = NULL;
			}

			delete cleaner;
		}
	}
}
