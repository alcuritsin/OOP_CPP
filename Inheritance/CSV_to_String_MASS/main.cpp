	//	https://www.cyberforum.ru/cpp-beginners/thread516548.html
	
#include <iterator> 
#include <iostream>
#include <string>
#include <vector>
#include <fstream>

using namespace std;
using std::cout;
using std::endl;

void ReadCSVFile(vector <vector <string>>& v, string FileName, string FolderPath = "", char sep = ';');
void WriteCSVFile(const vector <vector <string>>& v, string FileName, string FolderPath = "", char sep = ';');

void ParsingCSVString(vector <string>& v, string& str, char sep = ';');
string UnquoteCSV(const string& str);

string AssemlyCSVString(const vector <string>& v, char sep = ';');
string QuotingCSV(const string& str, char sep = ';');

void ReadCSVFile(vector <vector <string>>& v, string FileName, string FolderPath, char sep)
{
	///	<status> DONE </status>
	/// 
	/// <summary>
	///		��������� �� ����� ������.
	///		������ ������ �� �����������
	///		��������� ����������� � ������ �� ������.
	/// </summary>
	/// 
	/// <param name="v">
	///		������, � ������� ���������� ���������
	/// </param>
	/// <param name="FileName">
	///		��� �����
	/// </param>
	/// <param name="FolderPath">
	///		���� � �����, ��� �������� ����
	/// </param>
	/// <param name="sep">
	///		����������� � ������, �� ��������� ����� � �������
	/// </param>

	string str;
	string FullPath = FolderPath + "\\" + FileName;
	ifstream fin(FullPath);

	if (!fin)
	{
		cout << endl << "File: " << FileName << endl;
		cout << "In path: " << FolderPath << endl;
		cout << "Not found. \"" << FullPath << "\"" << endl;
		return;
	}

	cout << endl << "Read data from file: " << FullPath << endl;

	while (!fin.eof())
	{
		getline(fin, str);
		vector <string> s;
		ParsingCSVString(s, str, sep);
		v.push_back(s);
	}

	fin.close();
}

void WriteCSVFile(const vector <vector <string>>& v, string FileName, string FolderPath, char sep)
{
	/// <summary>
	///		������� ������ � ���� CSV.
	/// </summary>
	/// 
	/// <param name="v">
	///		�������� ������ ��������.
	/// </param>
	/// <param name="FileName">
	///		��� ����� ��� ������.
	/// </param>
	/// <param name="FolderPath">
	///		���� � �����.
	/// </param>
	/// <param name="sep">
	///		�����������. �� ��������� ����� � �������.
	/// </param>
	
	string FullPath = FolderPath + "\\" + FileName;
	ofstream fout(FullPath, ios::app);

	for (unsigned long long i = 0; i < v.size(); i++)
	{
		fout << AssemlyCSVString(v[i], sep) << endl;
	}

	fout.close();
}

void ParsingCSVString(vector <string>& v, string & str, char sep)
{
	///	<status> DONE </status>
	/// 
	/// <summary>
	///		������ ������ �� �����������.
	/// </summary>
	/// 
	/// <param name="v">
	///		������, � ������� ���������� ��������� ��������
	/// </param>
	/// <param name="str">
	///		������ ��������� ������
	/// </param>
	/// <param name="sep">
	///		��������, �� ��������� ���� � �������
	/// </param>

	// ���� ������ ������ ������ ��� ����� ���� ����������� ������ �����. ��������� ����� ������ � ������ ��� �������������.
	if (str.length() <= 1) return;

	string buf{ "" };
	bool quoted = false;	//	���� � ��������?

	int counter_quot = 0;	//	������� ������� � ������.

	for (int i = 0; i < str.length(); i++)
	{
		//	���� �� ��������� �����������
		if (str[i]!=sep)
		{
			//	����� ������� � ������.
			buf += str[i];
		}
		else
		{
			//	�������� ���� ���������
			for (int j = 0; j < buf.length(); j++)
			{
				if (buf[j] == '"')
				{
					//	���� �������� �������, ��� �����������, ��� ���� ��������� � �������. 
					quoted = true;					
					//	������� ���������� ������� � �������������� ����.
					counter_quot++;
					//break;
				}
			}

			if (!quoted || (quoted && counter_quot%2 == 0))
			{
				//	���� � ��������
				//	�
				//	���������� ������� ������
				//	���� ���������. ����������� �������� �����.

				//	������ ���������.
				// 
				//	�������� ������� ���� ��� ����.
				if (quoted)
				{
					buf = UnquoteCSV(buf);
				}
				v.push_back(buf);
				buf = "";
			}
			else
			{
				//	��������� ����������� �������� ������ ����
				//	����� ���������� ������ ������� � ������.
				//	�������� ������ '���� � ��������'...
				quoted = false;
				buf += str[i];
			}
			//	�������� ������� '���������� �������' � ����.
			//	��������� � ���������� �������
			counter_quot = 0;
		}
	}

	if (buf != "")
	{
		//	�������������� ������� ������ � ������.
		buf = UnquoteCSV(buf);
		v.push_back(buf);
	}
}

