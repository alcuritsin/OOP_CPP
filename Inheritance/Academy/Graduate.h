#pragma once
#include "Academy.h"
#include "Student.h"

//	Класс Дипломник
//	"дипломник" - студент, который пишет диплом :)

//	Methods prototips for class Graduate
//	(empty)


//	Class Graduate
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
	) :Student(HUMAN_GIVE_PARAMETRS,	//	Атрибуты базового класса
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
