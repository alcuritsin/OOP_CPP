//Fraction - дробь
#include <iostream>

//#define CONSTRUCTORS_CHECK	//	Проверка конструкторов/деструкторов
//#define PROPER_IMPROPER_REDUCE	//	Методы: `to_proper(); to_improper(); reduce();`
//#define ARITHMETIC_CHECK	//	Арифметические операции
//#define COMPOUND_ASSIGNMENT	//	Составные присваивания
//#define INCREMENT_DECREMENT	//	Инкремент / Декримент
#define COMPARISON	// Сравнение

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

	//	Constructors:
	Fraction()
	{
		//	с учетом знака дроби --done

		this->minus = 0;
		this->integer = 0;
		this->numerator = 0;
		this->denominator = 1;
		std::cout << "Constructor_0:\t\t" << this << std::endl;
	}
	Fraction(int integer)
	{
		//	с учетом знака дроби --done

		(integer >=0)?this->minus = 0: this->minus = 1;
		this->integer = abs(integer);
		this->numerator = 0;
		this->denominator = 1;
		std::cout << "Constructor_1:\t\t" << this << std::endl;
	}
	Fraction(int numerator, int denominator)
	{
		//	с учетом знака дроби --done

		this->integer = 0;
		(numerator >= 0)? this->minus = 0:this->minus = 1;
		this->numerator = abs(numerator);
		this->set_denominator(denominator);
		std::cout << "Constructor_2:\t\t" << this << std::endl;
	}
	Fraction(int integer, int numerator, int denominator)
	{
		//	с учетом знака дроби --done

		(integer >= 0) ? this->minus = 0 : this->minus = 1;
		this->integer = abs(integer);
		(numerator >= 0 && !minus)? this->minus = 0:this->minus = 1;
		this->numerator = abs(numerator);
		this->set_denominator(denominator);
		std::cout << "Constructor_3:\t\t" << this << std::endl;
	}
	~Fraction()
	{
		std::cout << "Distructor:\t\t" << this << std::endl;
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
	Fraction operator+=(const Fraction& other)
	{	
		this->integer = (this->minus ? -this->integer : this->integer) + (other.minus?-other.integer:other.integer);
		this->numerator = (this->minus ? -this->numerator : this->numerator) * other.denominator + (other.minus ? -other.numerator : other.numerator) * this->denominator;
		this->denominator = this->denominator * other.denominator;

		if (this->integer < 0 || this->numerator < 0)
		{	
			this->minus = 1;
			this->integer = abs(this->integer);
			this->numerator = abs(this->numerator);
			this->denominator = abs(this->denominator);

		}
		else
		{
			this->minus = 0;
		}

		this->to_proper();
		
		return *this;
		//	Хочется не так, но получилось только так :)
	}
	Fraction operator-=(const Fraction& other)
	{	
		this->integer = (this->minus ? -this->integer : this->integer) - (other.minus?-other.integer:other.integer);
		this->numerator = (this->minus ? -this->numerator : this->numerator) * other.denominator - (other.minus ? -other.numerator : other.numerator) * this->denominator;
		this->denominator = this->denominator * other.denominator;

		if (this->integer < 0 || this->numerator < 0)
		{	
			this->minus = 1;
			this->integer = abs(this->integer);
			this->numerator = abs(this->numerator);
			this->denominator = abs(this->denominator);
		}
		else
		{
			this->minus = 0;
		}

		this->to_proper();
		
		return *this;
		//	Хочется не так, но получилось только так :)
	}
	Fraction operator*=(Fraction other)
	{	

		this->to_improper();
		other.to_improper();

		this->numerator = ((this->minus ? -1:1)* this->numerator) * ((other.minus ? -1:1)* other.numerator);
		this->denominator = this->denominator * other.denominator;

		if (this->numerator < 0)
		{	
			this->minus = 1;
			this->integer = abs(this->integer);
			this->numerator = abs(this->numerator);
			this->denominator = abs(this->denominator);
		}
		else
		{
			this->minus = 0;
		}

		this->to_proper();
		
		return *this;
		//	Хочется не так, но получилось только так :)
	}
	Fraction operator/=(Fraction other)
	{	

		this->to_improper();
		other.to_improper();

		this->numerator = ((this->minus ? -1:1)* this->numerator) * ((other.minus ? -1:1)* other.denominator);
		this->denominator = this->denominator * other.numerator;

		if (this->numerator < 0)
		{	
			this->minus = 1;
			this->integer = abs(this->integer);
			this->numerator = abs(this->numerator);
			this->denominator = abs(this->denominator);
		}
		else
		{
			this->minus = 0;
		}

		this->to_proper();
		
		return *this;
		//	Хочется не так, но получилось только так :)
	}

	// Increment	/	Decrement
	Fraction operator ++ ()	//	Префиксный инкремент / Prefix Increment
	{
		*this += Fraction (1);
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
		*this -= Fraction(1);
		return *this;
	}
	Fraction operator -- (int)	//	Постфиксный декремент / Postfix Decrement
	{
		Fraction old = *this;
		--*this;
		return old;
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

		return *this;
	}
};

	//	Functions prototype (прототипы функций)
