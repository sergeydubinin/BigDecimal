#include <iostream>
#include <iomanip>
#include <cstdlib>
#include "BigDecimal.h"

int Menu()
{
	int variant;
	std::cout << std::endl;
	std::cout << "=====Выберите необходимое действие=====\n" << std::endl;
	std::cout << "1. Получить дополнительный код числа\n"
		<< "2. Умножить число на 10\n"
		<< "3. Разделить число на 10\n"
		<< "4. Сумма двух чисел\n"
		<< "5. Разность двух чисел\n"
		<< "6. Выход\n" << std::endl;
	std::cout << "Ваш выбор: ";
	std::cin >> variant;
	std::cout << std::endl;
	return variant;
}

int main()
{
	setlocale(LC_ALL, "rus");
	do
	{
	try
	{
		int variant = Menu();
		switch (variant)
		{
		case 1:
		{
			BigDecimal n;
			std::cout << "Введите число:";
			std::cin >> n;
			std::cin.get();
			std::cout << "Допополнительный код числа:" << ~n << '\n';
			break;
		}
		case 2:
		{
			BigDecimal n;
			std::cout << "Введите число:";
			std::cin >> n;
			std::cin.get();
			n.mul10();
			std::cout << "Результат:" << n << '\n';
			break;
		}
		case 3:
		{
			BigDecimal n;
			std::cout << "Введите число:";
			std::cin >> n;
			std::cin.get();
			n.div10();
			std::cout << "Результат:" << n << '\n';
			break;
		}
		case 4:
		{
			BigDecimal n, m, r;
			std::cout << "Введите первое число:";
			std::cin >> n;
			std::cout << "Введите второе число:";
			std::cin >> m;
			std::cin.get();
			r = n + m;
			std::cout << "Результат:" << r << '\n';
			break;
		}
		case 5:
		{
			BigDecimal n, m, r;
			std::cout << "Введите первое число:";
			std::cin >> n;
			std::cout << "Введите второе число:";
			std::cin >> m;
			std::cin.get();
			r = n - m;
			std::cout << "Результат:" << r << '\n';
			break;
		}
		case 6:
		{
			std::cout << "Выход из программы..." << std::endl;
			exit(EXIT_SUCCESS);
			break;
		}
		default:
		{
			std::cerr << "Вы выбрали неверный вариант" << std::endl;
			exit(EXIT_FAILURE);
		}
		}
	}
	catch (const char* ex)
	{
		std::cerr << "Ошибка: " << ex << std::endl;
	}
	} while (true);
	system("pause");
	return 0;
}