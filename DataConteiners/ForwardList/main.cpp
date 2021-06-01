//TODO:
//1. В классе Itertor перегрузить оператор разыменования;
//2. В классе ForwardList написать конструктор, который позволит создавать объекты следующим образом :
//ForwardList list = { 3, 5, 8, 13, 21 };

#include "Element.h"
#include "Iterator.h"
#include "ForwardList.h"
#include "Element.cpp"
#include "Iterator.cpp"
#include "ForwardList.cpp"

void main()
{
	setlocale(LC_ALL, "Russian");

#ifdef BASE_CHECK

#endif // BASE_CHECK

	//int n;
	//cout << "Введите размер списка: "; cin >> n;

	//ForwardList<int> list;
	//for (int  i = 0; i < n; i++)
	//{
	//	list.push_front(rand() % 100);
	//	list.push_back(rand() % 100);
	//}
	//list.print();
	//for (Iterator it = list.getHead(); it != nullptr; it++)
	//{
	//	*it = rand() % 100;
	//}
	//list.print();

	//list = list;

	//list.print();
#ifdef RANGE_BASED_ARRAY
	int arr[] = { 3, 5, 8, 13, 21 };
	cout << size(arr);
	for (int i = 0; i < size(arr); i++)
	{
		cout << arr[i] << "\t";
	}
	cout << endl;

	for (int i : arr)	//	Range-based for (цыкл фор для диапазона)
	{
		cout << i << "\t";
	}
	cout << endl;

#endif // RANGE_BASED_ARRAY

#ifdef RANGE_BASED_LIST
	ForwardList<int> list = { 3, 5, 8, 13, 21 };
	list.print();

	for (int i : list)
	{
		cout << i << "\t";
	}
	cout << endl;

#endif // RANGE_BASED_LIST

/*
	list.erase(6);
	list.print();

	cout << "List2:" << endl;
	ForwardList list2 (list);
	list2.print();
	cout << "List3::" << endl;
	ForwardList list3;
	list3 = list2;
	list3.print();

*/
	/*list.erasing_front();
	list.print();

	list.pop_back();
	list.print();*/

	//int value;
	//int index;

	//cout << "Value: "; cin >> value;
	//cout << "Index: "; cin >> index;

	//list.insert(value ,index);
	//list.print();
	

	//cout << "List2:" << endl;
	//ForwardList list2;
	//for (int i = 0; i < n; i++)
	//{
	//	//list.push_front(rand() % 100);
	//	list2.push_back(rand() % 100);
	//}
	//list2.print();


	//list.push_back(123);

	//list.print();

	ForwardList<double> list{ 2.5, 3.14,8.3,5.4,7.2 };
	for  (double i:list)
	{
		cout << i << "\t";
	}
	cout << endl;
}
/*
В класс ForwardList добавить :
1. метод erase(), который удаляет элемент по индексу;
2. Написать деструктор, чтобы он очищал список перед удалением;
3. Добавить CopyMethods;
*/