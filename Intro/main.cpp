#include<iostream>
#include <cmath> // для функции sqrt, pow

//#define INTRO
//#define CONSTRUCTORS
#define DISTANCE_HW

//Создание структуры.
//struct Point
class Point
{
	//Структура Point описывает точки на плоскости.
	double x; //Координата по X
	double y; //Координата по Y

public:
	double get_x() const
	{
		return x;
	}
	double get_y() const
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
	/*Point()
	{
		// Конструктор создаёт точку в начале координать.
		x = y = int(); //Якобы вызываем конструктор для `int` и он возвращает значение по умолчанию для `int`
		std::cout << "DefaultConstructor: \t" << this << std::endl;
	}

	Point(double x)
	{
		// Конструктор с одним параметром создаёт точку на прямой.
		this->x = x;
		this->y = 0;
		std::cout << "Singl argument constructor: \t" << this << std::endl;
	}

	Point(double x, double y)
	{
		// Конструктор с параметроми создаёт точку на плоскости.
		this->x = x;
		this->y = y;
		std::cout << "Constructor: \t\t" << this << std::endl;
	}*/
	Point(double x = 0, double y = 0)
	{
		//Этот конструктор с параметрами может быть вызван 
		// - без параметров
		// - с одним параметром
		// - с двумя параметрами

		this->x = x;
		this->y = y;
		std::cout << "Constructor:\t\t" << this << std::endl;
	}

	Point(const Point& other)
	{
		//other - это другой объект копию, которого мы создам
		this->x = other.x;
		this->y = other.y;
		std::cout << "CopyAssignment:\t\t" << this << std::endl;
	}

	~Point()
	{
		std::cout << "Destructor: \t\t" << this << std::endl;
	}

	// Operartors
	void operator = (const Point& other)
	{
		this->x = other.x;
		this->y = other.y;
		std::cout << "CopyAssignment:\t\t" << this << std::endl;
	}

	// Metods
	void print()
	{
		std::cout << "X = " << x << "\tY = " << y << std::endl;
	}
	double distance (const Point& other) const
	{
		// В классе Point реализовать МЕТОД ??? distance(???), который возвращает расстояние до указанной точки; --DONE
		//issues #1
		/*before optimization
		double x_distance = this->x - other.x;
		double y_distance = this->y - other.y;
		double ditance = sqrt(pow(x_distance, 2) + pow(y_distance, 2));
		return ditance;
		*/

		//Оптимизировать метод и функцию distance до одной строки кода
		//after optimization
		return sqrt(pow(this->x - other.x, 2) + pow(this->y - other.y, 2));
		//sqrt - Square Root (Квадратный корень)
		//pov - Power (возведение в степень)
		
	}
};
//	Создовая структуру или класс, мы создаём новый тип данных.
//	А обяъявляя объекты этого класса или структуры - мы создаём переменные нашего типа.

//Классы и структуры ещё называют пользовательскими типами данных.

//	Класс		- это тип данных.
//	Структура	- это тип данных.
//	Объект		- это обычная переменная.

double distance(const Point& A, const Point& B); //Реализовать функцию ??? distance(???), которая возвращает расстояние между двумя точками 

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
	Point A;		//Default constructor
	std::cout << "point A (" << A.get_x() << ", " << A.get_y() << ")" << std::endl;

	Point B = 5;	//Singl argument constructor
	B.print();
	Point C(5);		//Singl argument constructor
	C.print();
	Point D{ 5 };	//Singl argument constructor
	D.print();

	Point E (5,3);	// Параметризированный конструктор
	std::cout << "point B" << std::endl;
	E.print();

	Point F = E; //CopyConstructor. Здесть мы создаём объект X, и инициализируем его другим объектом.
	F.print();

	Point G;
	G = F;	//CopyAssignment
	G.print();

#endif // CONSTRUCTORS

#ifdef DISTANCE_HW

	std::cout << "# Расстояние до указанной точки #\n";

	Point A(2, 3);
	Point B(4, 5);

	A.print();
	B.print();

	std::cout << "Distance to the point 'AB'  = " << A.distance(B) << std::endl;

	std::cout << "\n# Возвращает расстояние между двумя точками #\n";
	std::cout << "Distance to the point 'AB'  = " << distance(A,B) << std::endl;

	/*
	double Xc = 2, Yc = 3; //Координаты точки C
	double Xd = 4, Yd = 5; //Координаты точки D

	std::cout << "Input point C\n";
	std::cout << "Xc = "; std::cin >> Xc;
	std::cout << "Yc = "; std::cin >> Yc;
	std::cout << "Input point D\n";
	std::cout << "Xd = "; std::cin >> Xd;
	std::cout << "Yd = "; std::cin >> Yd;

	Point C(Xc, Yc);	//Constructor C
	Point D(Xd, Yd);	//Construktor D

	std::cout << "Distance CD = " << distance(C, D) << std::endl;
	*/


#endif // DISTANCE_HW

}

double distance(const Point& A, const Point& B)
{
	//Реализовать функцию ??? distance(???), которая возвращает расстояние между двумя точками --DONE
/*
	A(Xa;Ya)	B(Xb:Yb)
	|AB| = sqrt ( (Xa - Xb)^2 + (Ya - Yb)^2 );
*/
	//optimization done
	return sqrt(pow(A.get_x() - B.get_x(), 2) + pow((A.get_y() - B.get_y()), 2));
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