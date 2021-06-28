#include<iostream>
#include<array>
#include<vector>

//using namespace std;

using std::cout;
using std::cin;
using std::endl;

#define tab "\t"

//#define STL_ARRAY
#define STL_VECTOR
//#define EXEPTIONS_IN_VECTOR

template<typename T> void vector_properties(const std::vector<T>& vec)
{
	cout << "Size:     " << vec.size() << endl;				//	Размер.
	cout << "Capasity: " << vec.capacity() << endl;		//	Вместительность - сколько элементов может вместить в себя вектор, без переопределения памяти.
	cout << "MaxSize:  " << vec.max_size() << endl;		//	Максимальный размер
}

template<typename T> void vector_print(const std::vector<T>& vec)
{
	for (typename std::vector<T>::const_iterator it = vec.begin(); it != vec.end(); it++)
	{
		cout << *it << tab;
	}
	cout << endl;
}

void main()
{
	setlocale(LC_ALL, "Russian");

#ifdef STL_ARRAY
	//	array - это контейнер, который хранит данные в виде статического массива.
	const int n = 5;
	std::array<int, n> arr = { 3,5,8,13,21 };
	for (int i = 0; i < arr.size(); i++)
	{
		cout << arr[i] << tab;
		//cout << arr.at(i) << tab;

	}
	cout << endl;
#endif // STL_ARRAY

#ifdef STL_VECTOR
	// Vector - это контейнер, который хранит данные в виде динамического массива.
	std::vector<int> vec = { 0, 1, 1, 2, 3, 5, 8, 13, 21, 34 };

	vector_properties(vec);

	vec.push_back(55);
	cout << "vec.push_back(55)" << endl;

	vector_properties(vec);

#ifdef EXEPTIONS_IN_VECTOR
	// exeption - это ошибка на этапе выполнения.
	try
	{
		for (int i = 0; i < vec.capacity(); i++)
		{
			//	[] - индекс оператоh (subscript operator)
			//	try...catch...
			//cout << vec[i] << tab;	//	Оператор '[]' - не бросает 'исключение' при выходе за пределы вектора.

			cout << vec.at(i) << tab;	//	Метод 'at()' - бросает 'исключение' (out of range exeption) при выходе за пределы вектора.
		}

		throw 123;
		cout << endl;
	}
	catch (const std::exception& e)
	{
		std::cerr << e.what() << endl;
	}
	catch (int e)
	{
		std::cerr << "Error: " << e << endl;
	}
#endif // EXEPTIONS_IN_VECTOR

	vector_print(vec);

#endif // STL_VECTOR



}
