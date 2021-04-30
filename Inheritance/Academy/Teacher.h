#pragma once
#include "Academy.h"
#include "Human.h"

//	Класс Учитель

//	Class Teacher
class Teacher :public Human
{
	string speciality;
	unsigned int experience;
public:
	const string& get_speciality()const;
	unsigned int get_experiance()const;

	void set_speciality(const string& speciality);
	void set_experiance(unsigned int experience);

	//	Constructors
	//Teacher() :Human("", "", 0);
	Teacher(HUMAN_TAKE_PARAMETRS, TEACHER_TAKE_PARAMETRS);
	~Teacher();

	//	Methods
	void info() const;
};
