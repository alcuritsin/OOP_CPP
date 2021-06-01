#pragma once
#include "Element.h"

template <typename T>
class Iterator
{
	Element<T>* Temp;
public:
	Iterator(Element<T>* Temp = nullptr);
	~Iterator();

	// Operators:
	Iterator<T>& operator++();
	Iterator<T> operator ++(int);
	bool operator== (const Iterator<T>& other) const;
	bool operator!= (const Iterator<T>& other) const;
	Element<T>*& operator-> ();
	Element<T>* get_current_address();

	const T& operator *()const;
	T& operator *();

};
