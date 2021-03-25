#include<iostream>
#include <cmath> // для функции sqrt, pow

//#define INTRO
//#define CONSTRUCTORS
//#define DISTANCE_HW
//#define ASSIGNMENT_CHECK

//HW - Operartors `+`, `-`, `*`, `/`
#define OPERATOR_OVERLOADS	//	Homework 2021/03/25
//#define ADDITIS_OVER		//	Перегрузка `+`
//#define SUBTRACTION_OVER	//	Перегрузка `-`
//#define MULTIPLICATIO_OVER	//	Перегрузка `*`
#define DIVISIO_OVER		//	Перегрузка `/`

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
		std::cout << "CopyConstructir:\t\t" << this << std::endl;
	}

	~Point()
	{
		std::cout << "Destructor: \t\t" << this << std::endl;
	}

	// Operartors
	Point& operator = (const Point& other)
	{
		this->x = other.x;
		this->y = other.y;
		std::cout << "CopyAssignment:\t\t" << this << std::endl;
		return *this;
	}

	Point operator + (const Point& other) const
	{
		Point C(this->x + other.x, this->y + other.y);	//Создаём объект `C` с результатом операции
		return C; //Возвращаем объект `C` на место вызова
	}

	Point operator - (const Point& other) const
	{
		Point C(this->x - other.x, this->y - other.y);	//Создаём объект `C` с результатом операции
		return C; //Возвращаем объект `C` на место вызова
	}

	Point operator * (const Point& other) const
	{
		Point C(this->x * other.x, this->y * other.y);	//Создаём объект `C` с результатом операции
		return C; //Возвращаем объект `C` на место вызова
	}
	Point operator / (const Point& other) const
	{
		Point C((other.x != 0 ? this->x / other.x : 0), (other.y != 0 ? this->y / other.y : 0));	//Создаём объект `C` с результатом операции
		return C; //Возвращаем объект `C` на место вызова
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
		return sqrt(pow(this->x - other.x, 2) + pow(this->y - other.y, 2));
		//sqrt - Square Root (Квадратный корень)
		//pov - Power (возведение в степень)
	}
};

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


#ifdef ASSIGNMENT_CHECK
	int a, b, c;
	a = b = c = 0;

	Point A, B, C;

	A = B = C = Point();

#endif // ASSIGNMENT_CHECK

#ifdef OPERATOR_OVERLOADS
//Homework 2021/03/25
	Point A(8, 20);
	Point B(4, 5);

#ifdef ADDITIS_OVER
	//+++++++++++++++++++++++++++++++++++++++++++//
	std::cout << std::endl;
	std::cout << "# Aditis 'overload' #" << std::endl;
	std::cout << "Point before deformation" << std::endl;
	std::cout << "Point A\n"; A.print();
	std::cout << "Point B\n"; B.print();
	std::cout << std::endl;

	Point C = A + B;
	std::cout << "Point 'C = A + B'\n";
	C.print();
	std::cout << "Point 'A + B'\n";
	(A + B).print();
	std::cout << "Point 'A.operator+(B)'\n";
	(A.operator+(B)).print();

	std::cout << std::endl;
	std::cout << "Point after deformation" << std::endl;
	std::cout << "Point A\n";
	A.print();
	std::cout << "Point B\n";
	B.print();
	std::cout << std::endl;
#endif // ADDITIS_OVER

#ifdef SUBTRACTION_OVER
	//-------------------------------------------//
	std::cout << std::endl;
	std::cout << "# Subtraction 'overload' #" << std::endl;
	std::cout << "Point before deformation" << std::endl;
	std::cout << "Point A\n"; A.print();
	std::cout << "Point B\n"; B.print();
	std::cout << std::endl;

	Point D = A - B;
	std::cout << "Point 'D = A - B'\n";
	D.print();
	std::cout << "Point 'A - B'\n";
	(A - B).print();
	std::cout << "Point 'A.operator-(B)'\n";
	(A.operator-(B)).print();

	std::cout << std::endl;
	std::cout << "Point after deformation" << std::endl;
	std::cout << "Point A\n";
	A.print();
	std::cout << "Point B\n";
	B.print();
	std::cout << std::endl;
#endif // SUBTRACTION_OVER

#ifdef MULTIPLICATIO_OVER
	//*******************************************//
	std::cout << std::endl;
	std::cout << "# Multiplicatio 'overload' #" << std::endl;
	std::cout << "Point before deformation" << std::endl;
	std::cout << "Point A\n"; A.print();
	std::cout << "Point B\n"; B.print();
	std::cout << std::endl;

	Point E = A * B;
	std::cout << "Point 'E = A * B'\n";
	E.print();
	std::cout << "Point 'A * B'\n";
	(A * B).print();
	std::cout << "Point 'A.operator-(B)'\n";
	(A.operator*(B)).print();

	std::cout << std::endl;
	std::cout << "Point after deformation" << std::endl;
	std::cout << "Point A\n";
	A.print();
	std::cout << "Point B\n";
	B.print();
	std::cout << std::endl;
#endif // MULTIPLICATIO_OVER

#ifdef DIVISIO_OVER
	///////////////////////////////////////////////
	std::cout << std::endl;
	std::cout << "# Divisio 'overload' #" << std::endl;
	std::cout << "Point before deformation" << std::endl;
	std::cout << "Point A\n"; A.print();
	std::cout << "Point B\n"; B.print();
	std::cout << std::endl;

	Point F = A / B;
	std::cout << "Point 'F = A / B'\n";
	F.print();
	std::cout << "Point 'A / B'\n";
	(A / B).print();
	std::cout << "Point 'A.operator/(B)'\n";
	(A.operator/(B)).print();

	std::cout << std::endl;
	std::cout << "Point after deformation" << std::endl;
	std::cout << "Point A\n";
	A.print();
	std::cout << "Point B\n";
	B.print();
	std::cout << std::endl;
#endif // DIVISIO_OVER

#endif // OPERATOR_OVERLOADS
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
|   Курс: PD_011                                    |
|   Предмет: Основы програмvирования на языке C++   |
|                                                   |
|   Исполнитель: Курицын Алексей                    |
|   Преподаватель: Ковтун Олег                      |
|                                                   |
|   Екатеринбург - 2021                             |
|                                                   |
-----------------------------------------------------*/