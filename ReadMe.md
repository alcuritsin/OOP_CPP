﻿![OOP_on_CPP](/images/OOP_CPP_git.png)

###### [Wiki](wiki) ######
###### [Todo](ToDo.md) ######

---
Содержание:

[TOC]

# Введение в ООП. #
###### 2021.03.17 ######
[repos\Intro\main.cpp](/Intro/main.cpp)

	***ООП (Object Oriented Programming)***
	это подход (парадигма - способ что-то делать), при котором программа состоит из объектов реального мира, и взаимодействия между этими объектами.

Ключевым понятием ООП является 'Объект'.

	***Объект***
	это какая-то сущность в реальном мире, которая существует в пространстве и времени. Например - ручка, телефон, человек и т.д.
	
Объекты являются экземплярами какого либо класса или структуры. Ещё говорят, что объекты принято классифицировать.

*Например:*

 	Компьютер (это класс) -- компьютер за которым мы работаем (это объект).

Класс (структура) описывает то, каким является объект. При этом объекты могут быть уникальными или идентичными.

	***Класс***
	это синтаксическая конструкция описывающая объекты.

	***Структура***
	это синтаксическая конструкция описывающая объекты.

Классы и структуры состоят из полей. Поля бывают двух типов - переменные и методы.
	
Переменные члены класса описывают, каким являются объект - характеризует какой он. Переменные члены отображают состояние объекта.

## Методы.

	***Метод***
	это функция внутри класса.

Методы определяют поведение объектов и взаимодействие их с другими объектами.

* Class
	* Data
		* Переменные члены класса.
		* Описывают характеристики объектов. Т.е. характеризуют объект.
 		* Так же могут отображать состояние объекта.
		* Это самые обычные переменные, объявленные внутри класса - структуры.
	* Method
		* Методы определяют поведение объекта и взаимодействие их (объектов) с другими объектами.
		* Метод - это функция внутри класса.

Если функция вызывается сама по себе, то метод может быть вызван только для какого-то объекта.

Чтобы хотя бы раз вызвать метод, нужно создать хотя бы один объект. 
	 
Прежде чем использовать класс, его нужно объявить и написать.

Создавая структуру или класс, мы создаём новый тип данных, а объявляя объекты этого класса или структуры - мы создаём переменные нашего типа.

Классы и структуры ещё называют пользовательскими типами данных.

	КЛАСС		- это тип данных.
	СТРУКТУРА	- это тип данных.
	ОБЪЕКТ		- это обычная переменная.

---

## Доступ к полям объекта ##
###### 2021.03.22 ######
[repos\Intro\main.cpp](/Intro/main.cpp)

Для доступа к полям объекта, можно использовать 'точку' или 'стрелку'.

	***точка (.)***
	оператор прямого доступа (Point operator). Используется для доступа к полям объекта по имени объекта.

	***стрелка (->)***
	оператор косвенного доступа (Arrov operator). Используется для доступа к полям объекта по адресу объекта.

Внутри класса невозможно узнать имя объекта, следовательно невозможно обратиться к нему по имени. Но мы всегда можем узнать адрес объекта при помощи *this*.

	***this***
	это указатель на объект, для которого вызывается метод.
	
---

## Концепции ООП. ##
###### 2021.03.22 ######
[repos\Intro\main.cpp](/Intro/main.cpp)

**ООП основана на трёх основных концепциях.**
* Инкапсуляция (Encapsulation)
* Наследование (Inharitance)
* Полиморфизм (Polimorphism)

## Инкапсуляция (Encapsulation). ##

	***Инкапсуляция***
	это сокрытие определённой части класса от внешнего мира.

Инкапсуляция реализуется модификаторами доступа и методами (**get / set**).

В языке С++ существует всего три модификатора доступа:

	* ***private***
	закрытые поля (члены) класса, доступные только изнутри класса и не доступны за его пределами. В `private` - секции класса обязательно должны находиться ПЕРЕМЕННЫЕ ЧЛЕНЫ КЛАССА. Это защищает их от случайной перезаписи.

	***public***
	открытые поля, доступные из любого места программы, где доступен объект. В `public` - секции обычно размещают методы.

	***protected***
	используется только при наследовании и открывают прямой доступ к полям только для дочерних классов. `protected` - поля доступны только внутри этого класса и его дочерних классах. `protected` частично нарушает инкапсуляцию (encapsulation).

