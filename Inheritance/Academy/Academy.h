#pragma once
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

//	Class prototips
class Human;
class Student;
class Teacher;
class Graduate;