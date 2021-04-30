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
	const string& get_speciality()const;
	const string& get_group()const;
	const double& get_rating()const;

	void set_speciality(const string& speciality);
	void set_group(const string& group);
	void set_rating(const double& rating);

	//Student() : Human("", "", 0);
	Student(HUMAN_TAKE_PARAMETRS, STUDENT_TAKE_PARAMETRS);

	~Student();

	//	Methods
	void info() const;
};

ostream& operator<<(ostream& os, const Student& obj);