#include "Fraction.h"

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
		(left.get_minus() ? -1 : 1) * left.get_numerator() * (right.get_minus() ? -1 : 1) * right.get_numerator(),
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
	if ((left.get_minus() ? -1 : 1) * left.get_numerator() * right.get_denominator() == (right.get_minus() ? -1 : 1) * right.get_numerator() * left.get_denominator())
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
