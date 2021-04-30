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
	const string& get_topic() const;
	void set_topic(const string& topic);
	//	Constructors
	Graduate(HUMAN_TAKE_PARAMETRS, STUDENT_TAKE_PARAMETRS, const string topic);
	~Graduate();
	//	Methods
	void info() const;
};

ostream& operator<<(ostream& os, const Graduate& obj);