std::ostream& operator<<(std::ostream& os, const Fraction& obj);

Fraction operator+ (Fraction left, Fraction	right);
Fraction operator- (Fraction left, Fraction	right);
Fraction operator* (Fraction left, Fraction	right);
Fraction operator/ (Fraction left, Fraction	right);

bool operator== (const Fraction& left, const Fraction& right);
bool operator!= (const Fraction& left, const Fraction& right);
bool operator> (const Fraction& left, const Fraction& right);
bool operator< (const Fraction& left, const Fraction& right);

bool operator>= (const Fraction& left, const Fraction& right);
bool operator<= (const Fraction& left, const Fraction& right);

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
	Fraction A(-2, 3, 4);
	Fraction B(-5, 6, 7);

	std::cout << A << " + " << B << " = " << (A + B) << std::endl;
	std::cout << B << " - " << B << " = " << (B - B) << std::endl;
	std::cout << B << " - " << A << " = " << (B - A) << std::endl;
	std::cout << A << " - " << B << " = " << (A - B) << std::endl;
	std::cout << A << " * " << B << " = " << (A * B) << std::endl;
	std::cout << A << " / " << B << " = " << (A / B) << std::endl;
#endif // ARITHMETIC_CHECK

	//	Составные присваивания
#ifdef COMPOUND_ASSIGNMENT
	Fraction A(2, 3, 4);
	Fraction B(5, 6, 7);

	std::cout << A << " -= " << B; std::cout << " >>> " << (A -= B) << std::endl; std::cout << "minus = " << A.get_minus() << std::endl;
	std::cout << A << " *= " << B; std::cout << " >>> " << (A *= B) << std::endl; std::cout << "minus = " << A.get_minus() << std::endl;
	std::cout << (A.reduce()) << std::endl;
	std::cout << A << " /= " << B; std::cout << " >>> " << (A /= B) << std::endl; std::cout << "minus = " << A.get_minus() << std::endl;
	std::cout << (A.reduce()) << std::endl;
#endif // COMPOUND_ASSIGNMENT

	//	Инкремент / Декримент
#ifdef INCREMENT_DECREMENT
	Fraction A(2, 3, 4);
	Fraction B(5, 6, 7);

	std::cout << "A++ ==> " << A++; std::cout << "minus = " << A.get_minus() << std::endl;
	std::cout << (A.reduce()) << std::endl;
	std::cout << "++A ==> " << ++A; std::cout << "minus = " << A.get_minus() << std::endl;
	std::cout << (A.reduce()) << std::endl;
	std::cout << "A-- ==> " << A--; std::cout << "minus = " << A.get_minus() << std::endl;
	std::cout << (A.reduce()) << std::endl;
	std::cout << "--A ==> " << --A; std::cout << "minus = " << A.get_minus() << std::endl;
	std::cout << (A.reduce()) << std::endl;
#endif // INCREMENT_DECREMENT

	// Сравнение
#ifdef COMPARISON
	Fraction A(2, 3, 4);
	Fraction B(5, 6, 7);
	//Fraction A(5, 6, 7);
	//Fraction B(2, 3, 4);
	
	std::cout << "A = " << A << "\tB = " << B << std::endl;
	std::cout << "A == B\t" << ((A == B) ? "true" : "false") << std::endl;
	std::cout << "A != B\t" << ((A != B) ? "true" : "false") << std::endl;
	std::cout << "A > B\t" << ((A > B) ? "true" : "false") << std::endl;
	std::cout << "A < B\t" << ((A < B) ? "true" : "false") << std::endl;
	std::cout << "A >= B\t" << ((A >= B) ? "true" : "false") << std::endl;
	std::cout << "A <= B\t" << ((A <= B) ? "true" : "false") << std::endl;
