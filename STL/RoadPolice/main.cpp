#include<iostream>
#include<map>
#include<list>
#include<string>

using std::cout;
using std::cin;
using std::endl;

const std::string base_file = "receipt.db";

class BaseReceipt
{
	std::map<std::string, std::list<std::string>> base;
	//	а000аа
	//		- квитанция 1
	//		- квитанция 2
	//		- квитанция n
public:
	BaseReceipt();
	~BaseReceipt();

	//	Methods:
void NewRecept(const std::string& vehicle_number, const std::string receipt)
{
	if (base.find(vehicle_number) != base.end())
	{
		//	Если Номер ТС обнаружен в базе, то добавляем только штраф
	}
	else
	{
		// Иначе добавляем новый номер ТС, и добавляем к нему штраф
	}
}

private:

};

BaseReceipt::BaseReceipt()
{
}

BaseReceipt::~BaseReceipt()
{
}



void WriteBase(BaseReceipt& base)
{

}

void ReadBase(BaseReceipt& base)
{

}

void Print()
{

}

void PrintByNumber(const std::string vehicle_number)
{

}

void PrintRange(const std::string& begin_vehicle_number, const std::string& end_vehicle_number)
{

}

void main()
{
	setlocale(LC_ALL, "Russian");

	BaseReceipt base;

	//	Ввод штрафа:
	std::string vehicle_number;	//	Номер транспортного средства
	std::string receipt; //	Квитанция

	cout << ":: Новый штраф ::" << endl;
	cout << "Номер ТС: "; cin >> vehicle_number;
	cout << "   Штраф: "; cin >> receipt;

	base.NewRecept(vehicle_number, receipt);

}

/*
Задание 1.
Реализовать базу данных ГАИ по штрафным квитанциям
с помощью бинарного дерева. Ключом будет служить
номер автомашины, значением узла — список правонарушений. Если квитанция добавляется в первый раз,
то в дереве появляется новый узел, а в списке данные
по правонарушению; если нет, то данные заносятся в существующий список. Необходимо также реализовать
следующие операции:

■ Полная распечатка базы данных (по номерам машин и списку правонарушений, числящихся за ними);
■ Распечатка данных по заданному номеру;
■ Распечатка данных по диапазону номеров;
■ Сохраняйте и загружайте информацию из файла
*/