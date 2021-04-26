#include <iostream>
#include <ctime>
#include<string>
using namespace std;

#define DEBUG

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
#ifdef DEBUG
		cout << "HConstructor:\t\t" << this << endl;
#endif // DEBUG
	}
	~Human()
	{
#ifdef DEBUG
		cout << "HDestructor:\t\t" << this << endl;
#endif // DEBUG
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
	Student():Human("","",0)
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
		const string& last_name, const string& first_name, const unsigned int& age,	//	Атрибуты базового класса
		const string& speciality, const string& group, double rating	//	Атрибуты нашего класса
	) :Human(last_name, first_name, age)
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
		const string& last_name, const string& first_name, const unsigned int& age,	//	Атрибуты базового класса
		const string& speciality, unsigned int experience	//	Атрибуты нашего класса
	) :Human(last_name, first_name, age)
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
class Graduate
{
	string	issue;	//	Тема диплома
	unsigned int page_count;	//	Количество страниц
	unsigned int year;	//	Год написания диплома
	string	city;	//	Город написания тут просится enum (филиалы академии)
	string link_to_file;	//	Ссылка на файл

	const Student* student;	//	Исполнитель
	const Teacher* teacher;	//	Преподаватель

public:
	const string& get_issue() const
	{
		return issue;
	}
	const unsigned int get_page_count() const
	{
		return page_count;
	}
	const unsigned int get_year() const
	{
		return year;
	}
	const string& get_city() const
	{
		return city;
	}
	const string& get_link_to_file() const
	{
		return link_to_file;
	}
	const Student* get_student() const
	{
		return student;
	}
	const Teacher* get_teacher() const
	{
		return teacher;
	}
	void set_issue(const string& issue)
	{
		this->issue = issue;
	}
	void set_page_count (const unsigned int page_count)
	{
		this->page_count = page_count;
	}
	void set_year (const unsigned int year)
	{
		this->year = year;
	}
	void set_city (const string& city)
	{
		this->city = city;
	}
	void set_link_to_file (const string& link_to_file)
	{
		this->link_to_file = link_to_file;
	}
	/*void set_student (const Student& student)
	{
		this->student = student;
	}
	void set_teacher (const Teacher& teacher)
	{
		this->teacher = teacher;
	}*/
	//	Constructors
	Graduate
	(
		const string& issue,			//	Тема диплома
		const unsigned int page_count,	//	Количество страниц
		const unsigned int year,		//	Год написания диплома
		const string&	city,			//	Город написания тут просится enum (филиалы академии)
		const string& link_to_file,		//	Ссылка на файл

		const Student& student,			//	Исполнитель
		const Teacher& teacher			//	Преподаватель
	)
	{
		set_issue(issue);
		set_page_count(page_count);
		set_year(year);
		set_city(city);
		set_link_to_file(link_to_file);

		/*set_student(student);
		set_teacher(teacher);*/
		this->student = &student;
		this->teacher = &teacher;
#ifdef DEBUG
		cout << "GConstructor:\t\t" << this << endl;
#endif // DEBUG
	}
	~Graduate()
	{
		delete this->student;
		delete this->teacher;
#ifdef DEBUG
		cout << "GDestructor:\t\t" << this << endl;
#endif // DEBUG
	}
	//	Methods
	void info() const
	{
			cout << "Тема: " << issue << endl;
			cout << city << ", " << year << " (" << page_count << " стр.)" << endl;
			cout << "Ссылка: " << link_to_file << endl;
			cout << "------" << endl;
			cout << "Исполнитель: "; student->info();
			cout << "------" << endl;
			cout << "Преподаватель: "; teacher->info();
	}
};

void main()
{
	setlocale(LC_ALL, "Russian");

	//Human human("Тупенко", "Василий", 25);
	//human.info();
	Student vasya("Тупенко", "Василий", 25, "Програмирование", "BV_011", 4.5);
	vasya.info();
	cout << endl;
	Teacher teacher("Einstein", "Albert", 150, "Phisics", 120);
	teacher.info();

	cout << "\n\nДиплом";
	Graduate diplom("Тема диплома", 25, 2021, "Екатеринбург", "диск:/путь/diplom.doc", vasya, teacher);
	diplom.info();
}