#pragma once

struct DataAboutTheChampion
{
	char *name;
	int scores;
	int level;
}/*нехуй тут ничего объ€вл€ть (€ про переменные, а не пол€)*/;

struct List
{
	DataAboutTheChampion champion;
	List *next;
};