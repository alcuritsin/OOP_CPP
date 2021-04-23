#include <iostream>
#include <ctime>
#include<string>
using namespace std;

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
	Human(const string& last_name, const string& first_name, const unsigned int& age)
	{
		set_last_name(last_name);
		set_first_name(first_name);
		set_age(age);
		//set_birth_date(birth_date);

		cout << "Hconstructor:\t\t" << this << endl;
	}
	~Human()
	{
		cout << "HDestructor:\t\t" << this << endl;
	}
	//	Methods
	void info()const
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
	Student
	(
		const string& last_name, const string& first_name, const unsigned int& age,	//	Атрибуты базового класса
		const string& speciality, const string& group, double rating	//	Атрибуты нашего класса
	) :Human(last_name, first_name, age)
	{
		set_speciality(speciality);
		set_group(group);
		set_rating(rating);
		cout << "Sconstructor:\t\t" << this << endl;
	}
	~Student()
	{
		cout << "SDestructor:\t\t" << this << endl;
	}

	//	Methods
	void info() const
	{
		Human::info();
		cout << speciality << ", " << group << " успеваемость: " << rating << endl;
	}
};

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
	Teacher
	(
		const string& last_name, const string& first_name, const unsigned int& age,	//	Атрибуты базового класса
		const string& speciality, unsigned int experience	//	Атрибуты нашего класса
	) :Human(last_name, first_name, age)
	{
		set_speciality(speciality);
		set_experiance(experience);
		cout << "Tconstructor:\t\t" << this << endl;
	}
	~Teacher()
	{
		cout << "TDestructor:\t\t" << this << endl;
	}

	//	Methods
	void info() const
	{
		Human::info();
		cout << speciality << ", опыт: " << experience << " лет" << endl;
	}

};


void main()
{
	setlocale(LC_ALL, "Russian");

	//Human human("Тупенко", "Василий", 25);
	//human.info();
	Student vasya("Тупенко", "Василий", 25, "Програмирование", "BV_011", 4.5);
	vasya.info();
	Teacher teacher("Einstein", "Albert", 150, "Phisics", 120);
	teacher.info();
}