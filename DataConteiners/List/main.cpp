#include "List.h"
#include "List.cpp"

//#define	BASE_CHECK
//#define SIZE_CONSTRUCTOR_AND_INDEX_OPERATOR
//#define ITERATORS_CHECK
//#define COPY_METHODS_CHECK
//#define MOVE_METHODS_CHECK
#define TEMPLATES_CHEK

	//	main
void main()
{
	setlocale(LC_ALL, "Russian");

	//int n; cout << "Введите размер списка: "; cin >> n;

#ifdef BASE_CHECK
	List list;
	for (int i = 0; i < n; i++)
	{
		list.push_back(rand() % 100);
	}

	list.print();
	//list.pop_front();
	cout << endl;
	list.print_revers();
	//list.pop_back();

	int index;
	int value;
	cout << "Введите индекс: "; cin >> index;
	cout << "Введите значение: "; cin >> value;
	list.insert(index, value);
	list.print();
	list.print_revers();

#endif // BASE_CHECK

#ifdef SIZE_CONSTRUCTOR_AND_INDEX_OPERATOR
	List list(n);
	for (size_t i = 0; i < list.getSize(); i++)
	{
		list[i] = rand() % 100;
	}
	for (size_t i = 0; i < list.getSize(); i++)
	{
		cout << list[i] << tab;
	}
	cout << endl;

	list.print();

#endif // SIZE_CONSTRUCTOR_AND_INDEX_OPERATOR

#ifdef ITERATORS_CHECK
	List list = { 3,5,8,13,21 };
	list.print();

	for (int i : list)
	{
		cout << i << tab;
	}
	cout << endl;

	for (List::Iterator it = list.begin(); it != list.end(); ++it)
	{
		cout << *it << tab;
	}
	cout << endl;

	cout << "Revers:\n";
	for (List::ReverseIterator it = list.rbegin(); it != list.rend(); ++it)
	{
		cout << *it << tab;
	}
#endif // ITERATORS_CHECK

#ifdef COPY_METHODS_CHECK
	List list1 = { 3,5,8,13,21 };
	list1.print();

	List list2 = list1;
	list2.print();

	List list3;
	list3 = list2;
	list3.print();
#endif // COPY_METHODS_CHECK

#ifdef MOVE_METHODS_CHECK
	List<int> list1 = { 3,5,8,13,21 };
	List<int> list2 = { 30,40,50 };

	//List list3 = list1 + list2; //MoveConstructor
	List<int> list3;
	list3 = list1 + list2;
	list3.print();
#endif // MOVE_METHODS_CHECK

#ifdef TEMPLATES_CHEK
	List<int> i_list = { 3,5,8,13,21 };
	i_list.print();
	List<double> d_list = { 2.5,3.14,5.2,8.3 };
	d_list.print();
	List<string> s_list = { "What","ken","I","do" };
	for (string i : s_list) cout << i << tab; cout << endl;
	
	for (List<string>::Iterator it = s_list.begin(); it != s_list.end(); ++it)
	{
		cout << *it << tab;
	}
	cout << endl;

	for (List<string>::ReverseIterator it = s_list.rbegin(); it != s_list.rend(); ++it)
	{
		cout << *it << tab;
	}
	cout << endl;
#endif // TEMPLATES_CHEK
}

//Signature - подпись
/*
-----------------------------------------------------
|                                                   |
|   "Компьютерная академия ШАГ"                     |
|   Курс: PD_011                                    |
|   Предмет: Объектно-ориентированное программиро-  |
|            вание с использованием языка C++       |
|                                                   |
|   Исполнитель: Курицын Алексей                    |
|   Преподаватель: Ковтун Олег                      |
|                                                   |
|   Екатеринбург - 2021                             |
|                                                   |
-----------------------------------------------------*/