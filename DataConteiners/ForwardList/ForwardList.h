#pragma once
#include "Element.h"

template <typename T>
class  ForwardList
{
	Element<T>* Head;
	int size;
public:
	Iterator<T> getHead();

	Iterator<T> begin();
	Iterator<T> end();


	ForwardList(initializer_list<T> il);

	ForwardList();


	ForwardList<T>(const ForwardList<T>& other);

	~ForwardList();

	//	Adding Elements
	void push_front(T Data);
	void push_back(T Data);

	//	Erassing elements:
	void erasing_front();

	void erase(T index);

	void pop_back();

	void insert(T Data, int index);


	//	Methods
	void print();

	// Operators
	ForwardList <T>& operator=(const ForwardList<T>& other);

};
