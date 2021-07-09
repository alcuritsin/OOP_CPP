#include<iostream>
#include<map>
#include<list>
#include<string>
#include<vector>
#include<fstream>
#include<Windows.h>

using std::cout;
using std::cin;
using std::endl;

const std::string base_file = "receipt.db";

//	CSV
void ReadCSVFile(std::vector <std::vector <std::string>>& v, std::string FileName, std::string FolderPath = "", char sep = ';');
void WriteCSVFile(const std::vector <std::vector <std::string>>& v, std::string FileName, std::string FolderPath = "", char sep = ';');

void ParsingCSVString(std::vector <std::string>& v, std::string& str, char sep = ';');
std::string UnquoteCSV(const std::string& str);

std::string AssemlyCSVString(const std::vector <std::string>& v, char sep = ';');
std::string QuotingCSV(const std::string& str, char sep = ';');



class BaseReceipt
{
	std::map<std::string, std::list<std::string>> base;
	//	а000аа
	//		- Штраф 1
	//		- Штраф 2
	//		- Штраф n
public:
	BaseReceipt();
	~BaseReceipt();

	//	Methods:
	void NewRecept(const std::string& vehicle_number, const std::string receipt)
	{
		if (base.find(vehicle_number) != base.end())
		{
			//	Если Номер ТС обнаружен в базе, то добавляем только штраф
			base[vehicle_number].push_back(receipt);
		}
		else
		{
			// Иначе добавляем новый номер ТС, и добавляем к нему штраф
			base.insert(std::pair<std::string, std::list<std::string>>(vehicle_number, { receipt }));
		}
	}

	void ReadBase()
	{

		std::vector <std::vector <std::string>> vec;
		//	Прочитать файл базы данных. Данные поместить во временный вектор vec.
		ReadCSVFile(vec, base_file);

		for (int row = 0; row < vec.size(); row++)
		{
			//	Бежим по строкам
			//	Считываем данные в память.
			NewRecept(vec[row][0], vec[row][1]);
		}

	}
	void WriteBase()
	{
		//	Пробежать по строчкам и вывести в файл новое состояние базы...

	}

	void Print()
	{
		for (std::map<std::string, std::list<std::string>>::iterator it = base.begin(); it != base.end(); it++)
		{
			cout << it->first << " : ";
			for (std::list<std::string>::iterator ij = it->second.begin(); ij != it->second.end(); ij++)
			{
				cout << *ij << "\t";
			}
			cout << endl;
		}

	}

	void PrintByNumber(const std::string vehicle_number)
	{
		//	Проверить наличие записи по ноеру ТС.
		//	Если совпадает выводим все штрафы по номеру.

		//	Если нет выводим штрафов не обнаружено.
	}

	void PrintRange(const std::string& begin_vehicle_number, const std::string& end_vehicle_number)
	{
		// Тут пока не придумал даже....
	}
private:

};

BaseReceipt::BaseReceipt()
{
}

BaseReceipt::~BaseReceipt()
{
}


//	CSV
void ReadCSVFile(std::vector <std::vector <std::string>>& v, std::string FileName, std::string FolderPath, char sep)
{
	///	<status> DONE </status>
	/// 
	/// <summary>
	///		Считывает из файла строки.
	///		Парсит строку по разделителю
	///		Результат добавляется в вектор по ссылке.
	/// </summary>
	/// 
	/// <param name="v">
	///		Вектор, в котором сохранится результат
	/// </param>
	/// <param name="FileName">
	///		Имя файла
	/// </param>
	/// <param name="FolderPath">
	///		Путь к папке, где хранится файл
	/// </param>
	/// <param name="sep">
	///		Разделитель в строке, по умолчанию точка с запятой
	/// </param>

	std::string str;
	std::string FullPath = FolderPath + "\\" + FileName;
	std::ifstream fin(FullPath);

	if (!fin)
	{
		cout << endl << "File: " << FileName << endl;
		cout << "In path: " << FolderPath << endl;
		cout << "Not found. \"" << FullPath << "\"" << endl;
		return;
	}

	cout << endl << "Read data from file: " << FullPath << endl;

	while (!fin.eof())
	{
		getline(fin, str);
		std::vector <std::string> s;
		ParsingCSVString(s, str, sep);
		v.push_back(s);
	}

	fin.close();
}

