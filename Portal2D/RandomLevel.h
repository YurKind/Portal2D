#pragma once

#define NUMBER_OF_LEVELS 10

namespace queue
{
	template <class T> struct Node
	{
		T data;
		Node *next;
	};

	template <class T> struct Queue
	{
		Node<T> *head = NULL;
		Node<T> *tail = NULL;
	};
}

namespace random
{
	template <class T> void push(queue::Queue<T> *q, T newData)
	{
		queue::Node<T> *node = NULL;
		node = new queue::Node<T>;
		node->data = newData;
		node->next = NULL;

		if (q->head == NULL)
		{
			q->head = node;
		}
		else
		{
			q->tail->next = node;
			q->tail = node;
		}
	}
}