#endif // COMPARISON
}

	//	Functions definitio (определение функций)
std::ostream& operator<<(std::ostream& os, const Fraction& obj)
{
	//	с учетом знака дроби --done

	if (obj.get_minus()) os << "(-)"; //Выводит знак дроби
	//Чтобы знак не дублировался, выводим модули чисел.	abs(val) -> |val|
	if (obj.get_integer()) os << abs(obj.get_integer());
	if (obj.get_integer() && obj.get_numerator()) os << "(";
	if (obj.get_numerator()) os << abs(obj.get_numerator()) << "/" << abs(obj.get_denominator());
	if (obj.get_integer() && obj.get_denominator() && obj.get_numerator())os << ")";
	if (obj.get_integer() == 0 && obj.get_numerator() == 0) os << 0;
	return os;
}

Fraction operator+ (Fraction left, Fraction	right)
{
	//	с учетом знака дроби --done

	left.to_proper();
	right.to_proper();

	return Fraction
	(
		(left.get_minus() ? -left.get_integer() : left.get_integer()) + (right.get_minus() ? -right.get_integer() : right.get_integer()),
		(left.get_minus() ? -left.get_numerator() : left.get_numerator()) * right.get_denominator() + (right.get_minus() ? -right.get_numerator() : right.get_numerator()) * left.get_denominator(),	//	с учетом знака дроби
		left.get_denominator() * right.get_denominator()
	).to_proper();
}
Fraction operator- (Fraction left, Fraction	right)
{
	//	с учетом знака дроби --done

	left.to_proper();
	right.to_proper();

	return Fraction
	(
		(left.get_minus() ? -left.get_integer() : left.get_integer()) - (right.get_minus() ? -right.get_integer() : right.get_integer()),
		(left.get_minus() ? -left.get_numerator() : left.get_numerator()) * right.get_denominator() - (right.get_minus() ? -right.get_numerator() : right.get_numerator()) * left.get_denominator(),
		left.get_denominator() * right.get_denominator()
	).to_proper();
}
Fraction operator* (Fraction left, Fraction	right)
{
	//	с учетом знака дроби --done

	left.to_improper();
	right.to_improper();

	return Fraction
	(
		(left.get_minus() ? -left.get_numerator() : left.get_numerator()) * (right.get_minus() ? -right.get_numerator() : right.get_numerator()),
		left.get_denominator() * right.get_denominator()
	).to_proper();
}
Fraction operator/ (Fraction left, Fraction	right)
{
	//	с учетом знака дроби --done

	left.to_improper();
	right.to_improper();

	return Fraction
	(
		(left.get_minus() ? -left.get_numerator() : left.get_numerator()) * (right.get_minus() ? -right.get_denominator() : right.get_denominator()),
		left.get_denominator() * right.get_numerator()
	).to_proper();
}

bool operator== (const Fraction& left, const Fraction& right)
{
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
	if
		(
			(left.get_minus() ? -1 : 1) * left.get_integer() != (right.get_minus() ? -1 : 1) * right.get_integer() &&
			(left.get_minus() ? -1 : 1) * left.get_numerator() * right.get_denominator() != (right.get_minus() ? -1 : 1) * right.get_numerator() * left.get_denominator()
			)
	{
		return true;
	}
	else
	{
		return false;
	}
}
bool operator> (const Fraction& left, const Fraction& right)
{
	if
		(
			(left.get_minus() ? -1 : 1) * left.get_integer() > (right.get_minus() ? -1 : 1) * right.get_integer() &&
			(left.get_minus() ? -1 : 1) * left.get_numerator() * right.get_denominator() > (right.get_minus() ? -1 : 1) * right.get_numerator() * left.get_denominator()
			)
	{
		return true;
	}
	else
	{
		return false;
	}
}
bool operator< (const Fraction& left, const Fraction& right)
{
	if
		(
			(left.get_minus() ? -1 : 1) * left.get_integer() < (right.get_minus() ? -1 : 1) * right.get_integer() &&
			(left.get_minus() ? -1 : 1) * left.get_numerator() * right.get_denominator() < (right.get_minus() ? -1 : 1) * right.get_numerator() * left.get_denominator()
			)
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