#include "Human.h"

//	Methods for class "Human"

//	Пока методы "за классом" для этого класса отсутствуют.
//	Поэтому исходник пустой.

const string& Human::get_last_name() const
{
	return last_name;
}
const string& Human::get_first_name() const
{
	return first_name;
}
const unsigned int& Human::get_age() const
{
	return age;
}
/*
const time_t& get_birth_date() const
{
	return birth_date;
}
*/

void Human::set_last_name(const string& last_name)
{
	this->last_name = last_name;
}
void Human::set_first_name(const string& first_name)
{
	this->first_name = first_name;
}
void Human::set_age(const unsigned  int& age)
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
Human::Human(HUMAN_TAKE_PARAMETRS)
{
	set_last_name(last_name);
	set_first_name(first_name);
	set_age(age);
	//set_birth_date(birth_date);
#ifdef DEBUG
	cout << "HConstructor:\t\t" << this << endl;
#endif // DEBUG
}
Human::~Human()
{
#ifdef DEBUG
	cout << "HDestructor:\t\t" << this << endl;
#endif // DEBUG
}

//	Methods
void Human::info()const
{
	/*
	cout << "Last name:\t" << last_name << endl;
	cout << "First name:\t" << first_name << endl;
	cout << "Age:\t\t" << age <<" years" << endl;
	*/
	cout << last_name << " " << first_name << ", " << age << " years" << endl;
	//cout << "Birth date:\t" << birth_date << endl;
}

ostream& operator<<(ostream& os, const Human& obj)
{
	// TODO: insert return statement here
	return os << obj.get_last_name() << " " << obj.get_first_name() << ", " << obj.get_age() << " лет";
}
