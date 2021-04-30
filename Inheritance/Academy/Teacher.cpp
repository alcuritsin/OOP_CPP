#include "Teacher.h"

//	Methods for class "Teacher"

//	Пока методы "за классом" для этого класса отсутствуют.
//	Поэтому исходник пустой.

const string& Teacher::get_speciality()const
{
	return speciality;
}
unsigned int Teacher::get_experiance()const
{
	return experience;
}

void Teacher::set_speciality(const string& speciality)
{
	this->speciality = speciality;
}
void Teacher::set_experiance(unsigned int experience)
{
	this->experience = experience;
}

//	Constructors
//Teacher::Teacher() :Human("", "", 0)
//{
//	set_speciality("");
//	set_experiance(0);
//#ifdef DEBUG
//	cout << "TDefaultConstructor:\t\t" << this << endl;
//#endif // DEBUG
//}
Teacher::Teacher
(
	HUMAN_TAKE_PARAMETRS,	//	Атрибуты базового класса
	TEACHER_TAKE_PARAMETRS	//	Атрибуты нашего класса
) :Human(HUMAN_GIVE_PARAMETRS)
{
	set_speciality(speciality);
	set_experiance(experience);
#ifdef DEBUG
	cout << "TConstructor:\t\t" << this << endl;
#endif // DEBUG
}
Teacher::~Teacher()
{
#ifdef DEBUG
	cout << "TDestructor:\t\t" << this << endl;
#endif // DEBUG
}

//	Methods
void Teacher::info() const
{
	Human::info();
	cout << speciality << ", опыт: " << experience << " лет" << endl;
}

ostream& operator<<(ostream& os, const Teacher& obj)
{
	// TODO: insert return statement here
	os << (Human)obj<<", ";
	return os << obj.get_speciality() << " опыт преподавания " << obj.get_experiance() << " лет";
}
