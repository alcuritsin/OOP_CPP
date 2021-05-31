﻿//TODO:
//1. В классе Itertor перегрузить оператор разыменования;
//2. В классе ForwardList написать конструктор, который позволит создавать объекты следующим образом :
//ForwardList list = { 3, 5, 8, 13, 21 };

#include <iostream>

using namespace std;

using std::cout;
using std::endl;

//#define DEBUG
//#define RANGE_BASED_ARRAY

class Element;
class ForwardList;

class Element
{
	int Data;	//	Значение элемента
	Element* pNext;	//	Указатель на следующий элемент
	static int count;

public:
	Element(int Data, Element* pNext = nullptr) : Data(Data), pNext(pNext)
	{
		count++;
#ifdef DEBUG
		cout << "EConstrictor:\t\t" << this << endl;
#endif // DEBUG
	}
	~Element()
	{
		count--;
#ifdef DEBUG
		cout << "EDestructor:\t\t" << this << endl;
#endif // DEBUG
	}
	friend class ForwardList;
	friend class Iterator;
	//	2. Написать деструктор, чтобы он очищал список перед удалением;
};

int Element::count = 0;	//	Инициализация статической переменной

class Iterator
{
	Element* Temp;
public:
	Iterator(Element* Temp = nullptr)
	{
		this->Temp = Temp;
#ifdef DEBUG
		cout << "IConstructor" << this << endl;

#endif // DEBUG

	}
	~Iterator()
	{
#ifdef DEBUG

		cout << "IDestructor" << this << endl;
#endif // DEBUG

	}

	// Operators:
	Iterator& operator++()
	{
		Temp = Temp->pNext;
		return *this;
	}
	Iterator operator ++(int)
	{
		Iterator old = *this;
		Temp = Temp->pNext;
		return old;
	}
	bool operator== (const Iterator& other) const
	{
		return this->Temp == other.Temp;
	}
	bool operator!= (const Iterator& other) const
	{
		return this->Temp != other.Temp;
	}
	Element*& operator-> ()
	{
		return Temp;
	}
	Element* get_current_address()
	{
		return Temp;
	}

	const int& operator *()const
	{
		return Temp->Data;
	}
	int& operator *()
	{
		return Temp->Data;
	}

};

class  ForwardList
{
	Element* Head;
	int size;
public:
	Iterator getHead()
	{
		return Head;
	}

	Iterator begin()
	{
		return Head;
	}
	Iterator end()
	{
		return nullptr;
	}


	ForwardList(initializer_list<int> il) :ForwardList() //	 Делегирование кнструктора по умолчанию
	{
		//	il - это контейнер, такой же, как наш ForwardList
		//	У любого контейнера есть методы begin() и end(),
		//	которые возвращают адрес на начало и конец контейнера

		cout << typeid(il.begin()).name() << endl;
		for (int const* it = il.begin(); it != il.end(); it++)
		{
			//	it - это итератор, которрый проходит по il
			push_back(*it);
		}
	}

	ForwardList() 	//	Создаёт пустой список.
	{
		Head = nullptr;
		size = 0;
#ifdef DEBUG
		cout << "LConstrictor:\t\t" << this << endl;
#endif // DEBUG

	}

	ForwardList(const ForwardList& other)
	{
		//	NOT DONE -- TODO!!!
		//	Добавить CopyMethods;
		Element* Temp = other.Head;

		while (Temp != nullptr)
		{
			this->push_back(Temp->Data);
			Temp = Temp->pNext;
		}


#ifdef DEBUG
		cout << "Copy_LConstrictor:\t\t" << this << endl;
#endif // DEBUG
	}

	~ ForwardList()
	{
		//	Написать деструктор, чтобы он очищал список перед удалением;
		while (Head->pNext != nullptr)
		{
			Element* Temp = Head;
			while (Temp->pNext->pNext != nullptr)
			{
				Temp = Temp->pNext;
			}
				delete Temp->pNext;
				Temp->pNext = nullptr;
		}
		delete Head;

#ifdef DEBUG
		cout << "LDestructor:\t\t" << this << endl;
#endif // DEBUG
	}
	//	Adding Elements
	void push_front(int Data)
	{
		//	Добавляет новый элемент в начало списка.
		Head = new Element(Data, Head);
		/*Element* New = new Element(Data);
		New->pNext = Head;
		Head = New;*/
		size++;
	}
	void push_back(int Data)
	{
		//	Добавляет значение в конец списка.
		//	Этот метод не умеет работать с пустым списком.
		if (Head == nullptr)
		{
			//	Если список пуст вызываем метод умеющий работать с пустым списком.
			push_front(Data);
			return;
		}
		//Element* New = new Element(Data);

		Element* Temp = Head; // Итератор
		

		while (Temp->pNext !=nullptr)
		{
			Temp = Temp->pNext;
		}
		Temp->pNext = new Element (Data);
		size++;
	}

	//	Erassing elements:
	void erasing_front()
	{

		Element* Temp = Head;

		Head = Head->pNext;

		delete Temp;
		size--;
	}

