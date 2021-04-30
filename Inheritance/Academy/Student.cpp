#include "Student.h"

//	Methods for class "Student"

//	Пока методы "за классом" для этого класса отсутствуют.
//	Поэтому исходник пустой.
const string& Student::get_speciality()const
{
	return speciality;
}
const string& Student::get_group()const
{
	return group;
}
const double& Student::get_rating()const
{
	return rating;
}

void Student::set_speciality(const string& speciality)
{
	this->speciality = speciality;
}
void Student::set_group(const string& group)
{
	this->group = group;
}
void Student::set_rating(const double& rating)
{
	this->rating = rating;
}

//	Constructors
//Student::Student() : Human("", "", 0)
//{
//	set_speciality("");
//	set_group("");
//	set_rating(0);
//#ifdef DEBUG
//	cout << "SDefaultConstructor:\t\t" << this << endl;
//#endif // DEBUG
//}
Student::Student
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

Student::~Student()
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
void Student::info() const
{
	Human::info();
	cout << speciality << ", " << group << " успеваемость: " << rating << endl;
}