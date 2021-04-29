#pragma once
#include "Academy.h"
#include "Human.h"

//	Класс Студент

//	Methods prototips for class Student
//	(empty)


//	Class Student
class Student : public Human
{
	string speciality;
	string group;
	double rating;
public:
	const string& get_speciality()const
	{
		return speciality;
	}
	const string& get_group()const
	{
		return group;
	}
	const double& get_rating()const
	{
		return rating;
	}

	void set_speciality(const string& speciality)
	{
		this->speciality = speciality;
	}
	void set_group(const string& group)
	{
		this->group = group;
	}
	void set_rating(const double& rating)
	{
		this->rating = rating;
	}

	//	Constructors
	Student() : Human("", "", 0)
	{
		set_speciality("");
		set_group("");
		set_rating(0);
#ifdef DEBUG
		cout << "SDefaultConstructor:\t\t" << this << endl;
#endif // DEBUG
	}
	Student
	(
		HUMAN_TAKE_PARAMETRS,	//	Атрибуты базового класса
		STUDENT_TAKE_PARAMETRS	//	Атрибуты нашего класса
	) :Human(HUMAN_GIVE_PARAMETRS)
	{
		set_speciality(speciality);
		set_group(group);
		set_rating(rating);
#ifdef DEBUG
		cout << "SConstructor:\t\t" << this << endl;
#endif // DEBUG

	}
	~Student()
	{
#ifdef DEBUG
		cout << "SDestructor:\t\t" << this << endl;
#endif // DEBUG
	}

	//	Operators:
	//Student& operator=(const Student& other)
	//{
	//}

	//	Methods
	void info() const
	{
		Human::info();
		cout << speciality << ", " << group << " успеваемость: " << rating << endl;
	}
};
