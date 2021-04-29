#pragma once
#include "Academy.h"
#include "Human.h"

//	Класс Учитель

//	Methods prototips for class Teacher
//	(empty)


//	Class Teacher
class Teacher :public Human
{
	string speciality;
	unsigned int experience;
public:
	const string& get_speciality()const
	{
		return speciality;
	}
	unsigned int get_experiance()const
	{
		return experience;
	}

	void set_speciality(const string& speciality)
	{
		this->speciality = speciality;
	}
	void set_experiance(unsigned int experience)
	{
		this->experience = experience;
	}

	//	Constructors
	Teacher() :Human("", "", 0)
	{
		set_speciality("");
		set_experiance(0);
#ifdef DEBUG
		cout << "TDefaultConstructor:\t\t" << this << endl;
#endif // DEBUG
	}
	Teacher
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
	~Teacher()
	{
#ifdef DEBUG
		cout << "TDestructor:\t\t" << this << endl;
#endif // DEBUG
	}

	//	Methods
	void info() const
	{
		Human::info();
		cout << speciality << ", опыт: " << experience << " лет" << endl;
	}

};
