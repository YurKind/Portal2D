#pragma once
#include "Structures.h"

enum Parametr
{
	SCORE, LEVEL, NAME, SUBSTRING
};

namespace tree
{
	/**
	 * Добавляет элемент в дерево.
	 */
	void addInTree(records::DataAboutTheChampion newData, BranchForNumber<records::DataAboutTheChampion> *&tree, int variant);

	/**
	 * Возвращает минимальный элемент.
	 */
	records::DataAboutTheChampion getMinimum(BranchForNumber<records::DataAboutTheChampion> *tree);

	/**
	 * Возвращает максимальный элемент.
	 */
	records::DataAboutTheChampion getMaximum(BranchForNumber<records::DataAboutTheChampion> *tree);

	/**
	 * Освобождает память, выделенную под дерево.
	 */
	void freeMemory(tree::BranchForNumber<records::DataAboutTheChampion> *tree);

	/**
	 * Инициализирует дерево в зависимости от параметра "varaint".
	 */
	void initializeTree(BranchForNumber<records::DataAboutTheChampion> **tree, char *fileName, int variant);
}