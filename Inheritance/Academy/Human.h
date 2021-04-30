#pragma once
#include "Academy.h"

//	Класс Человек

//	Methods prototips for class Human
//	(empty)


//	Class Human
class Human
{
	string last_name;
	string first_name;
	//time_t	birth_date;
	unsigned int age;
public:
	const string& get_last_name() const;
	const string& get_first_name() const;
	const unsigned int& get_age() const;

	void set_last_name(const string& last_name);
	void set_first_name(const string& first_name);
	void set_age(const unsigned  int& age);

	//	Constructors
	//Human(const string& last_name, const string& first_name, const time_t& birth_date)
	Human(HUMAN_TAKE_PARAMETRS);
	virtual ~Human();

	//	Methods
	virtual void info()const;
};

ostream& operator << (ostream& os, const Human& obj);
