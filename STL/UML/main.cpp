#include<iostream>
#include<conio.h>
#include<Windows.h>
#include<thread>

#include<vector>

using namespace std;

using std::cout;
using std::cin;
using std::endl;


enum Keys
{
	Esc = 27,
	Space = 32,
	Enter = 13,
	ArrowUp = 72,
	ArrowDown = 80,
	ArrowLeft = 75,
	ArrowRight = 77
};


const unsigned int DEFAULT_TANK_VOLUME = 60;

const double DEFAULT_CONSAMPTION = 8;

const unsigned int DEFAULT_MAX_SPEED = 250;

const unsigned int MIN_FUEL_LEVEL = 5;

const unsigned int DEFFAULT_ACCELERATION = 5;

//	Консольные цвета. Для разнообразия.
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
	void set_consumption_per_second(double consumption)
	{
		if (consumption >= 0.0003 && consumption <= 0.003)
		{
			this->consumtion_per_second = consumption;
		}
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
	CarDashboard car_dashboard;

	bool driver_inside;

	unsigned int speed;
	unsigned int MAX_SPEED;
	unsigned int accelleration;

	struct Control
	{
		std::thread main_thread;
		std::thread panel_thread;
		std::thread idel_thread;
		std::thread free_wheeling_thread;
	} control;
public:
	Car(unsigned int MAX_SPEED) :
		speed(0),
		MAX_SPEED(MAX_SPEED >= 100 && MAX_SPEED <= 350 ? MAX_SPEED : DEFAULT_MAX_SPEED),
		engine(this->MAX_SPEED / 15),
		tank(this->MAX_SPEED / 5),
		driver_inside(false)
	{

	}

	Car(double engine_consumption, unsigned int tank_volume, unsigned int MAX_SPEED = DEFAULT_MAX_SPEED) :
		engine(engine_consumption), tank(tank_volume),
		speed(0), MAX_SPEED(MAX_SPEED >= 100 && MAX_SPEED <= 350 ? MAX_SPEED : DEFAULT_MAX_SPEED),
		driver_inside(false), accelleration(5)
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
		if (driver_inside)
		{
			get_out();
		}
		cout << "Your car is over :-(\t" << this << endl;
	}
	bool get_in_car() const
	{
		return driver_inside;
	}

	bool is_started()
	{
		if (engine.is_started())
		{
			return true;
		}

		return false;
	}

	void get_in()
	{
		if (!driver_inside)
		{
			driver_inside = true;
			cout << "You got into the car. Press `s` to start engine..." << endl;	//	Вы сели в машину
			control.panel_thread = thread(&Car::panel, this);
		}
		else
		{
			cout << "You're already in the car." << endl;	//	Вы уже в машине
		}
	}

	void get_out()
	{
		if (driver_inside)
		{
			if (engine.is_started())
			{
				engine.stop();	//	Если двигтель заведён. При попвтке выхода он заглохнет.
				//	Или тут можно выдавать предупреждение что двигатель заведён. Действительно ли вы хотите выйти... :)
			}

			driver_inside = false;

			cout << "You got out of the car." << endl;	//	Вы вышли из машины
			if (control.panel_thread.joinable())
			{
				control.panel_thread.join();
			}
		}
		else
		{
			cout << "So you're outside." << endl;	//	Вы итак снаружи
		}
	}

	void start()
	{
		if (driver_inside && tank.get_fuel_level() > 0)
		{
			engine.start();
			control.idel_thread = thread(&Car::engine_idle, this);
		}

		//if (!this->engine.is_started() && this->tank.get_fuel_level() >= this->engine.get_consumption_per_second())
		//{
		//	idle();
		//	this->engine.start();
		//	cout << "Engine start. Vroom-Vroom!" << endl;	//	Двигатель заведён.
		//	cout << "Pres 0-9 to gas up. OR Pres any key to update." << endl;
		//	cout << "Esc - for stop." << endl;
		//}
		//else
		//{
		//	idle();
		//	cout << "Your engine is already running. Krikl!" << endl;	//	Ваш двигатель уже работает. Хрусть.
		//}
	}

	void stop()
	{
		engine.stop();
		if (control.idel_thread.joinable())
		{
			control.idel_thread.join();
		}
		//if (this->engine.is_started())
		//{
		//	if (tank.get_fuel_level() >= engine.get_consumption_per_second())
		//	{
		//		idle();	//	Расход на холостом ходу при получении команды стоп.
		//	}
		//	this->engine.stop();
		//	cout << "\nEngine stoped." << endl;	//	Двигатель заглушен.
		//}
		//else
		//{
		//	cout << "Your engine is already turned off." << endl;	//	Ваш двигатель уже заглушен.
		//}
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

	void engine_idle()
	{
		while (tank.give_fuel(engine.get_consumption_per_second()))
		{
			std::this_thread::sleep_for(1s);
		}
		engine.stop();
	}
	void free_wheeling()
	{
		while (speed > 0)
		{
			speed--;
			if (speed < 0)
			{
				speed = 0;
			}
			this_thread::sleep_for(1s);
		}
	}

	void accelerate()
	{
		if (engine.is_started() && speed < MAX_SPEED)
		{
			speed += accelleration;
			if (control.free_wheeling_thread.get_id() == std::thread::id())
			{
				control.free_wheeling_thread = std::thread(&Car::free_wheeling, this);
			}
			adjust_consumption();
		}
		this_thread::sleep_for(1s);
	}
	void slow_down()
	{
		if (speed > 0)
		{
			speed -= accelleration;
			if (speed < accelleration)
			{
				speed = 0;
				if (control.free_wheeling_thread.joinable())
				{
					control.free_wheeling_thread.join();
				}
			}
			adjust_consumption();
		}
		this_thread::sleep_for(1s);
	}

	void adjust_consumption()
	{
		if (speed > 0 && speed <= 60)
		{
			engine.set_consumption_per_second(0.002);
		}
		else if (speed >60 && speed <=100)
		{
			engine.set_consumption_per_second(0.0014);

		}
		else if (speed >100 && speed <=140)
		{
			engine.set_consumption_per_second(0.002);

		}
		else if (speed >140 && speed <=200)
		{
			engine.set_consumption_per_second(0.0025);

		}
		else if (speed >200)
		{
			engine.set_consumption_per_second(0.0030);
		}
		else if (speed ==0 )
		{
			engine.set_consumption_per_second(engine.get_consumption()*5e-5);
		}
	}

	void control_car()
	{
		char key = _getch();
		do
		{
			switch (key)
			{
			case Enter:	//	Вход выход из машины
				if (driver_inside)
				{
					get_in();
				}
				else
				{
					get_out();
				}
				break;

			case 'I': case 'i':	//	Завести/остановить
				if (engine.is_started())
				{
					stop();
				}
				else
				{
					start();
				}
				break;
			case 'F': case 'f':	//	Заправка
				double amount;
				cout << "How mutch:"; cin >> amount;
				tank.fill(amount);
				break;
			case 'W': case 'w':	//	Газулька
			case ArrowUp:
				break;

			case 'S': case 's':	//	Тормоз
			case ArrowDown: case Space:
				break;

			case Esc:
				get_out();
				break;
			default:
				break;
			}

			if (tank.get_fuel_level() == 0 && control.idel_thread.joinable())
			{
				control.idel_thread.join();
			}
		} while (key != Esc);
	}

	void panel() const
	{
		while (driver_inside)
		{
			system("CLS");
			cout << "Engine is " << (engine.is_started() ? "started" : "stoped") << endl;
			cout << "Fuel level: " << tank.get_fuel_level() << endl;
			if (tank.get_fuel_level() < MIN_FUEL_LEVEL)
			{
				cout << "Fuel low." << endl;
			}
			cout << "Spiid: " << speed << endl;
		}
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
		cout << (driver_inside ? "You in car." : "Are you outside.") << endl;
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

class CarDashboard
{
public:
	CarDashboard()
	{

	}
	~CarDashboard()
	{

	}

	void Board()
	{
		char board[] =
		{
			' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', '\n',
			' ', 201, 205, 205, 205, 205, 205, 205, 205, 205, 205, 205, 205, 187, ' ', '\n',
			' ', 186, ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', 186, ' ', '\n',
			' ', 200, 205, 205, 205, 205, 205, 205, 205, 205, 205, 205, 205, 188, ' ', '\n',
			' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', '\0'
		};

		to_panel(board, 0, 0);
	}

	void FuelLevel(double level)
	{
		//	Датчик уровня топлива
		//	Начальные координаты вывода от верхнего правого угла.
		int x = 5;	//	По горизонтали (колонка)
		int y = 5;	//	По вертикали (строка)

		int _level = level * 100000;

		char ch1 = _level / 10000000 + 48;
		char ch2 = _level / 1000000 % 10 + 48;
		char ch3 = _level / 100000 % 10 + 48;

		char ch4 = _level / 10000 % 10 + 48;
		char ch5 = _level / 1000 % 10 + 48;
		char ch6 = _level / 100 % 10 + 48;
		char ch7 = _level / 10 % 10 + 48;
		char ch8 = _level % 10 + 48;

		//	Формирование шаблона
		//	размеры экранчика:
		//	x +15
		//	y +4
		char fuel_level[] =
		{
			' ', ' ', ' ', ' ', 'F', ' ', 'U', ' ', 'E', ' ', 'L', ' ', ' ', ' ', ' ', '\n',
			' ', 201, 205, 205, 205, 205, 205, 205, 205, 205, 205, 205, 205, 187, ' ', '\n',
			' ', 186, ' ', ch1, ch2, ch3, '.', ch4, ch5, ch6, ch7, ch8, ' ', 186, ' ', '\n',
			' ', 200, 205, 205, 205, 205, 205, 205, 205, 205, 205, 205, 205, 188, ' ', '\0'
		};

		//	Вывод на панель, по координатам

		to_panel(fuel_level, x, y);
	}

	void Speedometer(double speed)
	{
		//	Датчик уровня топлива
		//	Начальные координаты вывода от верхнего правого угла.
		int x = 30;	//	По горизонтали (колонка)
		int y = 5;	//	По вертикали (строка)

		int _speed = speed * 1000;

		char ch1 = _speed / 1000 + 48;
		char ch2 = _speed / 100 % 10 + 48;
		char ch3 = _speed / 10 % 10 + 48;

		char ch4 = _speed % 10 + 48;

		//	Формирование шаблона
		//	размеры экранчика:
		//	x +17
		//	y +4

		char speed_value[] =
		{
			' ', ' ', ' ', ' ', 'S', ' ', 'P', ' ', 'E', ' ', 'E', ' ', 'D', ' ', ' ', ' ', ' ', '\n',
			' ', 201, 205, 205, 205, 205, 205, 205, 205, 205, 205, 205, 205, 205, 205, 187, ' ', '\n',
			' ', 186, 30,  ' ', ch1, ch2, ch3, '.', ch4, ' ', 'K', 'm', '/', 'h', ' ', 186, ' ', '\n',
			' ', 200, 205, 205, 205, 205, 205, 205, 205, 205, 205, 205, 205, 205, 205, 188, ' ', '\0'
		};

		//	Вывод на панель, по координатам
		to_panel(speed_value, x, y);
	}

	void to_panel(char* str, int x, int y)
	{
		setlocale(LC_ALL, "C");	//	Меняем кодировку для того чтобы появились Ascci символы.

		//	Установка курсора на координату
		gotoxy(x, y);

		size_t index = 0;	//	Индекс для того чтобы бежать по массиву char
		do
		{
			if (str[index] == '\n')
			{
				y++;
				gotoxy(x, y);
			}
			else
			{
				cout << str[index];
			}
			index++;

		} while (str[index] != '\0');

		setlocale(LC_ALL, "ru-Ru");	//	Возвращаем на руский.
	}

	void gotoxy(int x, int y)
	{
		COORD coord;
		coord.X = x;
		coord.Y = y;
		SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
	}
};

//#define TANK_CHECK
//#define ENGINE_CHECK
//#define IDLE_CHECK
//#define PANEL_CHECK

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
	Car car(8, 40);
	cout << endl; car.info();

	double fuel_quantity;
	cout << "\nRefill.\nFuel quantity: "; cin >> fuel_quantity;
	car.fill(fuel_quantity);

	cout << endl; car.info();

	if (_getch() == 13)
	{
		car.get_in();
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
			else if (key != Escape)
			{
				car.info();
			}

			//cout << key << endl;
			cout << endl;

			//Sleep(500);
			//system("CLS");
		} while (key != Escape && car.is_started());
		car.stop();
	}
	cout << endl; car.info();
#endif // IDLE_CHECK
	//for (size_t i = 0; i < 255; i++)
	//{
	//	cout << (char)i << i << "  ";
	//}

#ifdef PANEL_CHECK
	CarDashboard _dashboard;
	_dashboard.Board();
	_dashboard.FuelLevel(123.456789);
	_dashboard.Speedometer(123.456);
#endif // PANEL_CHECK


	Car car(8, 40);
	car.info();
	car.control_car();

	//cout << str1 << endl;
}


