#include<iostream>
#include<array>

//using namespace std;

using std::cout;
using std::cin;
using std::endl;

#define tab "\t"

//#define STL_ARRAY

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
	}
	cout << endl;
#endif // STL_ARRAY



}
