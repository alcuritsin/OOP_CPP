﻿//Fraction - дробь
#include <iostream>

//#define DEBUG
//#define CONSTRUCTORS_CHECK	//	Проверка конструкторов/деструкторов
//#define PROPER_IMPROPER_REDUCE	//	Методы: `to_proper(); to_improper(); reduce();`
//#define ARITHMETIC_CHECK	//	Арифметические операции
//#define COMPOUND_ASSIGNMENT	//	Составные присваивания
//#define INCREMENT_DECREMENT	//	Инкремент / Декримент
//#define COMPARISON	// Сравнение
#define TYPE_CONVERSIONS

class Fraction;	//	Class declaration  -- объявление класса

std::ostream& operator<<(std::ostream& os, const Fraction& obj);

Fraction operator+ (Fraction left, Fraction	right);
Fraction operator- (Fraction left, Fraction	right);
Fraction operator* (Fraction left, Fraction	right);
Fraction operator/ (Fraction left, Fraction	right);

bool operator== (Fraction left, Fraction right);
bool operator!= (const Fraction& left, const Fraction& right);
bool operator> (Fraction left, Fraction right);
bool operator< (Fraction left, Fraction right);

bool operator>= (const Fraction& left, const Fraction& right);
bool operator<= (const Fraction& left, const Fraction& right);
	//	Class (классы)
class Fraction
{	//Класс Fraction описывает простые дроби. Например:	2(3/4)
	bool minus;	//	Знак дроби.
	int integer;	// Целая часть
	int numerator;	//	Числитель
	int denominator;	//	Знаменатель
public:
	//	GET   /   SET:
	bool get_minus() const
	{
		return minus;
	}
	int get_integer()const
	{
		return integer;
	}
	int get_numerator()const
	{
		return numerator;
	}
	int get_denominator()const
	{
		return denominator;
	}
	void set_minus(bool minus)
	{
		this->minus = minus;
	}
	void set_integer(int integer)
	{
		if (integer < 0) this->minus = 1;
		this->integer = abs(integer);
	}
	void set_numerator(int numerator)
	{	
		if (numerator < 0) this->minus = 1;
		this->numerator = numerator;
	}
	void set_denominator(int denominator)
	{
		if (denominator < 0)this->minus = 1;
		if (denominator == 0)
		{
			denominator = 1;
		}
		this->denominator = abs(denominator);
	}

//////
	Fraction& set_minus_to_number()
	{
		if (minus)
		{
			integer = -integer;
			numerator = -numerator;
			minus = false;
		}
		return *this;
	}
	Fraction& get_minus_from_number()
	{
		if (integer < 0)
		{
			integer = -integer;
			minus = true;
		}
		if (numerator < 0)
		{
			numerator = -numerator;
			minus = true;
		}
		return *this;
	}
//////

	//	Constructors:
	Fraction()
	{
		//	с учетом знака дроби --done

		this->minus = false;
		this->integer = 0;
		this->numerator = 0;
		this->denominator = 1;
#ifdef DEBUG
		std::cout << "Constructor_0:\t\t" << this << std::endl;
#endif // DEBUG

	}
	Fraction(int integer)
	{
		//	с учетом знака дроби --done
		this->minus = false;
		(integer >= 0) ? this->minus = false : this->minus = true;
		this->integer = abs(integer);
		this->numerator = 0;
		this->denominator = 1;
#ifdef DEBUG
		std::cout << "Constructor_1:\t\t" << this << std::endl;
#endif // DEBUG
	}
	Fraction(int numerator, int denominator)
	{
		//	с учетом знака дроби --done

		this->integer = 0;
		(numerator >= 0)? this->minus = 0:this->minus = 1;
		this->numerator = abs(numerator);
		this->set_denominator(denominator);
#ifdef DEBUG
		std::cout << "Constructor_2:\t\t" << this << std::endl;
#endif // DEBUG
	}
	Fraction(int integer, int numerator, int denominator)
	{
		//	с учетом знака дроби --done
		this->minus = false;
		(integer >= 0) ? this->minus = false : this->minus = true;
		this->integer = abs(integer);
		(numerator >= 0 && !minus)? this->minus = false:this->minus = true;
		this->numerator = abs(numerator);
		this->set_denominator(denominator);
#ifdef DEBUG
		std::cout << "Constructor_3:\t\t" << this << std::endl;
#endif // DEBUG
	}
	~Fraction()
	{
#ifdef DEBUG
		std::cout << "Distructor:\t\t" << this << std::endl;
#endif // DEBUG
	}

