#pragma once
#include <conio.h>
#include "HighScores.h"

namespace list
{
	/**
	 * Освобождает память, выделенную для данного списка.
	 */
	void freeMemory(List<records::DataAboutTheChampion> *begin);

	/**
	 * Вставка элемента в начало списка.
	 */
	template<class T1, class T2> void addBegin(T1 **list, T2 insertable)
	{
		T1 *add = new T1;
		add->value = insertable;
		add->next = *list;
		*list = add;
	}

	/**
	 * Вставляет нового рекордсмена на определенное место в список.
	 */
	void addInCertainPlace(List<records::DataAboutTheChampion> **list,
		int placeNumber,
		records::DataAboutTheChampion newChampion);

	/**
	 * Удаляет элемент из списка.
	 */
	void deleteCurrentElement(list::List<char> **types, char element);
}
