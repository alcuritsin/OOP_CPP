#define _CRT_SECURE_NO_WARNINGS	//	Из-за использования strcpy()
#include <iostream>
using namespace std;

#define OR ||
#define AND &&
#define NOT	!=

class Binary;
Binary operator + (const Binary& left, const Binary& right);
bool operator > (const Binary& left, const Binary& right);
bool operator < (const Binary& left, const Binary& right);
bool operator == (const Binary& left, const Binary& right);



class Binary
{

	char* str;
	int size;

public:
	//	Get/Set:
	const char* get_str() const
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
	explicit Binary(int size = 2)
	{	
		// Default Constructor
		this->size = size;
		this->str = new char[size] {'0'};
	}
	Binary(const char* str)
	{
		//	Constructor
		this->size = strlen(str) +1;
		this->str = new char[size] {};

		strcpy(this->str, str);
	}
	Binary(const Binary& other)
	{
		//	CopyConstructor
		this->size = other.size;
		this->str = new char [size] {};
		strcpy(this->str, other.str);
	}
	Binary(Binary&& other)
	{
		//	MoveConstructor
		this->size = other.size;
		this->str = other.str;
		other.str = nullptr;
	}
	Binary(const string& str)
	{
		this->size = str.size()+1;
		for (int i = 0; i < str.size(); i++)
		{
			this->str[i] = str[i];
		}
	}

	~Binary()
	{
		//	Destructor
		delete[] this->str;
	}

	//	Operators:
	Binary& operator=(const Binary& other)
	{
		//	CopyAssignment
		if (this == &other) return *this;
		delete[] this->str;

		this->size = other.size;
		this->str = new char[size] {};

		strcpy(this->str, other.str);
		
		return *this;
 
	}
	Binary& operator=(Binary&& other)
	{
		delete[] this->str;
		this->size = other.size;
		this->str = other.str;
		other.str = nullptr;

		return *this;
	}

	const char& operator[](const int index) const
	{
		return this->str[index];
	}
	char& operator[](const int index)
	{
		return this->str[index];
	}

	//	Methods:
	Binary del_start_zero()
	{
		while (this->str[0] == '0')
		{
			for (int i = 0; i < this->get_size(); i++)
			{
				this->str[i] = this->str[i + 1];
			}
		}
	}

	void info()
	{
		cout <<"bin: "<< this->get_str() << endl;
	}
private:

};


Binary operator + (const Binary& left, const Binary& right)
{
	int index_left = left.get_size()-1;
	int index_right = right.get_size() - 1;
	string str{};


	int result = 0;
	char char_left;
	char char_right;

	while (index_left>=0 || index_right>=0)
	{
		if (index_left >= 0)
		{
			char_left = left[index_left];
		}
		else
		{
			char_left = '0';
		}
		if (index_right >= 0)
		{
			char_right = right[index_right];
		}
		else
		{
			char_right = '0';
		}
			
		result += char_left - '0' + char_right - '0';

		if (result>1)
		{
			str = '0' + str;
			result = 1;
		}
		else
		{
			str = (char)result + str;
			result = 0;
		}

		--index_left; --index_right;
	}

	if (result==1)
	{
		str = (char)result + str;
	}

	return Binary (str);
}

bool operator > (const Binary& left, const Binary& right)
{
//	left.del_start_zero(); right.del_start_zero();

	if (left.get_size() > right.get_size())
	{
		return true;
	}
	else if (left.get_size() == right.get_size())
	{
		for (int i = left.get_size()-1; i >= 0; i--)
		{
			if (left[i] > right[i])
			{
				return true;
			}
		}
	}
	else
	{
		return false;
	}
}
bool operator < (const Binary& left, const Binary& right)
{
	if (left.get_size() < right.get_size())
	{
		return true;
	}
	else if (left.get_size() == right.get_size())
	{
		for (int i = left.get_size() - 1; i >= 0; i--)
		{
			if (left[i] < right[i])
			{
				return true;
			}
		}
	}
	else
	{
		return false;
	}
}
bool operator == (const Binary& left, const Binary& right)
{
	if (left.get_size() == right.get_size())
	{
		for (int i = left.get_size() - 1; i >= 0; i--)
		{
			if (left[i] != right[i])
			{
				return false;
			}
		}
		return true;
	}
	else
	{
		return false;
	}
}

void main()
{
	setlocale(LC_ALL, "Russian");
	string str = "1010";

	Binary bin_one = "1010";
	Binary bin_two = "11010";
	Binary bin_three;
	Binary bin_for = str;
	bin_three = bin_two;
	bin_three = bin_one + bin_two;

	bin_one.info();
	bin_two.info();
	bin_three.info();

	string str1 = "hello";
	string str2 = "world";


	//cout << str1 + str2;

}
