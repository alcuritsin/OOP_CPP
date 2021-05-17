#include <iostream>
using namespace std;

using std::cout;
using std::endl;

#define DELIMETR "-----------------------------------"

class Vehicle	//	Странспорт
{
	//	Абстрактный класс
	int speed;
public:
	virtual void move() = 0;	//	Чисто виртуальная функция
};

class AirVehicle:public Vehicle
{
	//	Абстрактный класс
	int height;
public:
	virtual void takeoff() = 0;
	virtual void land() = 0;
};

class Airplain : public AirVehicle
{
	//	Конкретный класс
public:
	void takeoff()
	{
		cout << "Для взлета нужна взлетная полоса." << endl;
		cout << "Взлетаем." << endl;
	}
	void move()
	{
		cout << "Летит по воздуху." << endl;
	}
	void land()
	{
		cout << "Для посадки нужна взлетная полоса." << endl;
		cout << "Захожу на посадку." << endl;
	}

};

class HeliCopter :public AirVehicle
{
public:
	void takeoff()
	{
		cout << "Могу взлететь где угодно." << endl;
	}
	void move()
	{
		cout << "Плавно перемещаюсь по воздуху." << endl;
	}
	void land()
	{
		cout << "Могу сесть в поле." << endl;
	}

};

class LandVehicle :public Vehicle
{
public:

};

class Car :public LandVehicle
{
public:
	void move()
	{
		cout << "Едет по дороге на четырёх колёсах." << endl;
	}
};

class Bike :public LandVehicle
{
public:
	void move()
	{
		cout << "Едет по дороге на двух колесах." << endl;
	}
};

class WatherVehicle :public Vehicle
{
public:
	void move()
	{
		cout << "Хожу по воде." << endl;
	}

};

class Boat :public WatherVehicle
{
public:
};

void main()
{
	setlocale(LC_ALL, "Russian");
	//	Vehicle v;	//	Невозможно создать экземпляр абстрактного класса
	//	AirVehicle aV;	//	Этот класс также является абстрактным,
						//	поскольку наследует чисто виртуальный метод 'move' базового класса.
						//	и не реализует его.
	Airplain playn;

	playn.takeoff();
	playn.move();
	playn.land();

	cout << DELIMETR << endl;

	HeliCopter chopper;
	chopper.takeoff();
	chopper.move();
	chopper.land();

	cout << DELIMETR << endl;

	Car car;
	car.move();

	cout << DELIMETR << endl;
	Bike bike;
	bike.move();

	cout << DELIMETR << endl;
	Boat boat;
	boat.move();

}