### GET / SET - методы. ###

Это самые обычные методы, которые открывают доступ к переменным членам класса.

	***get (взять)***
	методы, открывают доступ на чтение. Т.е. позволяют взять значение переменной в классе.
 
***get - методы должны быть константными.***
 
**Константным** называется **метод**, который не изменяет объект, для которого он вызван.
 
Для константного объекта могут быть вызваны только константные методы.

	***set (задать + отфильтровать)***
	методы, открывают доступ на запись. Т.е. позволяют задать значение переменной в классе. НО кроме этого set-методы, также обеспечивают *фильтрацию данных*, если это необходимо. Т.е. предотвращают запись, не корректных значений в переменные члены класса. Фильтрация данных представляет собой if или цепочку if(-ов).

GET и SET методов в классе должно быть ровно столько, сколько переменных членов в классе.

	***Отличие между классом и структурой***
	единственным отличием между классом и структурой, является то что в классе (по умолчанию) все поля **закрытые** (**private**), а в структуре все поля **открытые** (**public**).

***Инкапсуляция защищает наши объекты от случайного изменения и от записи в них не корректных значений.***

## Наследование (Inharitance). ##

Это способность классов наследовать свойства других классов. Под свойствами, в данном случае, понимаются переменные и методы.

*Например:*

	- Машина, является транспортным средством и наследует все свойства транспортного средства.
	- Велосипед, также является транспортным средством, и наследует все его свойства.
	- Мусоровоз является машиной, и соответственно наследует все свойства обычной машины.

## Полиморфизм (Polimorphism). ##

Это способность объектов вести себя по разному, в зависимости от обстоятельств. Или же в зависимости от того кем они являются.

	Полиморфизм - многоформенность.

---

## Обязательные методы в классах. ##
###### 2021.03.22 ######
[repos\Intro\main.cpp](/Intro/main.cpp)

В классе обязательно должны быть ***конструктор*** - ***деструктор*** - ***оператор присваивания***.

	***Конструктор (constructor)***
	это метод, который создаёт объект. Т.е. выделяет память под объект и инициализирует его поля при создании.

	***Деструктор (destructor)***
	это метод, который уничтожает объект по истечении его времени жизни. Время жизни объекта истекает когда завершается область видимости, в которой он объявлен. Например, когда объект является параметром или локальной переменной функции или for или любых фигурных скобок.

Конструктор и деструктор всегда называются так же как и класс. И никогда не возвращают никаких значений. При этом, перед ними не пишется ключевое слово 'void'. Но перед деструктором ставится '~' (тильда).

*Например:*

~~~c++
	class Class
	{
		Class ()
		{
			//Конструктор (constructor)
		}
		~Class()
		{
			//Деструктор (destructor)
		}
	}
~~~

Конструктор может принимать параметры и его можно перегрузить, как и любую другую функцию. Поэтому в классе может быть сколько угодно конструкторов.

Деструктор никогда не принимает никаких параметров. Поэтому его нельзя перегрузить. Деструктор в классе может быть **только один**.

### Конструкторы. ###

