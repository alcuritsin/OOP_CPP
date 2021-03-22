#include<iostream>

//#define INTRO
#define CONSTRUCTORS

//Создание структуры.
//struct Point
class Point
{
	//Структура Point описывает точки на плоскости.
	double x; //Координата по X
	double y; //Координата по Y

public:
	double get_x()
	{
		return x;
	}
	double get_y()
	{
		return y;
	}
	void set_x(double x)
	{
		this->x = x;
	}
	void set_y(double y)
	{
		this->y = y;
	}

	// Constructors
	Point()
	{
		x = y = 0;
		std::cout << "DefaultConstructor: \t" << this << std::endl;
	}
	Point(double x)
	{
		this->x = x;
		this->y = 0;
		std::cout << "Constructor: \t" << this << std::endl;
	}
	~Point()
	{
		std::cout << "Destructor: \t" << this << std::endl;
	}

	// Metods
	void print()
	{
		std::cout << "X = " << x << "\tY = " << y << std::endl;
	}
};
//	Создовая структуру или класс, мы создаём новый тип данных.
//	А обяъявляя объекты этого класса или структуры - мы создаём переменные нашего типа.

//Классы и структуры ещё называют пользовательскими типами данных.

//	Класс		- это тип данных.
//	Структура	- это тип данных.
//	Объект		- это обычная переменная.

void main()
{
	setlocale(LC_ALL, "Russian");

#ifdef INTRO
	int a;		//Объявление переменной 'a' типа 'int'
	Point A;	//Оюъявление (Создание) объекта 'A'  структуры 'Point'.
				//Объявление переменной 'A' типа  'Point'

	A.set_x(2);
	A.set_y(3);

	std::cout << A.get_x() << "\t" << A.get_y() << std::endl;

	Point* pA = &A; //Создаём указатель на объект.

	std::cout << pA->get_x() << "\t" << pA->get_y() << std::endl;
#endif // INTRO

#ifdef CONSTRUCTORS
	Point A; //Default constructor
	std::cout << A.get_x() << "\t" << A.get_y() << std::endl;

	Point B = 5;
	B.print();

#endif // CONSTRUCTORS
}