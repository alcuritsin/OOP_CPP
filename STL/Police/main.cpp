#include<iostream>
#include<string>
#include<list>
#include<map>
#include<Windows.h>
#include<fstream>
#include<algorithm>

const std::string base_name = "base";

void print_base(const std::map<std::string, std::list<std::string>>& base);

void save_base(const std::map<std::string, std::list<std::string>>& base);
void load_base(std::map<std::string, std::list<std::string>>& base);


void main()
{
	setlocale(LC_ALL, "Russian");
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);

	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	COORD bufer = { 150, 150 };

	SetConsoleDisplayMode(hConsole, CONSOLE_FULLSCREEN_MODE, &bufer);



	std::map<std::string, std::list<std::string>> base; /* =
	{
		std::pair<std::string, std::list<std::string>>("m123mm777", {"Проезд на красный", "Привышение скорости"}),
		std::pair<std::string, std::list<std::string>>("m446mm011", {"Парковка в не положенном месте"}),
		std::pair<std::string, std::list<std::string>>("k123vk011", {"Езда в нетрезвом состоянии", "Оскорбление сотрудника полиции", "Оказание сопротивления при аресте"})
	};*/

	load_base(base);

	print_base(base);
	//save_base(base);
}

void print_base(const std::map<std::string, std::list<std::string>>& base)
{
	for (std::map<std::string, std::list<std::string>>::const_iterator it = base.cbegin(); it != base.cend(); it++)
	{
		std::cout << it->first << ":\t";
		for (std::list<std::string>::const_iterator ij = it->second.cbegin(); ij != it->second.cend(); ij++)
		{
			std::cout << *ij;
			if (ij != --(it->second.end())) std::cout << ", ";
		}
		//std::cout << "\b \b";
		//std::cout << "\b \b;\n";
		std::cout << ";\n";

	}

}

void save_base(const std::map<std::string, std::list<std::string>>& base)
{
	std::ofstream fout(base_name);
	for (std::map<std::string, std::list<std::string>>::const_iterator it = base.cbegin(); it != base.cend(); it++)
	{
		fout << it->first << ":\t";
		for (std::list<std::string>::const_iterator ij = it->second.cbegin(); ij != it->second.cend(); ij++)
		{
			fout << *ij;
			if (ij != --(it->second.end())) fout << ", ";

		}
		/*std::cout << "\b \b";
		std::cout << "\b \b;\n";*/
		fout << ";\n";
	}
	fout.close();



	std::string	command = "start notepad " + base_name;
	system(command.c_str());
}

void load_base(std::map<std::string, std::list<std::string>>& base)
{
	std::ifstream fin(base_name);

	std::string id;
	std::string crime;
	std::string crimes;
	if (fin.is_open())
	{
 		while (!fin.eof())
		{

			std::getline(fin, id, ':');
			//if (id.size() < 2) continue;
			//do
			//{
			//	std::getline(fin, crime, ',');
			//	base[id].push_back(crime);
			//} while (crime.back() != ';');
			// 
			/*while (std::getline(fin, crime,','))
			{
				base[id].push_back(crime);
			}*/

			std::getline(fin, crimes, ';');
			fin.ignore();
			for (int i = 0, next_coma = i; i < crimes.size(); i = next_coma)
			{
				next_coma = crimes.find(',', i+1);
				std::string crime(crimes, i+1 , (next_coma>0? next_coma - i - 1:crimes.size()-i));
				std::cout << ":"<<crime<<":" << "\n";
				base[id].push_back(crime);
			}
			


		}
	}
	else
	{
		std::cerr << "File not found" << std::endl;
	}

	fin.close();
}
