﻿#include "Academy.h"
#include "Human.h"
#include "Student.h"
#include "Teacher.h"
#include "Graduate.h"

#define DEBUG
//#define INHERITANCE_CHECK


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