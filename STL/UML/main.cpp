#include<iostream>
#include<conio.h>
#include<Windows.h>

using namespace std;

#define esc 27
#define space 32

const unsigned int DEFAULT_TANK_VOLUME = 60;

const double DEFAULT_CONSAMPTION = 8;

const unsigned int DEFAULT_MAX_SPEED = 250;

enum ConsoleColor {
	Black = 0,
	Blue = 1,
	Green = 2,
	Cyan = 3,
	Red = 4,
	Magenta = 5,
	Brown = 6,
	LightGray = 7,
	DarkGray = 8,
	LightBlue = 9,
	LightGreen = 10,
	LightCyan = 11,
	LightRed = 12,
	LightMagenta = 13,
	Yellow = 14,
	White = 15
};

class Tank
{
	//	Топливный бак:
	const unsigned int VOLUME;	//	объём бака
	double fuel_level;	//	уровень топлива
public:
	unsigned int get_volume() const
	{
		return VOLUME;
	}
	double get_fuel_level() const
	{
		return fuel_level;
	}
	void fill(double amount)
	{
		//	amount - количество топлива.
		if (amount < 0) return;
		if (fuel_level + amount < VOLUME) fuel_level += amount;
		else fuel_level = VOLUME;
	}
	double give_fuel(double amount)
	{
		if (fuel_level - amount > 0) fuel_level -= amount;
		else fuel_level = 0;
		return fuel_level;
	}
	Tank(const unsigned int VOLUME) :VOLUME(VOLUME >= 20 && VOLUME <= 80 ? VOLUME : DEFAULT_TANK_VOLUME), fuel_level(0)
	{
		cout << "Tank is ready:\t" << this << endl;
	}
	~Tank()
	{
		cout << "Tank is over:\t" << this << endl;

	}
	void info() const
	{
		cout << "VOLUME: " << VOLUME << endl;
		cout << "fuel_level:" << fuel_level << endl;
	}
private:

};

class Engine
{
	//	Это класс описывающий двигатель

	const double CONSUMPTION;	//	расход на 100 км
	double consumtion_per_second;	//	расход за одну секунду

	bool started;	//	состояние заведён выключен
public:
	const double get_consumption() const
	{
		return CONSUMPTION;
	}
	double get_consumption_per_second() const
	{
		return consumtion_per_second;
	}
	bool is_started() const
	{
		return started;
	}

	void start()
	{
		started = true;
	}
	void stop()
	{
		started = false;
	}
	Engine(double consumption) :CONSUMPTION(consumption >= 4 && consumption <= 25 ? consumption : DEFAULT_CONSAMPTION)
	{
		this->consumtion_per_second = this->CONSUMPTION * 5e-5;
		started = false;
		cout << "Emgine is ready:\t" << this << endl;
	}
	~Engine()
	{
		cout << "Engine is over:\t" << this << endl;
	}
	void info()const
	{
		cout << "Engine consumes " << CONSUMPTION << " liters per 100 rm" << endl;
		cout << "Engine consumes " << consumtion_per_second << " liters per 1 second in idel" << endl;
		cout << "Engine is " << (started ? "started" : "stoped") << endl;
	}
};

class Car
{
	Tank tank;
	Engine engine;

	bool in_car;
	unsigned int speed;
	unsigned int MAX_SPEED;


public:
	Car(unsigned int MAX_SPEED) :
		speed(0),
		MAX_SPEED(MAX_SPEED >= 100 && MAX_SPEED <= 350 ? MAX_SPEED : DEFAULT_MAX_SPEED),
		engine(this->MAX_SPEED / 15),
		tank(this->MAX_SPEED / 5),
		in_car(false)
	{

	}

	Car(double engine_consumption, unsigned int tank_volume, unsigned int MAX_SPEED = DEFAULT_MAX_SPEED) :
		engine(engine_consumption), tank(tank_volume),
		speed(0), MAX_SPEED(MAX_SPEED >= 100 && MAX_SPEED <= 350 ? MAX_SPEED : DEFAULT_MAX_SPEED),
		in_car(false)
	{
		cout << "Your car ready to go. Press `Enter` to get in\t" << this << endl;
		cout << "No fuel. Need fill.\t" << this << endl;
	}

	~Car()
	{
		if (engine.is_started())
		{
			engine.stop();
		}
		if (in_car)
		{
			set_out();
		}
		cout << "Your car is over :-(\t" << this << endl;
	}
	bool get_in_car() const
	{
		return in_car;
	}
	bool is_started()
	{
		if (engine.is_started())
		{
			return true;
		}

		return false;
	}

	void set_in()
	{
		if (!in_car)
		{
			in_car = true;
			cout << "You got into the car. Press `s` to start engine..." << endl;	//	Вы сели в машину
		}
		else
		{
			cout << "You're already in the car." << endl;	//	Вы уже в машине
		}
	}

	void set_out()
	{
		if (in_car)
		{
			if (engine.is_started())
			{
				engine.stop();	//	Если двигтель заведён. При попвтке выхода он заглохнет.
				//	Или тут можно выдавать предупреждение что двигатель заведён. Действительно ли вы хотите выйти... :)
			}
			in_car = false;
			cout << "You got out of the car." << endl;	//	Вы вышли из машины
		}
		else
		{
			cout << "So you're outside." << endl;	//	Вы итак снаружи
		}
	}

