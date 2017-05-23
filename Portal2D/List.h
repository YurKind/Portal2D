
#pragma once
#include <conio.h>
#include "HighScores.h"

namespace list
{
	void freeMemory(List<records::DataAboutTheChampion> *begin);

	template<class T1, class T2> void addBegin(T1 **begin, T2 insertable)        // вставка в начало списка
	{
		T1 *add = new T1;
		add->value = insertable;
		add->next = *begin;
		*begin = add;
	}

	void addInCertainPlace(List<records::DataAboutTheChampion> **begin,
		int placeNumber,
		records::DataAboutTheChampion newChampion);

	void deleteCurrentElement(list::List<char> **types, char element);
}
