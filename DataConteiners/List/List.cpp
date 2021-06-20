#pragma once
#include "List.h"

//	Element	-	methods
template <typename T> List<T>::Element::Element(T Data, Element* pNext, Element* pPrev)
{
	this->Data = Data;
	this->pNext = pNext;
	this->pPrev = pPrev;

#ifdef DEBUG
	cout << "EConstructor:\t" << this << endl;
#endif // DEBUG

}

template <typename T> List<T>::Element::~Element()
{
#ifdef DEBUG
	cout << "EDestructor:\t" << this << endl;
#endif // DEBUG
}

//	BaseIterator	-	methods
template <typename T> List<T>::BaseIterator::BaseIterator(Element* Temp) :Temp(Temp)
{
#ifdef DEBUG
	cout << "BITConstructor:\t" << this << endl;
#endif // DEBUG
}

template <typename T> List<T>::BaseIterator::~BaseIterator()
{
#ifdef DEBUG
	cout << "BITDestructor:\t" << this << endl;
#endif // DEBUG
}

template <typename T> bool List<T>::BaseIterator::operator==(const BaseIterator& other)const
{
	return this->Temp == other.Temp;
}

template <typename T> bool List<T>::BaseIterator::operator!=(const BaseIterator& other)const
{
	return this->Temp != other.Temp;
}

template <typename T> const T& List<T>::BaseIterator::operator*()const
{
	return Temp->Data;
}

template <typename T> T& List<T>::BaseIterator::operator*()
{
	return Temp->Data;
}

//	Iterator	-	methods
template <typename T> List<T>::Iterator::Iterator(Element* Temp) : BaseIterator(Temp)
{
#ifdef DEBUG
	cout << "ITConstructor:\t" << this << endl;
#endif // DEBUG
}

template <typename T> List<T>::Iterator::~Iterator()
{
#ifdef DEBUG
	cout << "ITDestructor:\t" << this << endl;
#endif // DEBUG
}

template <typename T> typename List<T>::Iterator& List<T>::Iterator::operator++()	//	Prefix increment
{
	BaseIterator::Temp = BaseIterator::Temp->pNext;
	return *this;
}

template <typename T> typename List<T>::Iterator List<T>::Iterator::operator++(int)	//	Postfix increment
{
	Iterator old = *this;
	BaseIterator::Temp = BaseIterator::Temp->pNext;
	return old;
}

template <typename T> typename List<T>::Iterator& List<T>::Iterator::operator--()	//	Prefix decrement
{
	BaseIterator::Temp = BaseIterator::Temp->pPrev;
	return *this;
}

template <typename T> typename List<T>::Iterator List<T>::Iterator::operator--(int)	//	Postfix decrement
{
	Iterator old = *this;
	BaseIterator::Temp = BaseIterator::Temp->pPrev;
	return old;
}

//	ReversIterator	-	methods
template <typename T> List<T>::ReverseIterator::ReverseIterator(Element* Temp) : BaseIterator(Temp)
{
#ifdef DEBUG
	cout << "rITConstructor:\t" << this << endl;
#endif // DEBUG
}

template <typename T> List<T>::ReverseIterator::~ReverseIterator()
{
#ifdef DEBUG
	cout << "rITDestructor:\t" << this << endl;
#endif // DEBUG
}

template <typename T> typename List<T>::ReverseIterator::ReverseIterator& List<T>::ReverseIterator::operator++()	//	Prefix increment
{
	BaseIterator::Temp = BaseIterator::Temp->pPrev;
	return *this;
}

template <typename T> typename List<T>::ReverseIterator::ReverseIterator List<T>::ReverseIterator::operator++(int)	//	Postfix increment
{
	ReverseIterator old = *this;
	BaseIterator::Temp = BaseIterator::Temp->pPrev;
	return old;
}

template <typename T> typename List<T>::ReverseIterator::ReverseIterator& List<T>::ReverseIterator::operator--()	//	Prefix decrement
{
	BaseIterator::Temp = BaseIterator::Temp->pNext;
	return *this;
}

template <typename T> typename List<T>::ReverseIterator::ReverseIterator List<T>::ReverseIterator::operator--(int)	//	Postfix decrement
{
	ReverseIterator old = *this;
	BaseIterator::Temp = BaseIterator::Temp->pNext;
	return old;
}

//	List	-	methods
template <typename T> size_t List<T>::getSize()const
{
	return size;
}

template <typename T> List<T>::List()
{
	Head = Tail = nullptr;
	size = 0;

#ifdef DEBUG
	cout << "LConstructor:\t" << this << endl;
#endif // DEBUG

}

template <typename T> List<T>::List(const initializer_list<T>& il) :List()
{
	//cout << typeid(il.begin()).name() << endl;

	for (T const* it = il.begin(); it != il.end(); it++)
	{
		push_back(*it);
	}
}

template <typename T> List<T>::List(int size) :List()
{
	//	explicit - Запрещает неявное преобразование.
	// 
	//	Без explicit было бы возможно:
	//	List list = n;
	// 	Преобразование типов. Из int в List (значение типа инт преобразуется в список).
	//	Это неадекватное поведение программы. Поэтому ставится explicit.
	//	Это даёт возможность создавать список с использованием круглых скобок и никак иначе!
	//	List list(n);

	while (size--)
	{
		push_back(0);
	}
}

template <typename T> List<T>::List(const List<T>& other) : List()
{

	for (T i : other) push_back(i);
#ifdef DEBUG
	cout << "CopyConstructor\t" << this << endl;
#endif // DEBUG
}

template <typename T> List<T>::List(List<T>&& other)
{
	this->size = other.size;
	this->Head = other.Head;
	this->Tail = other.Tail;
	other.Head = other.Tail = nullptr;

#ifdef DEBUG
	cout << "MoveConstructor\t" << this << endl;
#endif // DEBUG
}

