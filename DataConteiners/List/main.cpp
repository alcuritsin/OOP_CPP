﻿#pragma warning(disable:4326)
#include <iostream>

using namespace std;
using std::cin;
using std::cout;
using std::endl;

//#define DEBUG
#define tab "\t"
//#define	BASE_CHECK
//#define SIZE_CONSTRUCTOR_AND_INDEX_OPERATOR


class  List
{
public:
	class Element
	{
		int Data;		//	Значение элемента
		Element* pNext;	//	Указатель на следующий элемент
		Element* pPrev;	//	Указатель на предидущий элемент

	public:
		Element(int Data, Element* pNext = nullptr, Element* pPrev = nullptr)
		{
			this->Data = Data;
			this->pNext = pNext;
			this->pPrev = pPrev;

#ifdef DEBUG
			cout << "EConstructor:\t" << this << endl;
#endif // DEBUG

		}

		~Element()
		{
#ifdef DEBUG
			cout << "EDestructor:\t" << this << endl;
#endif // DEBUG
		}

		friend class List;
	};

	Element* Head;	//	Указатель на начальный элемент списка
	Element* Tail;	//	Указатель на конечный элемент списка

	unsigned int size;	//	Размер списка
public:
	class Iterator
	{
		Element* Temp;
	public:
		Iterator(Element* Temp = nullptr) : Temp(Temp)
		{
#ifdef DEBUG
			cout << "ITConstructor:\t" << this << endl;
#endif // DEBUG
		}
		~Iterator()
		{
#ifdef DEBUG
			cout << "ITDestructor:\t" << this << endl;
#endif // DEBUG
		}

		Iterator& operator++()	//	Prefix increment
		{
			Temp = Temp->pNext;
			return *this;
		}

		Iterator operator++(int)	//	Postfix increment
		{
			Iterator old = *this;
			Temp = Temp->pNext;
			return old;
		}

		Iterator& operator--()	//	Prefix decrement
		{
			Temp = Temp->pPrev;
			return *this;
		}

		Iterator operator--(int)	//	Postfix decrement
		{
			Iterator old = *this;
			Temp = Temp->pPrev;
			return old;
		}

		bool operator ==(const Iterator& other) const
		{
			return this->Temp == other.Temp;
		}

		bool operator !=(const Iterator& other) const
		{
			return this->Temp != other.Temp;
		}

		const int& operator*() const
		{
			return Temp->Data;
		}
		int& operator*()
		{
			return Temp->Data;
		}

	};

	class ReverseIterator
	{
		Element* Temp;
	public:

	ReverseIterator(Element* Temp = nullptr) : Temp(Temp)
		{
#ifdef DEBUG
			cout << "rITConstructor:\t" << this << endl;
#endif // DEBUG
		}
		~ReverseIterator()
		{
#ifdef DEBUG
			cout << "rITDestructor:\t" << this << endl;
#endif // DEBUG
		}

		ReverseIterator& operator++()	//	Prefix increment
		{
			Temp = Temp->pPrev;
			return *this;
		}

		ReverseIterator operator++(int)	//	Postfix increment
		{
			ReverseIterator old = *this;
			Temp = Temp->pPrev;
			return old;
		}

		ReverseIterator& operator--()	//	Prefix decrement
		{
			Temp = Temp->pNext;
			return *this;
		}

		ReverseIterator operator--(int)	//	Postfix decrement
		{
			ReverseIterator old = *this;
			Temp = Temp->pNext;
			return old;
		}

		bool operator ==(const ReverseIterator& other) const
		{
			return this->Temp == other.Temp;
		}

		bool operator !=(const ReverseIterator& other) const
		{
			return this->Temp != other.Temp;
		}

		const int& operator*() const
		{
			return Temp->Data;
		}

		int& operator*()
		{
			return Temp->Data;
		}

	};

	size_t getSize()const
	{
		return size;
	}

	List()
	{
		Head = Tail = nullptr;
		size = 0;

#ifdef DEBUG
		cout << "LConstructor:\t" << this << endl;
#endif // DEBUG

	}

	List(const initializer_list<int>& il) :List()
	{
		//cout << typeid(il.begin()).name() << endl;

		for (int const* it = il.begin(); it != il.end(); it++)
		{
			push_back(*it);
		}
	}

	explicit List(int size) :List()
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

	~List()
	{
		//while (Head) pop_front();
		while (Head) pop_back();
#ifdef DEBUG
		cout << "LDestructor:\t" << this << endl;
#endif // DEBUG
	}

	//		Operators:
	int& operator[](size_t index)
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

	//		Adding element:
	void push_front(int Data)
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

	void push_back(int Data)
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
	void pop_front()
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

	void pop_back()
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
	void insert(size_t Index, int Data)
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
	void print()
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

	void print_revers()
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

	Iterator begin()
	{
		return Head;
	}

	Iterator end()
	{
		return nullptr;
	}

	ReverseIterator rbegin()
	{
		return Tail;
	}

	ReverseIterator rend()
	{
		return nullptr;
	}

};

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
}
