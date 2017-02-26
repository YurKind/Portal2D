#include "Records.h"
#include "Structures.h"
#include "List"

void records::freeMemory(List *begin)       // освобождение памяти от списка 
{
	List *cleaner = begin;        // новый указатель на начало списка
	while (begin)
	{
		cleaner = begin;
		begin = begin->next;
		delete cleaner;
	}
}

void records::addInRecords(DataAboutTheChampion newChampion)
{
	List *begin = NULL;
	begin = new List;

	std::ifstream finSizeLine("Records.txt"), finSizeName("Records.txt"), finAll("Records.txt");     // 3 объекта для считывание из файла: для считывание длины строки, 
	                                                                                                // для считывание длины имени и для считывание всей строки в буфер
	int numberOfChampions = records::knowFileSize("Records.txt");         // узнаем количество строк в файле (кол-во рекордсменов)
	DataAboutTheChampion *champions = new DataAboutTheChampion[numberOfChampions];
	for (int i = 0; i < numberOfChampions; i++)
	{
		int counterInit = records::countLettersInFile("line", finSizeLine);      // узнаем размер строки
		char *buf = new char[counterInit];
		finAll.getline(buf, counterInit);       // инициализируем буфер
		champions[i] = records::sortingArrays(buf, finSizeName, i);      // из буфера инициализируем массив с рекордсменами 
		moveToNextLine(finSizeName);         // продвигаем объект для имён на следующую строку
		delete[] buf;
	}
	List *list = begin;           // новый указатель на начало списка
	records::addList(champions, numberOfChampions, begin);        // инициализируем список из массива 
	delete[] champions;
	int placeInRank = records::findingTheLocationInOrder(begin, numberOfChampions, newChampion);      // находим место нового рекордсмена в списке
	records::addInCertainPlace(&begin, placeInRank, newChampion);            // добавляем его в список
	overwriteFile(begin);             // перезаписываем файл
	finSizeLine.close();
	finSizeName.close();
	finAll.close();
	freeMemory(begin);             // освобождаем память от списка
}

void records::overwriteFile(List *begin)        // перезапись файла
{
	std::ofstream fout("Records.txt");
	while (begin->next != NULL)
	{
		fout << begin->champion.name << "|" << begin->champion.scores << "|" << begin->champion.level << "|";
		if (begin->next->next != NULL) {
			fout << std::endl;
		}
		begin = begin->next;
	}
	fout.close();
}

void records::addList(DataAboutTheChampion champions[], int numberOfChampions, List *begin)          // создание и инициализация списка
{
	List *add = begin;
	for (int i = 0; i < numberOfChampions; i++)
	{
		add->next = new List;
		add->champion = champions[i];
		add = add->next;
		add->next = NULL;
	}
}

int records::findingTheLocationInOrder(List *begin, int numberOfChampions, DataAboutTheChampion newChampion)      // высчитывание места нового рекордсмена в зависимости от уровня и очков
{
	int counter = 0;
	List *list = begin;
	while (list->champion.level > newChampion.level)
	{
		list = list->next;
		counter++;
	}
	while (list->champion.scores > newChampion.scores && list->champion.level == newChampion.level)
	{
		list = list->next;
		counter++;
	}

	return counter;
}

void records::addBegin(List **begin, DataAboutTheChampion newChampion)        // вставка в начало списка
{
	List *add = new List;
	add->champion = newChampion;
	add->next = *begin;
	*begin = add;
}

void records::addInCertainPlace(List **begin, int placeNumber, DataAboutTheChampion newChampion)       // вставка элемента списка с новым рекордсменом на соответствующее место 
{
	if (placeNumber == 0)
	{
		records::addBegin(begin, newChampion);           // всавка в начало списка
	}
	else
	{
		List *insert = *begin;         // новый указатель на начало списка
		for (int i = 0; i < placeNumber - 1; i++)
		{
			insert = insert->next;      // передвигаемся до нужного места
		}
		List *end = insert->next;       // указатель на элемент на который будет ссылаться новый элемент списка 
		List *add = new List;           // новый элемент
		insert->next = add;             // указатель предыдущего элемента на новый элемент
		add->champion = newChampion;    // инициализация нового элемента
		add->next = end;                // указатель нового элемента к следующему элементу списка
	}
}

