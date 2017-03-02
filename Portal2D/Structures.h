#pragma once

namespace records
{
	struct DataAboutTheChampion
	{
		std::string name;
		int scores;
		int level;
	};
}

namespace list
{
	template <class T> struct List
	{
		T value;
		List<T> *next;
	};
}