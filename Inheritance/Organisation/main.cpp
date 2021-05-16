#include <iostream>
#include <fstream>

using namespace std;
using std::cin;
using std::cout;
using std::endl;
using std::string;

class Person
{
	string first_name;	//	Имя
	string last_name;	//	Фамилия
	string middle_name;	//	Отчество

	unsigned int year_of_birth;	//	Год рождения

public:
	Person();
	~Person();

private:

};

Person::Person()
{
}

Person::~Person()
{
}

enum SalaryType
{
	//	Тип оплаты труда
	HourlyWage,	//	Почасовая заработная плата
	MonthlySalary	//	Месячная заработная плата (оклад)
};
enum Position
{
	//	Должность
	Director,	//	Директор
	Maneger,	//	Менеджер
	Accauntant,	//	Бухгалтер
	Maker		//	Сборщик
};

//staff list
class Worker:Person
{	
	Position position;	//	Должность
	SalaryType salory_type;		//	Тип оплаты труда
	double salary_rate;	//	Ставка оплаты

public:
	Worker();
	~Worker();

private:

};

Worker::Worker()
{
}

Worker::~Worker()
{
}

unsigned long long CoutStrInFile(string FileName, string FolderPath = "")
{
	//	Подсчет количества строк в файле.

	string FullPath = FolderPath + FileName;
	
	unsigned long long count_str = 0;	//
	
	ifstream fin;

	fin.open(FullPath);	//	Открыть файл для чтения.

	if (fin.is_open())
	{
		while (!fin.eof())
		{
			int symbol = fin.get();
			//	10 - код символа переноса строки
			//	-1 - код символа окончания файла
			if (symbol == 10 || symbol == -1 )
			{
				++count_str;
			}
		}
	}
	else
	{
		//throw "File is not opened.";
	}

	fin.close();

	return count_str;
}

unsigned long long MaxLeighStrInFile(string FileName, string FolderPath = "")
{
	string FullPath = FolderPath + FileName;
	unsigned long long max_leigh = 0;
	unsigned long long str_leigh = 0;
	ifstream fin;

	fin.open(FullPath);


	if (fin.is_open())
	{
		while (!fin.eof())
		{
			int symbol = fin.get();
			str_leigh++;
			if (symbol == 10 || symbol == -1)
			{
				if (str_leigh>max_leigh)
				{
					max_leigh = str_leigh;
				}
				str_leigh = 0;
			}
		}
	}

	fin.close();

	return max_leigh;
}

void ReadFromFile(char &AS, unsigned long long &leight_str, string FileName, string FolderPath = "")
{
	string FullPath = FolderPath + FileName;
	unsigned long long str_number = 0;
	ifstream fin;

	fin.open(FullPath);

	const unsigned long long n = 256;
	char sz_buffer[n]{};

	if (fin.is_open())
	{
		while (!fin.eof())
		{
			//fin.getline(sz_buffer, n);
			fin >> AS[str_number];

		}
	}

	fin.close();

	//return sz_buffer;
}



void WriteToFile(const char* Source, string FileName, string FolderPath = "")
{
	string FullPath = FolderPath + FileName;
	
	ofstream fout;

	fout.open(FullPath, ios::app);



	fout.close();
}



void main()
{
	setlocale(LC_ALL, "Russian");
	
	string FileName = "file.csv";
	string FolderPath = "";

	int str_in_file = CoutStrInFile(FileName,FolderPath);	//	Строк в файле
	int max_leight_str = MaxLeighStrInFile(FileName, FolderPath);	//	Максимальная длина строки в файле

	//	Резервирование места под строки из файла.
	//	Строка - новый элемент массива.
	char **pArr = new char* [str_in_file];
	
	for (int i = 0; i < str_in_file; i++)
	{
		//	Резервирование места под строку (размером самой длинной строки)
		//	Теоретически можно взять ровно столько места сколько нужно для каждой строки, но может и не стоит.
		pArr[i] = new char[max_leight_str];
	}

	pArr[0];
	//ReadFromFile(pArr, max_leight_str, FileName);




	for (int i = 0; i < str_in_file; i++)
	{
		delete[] pArr[i];
	}
	delete[] pArr;


	cout << CoutStrInFile("file.csv") <<" строк" << endl;
	cout << MaxLeighStrInFile("file.csv") << " символов" << endl;
	


	//string *Array_str;
	//unsigned long long n = CoutStrInFile(FileName);

	//Array_str = new string[n];

	//ReadFromFile(Array_str, FileName);

	//for (unsigned long long i = 0; i < n; i++)
	//{
	//	cout << Array_str[i].c_str() << endl;
	//}


	//delete[] Array_str;
}