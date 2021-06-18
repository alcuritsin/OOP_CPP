#pragma warning(disable:4326)
#include <iostream>

using namespace std;
using std::cin;
using std::cout;
using std::endl;

//#define DEBUG
#define tab "\t"
//#define	BASE_CHECK
//#define SIZE_CONSTRUCTOR_AND_INDEX_OPERATOR
//#define ITERATORS_CHECK
//#define COPY_METHODS_CHECK
//#define MOVE_METHODS_CHECK
#define TEMPLATES_CHEK

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
		Iterator(Element* Temp = nullptr) : BaseIterator(Temp)
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
			BaseIterator::Temp = BaseIterator::Temp->pNext;
			return *this;
		}

		Iterator operator++(int)	//	Postfix increment
		{
			Iterator old = *this;
			BaseIterator::Temp = BaseIterator::Temp->pNext;
			return old;
		}

		Iterator& operator--()	//	Prefix decrement
		{
			BaseIterator::Temp = BaseIterator::Temp->pPrev;
			return *this;
		}

		Iterator operator--(int)	//	Postfix decrement
		{
			Iterator old = *this;
			BaseIterator::Temp = BaseIterator::Temp->pPrev;
			return old;
		}

	};

	class ReverseIterator:public BaseIterator
	{
	public:
		ReverseIterator(Element* Temp = nullptr) : BaseIterator(Temp)
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
			BaseIterator::Temp = BaseIterator::Temp->pPrev;
			return *this;
		}

		ReverseIterator operator++(int)	//	Postfix increment
		{
			ReverseIterator old = *this;
			BaseIterator::Temp = BaseIterator::Temp->pPrev;
			return old;
		}

		ReverseIterator& operator--()	//	Prefix decrement
		{
			BaseIterator::Temp = BaseIterator::Temp->pNext;
			return *this;
		}

		ReverseIterator operator--(int)	//	Postfix decrement
		{
			ReverseIterator old = *this;
			BaseIterator::Temp = BaseIterator::Temp->pNext;
			return old;
		}

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

#ifdef ITERATORS_CHECK
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
#endif // ITERATORS_CHECK

#ifdef COPY_METHODS_CHECK
	List list1 = { 3,5,8,13,21 };
	list1.print();

	List list2 = list1;
	list2.print();

	List list3;
	list3 = list2;
	list3.print();
#endif // COPY_METHODS_CHECK

#ifdef MOVE_METHODS_CHECK
	List<int> list1 = { 3,5,8,13,21 };
	List<int> list2 = { 30,40,50 };

	//List list3 = list1 + list2; //MoveConstructor
	List<int> list3;
	list3 = list1 + list2;
	list3.print();
#endif // MOVE_METHODS_CHECK

#ifdef TEMPLATES_CHEK
	List<int> i_list = { 3,5,8,13,21 };
	i_list.print();
	List<double> d_list = { 2.5,3.14,5.2,8.3 };
	d_list.print();
	List<string> s_list = { "What","ken","I","do" };
	for (string i : s_list) cout << i << tab; cout << endl;
#endif // TEMPLATES_CHEK

}
