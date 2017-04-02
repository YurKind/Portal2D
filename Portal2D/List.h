#pragma once
#include <conio.h>
#include "Records.h"

namespace list
{
	void addList(List<records::DataAboutTheChampion> **begin, std::ifstream &fin);

	void freeMemory(List<records::DataAboutTheChampion> *begin);

	template<class T1, class T2>
	void addBegin(T1 **begin, T2 newChampion);

	void addInCertainPlace(List<records::DataAboutTheChampion> **begin, int placeNumber, records::DataAboutTheChampion newChampion);

	template <class T1, class T2>
	void deleteCurrentElement(list::List<T1> *types, T2 element);

	template <typename T>
	T peek(List<T>* types);
}
