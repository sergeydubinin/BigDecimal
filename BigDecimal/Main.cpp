#include <iostream>
#include <iomanip>
#include <cstdlib>

#include "BigDecimal.h"

int main(void)
{
	system("chcp 1251 && cls");
	BigDecimal n;
	do
	{
		std::cout << " 0. ������ �����.\n";
		std::cout << " 1. ������� �������� ����� �� �����.\n";
		std::cout << " 2. �������� �� 10.\n";
		std::cout << " 3. ��������� �� 10.\n";
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
		case '7':
		{
			//������� �������
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