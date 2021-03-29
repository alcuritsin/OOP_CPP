//Fraction - дробь
#include <iostream>

//#define CONSTRUCTORS_CHECK
//#define PROPER_IMPROPER


class Fraction
{	//Класс Fraction описывает простые дроби. Например:	2(3/4)
	bool minus;	//	Знак дроби.
	int integer;	// Целая часть
	int numerator;	//	Числитель
	int denominator;	//	Знаменатель
public:
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
	void set_integer(int integer)
	{
		this->integer = integer;
	}
	void set_numerator(int numerator)
	{
		this->numerator = numerator;
	}
	void set_denominator(int denominator)
	{
		if (denominator == 0)
		{
			denominator = 1;
		}
		this->denominator = denominator;
	}

	//	Constructors:
	Fraction()
	{
		this->minus = 0;
		this->integer = 0;
		this->numerator = 0;
		this->denominator = 1;
		std::cout << "Constructor_0:\t\t" << this << std::endl;
	}
	Fraction(int integer)
	{
		this->minus = 0;
		this->integer = integer;
		this->numerator = 0;
		this->denominator = 1;
		std::cout << "Constructor_1:\t\t" << this << std::endl;
	}
	Fraction(int numerator, int denominator)
	{
		this->minus = 0;
		this->integer = 0;
		this->numerator = numerator;
		this->set_denominator(denominator);
		std::cout << "Constructor_2:\t\t" << this << std::endl;
	}
	Fraction(int integer, int numerator, int denominator)
	{
		this->minus = 0;
		this->integer = integer;
		this->numerator = numerator;
		this->set_denominator(denominator);
		std::cout << "Constructor_3:\t\t" << this << std::endl;
	}
	~Fraction()
	{
		std::cout << "Distructor:\t\t" << this << std::endl;
	}

	//	Metods:
	Fraction& to_proper()
	{
		integer += numerator / denominator;
		numerator %= denominator;
		return *this;
	}
	Fraction& to_improper()
	{
		numerator += integer * denominator;
		integer = 0;
		return *this;
	}

};

std::ostream& operator<<(std::ostream& os, const Fraction& obj);

Fraction operator+(Fraction left, Fraction	right)
{
	left.to_proper();
	right.to_proper();
	Fraction result;
	result.set_integer(left.get_integer() + right.get_integer());
	result.set_numerator(left.get_numerator() * right.get_denominator() + right.get_numerator() * left.get_denominator());
	result.set_denominator(left.get_denominator() * right.get_denominator());

	result.to_proper();
	return result;
}

Fraction operator-(Fraction left, Fraction	right)
{
	left.to_proper();
	right.to_proper();

	return Fraction
	(
		left.get_integer() - right.get_integer(),
		left.get_numerator() * right.get_denominator() - right.get_numerator() * left.get_denominator(),
		left.get_denominator() * right.get_denominator()
	).to_proper();
}

Fraction operator*(Fraction left, Fraction	right);

Fraction operator/(Fraction left, Fraction	right)
{
	left.to_improper();
	right.to_improper();
	return Fraction
	(
		left.get_numerator() * right.get_denominator(),
		left.get_denominator() * right.get_numerator()
	).to_proper();
}


void main()
{
	setlocale(LC_ALL, "Russian");

#ifdef CONSTRUCTORS_CHECK
	Fraction A;
	std::cout << A << std::endl;
	Fraction B = 5;
	std::cout << B << std::endl;
	Fraction C(1, 2);
	std::cout << C << std::endl;
	Fraction D(2, 3, 4);
	std::cout << D << std::endl;
#endif // CONSTRUCTORS_CHECK

#ifdef PROPER_IMPROPER
	Fraction A(7, 2);
	std::cout << A << " = ";
	std::cout << (A.to_proper()) << std::endl;
	std::cout << A << " = ";
	std::cout << (A.to_improper()) << std::endl;
#endif // PROPER_IMPROPER

	Fraction A(2, 3, 4);
	Fraction B(5, 6, 7);

	std::cout <<A << " + " << B << " = " << (A + B) << std::endl;
	std::cout << B << " - " << B << " = " << (B - B) << std::endl;
	std::cout << B << " - " << A << " = " << (B - A) << std::endl;
	std::cout << A << " - " << B << " = " << (A - B) << std::endl;
	std::cout <<A << " * " << B << " = " << (A * B) << std::endl;
	std::cout <<A << " / " << B << " = " << (A / B) << std::endl;

}

std::ostream& operator<<(std::ostream& os, const Fraction& obj)
{
	if (obj.get_integer()) os << obj.get_integer();
	if (obj.get_integer() && obj.get_numerator()) os << "(";
	if (obj.get_numerator()) os << obj.get_numerator() << "/" << obj.get_denominator();
	if (obj.get_integer() && obj.get_denominator() && obj.get_numerator())os << ")";
	if (obj.get_integer() == 0 && obj.get_numerator() == 0) os << 0;
	return os;
}

Fraction operator*(Fraction left, Fraction	right)
{
	left.to_improper();
	right.to_improper();
	return Fraction
	(
		left.get_numerator() * right.get_numerator(),
		left.get_denominator() * right.get_denominator()
	).to_proper();
}