***Конструкторы бывают:***
* по умолчанию
* без параметров
* [с одним параметром](#Singl-argumentConstructor)
* с параметрами
* конструктор копирования
* конструктор переноса

#### Конструктор по умолчанию. ####

	***Конструктор по умолчанию***
	это конструктор, который может быть вызван без параметров.
	* Это может быть конструктор, не принимающий никаких параметров.
	* Конструктор, каждый параметр которого имеет значение по умолчанию.

Конструктор по умолчанию выделяет память под объект и инициализирует его поля некоторыми значениями по умолчанию.

Конструктор по умолчанию может быть не явным, т.е. если в классе нет ни одного конструктора, то компилятор сам добавить туда конструктор по умолчанию. Без конструктора не может быть создан ни один объект.

Конструктор по умолчанию добавленный компилятором называют **не явным**. Не явный конструктор по умолчанию, инициализирует переменные члены класса мусором.

Конструктор по умолчанию, вызывается всякий раз, когда мы создаём объект, но не знаем какой он должен быть, т.е. не знаем что в него нужно записать.

*Например:*

~~~c++
void main()
{
	...
	Point B;	//Default constructor

	...
}
~~~

---

<a name="Singl-argumentConstructor"></a>
#### Конструктор с одним параметром (Singl-argument). ####
###### 2021.03.24 ######
[repos\Intro\main.cpp](/Intro/main.cpp)

Важность конструктора с одним параметром заключается в том что он необходим для преобразования типов.

*Например:*
~~~c++
void main()
{
	...
	Point E = 5;	//Singl-argument constructor
	Point F(5);	//Singl-argument constructor
	Point G{ 5 };	//Singl-argument constructor
	...
}
~~~

*Singl-argument constructor* преобразует другие типы в наш тип.

Конструктор может принимать сколько угодно параметров, это ничем не ограничивается.

*Например:*
~~~c++
class Point
{
...
public:
...
	// Constructors
	...
	Point(double x = 0, double y = 0)
	{
	//Этот конструктор с параметрами может быть вызван:
		// - без параметров;
		// - с одним параметром;
		// - с двумя параметрами.

		this->x = x;
		this->y = y;
		std::cout << "Constructor:\t\t" << this << std::endl;
	}
	...
};
~~~

#### Конструктор копирования. ####

	***Конструктор копирования***
	это конструктор, который копирует объект, точную копию объекта. Вызывается всякий раз, когда нужно сделать объект точной копией существующего объекта.

Конструктор копирования особенно важен, когда в классе используется **динамическая память**. Он предотвращает ситуацию, когда два и более объекта используют одну и туже область динамической памяти.

Если конструктора копирования в классе нет, то компилятор сам его добавит. Но такой, не явный конструктор копирования, не всегда будет работать корректно. Если членом класса является указатель, то не явный конструктор копирования просто скопирует адрес из одного объекта в другой. Тогда, два объекта, будут использовать одну и туже область динамической памяти. Это может привести к очень плохим последствиям. Поэтому когда в классе используется динамическая память, конструктор копирования обязательно должен быть реализован.

**Конструктор копирования:**
* выделяет память под объект;
* выполняет побитовое копирование -  т.е. копирует содержимое динамической памяти из существующего объекта в создоваемый.

Под побитовым копированием называют поэлементное копирование памяти c использованием цикла `for`.

Конструктор копирования всегда принимает **константную** ссылку на объект нашего класса.

*Например:*
~~~c++
class Point
{
...
public:
...
	// Constructors
	...
	Point(const Point& other)
	{
		//other - это другой объект копию, которого мы создам
		this->x = other.x;
		this->y = other.y;
	}
	...
};
~~~

Конструктор копирования может быть вызван явно, когда мы создаём объект и инициализируем его другим объектом.

*Например:*
~~~c++
void main()
{
...
	Point X = E; //CopyConstructor. Здесть мы создаём объект X, и инициализируем его другим объектом.
...
}
~~~

Когда мы передаём объект в функцию по значению, тогда значение объекта копируется в функцию. Для того чтобы скопировать объект, не явно вызывается конструктор копирования. 

Оператор присваивания, делает тоже самое, что и конструктор копирования, но с существующим объектом. 

После создания объекта конструктор копирования вызвать невозможно, так как объект уже создан. Если его необходимо сделать точной копией другого объекта, то вызывается оператор присвоить.

*Например:*
~~~c++
void main()
{
...
	Point F = E; //CopyConstructor. Здесть мы создаём объект X, и инициализируем его другим объектом.
...
}
~~~

Оператор присвоить так же всегда принимает ***константную*** ссылку на объект нашего класса.

*Например:*
~~~c++
class Point
{
...
public:
...
	// Operartors
	...
	void operator=(const Point& other)
	{
		this->x = other.x;
		this->y = other.y;
		std::cout << "CopyAssignment:\t" << std::endl;
	}
	...
};
~~~

---
##  ##
###### 2021.03.25 ######
[repos\Intro\main.cpp](/Intro/main.cpp)

---
[Me]: <https://github.com/alcuritsin/OOP_CPP/ReadMe.md>