	// Operartors:
	Fraction& operator = (const Fraction& other)
	{
		this->minus = other.minus;
		this->integer = other.integer;
		this->numerator = other.numerator;
		this->denominator = other.denominator;

		return *this;
	}
	Fraction& operator+=(const Fraction& other)
	{	
		return *this = *this + other;
	}
	Fraction& operator-=(const Fraction& other)
	{	
		return *this = *this - other;
	}
	Fraction& operator*=(Fraction other)
	{	
		return *this = *this * other;
	}
	Fraction& operator/=(Fraction other)
	{	
		return *this = *this / other;
	}

	// Increment	/	Decrement
	Fraction operator ++ ()	//	Префиксный инкремент / Prefix Increment
	{
		this->integer++;
		return *this;
	}
	Fraction operator ++ (int)	//	Постфиксный инкремент / Postfix Increment
	{
		Fraction old = *this;
		++*this;
		return old;
	}
	Fraction operator -- ()	//	Префиксный декремент / Prefix Decrement
	{
		this->integer--;
		return *this;
	}
	Fraction operator -- (int)	//	Постфиксный декремент / Postfix Decrement
	{
		Fraction old = *this;
		--*this;
		return old;
	}
	//	Type cast operator
	operator int()const
	{
		return minus ? -integer : integer;
	}


	//	Metods:
	Fraction& to_proper()
	{
		//Переводит неправильную дробь в правильную 11 / 4 = > 2(3 / 4)
		//	с учетом знака дроби --done

		integer += numerator / denominator;
		numerator %= denominator;
		return *this;
	}
	Fraction& to_improper()
	{
		//Переводит дробь в неправильную	2(3 / 4) = > 11 / 4
		//	с учетом знака дроби --done

		numerator += integer * denominator;
		integer = 0;
		return *this;
	}
	Fraction& reduce()
	{
		/*
		//	Сокращает дробь		5/10 => 1/2 --done
		//	с учетом знака дроби --done
		int counter = (this->numerator<this->denominator)?this->numerator:this->denominator;	//	Определили наименьшее максимальное число, для проведения проверки.

		int gcd = 1;	//	Greatest Common Divisor (Наибольший Общий Делитель)

		for (int i = gcd; i <= counter; i++)
		{
			if (numerator % i == 0 && denominator % i == 0) gcd = i;	// Числитель и знаменатель делятся на `i` без остатка, предпологаем, что это наибольший общий делитель.
		}

		this->numerator /= gcd;
		this->denominator /= gcd;
		*/
		//	CW
		if (numerator == 0) return *this;
		int more, less, rest;
		//Выясняем кто больше числитель или знаменатель
		if (numerator > denominator) less = numerator, more = denominator;
		else less = denominator, more = numerator;
		//Находим наибольший общий делитель
		do
		{
			rest = more % less;
			more = less;
			less = rest;
		} while (rest);
		int GCD = more; //Greatest Common Divisor(Наибольший Общий Делитель)
		numerator /= GCD;
		denominator /= GCD;

		return *this;
	}
};

	//	Functions prototype (прототипы функций)

	//	Точка входа :)
