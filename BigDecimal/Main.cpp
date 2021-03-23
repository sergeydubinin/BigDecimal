#include <iostream>

#include "BigDecimal.h"

int main(void)
{
	setlocale(LC_ALL, "rus");
	BigDecimal n;
	do
	{
		std::cout << " 0. Задать число.\n";
		std::cout << " 1. Вывести значение числа на экран.\n";
		std::cout << " 2. Умножить на 10.\n";
		std::cout << " 3. Разделить на 10.\n";
		std::cout << " 4. Вывести число в дополнительном коде.\n";
		std::cout << " 5. Добавить к числу.\n";
		std::cout << " 6. Вычесть из числа\n";
		std::cout << " 7. Очистка консоли\n";
		std::cout << "Иначе Выход\n";
		char ch = std::cin.get();
		std::cin.ignore(255, '\n');
		switch (ch)
		{
		case '0':
		{
			std::cout << "Введите число:";
			std::cin >> n;
			std::cin.get();
			break;
		}
		case '1':
		{
			std::cout << "Текущее значение:" << n << '\n';
			break;
		}
		case '2':
		{
			try
			{
				n.mul10();
			}
			catch (std::exception& e)
			{
				std::cout << e.what() << '\n';
			}
			break;
		}
		case '3':
		{
			n.div10();
			break;
		}
		case '4':
		{
			std::cout << "Доп. код числа:" << ~n << '\n';
			break;
		}
		case '5':
		{
			BigDecimal m;
			std::cout << "Введите число для добавления:";
			std::cin >> m;
			n = n + m;
			std::cin.get();
			break;
		}
		case '6':
		{
			BigDecimal m;
			std::cout << "Введите число для вычитания:";
			std::cin >> m;
			n = n - m;
			std::cin.get();
			break;
		}
		case '7':
		{
			system("cls");
			break;
		}
		default:
		{
			std::cin.get();
			std::cin.get();
			return 0;
		}
		}
	} while (true);
}