void WriteCSVFile(const std::vector <std::vector <std::string>>& v, std::string FileName, std::string FolderPath, char sep)
{
	/// <summary>
	///		Выводит вектор в файл CSV.
	/// </summary>
	/// 
	/// <param name="v">
	///		Исходный массив векторов.
	/// </param>
	/// <param name="FileName">
	///		Имя файла для записи.
	/// </param>
	/// <param name="FolderPath">
	///		Путь к папке.
	/// </param>
	/// <param name="sep">
	///		Разделитель. По умолчанию точка с запятой.
	/// </param>

	std::string FullPath = FolderPath + "\\" + FileName;
	std::ofstream fout(FullPath, std::ios::app);

	for (unsigned long long i = 0; i < v.size(); i++)
	{
		fout << AssemlyCSVString(v[i], sep) << endl;
	}

	fout.close();
}

void ParsingCSVString(std::vector <std::string>& v, std::string& str, char sep)
{
	///	<status> DONE </status>
	/// 
	/// <summary>
	///		Парсит строку по разделителю.
	/// </summary>
	/// 
	/// <param name="v">
	///		Вектор, в котором сохранится результат парсинга
	/// </param>
	/// <param name="str">
	///		Строка исходного текста
	/// </param>
	/// <param name="sep">
	///		Делиметр, по умолчанию тока с запятой
	/// </param>

	// Если строка пустая значит это может быть завершающая строка файла. Добавлять такую строку в вектор нет необходимости.
	if (str.length() <= 1) return;

	std::string buf{ "" };
	bool quoted = false;	//	поле в кавычках?

	int counter_quot = 0;	//	Счетчик кавычек в строке.

	for (int i = 0; i < str.length(); i++)
	{
		//	Пока не встретили разделитель
		if (str[i] != sep)
		{
			//	Копим символы в буфере.
			buf += str[i];
		}
		else
		{
			//	Возможно поле завершено
			for (int j = 0; j < buf.length(); j++)
			{
				if (buf[j] == '"')
				{
					//	поле содержит кавычку, это гарантирует, что поле заключено в кавычки. 
					quoted = true;
					//	считаем количество кавычек в предпологаемом поле.
					counter_quot++;
					//break;
				}
			}

			if (!quoted || (quoted && counter_quot % 2 == 0))
			{
				//	поле в кавычках
				//	и
				//	количество ковычек чётное
				//	поле завершено. разделитель определён верно.

				//	Ячейка завершена.
				// 
				//	Обрезаем кавычки если они есть.
				if (quoted)
				{
					buf = UnquoteCSV(buf);
				}
				v.push_back(buf);
				buf = "";
			}
			else
			{
				//	найденный разделитель является частью поля
				//	нужно продолжать копить символы в буфере.
				//	обнуляем маркер 'поле в кавычках'...
				quoted = false;
				buf += str[i];
			}
			//	обнуляем счетчик 'количество кавычек' в поле.
			//	готовимся к следующему проходу
			counter_quot = 0;
		}
	}

	if (buf != "")
	{
		//	Обрабатывается крайняя ячейка в строке.
		buf = UnquoteCSV(buf);
		v.push_back(buf);
	}
}

std::string UnquoteCSV(const std::string& str)
{
	///	<status> DONE </status>
	/// 
	/// <summary>
	/// Удаляет из строки лишние кавычки.
	/// При этом проверяет соответствует ли строка требованиям:
	///		- строка должна быть обрамлена в кавычки;
	///		- количество ковычек в строке должно быть четным. 
	/// </summary>
	/// 
	/// <param name="str">
	/// Исходная строка
	/// </param>
	/// 
	/// <returns>
	/// Строка без лишних кавычек.
	/// ИЛИ
	/// Исходная строка, если она не соответствует требованиям.
	/// </returns>

	unsigned int counter_quot = 0;
	for (unsigned long long i = 0; i < str.length(); i++)
	{
		if (str[i] == '"')
		{
			counter_quot++;
		}
	}

	if (str[0] != '"' || str[str.length() - 1] != '"' && counter_quot % 2 != 0)
	{
		//	Не правильная строка.
		//	Ничего не делать. Вернуть исходну строку.
		return str;
	}

	std::string unquote_str;

	for (unsigned long long i = 1; i < str.length() - 2; i++)
	{
		if (str[i] == '"' && str[i + 1] == '"' && i + 1 != str.length() - 1)
		{
			//	Встреча кавычки
			//	И
			//	Следующий символ не кавычка
			//	И
			//	Следующий символ не последний в строке (где по любому будет кавычка)

			//	Следующий шаг цикла
			unquote_str += str[i++];	//	добавляем этот символ к результату и пропускаем следующий символ
			//continue;
		}
		else
		{
			//	Собираем строку для возврата
			unquote_str += str[i];
		}
	}

	return unquote_str;
}

