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
	const string& get_last_name() const
	{
		return last_name;
	}
	const string& get_first_name() const
	{
		return first_name;
	}
	const unsigned int& get_age() const
	{
		return age;
	}
	/*
	const time_t& get_birth_date() const
	{
		return birth_date;
	}
	*/

	void set_last_name(const string& last_name)
	{
		this->last_name = last_name;
	}
	void set_first_name(const string& first_name)
	{
		this->first_name = first_name;
	}
	void set_age(const unsigned  int& age)
	{
		this->age = age;
	}
	/*
	void set_birth_date(const time_t& birth_date)
	{
		this->birth_date = birth_date;
	}
	*/

	//	Constructors
	//Human(const string& last_name, const string& first_name, const time_t& birth_date)
	Human(HUMAN_TAKE_PARAMETRS)
	{
		set_last_name(last_name);
		set_first_name(first_name);
		set_age(age);
		//set_birth_date(birth_date);
#ifdef DEBUG
		cout << "HConstructor:\t\t" << this << endl;
#endif // DEBUG
	}
	virtual ~Human()
	{
#ifdef DEBUG
		cout << "HDestructor:\t\t" << this << endl;
#endif // DEBUG
	}

	//	Methods
	virtual void info()const
	{
		/*
		cout << "Last name:\t" << last_name << endl;
		cout << "First name:\t" << first_name << endl;
		cout << "Age:\t\t" << age <<" years" << endl;
		*/
		cout << last_name << " " << first_name << ", " << age << " years" << endl;
		//cout << "Birth date:\t" << birth_date << endl;
	}
};
