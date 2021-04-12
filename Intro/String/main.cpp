#define _CRT_SECURE_NO_WARNINGS	//	Из-за использования strcpy()
#include<iostream>

#define DELIMETR "\n---------------------------------------\n"

#define DEBUG
//#define CONSTRUCTOR_CHECK
//#define ASSIGNMENT_CHECK

class String
{
	char* str;
	int size;

public:
	const char* get_str()const
	{
		return str;
	}
	char* get_str()
	{
		return str;
	}
	int get_size()const
	{
		return size;
	}
	//	Constructors:
	explicit String(int size = 80)
	{
		this->size = size;
		this->str = new char[size] {};
#ifdef DEBUG
		std::cout << (size<80?"Default":"Size") <<"Constructor:\t\t" << this << std::endl;
#endif // DEBUG
	}
	String(const char* str)
	{

		this->size = strlen(str) + 1;
		this->str = new char[size] {};

		strcpy(this->str, str);	//	String copy

#ifdef DEBUG
		std::cout << "Constructor:\t\t" << this << std::endl;
#endif // DEBUG
	}
	String(const String& other)
	{
		this->size = other.size;
		this->str = new char[size] {};
		strcpy(this->str, other.str);

#ifdef DEBUG
		std::cout << "CopyConstructor:\t\t" << this << std::endl;
#endif // DEBUG
	}
	//	Distructor
	~String()
	{
		delete[] this->str;
#ifdef DEBUG
		std::cout << "Destructor:\t\t" << this << std::endl;
#endif // DEBUG
	}

	//	Operators:

	String& operator=(const String& other)
	{
		//	Проверить не является другой объект этим объектом:
		if (this == &other) return *this;
		delete[] this->str;
		//	В первую очередь удаляем старое значение объекта,
		//	и только после этого присваиваем ему новое значение.

		this->size = other.size;
		this->str = new char[size] {};
		strcpy(this->str, other.str);

#ifdef DEBUG
		std::cout << "CopyAssignment:\t\t" << this << std::endl;
#endif // DEBUG
		return *this;
	}

	void print() const
	{
		std::cout << "str:\t" << str << std::endl;
		std::cout << "size:\t" << size << std::endl;
	}

private:

};

std::ostream& operator<<(std::ostream& os, const String& obj)
{
	return os << obj.get_str();
}

String operator+(const String& left, const String& right)
{
	String result(left.get_size() + right.get_size() - 1);

	for (int i = 0; i < left.get_size(); i++)
	{
		//result.get_str()[i] = left.get_str()[i];
		result[i] = left[i];
	}

	for (int i = 0; i < right.get_size(); i++)
	{
		//result.get_str()[i + left.get_size() - 1] = right.get_str()[i];
		result[i + left.get_size() - 1] = left[i];
	}
	return result;
}

void main()
{
	setlocale(LC_ALL, "Russian");

#ifdef CONSTRUCTOR_CHECK

	String str;
	str.print();

	String str2 (5);	//	
	str2.print();

	String str3 = "Hello";
	str3.print();

	std::cout << str3 << std::endl;

	String str4 = str3;	//	Copy constructor
	std::cout << "str4: " <<  str4 << std::endl;

	String str5;
	str5 = str4;
	std::cout << "str5: " << str5 << std::endl;

#endif // CONSTRUCTOR_CHECK

#ifdef ASSIGNMENT_CHECK

	String str1 = "Hello";
	String str2;

	str1 = str1;

	std::cout << str1 << std::endl;
	std::cout << str2 << std::endl;


#endif // ASSIGNMENT_CHECK


	String str1 = "Hello";
	String str2 = "World";

	std::cout << DELIMETR << std::endl;
	String str3 = str1 + " " + str2; //	Оператор `+` будет выполнять конкатенацию строк
	std::cout << DELIMETR << std::endl;
	std::cout << str3 << std::endl;


}
