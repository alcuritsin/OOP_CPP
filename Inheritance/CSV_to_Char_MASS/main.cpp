#include <iostream>
#include <fstream>

using namespace std;

int main()
{

	const int len = 30, strings = 5;
	const char ch = '\n';
	char mass[len][strings];

	ifstream fs("..\\Organisation\\file.csv", ios::in | ios::binary);

	if (!fs) return 1; //���� ������ �������� �����, �� ��������� ���������

	for (int r = 0; r < strings; r++)
	{
		fs.getline(mass[r], len - 1, ch); //��������� ������ � ������
		cout << "String " << r + 1 << " = " << mass[r] << endl; //������ ������ �� �������
	}
	fs.close(); //��������� ����
	return 0;
}