#pragma once
#include <string>
#include <iostream>
#include <fstream>
#include "Structures.h"

#define FILE_NAME_RECORDS "Records.txt"

namespace records
{
	/**
	 * Перезаписывает файл с учетом нового рекордсмена.
	 */
	void overwriteFile(list::List<DataAboutTheChampion> *listWithAll);

	/**
	 * Возвращает место нового рекордсмена в зависимости от уровня и очков,
	 * чтобы записать в файл не нарушив порядок.
	 */
	int getPlaceOfChampionInOrder(list::List<DataAboutTheChampion> *listWithAll, DataAboutTheChampion newChampion);

	/**
	 * Команды: "add" - добавить в рекорды, "show" - показать все рекорды (не больше 10к).
	 */
	void addInRecordsOrShowRecords(DataAboutTheChampion *newChampion, char *variant);

	/**
	 * Инициализирует переменную с данными о пользователе из буфера и возвращает ее.
	 */
	DataAboutTheChampion getChampionWithDataFromBuffer(char *buf);

	/**
	 * Выводит на печать лучший результат на уровне.
	 */
	void printBestPlayerInLevel(int levelNumber);

	/**
	 * Функция удаляет элементы с уровнем != rightLevel и
	 * возвращает лучший результат среди рекордсменов уровня rightLevel.
	 */
	DataAboutTheChampion getBestResultOnTheLevel(list::List<DataAboutTheChampion> *listWithAll, int rightLevel);

	/**
	 * Возвращает длину строки.
	 */
	int getLineLength(std::ifstream &finForSize);
}

namespace list 
{
	/**
	 * Cозданет и инициализирует список из файла.
	 */
	void addList(List<records::DataAboutTheChampion> **begin, std::ifstream &fin);   
}