	void erase(int index)
	{
		//	метод erase(), который удаляет элемент по индексу;

		//	Введённый индекс выходит за правую границу списка.
		//	Список не изменится. Выход из метода.
		if (size < index) return;	//	Когда есть размер списка. Если такого параметра нет ниже предусмотрен другой вариант выхода.

		Element* Temp = Head;

		if (index == 0)
		{
			erasing_front();
			return;
		}

		for (int i = 0; i < index - 1; i++)
		{
			Temp = Temp->pNext;
			if (Temp->pNext->pNext == nullptr)
			{
				//	Достигнут предпоследний элемент списка. 
				if (i + 2 < index-1)
				{	
					//	Другой вариант выхода:
					//	Введённый индекс выходит за правую границу списка.
					//	Список не изменится. Выход из метода.
					return;
				}
				break;
			}
		}

		//	Запоминаем эелемент для освобождения памяти.
		Element* erTemp = Temp->pNext;
		//	Адрес следующего элемента списка, получает значение через элемент.
		Temp->pNext  = Temp->pNext->pNext;
		//	Освобождаем память
		delete erTemp;
		//	Уменьшаем размер массива.
		size--;
	}

	void pop_back()
	{
		Element* Temp = Head;

		while (Temp->pNext->pNext != nullptr)
		{
			Temp = Temp->pNext;
		}

		delete Temp->pNext;

		Temp->pNext = nullptr;

		//Element* Temp = Head;
		//Element* Temp_2 = Temp;
		//while (Temp->pNext != nullptr)
		//{
		//	Temp_2 = Temp;
		//	Temp = Temp->pNext;
		//}

		//Temp_2->pNext = nullptr;

		//delete Temp;
		size--;
	}

	void insert( int Data, int index)
	{
		if (index == 0)
		{
			push_front(Data);
			return;
		}

		Element* Temp = Head;

		//Element* New = new Element(Data);
		
		for (int i = 0; i < index - 1; i++, Temp = Temp->pNext)
		{
			if (Temp->pNext == nullptr)break;
		}

		/*New->pNext = Temp->pNext;
		Temp->pNext = New;*/
		Temp->pNext = new Element(Data, Temp->pNext);
		size++;
	}


	//	Methods
	void print()
	{
		//Element* Temp = Head;
		//while (Temp!=nullptr)
		//{
		//	cout << Temp << "\t" << Temp->Data << "\t" << Temp->pNext << endl;
		//	Temp = Temp->pNext;
		//}

		//for (Element* Temp =Head; Temp; Temp=Temp->pNext )
		for (Iterator Temp = Head; Temp!= nullptr; Temp++)
		{
			//cout<< Temp.get_current_address() << "\t" << Temp->Data << "\t" << Temp->pNext << endl;
			cout<< *Temp << "\t";
		}
		cout << endl;
		cout << "Count := " << Element::count << endl;
		cout << "Size := " << size << endl;
	}

	// Operators
	ForwardList& operator=(const ForwardList& other)
	{
		//	NOT DONE -- TODO!!!
		//	Добавить CopyMethods;
		if (this == &other) return *this;
		while (Head) erasing_front();
		Element* Temp = other.Head;

		while (Temp != nullptr)
		{
			this->push_back(Temp->Data);
			Temp = Temp->pNext;
		}

		

#ifdef DEBUG
		cout << "CopyAssignment_LConstrictor:\t\t" << this << endl;
#endif // DEBUG
		return *this;
	}

};

void main()
{
	setlocale(LC_ALL, "Russian");

#ifdef BASE_CHECK

#endif // BASE_CHECK

	//int n;
	//cout << "Введите размер списка: "; cin >> n;

	//ForwardList list;
	//for (int  i = 0; i < n; i++)
	//{
	//	//list.push_front(rand() % 100);
	//	list.push_back(rand() % 100);
	//}
	//list.print();
	//for (Iterator it = list.getHead(); it != nullptr; it++)
	//{
	//	*it = rand() % 100;
	//}
	//list.print();

	//list = list;

	//list.print();
#ifdef RANGE_BASED_ARRAY
	int arr[] = { 3, 5, 8, 13, 21 };
	cout << size(arr);
	for (int i = 0; i < size(arr); i++)
	{
		cout << arr[i] << "\t";
	}
	cout << endl;

	for (int i : arr)	//	Range-based for (цыкл фор для диапазона)
	{
		cout << i << "\t";
	}
	cout << endl;

#endif // RANGE_BASED_ARRAY

	ForwardList list = { 3, 5, 8, 13, 21 };
	list.print();

	for (int i : list)
	{
		cout << i << "\t";
	}
	cout << endl;

/*
	list.erase(6);
	list.print();

	cout << "List2:" << endl;
	ForwardList list2 (list);
	list2.print();
	cout << "List3::" << endl;
	ForwardList list3;
	list3 = list2;
	list3.print();

*/
	/*list.erasing_front();
	list.print();

	list.pop_back();
	list.print();*/

	//int value;
	//int index;

	//cout << "Value: "; cin >> value;
	//cout << "Index: "; cin >> index;

	//list.insert(value ,index);
	//list.print();
	

	//cout << "List2:" << endl;
	//ForwardList list2;
	//for (int i = 0; i < n; i++)
	//{
	//	//list.push_front(rand() % 100);
	//	list2.push_back(rand() % 100);
	//}
	//list2.print();


	//list.push_back(123);

	//list.print();
}
/*
В класс ForwardList добавить :
1. метод erase(), который удаляет элемент по индексу;
2. Написать деструктор, чтобы он очищал список перед удалением;
3. Добавить CopyMethods;
*/