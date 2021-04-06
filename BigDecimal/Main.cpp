#include <iostream>
#include <iomanip>
#include <cstdlib>
#include "BigDecimal.h"

int Menu()
{
	int variant;
	std::cout << std::endl;
	std::cout << "=====�������� ����������� ��������=====\n" << std::endl;
	std::cout << "1. �������� ����� �� 10\n"
		<< "2. ��������� ����� �� 10\n"
		<< "3. ����� ���� �����\n"
		<< "4. �������� ���� �����\n"
		<< "5. �����\n" << std::endl;
	std::cout << "��� �����: ";
	std::cin >> variant;
	std::cin.get();
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
			std::cout << "������� �����:";
			std::cin >> n;
			n.mul10();
			std::cout << "���������:" << n << '\n';
			break;
		}
		case 2:
		{
			BigDecimal n;
			std::cout << "������� �����:";
			std::cin >> n;
			n.div10();
			std::cout << "���������:" << n << '\n';
			break;
		}
		case 3:
		{
			BigDecimal n, m, r;
			std::cout << "������� ������ �����:";
			std::cin >> n;
			std::cout << "������� ������ �����:";
			std::cin >> m;
			r = n + m;
			std::cout << "���������:" << r << '\n';
			break;
		}
		case 4:
		{
			BigDecimal n, m, r;
			std::cout << "������� ������ �����:";
			std::cin >> n;
			std::cout << "������� ������ �����:";
			std::cin >> m;
			r = n - m;
			std::cout << "���������:" << r << '\n';
			break;
		}
		case 5:
		{
			std::cout << "����� �� ���������..." << std::endl;
			exit(EXIT_SUCCESS);
			break;
		}
		default:
		{
			std::cerr << "�� ������� �������� �������" << std::endl;
			exit(EXIT_FAILURE);
		}
		}
	}
	catch (const char* ex)
	{
		std::cerr << "������: " << ex << std::endl;
	}
	} while (true);
	system("pause");
	return 0;
}