void records::showAllOfRecords()
{
	std::ifstream finSizeLine("Records.txt"), finSizeName("Records.txt"), finAll("Records.txt");           // 3 объекта для считывание из файла: для считывание длины строки, 
	                                                                                             // для считывание длины имени и для считывание всей строки в буфер
	int N = records::knowFileSize("Records.txt");         // узнаем количество строк в файле (кол-во рекордсменов)
	DataAboutTheChampion *champions = new DataAboutTheChampion[N];
	for (int i = 0; i < N; i++)
	{
		int counterInit = records::countLettersInFile("line", finSizeLine);      // узнаем размер строки
		char *buf = new char[counterInit];
		finAll.getline(buf, counterInit);          // инициализируем буфер
		champions[i] = records::sortingArrays(buf, finSizeName, i);      // из буфера инициализируем массив с рекордсменами 
		moveToNextLine(finSizeName);            // продвигаем объект для имён на следующую строку
		delete[] buf;
		std::cout << "\nname: " << champions[i].name << " scores: " << champions[i].scores << " lvl: " << champions[i].level << "";
	}
	delete[] champions;
	finSizeLine.close();
	finSizeName.close();
	finAll.close();
}

void records::moveToNextLine(std::ifstream &fin)      // переход объекта на следующую строку
{
	char *b = new char[20];
	fin.getline(b, 20);
	delete[] b;
}

int records::knowFileSize(char *fileName)           // узнаем количество рекордсменов в файле (количество строк)
{
	int count = 0;
	std::ifstream fin(fileName);

	while (!fin.eof())
	{
		char *arr = new char[1024];
		fin.getline(arr, 1024);
		count++;
		delete[] arr;
	}
	fin.close();
	return count;
}

int records::countLettersInFile(char* variant, std::ifstream &fin)          // функция для вычисления размера имени рекорсдмена или           
{                                                                          //размера всей строки (все данных о рекордсмене)
	char temp = NULL;
	char* buf = new char[1000];
	int counter = 0;             // счетчик символов
	if (!strcmp(variant, "name"))
	{
		while (!fin.eof())
		{
			if (temp == '|')         // пока не наткнулись на разделитель 
				break;
			fin >> temp;        // считываем очередной символ из файла
			counter++;               
		}
	}
	else if (!strcmp(variant, "line"))
	{
		char temp = NULL;
		fin.getline(buf, 1000);
		while (buf[counter++] != '\0');    // пока не конец строки прибавляем 1 к счетчику 
	}
	delete[] buf;
	return ++counter;
}

DataAboutTheChampion records::sortingArrays(char *buf, std::ifstream &fin, int callNumber)
{
	char time[5], lvl[2];
	DataAboutTheChampion champion;
	int counterLetter = 0, i = 0, fileSize = knowFileSize("Records.txt");
	int sizeName = records::countLettersInFile("name", fin);
	char *name = new char[sizeName];

	while (buf[counterLetter] != '|')
	{
		name[counterLetter] = buf[counterLetter];
		counterLetter++;
	}
	counterLetter++;

	static std::string *str;
	if (callNumber == 0)
	{
		str = new std::string[fileSize];
	}

	for (int j = 0; j < sizeName - 2; j++)
	{
		str[callNumber] += name[j];
	}
	champion.name = &str[callNumber][0];
	delete[] name;

	while (buf[counterLetter] != '|')
	{
		time[i] = buf[counterLetter];
		counterLetter++;
		i++;
	}
	int scores = atoi(time);
	champion.scores = scores;
	counterLetter++;
	i = 0;

	while (buf[counterLetter] != '|')
	{
		lvl[i] = buf[counterLetter];
		counterLetter++;
		i++;
	}
	int level = atoi(lvl);
	champion.level = level;

	if (callNumber == fileSize)
	{
		delete[] str;
	}

	return champion;
}
