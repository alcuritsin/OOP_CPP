#include <iostream>

using namespace std;
using std::cout;
using std::endl;

#define DEBUG
#define tab "\t"

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
	List()
	{
		Head = Tail = nullptr;
		size = 0;
		
#ifdef DEBUG
		cout << "LConstructor:\t" << this << endl;
#endif // DEBUG

	}

	~List()
	{
		//while (Head) pop_front();
		while (Head) pop_back();
#ifdef DEBUG
			cout << "LDestructor:\t" << this << endl;
#endif // DEBUG
	}

	//		Adding element
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
	void insert(int Index, int Data)
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
			for (int i = 0; i < Index; i++)Temp = Temp->pNext;
		}
		else
		{
			Temp = Tail;
			for (int i = 0; i < size - Index - 1; i++)Temp = Temp->pNext;
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

};


void main()
{
	setlocale(LC_ALL, "Russian");

	int n;

	cout << "Введите размер списка: "; cin >> n;
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

}