void main()
{
	setlocale(LC_ALL, "Russian");

	//	Проверка конструкторов/деструкторов
#ifdef CONSTRUCTORS_CHECK
	Fraction A;
	std::cout << A << std::endl;

	Fraction B = -5;
	std::cout << B << std::endl;

	Fraction C(1, -2);
	std::cout << C << std::endl;

	Fraction D(2, 3, -4);
	std::cout << D << std::endl;
#endif // CONSTRUCTORS_CHECK

	//	Методы: `to_proper(); to_improper(); reduce();`
#ifdef PROPER_IMPROPER_REDUCE	//	Методы: `to_proper(); to_improper(); reduce();`
	Fraction A(-2,18, 36);

	std::cout << A << " = ";
	std::cout << (A.to_proper()) << std::endl;
	std::cout << A << " = ";
	std::cout << (A.to_improper()) << std::endl;
	std::cout << A << " = ";
	std::cout << (A.reduce()) << std::endl;
#endif // PROPER_IMPROPER_REDUCE

	//	Арифметические операции
#ifdef ARITHMETIC_CHECK
	Fraction A(2, 3, 4);
	Fraction B(5, 6, 7);

	std::cout << "A = " << A << "\tB = " << B << std::endl << std::endl;

	std::cout << "A + B\t-->>\t" << A << " + " << B << " = " << (A + B) << std::endl;
	std::cout << "B - B\t-->>\t" << B << " - " << B << " = " << (B - B) << std::endl;
	std::cout << "B - A\t-->>\t" << B << " - " << A << " = " << (B - A) << std::endl;
	std::cout << "A - B\t-->>\t" << A << " - " << B << " = " << (A - B) << std::endl;
	std::cout << "A * B\t-->>\t" << A << " * " << B << " = " << (A * B) << std::endl;
	std::cout << "A / B\t-->>\t" << A << " / " << B << " = " << (A / B) << std::endl;
#endif // ARITHMETIC_CHECK

	//	Составные присваивания
#ifdef COMPOUND_ASSIGNMENT
	Fraction A(2, 3, 4);
	Fraction B(5, 6, 7);

	std::cout << "A = " << A << "\tB = " << B << std::endl << std::endl;

	std::cout << A << " -= " << B; std::cout << "\t>>>\t" << (A -= B) << "\tminus = " << A.get_minus() << std::endl;
	std::cout << A << " *= " << B; std::cout << "\t>>>\t" << (A *= B) << "\tminus = " << A.get_minus() << std::endl;
	std::cout << (A.reduce()) << std::endl;
	std::cout << A << " /= " << B; std::cout << "\t>>>\t" << (A /= B) << "\tminus = " << A.get_minus() << std::endl;
	std::cout << (A.reduce()) << std::endl;
#endif // COMPOUND_ASSIGNMENT

	//	Инкремент / Декримент
#ifdef INCREMENT_DECREMENT
	Fraction A(2, 3, 4);
	Fraction B(5, 6, 7);

	std::cout << "A = " << A << "\tB = " << B << std::endl << std::endl;

	std::cout << "A++\t-->>\t" << A++ << "\tminus = " << A.get_minus() << std::endl;
	std::cout << (A.reduce()) << std::endl;
	std::cout << "++A\t-->>\t" << ++A << "\tminus = " << A.get_minus() << std::endl;
	std::cout << (A.reduce()) << std::endl;
	std::cout << "A--\t-->>\t" << A-- << "\tminus = " << A.get_minus() << std::endl;
	std::cout << (A.reduce()) << std::endl;
	std::cout << "--A\t-->>\t" << --A << "\tminus = " << A.get_minus() << std::endl;
	std::cout << (A.reduce()) << std::endl;
#endif // INCREMENT_DECREMENT

	// Сравнение
#ifdef COMPARISON
	Fraction A(2, 3, 4);
	Fraction B(5, 6, 7);
	//Fraction A(5, 6, 7);
	//Fraction B(2, 3, 4);
	
	std::cout << "A = " << A << "\tB = " << B << std::endl << std::endl;

	std::cout << "A == B\t-->>\t" << ((A == B) ? "true" : "false") << std::endl;
	std::cout << "A != B\t-->>\t" << ((A != B) ? "true" : "false") << std::endl;
	std::cout << "A >  B\t-->>\t" << ((A >  B) ? "true" : "false") << std::endl;
	std::cout << "A <  B\t-->>\t" << ((A <  B) ? "true" : "false") << std::endl;
	std::cout << "A >= B\t-->>\t" << ((A >= B) ? "true" : "false") << std::endl;
	std::cout << "A <= B\t-->>\t" << ((A <= B) ? "true" : "false") << std::endl;
#endif // COMPARISON


#ifdef TYPE_CONVERSIONS
	int a;
	Fraction A = 5;	//	From other to this. Это преобразование выполняет SinglArgumentConstructor (конструктор с одним параметром)
	a = A;	//	From this to other. Posible loss of data.
	std::cout << a << std::endl;
#endif // TYPE_CONVERSIONS


}

	//	Functions definitio (определение функций)
