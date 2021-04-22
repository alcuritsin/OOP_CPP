#include "Fraction.h"

//#define DEBUG
//#define CONSTRUCTORS_CHECK	//	Проверка конструкторов/деструкторов
//#define PROPER_IMPROPER_REDUCE	//	Методы: `to_proper(); to_improper(); reduce();`
//#define ARITHMETIC_CHECK	//	Арифметические операции
//#define COMPOUND_ASSIGNMENT	//	Составные присваивания
//#define INCREMENT_DECREMENT	//	Инкремент / Декримент
//#define COMPARISON	// Сравнение
#define TYPE_CONVERSIONS

	//	Точка входа :)
void main()
{
	setlocale(LC_ALL, "Russian");

	//	Проверка конструкторов/деструкторов
#ifdef CONSTRUCTORS_CHECK
	Fraction A;
	std::cout << A << std::endl;

	Fraction B = -5;
	std::cout << B << std::endl;

	Fraction C(1, -2);
	std::cout << C << std::endl;

	Fraction D(2, 3, -4);
	std::cout << D << std::endl;
#endif // CONSTRUCTORS_CHECK

	//	Методы: `to_proper(); to_improper(); reduce();`
#ifdef PROPER_IMPROPER_REDUCE	//	Методы: `to_proper(); to_improper(); reduce();`
	Fraction A(-2,18, 36);

	std::cout << A << " = ";
	std::cout << (A.to_proper()) << std::endl;
	std::cout << A << " = ";
	std::cout << (A.to_improper()) << std::endl;
	std::cout << A << " = ";
	std::cout << (A.reduce()) << std::endl;
#endif // PROPER_IMPROPER_REDUCE

	//	Арифметические операции
#ifdef ARITHMETIC_CHECK
	Fraction A(2, 3, 4);
	Fraction B(5, 6, 7);

	std::cout << "A = " << A << "\tB = " << B << std::endl << std::endl;

	std::cout << "A + B\t-->>\t" << A << " + " << B << " = " << (A + B) << std::endl;
	std::cout << "B - B\t-->>\t" << B << " - " << B << " = " << (B - B) << std::endl;
	std::cout << "B - A\t-->>\t" << B << " - " << A << " = " << (B - A) << std::endl;
	std::cout << "A - B\t-->>\t" << A << " - " << B << " = " << (A - B) << std::endl;
	std::cout << "A * B\t-->>\t" << A << " * " << B << " = " << (A * B) << std::endl;
	std::cout << "A / B\t-->>\t" << A << " / " << B << " = " << (A / B) << std::endl;
#endif // ARITHMETIC_CHECK

	//	Составные присваивания
#ifdef COMPOUND_ASSIGNMENT
	Fraction A(2, 3, 4);
	Fraction B(5, 6, 7);

	std::cout << "A = " << A << "\tB = " << B << std::endl << std::endl;

	std::cout << A << " -= " << B; std::cout << "\t>>>\t" << (A -= B) << "\tminus = " << A.get_minus() << std::endl;
	std::cout << A << " *= " << B; std::cout << "\t>>>\t" << (A *= B) << "\tminus = " << A.get_minus() << std::endl;
	std::cout << (A.reduce()) << std::endl;
	std::cout << A << " /= " << B; std::cout << "\t>>>\t" << (A /= B) << "\tminus = " << A.get_minus() << std::endl;
	std::cout << (A.reduce()) << std::endl;
#endif // COMPOUND_ASSIGNMENT

	//	Инкремент / Декримент
#ifdef INCREMENT_DECREMENT
	Fraction A(2, 3, 4);
	Fraction B(5, 6, 7);

	std::cout << "A = " << A << "\tB = " << B << std::endl << std::endl;

	std::cout << "A++\t-->>\t" << A++ << "\tminus = " << A.get_minus() << std::endl;
	std::cout << (A.reduce()) << std::endl;
	std::cout << "++A\t-->>\t" << ++A << "\tminus = " << A.get_minus() << std::endl;
	std::cout << (A.reduce()) << std::endl;
	std::cout << "A--\t-->>\t" << A-- << "\tminus = " << A.get_minus() << std::endl;
	std::cout << (A.reduce()) << std::endl;
	std::cout << "--A\t-->>\t" << --A << "\tminus = " << A.get_minus() << std::endl;
	std::cout << (A.reduce()) << std::endl;
#endif // INCREMENT_DECREMENT

	// Сравнение
#ifdef COMPARISON
	Fraction A(2, 3, 4);
	Fraction B(5, 6, 7);
	//Fraction A(5, 6, 7);
	//Fraction B(2, 3, 4);
	
	std::cout << "A = " << A << "\tB = " << B << std::endl << std::endl;

	std::cout << "A == B\t-->>\t" << ((A == B) ? "true" : "false") << std::endl;
	std::cout << "A != B\t-->>\t" << ((A != B) ? "true" : "false") << std::endl;
	std::cout << "A >  B\t-->>\t" << ((A >  B) ? "true" : "false") << std::endl;
	std::cout << "A <  B\t-->>\t" << ((A <  B) ? "true" : "false") << std::endl;
	std::cout << "A >= B\t-->>\t" << ((A >= B) ? "true" : "false") << std::endl;
	std::cout << "A <= B\t-->>\t" << ((A <= B) ? "true" : "false") << std::endl;
#endif // COMPARISON


#ifdef TYPE_CONVERSIONS
	int a;
	Fraction A = 5;	//	From other to this. Это преобразование выполняет SinglArgumentConstructor (конструктор с одним параметром)
	a = A;	//	From this to other. Posible loss of data.
	std::cout << a << std::endl;
	
	//	Проверка оператора преобразования в `double`
	Fraction B(-5, 6, 7);
	double b;
	b = B;
	std::cout << "b = " << b << std::endl;

	//	Проверка инициализации `double`-м
	Fraction C(4.25612254669854);
	std::cout << "C = " << C << std::endl;

#endif // TYPE_CONVERSIONS
}


//Signature - подпись
/*
-----------------------------------------------------
|                                                   |
|   "Компьютерная академия ШАГ"                     |
|   Курс: PD_011                                    |
|   Предмет: Основы програмvирования на языке C++   |
|                                                   |
|   Исполнитель: Курицын Алексей                    |
|   Преподаватель: Ковтун Олег                      |
|                                                   |
|   Екатеринбург - 2021                             |
|                                                   |
-----------------------------------------------------*/