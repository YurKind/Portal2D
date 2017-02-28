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
	struct List
	{
		records::DataAboutTheChampion champion;
		List *next;
	};
}