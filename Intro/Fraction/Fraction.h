#pragma once
//Fraction - дробь
#include <iostream>
	//	Class prototype (прототип класса)
class Fraction;	//	Class declaration  -- объявление класса

	//	Functions prototype (прототипы функций)
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
		(numerator >= 0) ? this->minus = 0 : this->minus = 1;
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
		(numerator >= 0 && !minus) ? this->minus = false : this->minus = true;
		this->numerator = abs(numerator);
		this->set_denominator(denominator);
#ifdef DEBUG
		std::cout << "Constructor_3:\t\t" << this << std::endl;
#endif // DEBUG
	}
	Fraction(const double decimal, const int acc = 6)
	{
		//	Конструктор для инициализации дроби десятичным числом
		//	Fraction Accuracy // Точность пусть будет 1 / 100 000, но можно указывать при инициализации...
		//	`acc` - количество знаков после запятой, которые берутся в учет.

		this->minus = (decimal < 0) ? true : false;	//	записываем минус в параметр-свойство
		this->integer = abs((int)decimal);	//	выделяем целое цисло

		if (acc <= 0)	//	Не учитывать дробную часть... ) Ну, захотелось так пользователю!
		{
			this->numerator = 0;
			this->denominator = 1;
			this->integer = abs(round(decimal));	//	Округляем число до целого по математическим правилам.
		}
		else
		{
			//	Вычисляем знаменатель
			if (acc > 14) //	Искуственное ограничение в 14 знаков после запятой.
			{
				this->denominator = pow(10, 14);
			}
			else
			{
				this->denominator = pow(10, acc);
			}

			//	Вычисляем числитель
			this->numerator = round((double)(abs(decimal) - this->get_integer()) * this->get_denominator());
		}

		this->reduce();	//	Сокращаем если возможно

#ifdef DEBUG
		std::cout << "Constructor_4:\t\t" << this << std::endl;
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
		++* this;
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
		--* this;
		return old;
	}
	//	Type cast operator
	operator int()const
	{
		return minus ? -integer : integer;
	}
	operator double()const
	{
		return (minus ? -1 : 1) * integer + (double)numerator / denominator;
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