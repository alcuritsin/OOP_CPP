#include<iostream>
#include <cmath> // для функции sqrt, pow

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
	Point(double x, double y)
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
	double distance(double x, double y)
	{
		// В классе Point реализовать МЕТОД ??? distance(???), который возвращает расстояние до указанной точки; --DONE
		return sqrt(pow((x - this->x), 2) + pow((y - this->y), 2));
	}
};
//	Создовая структуру или класс, мы создаём новый тип данных.
//	А обяъявляя объекты этого класса или структуры - мы создаём переменные нашего типа.

//Классы и структуры ещё называют пользовательскими типами данных.

//	Класс		- это тип данных.
//	Структура	- это тип данных.
//	Объект		- это обычная переменная.

double distance(Point* A, Point* B); //Реализовать функцию ??? distance(???), которая возвращает расстояние между двумя точками 

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
	std::cout << "point A (" << A.get_x() << ", " << A.get_y() << ")" << std::endl;


	Point B (5,0);
	std::cout << "point B" << std::endl;
	B.print();

	std::cout << "# Расстояние до указанной точки #";
	double x = 0;  double y = 0;

	std::cout << "\nВведите координаты точки:\n";
	std::cout << "x = "; std::cin >> x;
	std::cout << "y = "; std::cin >> y;
		
	std::cout << "Distance to the point 'A'  = " << A.distance(x, y) << std::endl;
	std::cout << "Distance to the point 'B'  = " << B.distance(x, y) << std::endl;


	std::cout << "\n# Возвращает расстояние между двумя точками #\n";
	double Xc, Yc; //Координаты точки C
	double Xd, Yd; //Координаты точки D

	std::cout << "Input point C\n";
	std::cout << "Xc = "; std::cin >> Xc;
	std::cout << "Yc = "; std::cin >> Yc;
	std::cout << "Input point D\n";
	std::cout << "Xd = "; std::cin >> Xd;
	std::cout << "Yd = "; std::cin >> Yd;

	Point C(Xc, Yc);	//Constructor C
	Point D(Xd, Yd);	//Construktor D

	std::cout << "Distance CD = " << distance(&C, &D);

#endif // CONSTRUCTORS
}

double distance(Point* A, Point* B)
{
	//Реализовать функцию ??? distance(???), которая возвращает расстояние между двумя точками --DONE
/*
	A(Xa;Ya)	B(Xb:Yb)
	|AB| = sqrt ( (Xa - Xb)^2 + (Ya - Yb)^2 );
*/
	return sqrt(pow(A->get_x() - B->get_x(), 2) + pow((A->get_x() - B->get_y()), 2));
}

//Исполнитель
/*
-----------------------------------------------------
|                                                   |
|   "Компьютерная академия ШАГ"                     |
|   Курс: БД011                                     |
|   Предмет: Основы програмvирования на языке C++   |
|                                                   |
|   Исполнитель: Курицын Алексей                    |
|   Преподаватель: Ковтун Олег                      |
|                                                   |
|   Екатеринбург - 2021                             |
|                                                   |
-----------------------------------------------------*/