	void start()
	{
		if (!this->engine.is_started() && this->tank.get_fuel_level() >= this->engine.get_consumption_per_second())
		{
			idle();
			this->engine.start();
			cout << "Engine start. Vroom-Vroom!" << endl;	//	Двигатель заведён.
			cout << "Pres 0-9 to gas up. OR Pres any key to update." << endl;
			cout << "Esc - for stop." << endl;
		}
		else
		{
			idle();
			cout << "Your engine is already running. Krikl!" << endl;	//	Ваш двигатель уже работает. Хрусть.
		}
	}

	void stop()
	{
		if (this->engine.is_started())
		{
			if (tank.get_fuel_level() >= engine.get_consumption_per_second())
			{
				idle();	//	Расход на холостом ходу при получении команды стоп.
			}
			this->engine.stop();
			cout << "\nEngine stoped." << endl;	//	Двигатель заглушен.
		}
		else
		{
			cout << "Your engine is already turned off." << endl;	//	Ваш двигатель уже заглушен.
		}
	}

	void press_gas_pedal(int volume)
	{
		if (!is_started())return;
		//	Допстим педаль можно нажать на максимум 10.
		//	Т.е. макимальный объем топлива израсходованый при нажатии будет edle * 10.
		if (volume <= 0)
		{
			idle();
			return;
		}
		else
		{
			/*Получаение дескриптора устройства стандартного вывода*/
			HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
			for (size_t i = 0; i < (volume >= 10 ? 10 : volume); i++)
			{

				/*Установка белого фона за отдельным символом. Цвет символа - черный*/
				//SetConsoleTextAttribute(hConsole, (WORD)((цвет фона << 4) | цвет символа));

				switch (i)
				{
				case 0: case 1: case 2:
					SetConsoleTextAttribute(hConsole, (WORD)((Black << 4) | White));
					break;
				case 3: case 4: case 5:
					SetConsoleTextAttribute(hConsole, (WORD)((Black << 4) | Green));
					break;
				case 6: case 7:
					SetConsoleTextAttribute(hConsole, (WORD)((Black << 4) | Yellow));
					break;
				case 8:
					SetConsoleTextAttribute(hConsole, (WORD)((Black << 4) | Red));
					break;
				case 9:
					SetConsoleTextAttribute(hConsole, (WORD)((Red << 4) | Black));
					break;
				default:
					break;
				}

				idle();
				if (is_started())
				{
					cout << "Vrun. ";
					Sleep(100);
				}
				else
				{
					break;
				}

			}
			SetConsoleTextAttribute(hConsole, (WORD)((Black << 4) | White));
			cout << endl;
		}
	}

	void fill(double amount)
	{
		tank.fill(amount);
	}

	void info()
	{
		if (is_started())
		{
			idle();	//	Расход на холостом ходу. Поэтому метод не константный.
		}
		tank.info();
		cout << endl;
		engine.info();
		cout << endl;
		cout << "Max speed:\t" << MAX_SPEED << " km/h" << endl;
		cout << "Current speed:\t" << speed << " km/h" << endl;
		cout << (in_car ? "You in car." : "Are you outside.") << endl;
	}

private:
	void idle()
	{
		if (engine.is_started() && tank.get_fuel_level() >= engine.get_consumption_per_second())
		{
			tank.give_fuel(engine.get_consumption_per_second());
		}
		else
		{
			stop();
			cout << "We ran out of fuel." << endl;	//	Закончилось топливо.
		}
	}
};

//#define TANK_CHECK
//#define ENGINE_CHECK
#define IDLE_CHECK

void main()
{
	setlocale(LC_ALL, "Russian");

#ifdef TANK_CHECK
	Tank tank(11);
	tank.info();

	tank.fill(3);
	tank.info();

	tank.fill(30);
	tank.info();

	tank.fill(30);
	tank.info();
#endif // TANK_CHECK

#ifdef ENGINE_CHECK
	Engine engine(6);
	engine.info();

	engine.start();
	engine.info();

#endif // ENGINE_CHECK


#ifdef IDLE_CHECK
	Car car(11, 11);
	cout << endl; car.info();

	double fuel_quantity;
	cout << "\nRefill.\nFuel quantity: "; cin >> fuel_quantity;
	car.fill(fuel_quantity);

	cout << endl; car.info();

	if (_getch() == 13)
	{
		car.set_in();
	}
	cout << endl; car.info();

	int key = _getch();
	if (car.get_in_car() && (key == (int)'s' || key == (int)'S' || key == (int)'ы' || key == (int)'Ы'))
	{
		car.start();
	}
	cout << endl; car.info();


	if (car.is_started())
	{
		Sleep(1000);
		system("CLS");
		do
		{
			car.info();
			cout << "\nМожно погазовать!" << endl;
			cout << "Pres 0-9 to gas up. OR Pres any key to update." << endl;
			cout << "Esc - for stop." << endl;

			key = _getch();
			if (key >= 48 && key <= 57)
			{

				car.press_gas_pedal(key - 47);
			}
			else if (key != esc)
			{
				car.info();
			}

			//cout << key << endl;
			cout << endl;

			//Sleep(500);
			//system("CLS");
		} while (key != esc && car.is_started());
		car.stop();
	}
	cout << endl; car.info();
#endif // IDLE_CHECK

}
