#include <iostream>
#include <ctime>
#include<string>
using namespace std;
#define DELIMETR "\n--------------------------------------------------\n"
#define	HUMAN_TAKE_PARAMETRS const string& last_name, const string& first_name, const unsigned int& age
#define STUDENT_TAKE_PARAMETRS const string& speciality, const string& group, double rating
#define TEACHER_TAKE_PARAMETRS const string& speciality, unsigned int experience

#define	HUMAN_GIVE_PARAMETRS last_name, first_name, age
#define STUDENT_GIVE_PARAMETRS speciality, group, rating
#define TEACHER_GIVE_PARAMETRS speciality, experience

#define DEBUG
//#define INHERITANCE_CHECK


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
class Graduate :public Student
{
	string	topic;	//	Тема диплома

public:
	const string& get_topic() const
	{
		return topic;
	}
	void set_topic(const string& topic)
	{
		this->topic = topic;
	}
	//	Constructors
	Graduate
	(
		HUMAN_TAKE_PARAMETRS,	//	Атрибуты базового класса
		STUDENT_TAKE_PARAMETRS,	//	Атрибуты нашего класса
		const string topic
	):Student(HUMAN_GIVE_PARAMETRS,	//	Атрибуты базового класса
		STUDENT_GIVE_PARAMETRS	//	Атрибуты нашего класса
		)
	{
		set_topic(topic);
#ifdef DEBUG
		cout << "GConstructor:\t\t" << this << endl;
#endif // DEBUG
	}
	~Graduate()
	{
#ifdef DEBUG
		cout << "GDestructor:\t\t" << this << endl;
#endif // DEBUG
	}
	//	Methods
	void info() const
	{
			cout << "Студент: "; Student::info();
			cout << "Тема: " << topic << endl;
	}
};

void main()
{
	setlocale(LC_ALL, "Russian");

#ifdef INHERITANCE_CHECK
	//Human human("Тупенко", "Василий", 25);
	//human.info();
	Student vasya("Тупенко", "Василий", 25, "Програмирование", "BV_011", 4.5);
	vasya.info();
	cout << endl;
	Teacher teacher("Einstein", "Albert", 150, "Phisics", 120);
	teacher.info();

	cout << "\n\nДипломник\n";
	Graduate Tony
	(
		"Монтана", "Антонио", 25,
		"Современные технологии продаж", "BV_011", 80,
		"Распростронение товаров.");
	Tony.info();
#endif // INHERITANCE_CHECK

	//	Generalisation
	Human* group[] =
	{
		new Student("Батодалаев", "Даши", 16,"РПО","PD_011",5),
		new Student("Загидуллин", "Линар", 32, "РПО","PD_011", 5),
		new Graduate("Шугани","Сергей", 15, "РПО", "PD_011", 5, "Защита персональных данных"),
		new Teacher("Einstein", "Albert", 141, "Astrophisics", 110),
		new Student("Маркин", "Даниил", 17, "РПО", "PD_011",5),
		new Teacher("Richter","Jeffrey", 45,"Windows development",20)
	};

	cout << DELIMETR;
	//	Specialisation
	for (int i = 0; i < sizeof(group)/sizeof(Human*); i++)
	{
		group[i]->info();
		cout << DELIMETR;
	}
	
	for (int i = 0; i < sizeof(group)/sizeof(Human*); i++)
	{
		delete group[i];
	}
}