string UnquoteCSV(const string& str)
{
	///	<status> DONE </status>
	/// 
	/// <summary>
	/// ������� �� ������ ������ �������.
	/// ��� ���� ��������� ������������� �� ������ �����������:
	///		- ������ ������ ���� ��������� � �������;
	///		- ���������� ������� � ������ ������ ���� ������. 
	/// </summary>
	/// 
	/// <param name="str">
	/// �������� ������
	/// </param>
	/// 
	/// <returns>
	/// ������ ��� ������ �������.
	/// ���
	/// �������� ������, ���� ��� �� ������������� �����������.
	/// </returns>
		
	unsigned int counter_quot = 0;
	for (unsigned long long i = 0; i < str.length(); i++)
	{
		if (str[i] == '"')
		{
			counter_quot++;
		}
	}

	if (str[0] != '"' || str[str.length()-1]!='"' && counter_quot%2 != 0)
	{
		//	�� ���������� ������.
		//	������ �� ������. ������� ������� ������.
		return str;
	}

	string unquote_str;

	for (unsigned long long i = 1; i < str.length()-2; i++)
	{
		if (str[i] == '"' && str[i + 1] == '"' && i + 1 != str.length() - 1)
		{
			//	������� �������
			//	�
			//	��������� ������ �� �������
			//	�
			//	��������� ������ �� ��������� � ������ (��� �� ������ ����� �������)

			//	��������� ��� �����
			unquote_str += str[i++];	//	��������� ���� ������ � ���������� � ���������� ��������� ������
			//continue;
		}
		else
		{
			//	�������� ������ ��� ��������
			unquote_str += str[i];
		}
	}

	return unquote_str;
}

string AssemlyCSVString(const vector <string>& v, char sep )
{
	/// <status> DONE </status>
	/// 
	/// <summary>
	///		�������� ���� � ���� ������ ����� �����������.
	///		��������� ����������� �������.
	/// </summary>
	/// 
	/// <param name="v">
	/// �������� ������ ����� ����� ������.
	/// </param>
	/// <param name="sep">
	/// �����������
	/// </param>
	/// 
	/// <returns>
	/// ������ � �������������
	/// </returns>
	
	string assembly_str;

	for (unsigned int i = 0; i < v.size(); i++)
	{
		assembly_str += QuotingCSV(v[i]);
		if (i != v.size()-1)
		{
			assembly_str += sep;
		}
	}

	return assembly_str;
}

string QuotingCSV(const string& str, char sep)
{
	///	<status> DONE </status>
	/// 
	/// <summary>
	///		��������� � ������ ����������� �������.
	///		��������� ������� �� ������ ������� �������:
	///			- ������ ������ - '�������'
	///			- ������ ������ - '���� �����������' (�� ��������� '����� � �������')
	/// </summary>
	/// 
	/// <param name="str">
	///		�������� ������
	/// </param>
	/// <param name="sep">
	///		����������� �����
	/// </param>
	/// 
	/// <returns>
	///		������ � ������������ ���������
	///		���
	///		�������� ������, ���� ��� �� �������� ��������� ��������
	/// </returns>
	
	//	�������� �� ������������� ������������� �������
	bool quoting_need = false;	//	��������� ��������� �������? ���, �� ����� ���������.

	if (str.length() != 0)
	{
		for (unsigned long long i = 0; i < str.length(); i++)
		{
			if (str[i] == '"' || str[i] == sep)
			{
				//	������� ������ �� ���������� �������
				//	��������� ������ �������
				quoting_need = true;
				break;	// ��� ������ ��������� ������. �������� �����...
			}
		}
	}
	
	if (!quoting_need)
	{	
		//	��� �������� �� ���������� ������������� ���������� �������
		//	������� �������� ������ �� ����� ������
		return str;
	}

	//	���������� � ������ ����������� �������.

	string quote_str{ '"' };	//	������ ������ �������
	
	for (unsigned long long i = 0; i < str.length(); i++)
	{
		if (str[i] == '"')
		{
			//	���������� ���������� �������
			quote_str += '"';
		}
		//	����� ������ ��� ��������
		quote_str += str[i];
	}
	quote_str += '"';	//	������� ������ ���� �������

	return quote_str;
}

int main()
{
	setlocale(LC_ALL, "Russian");

	string FileName;
	//FileName = "file.csv";
	string FolderPath = "..\\Organisation";

	vector <vector <string>> v;

	FileName = "tab_in.csv";
	ReadCSVFile(v, FileName, FolderPath, ';');

	for (int row = 0; row < v.size(); row++)
	{
		for (int col = 0; col < v[row].size(); col++)
		{
			cout << v[row][col] << " * ";
		}
		cout << endl;
	}

	FileName = "tab_out.csv";
	WriteCSVFile(v, FileName, FolderPath, ';');

	return 0;
}