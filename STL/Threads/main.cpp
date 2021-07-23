#include <iostream>
#include <thread>
#include <Windows.h>

using namespace std;
using namespace std::literals::chrono_literals;

using std::cout;
using std::cin;
using std::endl;

bool finish = false;

void hello()
{
	while (!finish)
	{
		cout << " Hello ";
		Sleep(1000);
		//std::this_thread::sleep_for(1s);
	}
}

void world()
{
	while (!finish)
	{
		cout <<  " World ";
		std::this_thread::sleep_for(1s);
	}
}

void main()
{
	setlocale(LC_ALL, "Russian");

		std::thread thread_hello(hello);
		std::thread thread_world(world);

		std::cin.get();	// Ожидает нажатие клавиши ентер
		finish = true;

		thread_world.join();
		thread_world.join();
}