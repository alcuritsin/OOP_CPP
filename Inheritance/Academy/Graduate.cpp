#include "Graduate.h"

//	Methods for class "Graduate"

//	Пока методы "за классом" для этого класса отсутствуют.
//	Поэтому исходник пустой.
const string& Graduate::get_topic() const
{
	return topic;
}
void Graduate::set_topic(const string& topic)
{
	this->topic = topic;
}
//	Constructors
Graduate::Graduate 
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
Graduate::~Graduate()
{
#ifdef DEBUG
	cout << "GDestructor:\t\t" << this << endl;
#endif // DEBUG
}
//	Methods
void Graduate::info() const
{
	cout << "Студент: "; Student::info();
	cout << "Тема: " << topic << endl;
}

ostream& operator<<(ostream& os, const Graduate& obj)
{
	// TODO: insert return statement here

	return os <<(Student)obj << ", " << obj.get_topic();
}
