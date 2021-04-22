#pragma once
//Fraction - �����
#include <iostream>
	//	Class prototype (�������� ������)
class Fraction;	//	Class declaration  -- ���������� ������

	//	Functions prototype (��������� �������)
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

//	Class (������)
class Fraction
{	//����� Fraction ��������� ������� �����. ��������:	2(3/4)
	bool minus;	//	���� �����.
	int integer;	// ����� �����
	int numerator;	//	���������
	int denominator;	//	�����������
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
		//	� ������ ����� ����� --done

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
		//	� ������ ����� ����� --done
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
		//	� ������ ����� ����� --done

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
		//	� ������ ����� ����� --done
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
		//	����������� ��� ������������� ����� ���������� ������
		//	Fraction Accuracy // �������� ����� ����� 1 / 100 000, �� ����� ��������� ��� �������������...
		//	`acc` - ���������� ������ ����� �������, ������� ������� � ����.

		this->minus = (decimal < 0) ? true : false;	//	���������� ����� � ��������-��������
		this->integer = abs((int)decimal);	//	�������� ����� �����

		if (acc <= 0)	//	�� ��������� ������� �����... ) ��, ���������� ��� ������������!
		{
			this->numerator = 0;
			this->denominator = 1;
			this->integer = abs(round(decimal));	//	��������� ����� �� ������ �� �������������� ��������.
		}
		else
		{
			//	��������� �����������
			if (acc > 14) //	������������ ����������� � 14 ������ ����� �������.
			{
				this->denominator = pow(10, 14);
			}
			else
			{
				this->denominator = pow(10, acc);
			}

			//	��������� ���������
			this->numerator = round((double)(abs(decimal) - this->get_integer()) * this->get_denominator());
		}

		this->reduce();	//	��������� ���� ��������

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
	Fraction operator ++ ()	//	���������� ��������� / Prefix Increment
	{
		this->integer++;
		return *this;
	}
	Fraction operator ++ (int)	//	����������� ��������� / Postfix Increment
	{
		Fraction old = *this;
		++* this;
		return old;
	}
	Fraction operator -- ()	//	���������� ��������� / Prefix Decrement
	{
		this->integer--;
		return *this;
	}
	Fraction operator -- (int)	//	����������� ��������� / Postfix Decrement
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
		//��������� ������������ ����� � ���������� 11 / 4 = > 2(3 / 4)
		//	� ������ ����� ����� --done

		integer += numerator / denominator;
		numerator %= denominator;
		return *this;
	}
	Fraction& to_improper()
	{
		//��������� ����� � ������������	2(3 / 4) = > 11 / 4
		//	� ������ ����� ����� --done

		numerator += integer * denominator;
		integer = 0;
		return *this;
	}
	Fraction& reduce()
	{
		/*
		//	��������� �����		5/10 => 1/2 --done
		//	� ������ ����� ����� --done
		int counter = (this->numerator<this->denominator)?this->numerator:this->denominator;	//	���������� ���������� ������������ �����, ��� ���������� ��������.

		int gcd = 1;	//	Greatest Common Divisor (���������� ����� ��������)

		for (int i = gcd; i <= counter; i++)
		{
			if (numerator % i == 0 && denominator % i == 0) gcd = i;	// ��������� � ����������� ������� �� `i` ��� �������, ������������, ��� ��� ���������� ����� ��������.
		}

		this->numerator /= gcd;
		this->denominator /= gcd;
		*/
		//	CW
		if (numerator == 0) return *this;
		int more, less, rest;
		//�������� ��� ������ ��������� ��� �����������
		if (numerator > denominator) less = numerator, more = denominator;
		else less = denominator, more = numerator;
		//������� ���������� ����� ��������
		do
		{
			rest = more % less;
			more = less;
			less = rest;
		} while (rest);
		int GCD = more; //Greatest Common Divisor(���������� ����� ��������)
		numerator /= GCD;
		denominator /= GCD;

		return *this;
	}
};