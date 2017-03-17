#include "List.h"
#include "SortingMethods.h"

/*Команды: add - добавить в рекорды / show - показать все рекорды (не больше 10к) / show10 - показать 10 рекордов*/
void records::addInRecordsOrShowRecords(records::DataAboutTheChampion *newChampion, char *variant)
{
	int counterOfPrintedChampions = 0;
	list::List<records::DataAboutTheChampion> *begin = new list::List<records::DataAboutTheChampion>;
	std::ifstream fin(FILE_NAME_RECORDS);
	list::addList(&begin, fin);       // инициализируем список

	if (!strcmp(variant, "show"))     // показать все рекорды
	{
		std::cout << "\n\t\t\t\t\t\tALL RECORDS" << std::endl;
		std::cout << "\n";
		while (begin->next && counterOfPrintedChampions < 1000)
		{
			counterOfPrintedChampions++;
			std::cout << "\n\t\t\t  " << counterOfPrintedChampions << "." << "name: " << begin->value.name << " level: " << begin->value.level << " score: " << begin->value.score << std::endl;
			begin = begin->next;
		}
		std::cout << "\n";
		_getch();
		system("cls");
	}
	else if (!strcmp(variant, "add"))     // добавить в рекорды
	{
		int placeInRank = records::findingTheLocationInOrder(begin, *newChampion);    // узнаем потенциальное место в списке
		list::addInCertainPlace(&begin, placeInRank, *newChampion);          // вставляем в найденное место
		records::overwriteFile(begin);               // перезапись файла 
	}
	else if (!strcmp(variant, "show10"))     // показать 10 лучших рекордов
	{
		std::cout << "\n\t\t\t\t\t TOP 10 RECORDS" << std::endl;
		std::cout << "\n";
		while (begin->next && counterOfPrintedChampions < 10)
		{
			counterOfPrintedChampions++;
			std::cout << "\n\t\t\t  " << counterOfPrintedChampions << "." << "name: " << begin->value.name << " level: " << begin->value.level << " score: " << begin->value.score << std::endl;
			begin = begin->next;	
		}
		std::cout << "\n";
		_getch();
		system("cls");
	}
	fin.close();
	list::freeMemory(begin);
}

void records::giveBestPlayerInLevel(int levelNumber)
{
	list::List<records::DataAboutTheChampion> *begin = new list::List<records::DataAboutTheChampion>;;
	begin->next = NULL;
	std::ifstream fin(FILE_NAME_RECORDS);
	list::addList(&begin, fin);    // инициализируем список

	records::DataAboutTheChampion bestResult = records::removeItemsExcessLevels(begin, levelNumber);
	if (bestResult.name == "_errorEmptyListOfRecords")      // если никого не нашли на данном уровне
	{
		std::cout << "Be the first at this level! " << std::endl;
	}
	else
	{
		std::cout << " -> name: " << bestResult.name << " score: " << bestResult.score << std::endl;
	}
	fin.close();
}

/**
  *функция удаляет элементы с уровнем != rightLevel и возвращает лучший результат среди рекордсменов уровня rightLevel
  */
records::DataAboutTheChampion records::removeItemsExcessLevels(list::List<records::DataAboutTheChampion> *begin, int rightLevel)    
{                                                                
	bool counterEmptyListOfRecordsForRightlevel = false;           
	list::List<records::DataAboutTheChampion> *cleaner = begin;    // новый указатель на начало списка
	list::List<records::DataAboutTheChampion> *end = NULL;         // указатель для хранения конца списка
	records::DataAboutTheChampion bestResult;
	bestResult.score = NULL;
	while (begin && bestResult.score == NULL)
	{
		if (begin->value.level != rightLevel && bestResult.score == NULL)    
		{
			if (end)
			{
				end->next = NULL;
			}
			cleaner = begin;
			begin = begin->next;
			delete cleaner;
		}
		else
		{
			end = begin;
			counterEmptyListOfRecordsForRightlevel++;    
			bestResult = begin->value;
			begin = begin->next;
		}
	}
	if (!counterEmptyListOfRecordsForRightlevel)       // если никого в рекордах с уровнем rightLevel нет, то возвращаем имя-ошибку
	{
		bestResult.name = "_errorEmptyListOfRecords";
	}
	list::freeMemory(begin);
	return bestResult;
}

int records::countLengthLine(std::ifstream &finForSize)
{
	int lengthLine = 0;
	char temp = ' ';
	while (temp != '>')
	{
		finForSize >> temp;
		lengthLine++;
	}
	return ++lengthLine;
}

void records::overwriteFile(list::List<records::DataAboutTheChampion> *begin)        // перезапись файла
{
	std::ofstream fout(FILE_NAME_RECORDS);
	while (begin->next != NULL)
	{
		fout << begin->value.name << "|" << begin->value.score << "|" << begin->value.level << ">";
		if (begin->next->next != NULL) {
			fout << std::endl;
		}
		begin = begin->next;
	}
	fout.close();
}

int records::findingTheLocationInOrder(list::List<records::DataAboutTheChampion> *begin, records::DataAboutTheChampion newChampion)     
{                                                                 // высчитывание места нового рекордсмена в зависимости от уровня и очков (чтобы записать в файл не нарушив порядок)
	int placInOrder = 0;
	list::List<records::DataAboutTheChampion> *ptr = begin;
	while (ptr->value.level > newChampion.level)    // пока уровень рекордсмена из списка больше чем у вставляемого рекордсмена
	{
		ptr = ptr->next;
		placInOrder++;
	}
	while (ptr->value.score > newChampion.score && ptr->value.level == newChampion.level)   // пока кол-во очков из списка больше вставляемого и уровень из списка равен уровню вставляемого рекордсмена
	{
		ptr = ptr->next;
		placInOrder++;
	}

	return placInOrder;
}

records::DataAboutTheChampion records::initializationDataAboutTheChampion(char *buf)         
{
	char points[25], lvl[2];
	records::DataAboutTheChampion champion = {};
	int counterLetter = 0, i = 0;
	while (buf[counterLetter] != '|')        // инициализация поля name из буфера со всей строкой
	{
		champion.name += buf[counterLetter];
		counterLetter++;
	}
	counterLetter++;
	while (buf[counterLetter] != '|')        // инициализация поля score 
	{
		points[i] = buf[counterLetter];
		i++;
		counterLetter++;
	}
	double score = atof(points);
	champion.score = score;
	counterLetter++;
	i = 0;
	while (buf[counterLetter] != '>')        // инициализация поля level 
	{
		lvl[i] = buf[counterLetter];
		counterLetter++;
		i++;
	}
	int level = atoi(lvl); 
	champion.level = level;

	return champion;
}
