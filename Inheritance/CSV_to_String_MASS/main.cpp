	//	https://www.cyberforum.ru/cpp-beginners/thread516548.html
	
#include <iterator> 
#include <iostream>
#include <string>
#include <vector>
#include <fstream>

using namespace std;
using std::cout;
using std::endl;

void ReadCSVFile(vector <vector <string>>& v, string FileName, string FolderPath = "", char sep = ';');
void WriteCSVFile(const vector <vector <string>>& v, string FileName, string FolderPath = "", char sep = ';');

void ParsingCSVString(vector <string>& v, string& str, char sep = ';');
string UnquoteCSV(const string& str);

string AssemlyCSVString(const vector <string>& v, char sep = ';');
string QuotingCSV(const string& str, char sep = ';');

void ReadCSVFile(vector <vector <string>>& v, string FileName, string FolderPath, char sep)
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

	string str;
	string FullPath = FolderPath + "\\" + FileName;
	ifstream fin(FullPath);

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
		vector <string> s;
		ParsingCSVString(s, str, sep);
		v.push_back(s);
	}

	fin.close();
}

void WriteCSVFile(const vector <vector <string>>& v, string FileName, string FolderPath, char sep)
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
	
	string FullPath = FolderPath + "\\" + FileName;
	ofstream fout(FullPath, ios::app);

	for (unsigned long long i = 0; i < v.size(); i++)
	{
		fout << AssemlyCSVString(v[i], sep) << endl;
	}

	fout.close();
}

void ParsingCSVString(vector <string>& v, string & str, char sep)
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

	string buf{ "" };
	bool quoted = false;	//	поле в кавычках?

	int counter_quot = 0;	//	Счетчик кавычек в строке.

	for (int i = 0; i < str.length(); i++)
	{
		//	Пока не встретили разделитель
		if (str[i]!=sep)
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

			if (!quoted || (quoted && counter_quot%2 == 0))
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

string UnquoteCSV(const string& str)
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

	if (str[0] != '"' || str[str.length()-1]!='"' && counter_quot%2 != 0)
	{
		//	Не правильная строка.
		//	Ничего не делать. Вернуть исходну строку.
		return str;
	}

	string unquote_str;

	for (unsigned long long i = 1; i < str.length()-2; i++)
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

string AssemlyCSVString(const vector <string>& v, char sep )
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
	
	string assembly_str;

	for (unsigned int i = 0; i < v.size(); i++)
	{
		assembly_str += QuotingCSV(v[i]);
		if (i != v.size()-1)
		{
			assembly_str += sep;
		}
	}

	return assembly_str;
}

string QuotingCSV(const string& str, char sep)
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

	string quote_str{ '"' };	//	Первый символ кавычка
	
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

int main()
{
	setlocale(LC_ALL, "Russian");

	string FileName;
	//FileName = "file.csv";
	string FolderPath = "..\\Organisation";

	vector <vector <string>> v;

	FileName = "tab_in.csv";
	ReadCSVFile(v, FileName, FolderPath, ';');

	for (int row = 0; row < v.size(); row++)
	{
		for (int col = 0; col < v[row].size(); col++)
		{
			cout << v[row][col] << " * ";
		}
		cout << endl;
	}

	FileName = "tab_out.csv";
	WriteCSVFile(v, FileName, FolderPath, ';');

	return 0;
}