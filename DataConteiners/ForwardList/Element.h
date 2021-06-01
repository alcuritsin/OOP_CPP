#pragma once
#include <iostream>

using namespace std;

using std::cout;
using std::endl;

//#define DEBUG
//#define RANGE_BASED_ARRAY
//#define RANGE_BASED_LIST

template<typename T> class ForwardList;
template<typename T> class Iterator;
template<typename T> class Element;

template <typename T>
class Element
{
	T Data;	//	Значение элемента
	Element<T>* pNext;	//	Указатель на следующий элемент
	static int count;

public:
	Element(T Data, Element<T>* pNext = nullptr);
	~Element();

	friend class ForwardList<T>;
	friend class Iterator<T>;
	//	2. Написать деструктор, чтобы он очищал список перед удалением;
};
