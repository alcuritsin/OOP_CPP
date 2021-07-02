#include<iostream>
#include<map>
#include<unordered_map>
#include<string>

//using namespace std;

#define tab "\t"

using std::cout;
using std::cin;
using std::endl;

//#define STL_MAP

void main()
{
	setlocale(LC_ALL, "Russian");
#ifdef STL_MAP
	//	map -  это контейнер, который хранит объекты в виде бинарного дерева.
	//	каждым элементом `map` является ПАРА "ключ - значение" (key - value)

	//	Ключи являются уникальными, т.е. в одном мап не может быть двух
	//	элементов с одинаковыми ключами, хотя значения могут повторяться.

	//	multimap - позволяет хранить два и более одинаковых ключа.

	std::map<int, std::string> week =
	{
		std::pair<int, std::string>(2, "Tuesday"),
		std::pair<int, std::string>(4, "Thursday"),
		std::pair<int, std::string>(5, "Friday"),
		std::pair<int, std::string>(3, "Wednesday"),
		std::pair<int, std::string>(5, "Friday"),
		std::pair<int, std::string>(6, "Saturday"),
		std::pair<int, std::string>(5, "Friday"),
		std::pair<int, std::string>(1, "Monday"),
		std::pair<int, std::string>(0, "Sunday")
	};

	week[7] = "Воскресенье";
	cout << "map\n";
	for (std::map<int, std::string>::const_iterator it = week.begin(); it != week.end(); it++)
	{
		cout << it->first << tab;
		cout << it->second << endl;
	}


	std::unordered_map<int, std::string> u_week =
	{
		std::pair<int, std::string>(2, "Tuesday"),
		std::pair<int, std::string>(4, "Thursday"),
		std::pair<int, std::string>(5, "Friday"),
		std::pair<int, std::string>(3, "Wednesday"),
		std::pair<int, std::string>(5, "Friday"),
		std::pair<int, std::string>(6, "Saturday"),
		std::pair<int, std::string>(5, "Friday"),
		std::pair<int, std::string>(1, "Monday"),
		std::pair<int, std::string>(0, "Sunday")
	};
	cout << "unordered_map\n";
	for (std::unordered_map<int, std::string>::const_iterator it = u_week.begin(); it != u_week.end(); it++)
	{
		cout << it->first << tab;
		cout << it->second << endl;
	}

	cout << "multimap\n";
	std::multimap<int, std::string> m_week =
	{
		std::pair<int, std::string>(2, "Tuesday"),
		std::pair<int, std::string>(4, "Thursday"),
		std::pair<int, std::string>(5, "Friday"),
		std::pair<int, std::string>(3, "Wednesday"),
		std::pair<int, std::string>(5, "Friday"),
		std::pair<int, std::string>(6, "Saturday"),
		std::pair<int, std::string>(5, "Friday"),
		std::pair<int, std::string>(1, "Monday"),
		std::pair<int, std::string>(0, "Sunday")
	};
	for (std::multimap<int, std::string>::const_iterator it = m_week.begin(); it != m_week.end(); it++)
	{
		cout << it->first << tab;
		cout << it->second << endl;
	}

	cout << "unordered_multimap\n";
	std::unordered_multimap <int, std::string> um_week =
	{
		std::pair<int, std::string>(2, "Tuesday"),
		std::pair<int, std::string>(4, "Thursday"),
		std::pair<int, std::string>(5, "Friday"),
		std::pair<int, std::string>(3, "Wednesday"),
		std::pair<int, std::string>(5, "Friday"),
		std::pair<int, std::string>(6, "Saturday"),
		std::pair<int, std::string>(5, "Friday"),
		std::pair<int, std::string>(1, "Monday"),
		std::pair<int, std::string>(0, "Sunday")
	};
	for (std::unordered_multimap<int, std::string>::const_iterator it = um_week.begin(); it != um_week.end(); it++)
	{
		cout << it->first << tab;
		cout << it->second << endl;
	}

#endif // STL_MAP
}