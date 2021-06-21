#pragma once
#pragma warning(disable:4326)
#include <iostream>

//#define DEBUG
#define tab "\t"

using namespace std;
using std::cin;
using std::cout;
using std::endl;

template<typename T> class  List;

template<typename T> class  List
{
public:
	class Element
	{
		T Data;		//	Значение элемента
		Element* pNext;	//	Указатель на следующий элемент
		Element* pPrev;	//	Указатель на предидущий элемент

	public:
		Element(T Data, Element* pNext = nullptr, Element* pPrev = nullptr);

		~Element();

		friend class List<T>;
	};

	Element* Head;	//	Указатель на начальный элемент списка
	Element* Tail;	//	Указатель на конечный элемент списка

	unsigned int size;	//	Размер списка

	class BaseIterator
	{
	protected:
		Element* Temp;
	public:
		BaseIterator(Element* Temp = nullptr);

		~BaseIterator();

		bool operator ==(const BaseIterator& other) const;

		bool operator !=(const BaseIterator& other) const;

		const T& operator*() const;

		T& operator*();

	};

public:
	class Iterator :public BaseIterator
	{
	public:
		Iterator(Element* Temp = nullptr);

		~Iterator();

		Iterator& operator++();

		Iterator operator++(int);

		Iterator& operator--();

		Iterator operator--(int);

	};

	class ReverseIterator :public BaseIterator
	{
	public:
		ReverseIterator(Element* Temp = nullptr);
		~ReverseIterator();

		ReverseIterator& operator++();

		ReverseIterator operator++(int);

		ReverseIterator& operator--();

		ReverseIterator operator--(int);

	};

	size_t getSize()const;

	List();

	List(const initializer_list<T>& il);

	explicit List(int size);

	List(const List<T>& other);

	List(List<T>&& other);

	~List();

	//		Operators:
	T& operator[](size_t index);

	List<T>& operator=(const List<T>& other);

	List<T>& operator= (List<T>&& other);

	//		Adding element:
	void push_front(T Data);

	void push_back(T Data);

	//		Erasing element:
	void pop_front();

	void pop_back();

	void insert(size_t Index, T Data);

	//		Methods:
	void print();

	void print_revers();

	Iterator begin();

	const Iterator begin()const;

	Iterator end();

	const Iterator end()const;

	ReverseIterator rbegin();

	const ReverseIterator rbegin() const;

	ReverseIterator rend();

	const ReverseIterator rend() const;

};