template <typename T> List<T>::~List()
{
	//while (Head) pop_front();
	while (Head) pop_back();
#ifdef DEBUG
	cout << "LDestructor:\t" << this << endl;
#endif // DEBUG
}

//		Operators:
template <typename T> T& List<T>::operator[](size_t index)
{
	Element* Temp;

	if (index < size / 2)
	{
		Temp = Head;
		for (size_t i = 0; i < index; i++)
		{
			Temp = Temp->pNext;
		}
	}
	else
	{
		Temp = Tail;
		for (size_t i = 0; i < size - index - 1; i++)
		{
			Temp = Temp->pPrev;
		}
	}
	return Temp->Data;
}

template <typename T> List<T>& List<T>::operator=(const List<T>& other)
{
	//for (int i : other.begin())
	//{
	//	push_back(i);
	//}
	if (this == &other) return *this;
	while (Head) pop_front();

	for (T i : other) push_back(i);

#ifdef DEBUG
	cout << "CopyAssignment\t" << this << endl;
#endif // DEBUG

	/*for (Iterator it = other.begin(); it != other.end(); ++it)
	{
		push_back(*it);
	}*/
}

template <typename T> List<T>& List<T>::operator= (List<T>&& other)
{
	while (Head)pop_front();
	this->size = other.size;
	this->Head = other.Head;
	this->Tail = other.Tail;
	other.Head = other.Tail = nullptr;

#ifdef DEBUG
	cout << "MoveAssignment\t" << this << endl;
#endif // DEBUG

	return *this;
}

//		Adding element:
template <typename T> void List<T>::push_front(T Data)
{
	if (Head == nullptr && Tail == nullptr)
	{
		Head = Tail = new Element(Data);
		size++;
		return;
	}

	Element* New = new Element(Data);

	New->pNext = Head;
	Head->pPrev = New;

	Head = New;

	//Head = new Element(Data, Head, Tail);
	size++;
}

template <typename T> void List<T>::push_back(T Data)
{
	if (Head == nullptr && Tail == nullptr)
	{
		//push_front(Data);
		Head = Tail = new Element(Data);
		size++;
		return;
	}

	Element* New = new Element(Data);

	New->pPrev = Tail;
	Tail->pNext = New;
	Tail = New;
	size++;
}

//		Erasing element:
template <typename T> void List<T>::pop_front()
{
	if (Head == Tail)
	{
		delete Head;
		Head = Tail = nullptr;
		size--;
		return;
	}

	Head = Head->pNext;
	delete Head->pPrev;

	Head->pPrev = nullptr;
	size--;
}

template <typename T> void List<T>::pop_back()
{
	if (Head == Tail)
	{
		delete Head;
		Head = Tail = nullptr;
		size--;
		return;
	}

	Tail = Tail->pPrev;
	delete Tail->pNext;
	Tail->pNext = nullptr;
	size--;
}

template <typename T> void List<T>::insert(size_t Index, T Data)
{
	if (Index > size)return;
	if (Index == 0)
	{
		push_front(Data);
		return;
	}

	if (Index == size)
	{
		push_back(Data);
		return;
	}

	Element* Temp;
	if (Index < size / 2)
	{
		Temp = Head;
		for (size_t i = 0; i < Index; i++)Temp = Temp->pNext;
	}
	else
	{
		Temp = Tail;
		for (size_t i = 0; i < size - Index - 1; i++)Temp = Temp->pNext;
	}

	Element* New = new Element(Data);

	New->pNext = Temp;
	New->pPrev = Temp->pPrev;
	Temp->pPrev->pNext = New;
	Temp->pPrev = New;
	size++;
}

//		Methods:
template <typename T> void List<T>::print()
{
	cout << "print:\n";
	for (Element* Temp = Head; Temp != nullptr; Temp = Temp->pNext)
	{
#ifdef DEBUG
		cout << Temp << endl;
		cout << Temp->pPrev << tab;
#endif // DEBUG

		cout << Temp->Data << tab;

#ifdef DEBUG
		cout << Temp->pNext;
		cout << endl;
#endif // DEBUG
	}
	cout << "size: " << size;
	cout << endl;
}

template <typename T> void List<T>::print_revers()
{
	cout << "print_revers:\n";
	for (Element* Temp = Tail; Temp != nullptr; Temp = Temp->pPrev)
	{
#ifdef DEBUG
		cout << Temp << endl;
		cout << Temp->pPrev << tab;
#endif // DEBUG

		cout << Temp->Data << tab;

#ifdef DEBUG
		cout << Temp->pNext;
		cout << endl;
#endif // DEBUG
	}
	cout << "size: " << size;
	cout << endl;
}

template <typename T> typename List<T>::Iterator List<T>::begin()
{
	return Head;
}

template <typename T> const typename List<T>::Iterator List<T>::begin()const
{
	return Head;
}

template <typename T> typename List<T>::Iterator List<T>::end()
{
	return nullptr;
}

template <typename T> const typename List<T>::Iterator List<T>::end()const
{
	return nullptr;
}

template <typename T> typename List<T>::ReverseIterator List<T>::rbegin()
{
	return Tail;
}

template <typename T> const typename List<T>::ReverseIterator List<T>::rbegin() const
{
	return Tail;
}

template <typename T> typename List<T>::ReverseIterator List<T>::rend()
{
	return nullptr;
}

template <typename T> const typename List<T>::ReverseIterator List<T>::rend() const
{
	return nullptr;
}

template<typename T> List<T> operator+(const List<T>& left, const List<T>& right)
{
	List<T> cat = left;
	for (T i : right) cat.push_back(i);
	return cat;
}