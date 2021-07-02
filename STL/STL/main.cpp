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

template <typename T> void vector_reverse_print(const std::vector<T>& vec)
{
	//	Написать функцию vector_reverse_print(...),
	//	которая будет выводить ветктор в обратном порядке.
	for (typename std::vector<T>::const_reverse_iterator it = vec.crbegin(); it != vec.crend(); it++)
	{
		cout << *it << tab;
	}
	cout << endl;
}

template<typename T> void vector_insert(std::vector<T>& vec, int index, T data)
{
	//	Добавить значение в вектор по индексу.
	//	Индекс и значение вводятся с клавиатуры.
	
	////	C++98
	//if (index > vec.size())
	//{
	//	vec.push_back(data);
	//}
	//else
	//{
	//	vec.insert(vec.begin() + index, data);
	//}

	//	Более эффективный метод!
	//	>= C++11
	if (index > vec.size())
	{
		vec.emplace_back(data);
	}
	else if (index < 0)
	{
		return;
	}
	else
	{
		vec.emplace(vec.begin()+index, data);
	}
}

template<typename T> void vector_erase(std::vector<T>& vec, int index)
{
	//	Удалить значение из вектора по указанному индексу, введенному с клавиатуры.
	if (index > vec.size() || index < 0)
	{
		return;
	}
	else
	{
		vec.erase(vec.begin() + index);
	}
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
	cout << "Revers:\n";
	vector_reverse_print(vec);

	vector_properties(vec);
	int data; int index;
	cout << "Индекс вставки: "; cin >> index;
	cout << "Значение для вставки: "; cin >> data;
	vector_insert(vec, index, data);
	
	/*std::vector<int>::iterator position = vec.begin() + index;
	vec.insert(position, data);*/

	vector_print(vec);
	vector_properties(vec);
	cout << "Индекс для удаления: "; cin >> index;
	//vec.erase(vec.begin() + index);
	vector_erase(vec, index);
	vector_print(vec);
	vector_properties(vec);

	vector_properties(vec);
	vec.assign({ 1024,2048,3072 });
	vector_print(vec);
	vector_properties(vec);
	vec.shrink_to_fit();
	vector_properties(vec);

#endif // STL_VECTOR
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