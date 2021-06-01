#include "ForwardList.h"

template <typename T> Iterator<T> ForwardList<T>::getHead()
{
	return Head;
}

template <typename T> Iterator<T> ForwardList<T>::begin()
{
	return Head;
}

template <typename T> Iterator<T> ForwardList<T>::end()
{
	return nullptr;
}

template <typename T> ForwardList<T>::ForwardList(initializer_list<T> il) :ForwardList() //	 Делегирование кнструктора по умолчанию
{
	//	il - это контейнер, такой же, как наш ForwardList
	//	У любого контейнера есть методы begin() и end(),
	//	которые возвращают адрес на начало и конец контейнера

	cout << typeid(il.begin()).name() << endl;
	for (T const* it = il.begin(); it != il.end(); it++)
	{
		//	it - это итератор, которрый проходит по il
		push_back(*it);
	}
}

template <typename T> ForwardList<T>::ForwardList() 	//	Создаёт пустой список.
{
	Head = nullptr;
	size = 0;
#ifdef DEBUG
	cout << "LConstrictor:\t\t" << this << endl;
#endif // DEBUG

}

template <typename T> ForwardList<T>::ForwardList<T>(const ForwardList<T>& other)
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

template <typename T> ForwardList<T>::~ForwardList()
{
	//	Написать деструктор, чтобы он очищал список перед удалением;
	while (Head->pNext != nullptr)
	{
		Element<T>* Temp = Head;
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
template <typename T> void ForwardList<T>::push_front(T Data)
{
	//	Добавляет новый элемент в начало списка.
	Head = new Element<T>(Data, Head);
	/*Element* New = new Element(Data);
	New->pNext = Head;
	Head = New;*/
	size++;
}

template <typename T> void ForwardList<T>::push_back(T Data)
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

	Element<T>* Temp = Head; // Итератор

	while (Temp->pNext != nullptr)
	{
		Temp = Temp->pNext;
	}
	Temp->pNext = new Element<T>(Data);
	size++;
}

//	Erassing elements:
template <typename T> void ForwardList<T>::erasing_front()
{
	Element* Temp = Head;

	Head = Head->pNext;

	delete Temp;
	size--;
}

template <typename T> void ForwardList<T>::erase(T index)
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
			if (i + 2 < index - 1)
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
	Temp->pNext = Temp->pNext->pNext;
	//	Освобождаем память
	delete erTemp;
	//	Уменьшаем размер массива.
	size--;
}

template <typename T> void ForwardList<T>::pop_back()
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

template <typename T> void ForwardList<T>::insert(T Data, int index)
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
template <typename T> void ForwardList<T>::print()
{
	//Element* Temp = Head;
	//while (Temp!=nullptr)
	//{
	//	cout << Temp << "\t" << Temp->Data << "\t" << Temp->pNext << endl;
	//	Temp = Temp->pNext;
	//}

	//for (Element* Temp =Head; Temp; Temp=Temp->pNext )
	for (Iterator<T> Temp = Head; Temp != nullptr; Temp++)
	{
		//cout<< Temp.get_current_address() << "\t" << Temp->Data << "\t" << Temp->pNext << endl;
		cout << *Temp << "\t";
	}
	cout << endl;
	cout << "Count := " << Element<T>::count << endl;
	cout << "Size := " << size << endl;
}

// Operators
template <typename T> ForwardList <T>& ForwardList<T>::operator=(const ForwardList<T>& other)
{
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