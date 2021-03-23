#include <iostream>

#include "BigDecimal.h"

int main(void)
{
	setlocale(LC_ALL, "rus");
	BigDecimal n;
	do
	{
		std::cout << " 0. ������ �����.\n";
		std::cout << " 1. ������� �������� ����� �� �����.\n";
		std::cout << " 2. �������� �� 10.\n";
		std::cout << " 3. ��������� �� 10.\n";
		std::cout << " 4. ������� ����� � �������������� ����.\n";
		std::cout << " 5. �������� � �����.\n";
		std::cout << " 6. ������� �� �����\n";
		std::cout << " 7. ������� �������\n";
		std::cout << "����� �����\n";
		char ch = std::cin.get();
		std::cin.ignore(255, '\n');
		switch (ch)
		{
		case '0':
		{
			std::cout << "������� �����:";
			std::cin >> n;
			std::cin.get();
			break;
		}
		case '1':
		{
			std::cout << "������� ��������:" << n << '\n';
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
			std::cout << "���. ��� �����:" << ~n << '\n';
			break;
		}
		case '5':
		{
			BigDecimal m;
			std::cout << "������� ����� ��� ����������:";
			std::cin >> m;
			n = n + m;
			std::cin.get();
			break;
		}
		case '6':
		{
			BigDecimal m;
			std::cout << "������� ����� ��� ���������:";
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