std::ostream& operator<<(std::ostream& os, const Fraction& obj)
{
	//	с учетом знака дроби --done

	if (obj.get_minus()) os << "(-"; //Выводит знак дроби
	//Чтобы знак не дублировался, выводим модули чисел.	abs(val) -> |val|
	if (obj.get_integer()) os << abs(obj.get_integer());
	if (obj.get_integer() && obj.get_numerator()) os << "(";
	if (obj.get_numerator()) os << abs(obj.get_numerator()) << "/" << abs(obj.get_denominator());
	if (obj.get_integer() && obj.get_denominator() && obj.get_numerator())os << ")";
	if (obj.get_integer() == 0 && obj.get_numerator() == 0) os << 0;
	if (obj.get_minus()) os << ")"; //Выводит знак дроби

	return os;
}

Fraction operator+ (Fraction left, Fraction	right)
{
	//	с учетом знака дроби --done

	left.to_proper();
	right.to_proper();

	return Fraction
	(
		(left.get_minus() ? -1 : 1) * left.get_integer() + (right.get_minus() ? -1 : 1) * right.get_integer(),
		(left.get_minus() ? -1 : 1) * left.get_numerator() * right.get_denominator() + (right.get_minus() ? -1 : 1) * right.get_numerator() * left.get_denominator(),	//	с учетом знака дроби
		left.get_denominator() * right.get_denominator()
	).to_proper().reduce();
}
Fraction operator- (Fraction left, Fraction	right)
{
	//	с учетом знака дроби --done

	left.to_proper();
	right.to_proper();

	return Fraction
	(
		(left.get_minus() ? -1 : 1) * left.get_integer() - (right.get_minus() ? -1 : 1) * right.get_integer(),
		(left.get_minus() ? -1 : 1) * left.get_numerator() * right.get_denominator() - (right.get_minus() ? -1 : 1) * right.get_numerator() * left.get_denominator(),
		left.get_denominator() * right.get_denominator()
	).to_proper().reduce();
}
Fraction operator* (Fraction left, Fraction	right)
{
	//	с учетом знака дроби --done

	left.to_improper();
	right.to_improper();

	return Fraction
	(
		(left.get_minus() ? -1 : 1)* left.get_numerator() * (right.get_minus() ? -1 : 1)* right.get_numerator(),
		left.get_denominator() * right.get_denominator()
	).to_proper().reduce();
}
Fraction operator/ (Fraction left, Fraction	right)
{
	//	с учетом знака дроби --done

	left.to_improper();
	right.to_improper();

	return Fraction
	(
		(left.get_minus() ? -1 : 1) * left.get_numerator() * (right.get_minus() ? -1 : 1) * right.get_denominator(),
		left.get_denominator() * right.get_numerator()
	).to_proper().reduce();
}

bool operator== (Fraction left, Fraction right)
{
	left.to_improper().reduce();
	right.to_improper().reduce();
	if
		(
			(left.get_minus() ? -1 : 1) * left.get_integer() == (right.get_minus() ? -1 : 1) * right.get_integer() &&
			(left.get_minus() ? -1 : 1) * left.get_numerator() * right.get_denominator() == (right.get_minus() ? -1 : 1) * right.get_numerator() * left.get_denominator()
			)
	{
		return true;
	}
	else
	{
		return false;
	}
}
bool operator!= (const Fraction& left, const Fraction& right)
{
	if (left == right)
	{
		return false;
	}
	else
	{
		return true;
	}
}
bool operator> (Fraction left, Fraction right)
{
	left.to_improper().reduce();
	right.to_improper().reduce();
	if ((left.get_minus() ? -1 : 1) * left.get_numerator() * right.get_denominator() > (right.get_minus() ? -1 : 1) * right.get_numerator() * left.get_denominator())
	{
		return true;
	}
	else
	{
		return false;
	}
}
bool operator< (Fraction left, Fraction right)
{
	left.to_improper().reduce();
	right.to_improper().reduce();
	if ((left.get_minus() ? -1 : 1) * left.get_numerator() * right.get_denominator() < (right.get_minus() ? -1 : 1) * right.get_numerator() * left.get_denominator())
	{
		return true;
	}
	else
	{
		return false;
	}
}

bool operator>= (const Fraction& left, const Fraction& right)
{
	if (left == right || left > right)
	{
		return true;
	}
	else
	{
		return false;
	}
}
bool operator<= (const Fraction& left, const Fraction& right)
{
	if (left == right || left < right)
	{
		return true;
	}
	else
	{
		return false;
	}
}

//Signature - подпись
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