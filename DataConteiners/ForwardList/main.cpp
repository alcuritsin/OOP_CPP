#include <iostream>

using namespace std;

using std::cout;
using std::endl;

#define DEBUG

class Element
{
	int Data;	//	Значение элемента
	Element* pNext;	//	Указатель на следующий элемент
public:
	Element(int Data, Element* pNext = nullptr) : Data(Data), pNext(pNext)
	{
#ifdef DEBUG
		cout << "EConstrictor:\t\t" << this << endl;
#endif // DEBUG
	}
	~Element()
	{
#ifdef DEBUG
		cout << "EDestructor:\t\t" << this << endl;
#endif // DEBUG
	}
	friend class ForwardList;
};

class  ForwardList
{
	Element* Head;
public:
	ForwardList() :Head(nullptr)
	{
#ifdef DEBUG
		cout << "LConstrictor:\t\t" << this << endl;
#endif // DEBUG

	}
	~ ForwardList()
	{
#ifdef DEBUG
		cout << "LDestructor:\t\t" << this << endl;
#endif // DEBUG
	}
	//	Adding Elements
	void push_front(int Data)
	{
		//	Добавляет новый элемент в начало списка.
		Element* New = new Element(Data);
		New->pNext = Head;
		Head = New;
	}

	//	Methods
	void print()
	{
		Element* Temp = Head;
		while (Temp!=nullptr)
		{
			cout << Temp << "\t" << Temp->Data << "\t" << Temp->pNext << endl;
			Temp = Temp->pNext;
		}
	}
};
void main()
{
	setlocale(LC_ALL, "Russian");
	int n;
	cout << "Введите размер списка: "; cin >> n;

	ForwardList list;
	for (int  i = 0; i < n; i++)
	{
		list.push_front(rand() % 100);
	}

	list.print();
}