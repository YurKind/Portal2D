#pragma once

struct DataAboutTheChampion
{
	char *name;
	int scores;
	int level;
};

struct List
{
	DataAboutTheChampion champion;
	List *next;
};