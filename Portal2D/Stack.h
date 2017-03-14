#pragma once

#include "Structures.h"
#include "Map.h"

namespace game
{
	template <typename T>
	T pop(Stack<T>* &topNode);

	template <typename T>
	void push(T newElement, Stack<T>* &topNode);
	
	template <typename T>
	T peek(Stack<T>* &topNode);

	template <typename T>
	void push(T newElement, Stack<T>* &topNode)
	{
		Stack<T>* newNode = new Stack<T>;
		newNode->element = newElement;
		newNode->next = topNode;
		topNode = newNode;
	}

	template <typename T>
	T pop(Stack<T>* &topNode)
	{
		T temp = topNode->element;
		Stack<T>* currentElement = topNode;
		topNode = topNode->next;
		delete currentElement;
		return temp;
	}

	template <typename T>
	T peek(Stack<T>* &topNode)
	{

 		T top = topNode->element;
		return top;
	}
}