std::string AssemlyCSVString(const std::vector <std::string>& v, char sep)
{
	/// <status> DONE </status>
	/// 
	/// <summary>
	///		Собирает поля в одну строку через разделитель.
	///		Добавляет необходимые кавычки.
	/// </summary>
	/// 
	/// <param name="v">
	/// Исходный массив полей одной строки.
	/// </param>
	/// <param name="sep">
	/// Разделитель
	/// </param>
	/// 
	/// <returns>
	/// Строка с разделителями
	/// </returns>

	std::string assembly_str;

	for (unsigned int i = 0; i < v.size(); i++)
	{
		assembly_str += QuotingCSV(v[i]);
		if (i != v.size() - 1)
		{
			assembly_str += sep;
		}
	}

	return assembly_str;
}

std::string QuotingCSV(const std::string& str, char sep)
{
	///	<status> DONE </status>
	/// 
	/// <summary>
	///		Добавляет в строку необходимые кавычки.
	///		Проверяет содежит ли строка символы маркеры:
	///			- символ маркер - 'кавычка'
	///			- символ маркер - 'знак разделителя' (по умолчанию 'точка с запятой')
	/// </summary>
	/// 
	/// <param name="str">
	///		Исходная строка
	/// </param>
	/// <param name="sep">
	///		Разделитель полей
	/// </param>
	/// 
	/// <returns>
	///		Строка с необходимыми кавычками
	///		ИЛИ
	///		Исходная строка, если она не содержит маркерных символов
	/// </returns>

	//	Проверка на необходимость использования кавычек
	bool quoting_need = false;	//	Требуется установка кавычек? Нет, но нужно проверить.

	if (str.length() != 0)
	{
		for (unsigned long long i = 0; i < str.length(); i++)
		{
			if (str[i] == '"' || str[i] == sep)
			{
				//	Встреча одного из маркерного символа
				//	Требуется встака кавычек
				quoting_need = true;
				break;	// Нет смысла проверять дальше. Экономим время...
			}
		}
	}

	if (!quoting_need)
	{
		//	При проверке не обнаружена необходимость добавления кавычек
		//	Возврат исходной строки на место вызова
		return str;
	}

	//	Добавление в строку необходимых кавычек.

	std::string quote_str{ '"' };	//	Первый символ кавычка

	for (unsigned long long i = 0; i < str.length(); i++)
	{
		if (str[i] == '"')
		{
			//	Экранируем встреченую кавычку
			quote_str += '"';
		}
		//	Копим строку для возврата
		quote_str += str[i];
	}
	quote_str += '"';	//	Крайний символ тоже кавычка

	return quote_str;
}

void main()
{
	setlocale(LC_ALL, "Russian");
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);

	BaseReceipt base;
	//base.ReadBase();	//	Выгрузить базу в память.

	//	Ввод штрафа:





	for (int i = 0; i < 3; i++)
	{
		std::string vehicle_number;	//	Номер транспортного средства
		std::string receipt; //	Квитанция
		cout << ":: Новый штраф ::" << endl;
		cout << "Номер ТС: "; getline(cin, vehicle_number);//cin >> vehicle_number;
		//cin.ignore();
		cout << "   Штраф: "; getline(cin, receipt);//cin >> receipt;

		base.NewRecept(vehicle_number, receipt);
	}

	base.Print();	//	Вывод Всей базы..

	//base.WriteBase();	// Произвести запись нового состояния базы в память. Перед выходом.

}

/*
Задание 1.
Реализовать базу данных ГАИ по штрафным квитанциям
с помощью бинарного дерева. Ключом будет служить
номер автомашины, значением узла — список правонарушений. Если квитанция добавляется в первый раз,
то в дереве появляется новый узел, а в списке данные
по правонарушению; если нет, то данные заносятся в существующий список. Необходимо также реализовать
следующие операции:

■ Полная распечатка базы данных (по номерам машин и списку правонарушений, числящихся за ними);
■ Распечатка данных по заданному номеру;
■ Распечатка данных по диапазону номеров;
■ Сохраняйте и загружайте информацию из файла
*/

/*
Класс правонарушение
Дата
ID_Авто
Фио_Нарушителя
Место проишествия
Проишествие


ЛоадБАсе
СейвБАзе
Инсерт



*/