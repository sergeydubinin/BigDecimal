#include <string>
#include <cstring>
#include "BigDecimal.h"

void BigDecimal::init()
{
	for (int i = 0; i <= N; i++)
	{
		digits[i] = '0';
		complement[i] = '0';
	}
}

BigDecimal::BigDecimal() : length(1), digits{}, complement{}
{
	init();
}

BigDecimal::BigDecimal(long number) : digits{}, complement{}
{
	init();
	if (number == 0)
	{
		length = 1;
		return;
	}
	else if (number < 0)
	{
		digits[N] = '9';
		number *= -1;
	}

	int i = 0;
	for (; number != 0; i++)
	{
		int rem = number % 10;
		digits[i] = '0' + rem;
		number = number / 10;
	}
	length = i;
}

void BigDecimal::from_str(const char* str)
{
	int n = strlen(str);
	int i = n - 1, j = 0;
	if (strcmp(str, "0") == 0)
	{
		digits[N] = '0';
		length = 1;
		return;
	}
	else if (n && str[0] == '-')
	{
		digits[N] = '9';
		n--;
	}

	for (; i >= 0 && str[i] >= '0' && str[i] <= '9'; i--, j++)
	{
		digits[j] = str[i];
	}
	length = j;

	if (length == 0 || length != n)
	{
		throw "Invalid string passed to constructor";
	}
}

BigDecimal::BigDecimal(const char* str) : digits{}, complement{}
{
	init();
	from_str(str);
}

void BigDecimal::mul10()
{
	if (length == N)
	{
		throw "mul10 overflow";
	}

	for (int i = length; i > 0; i--)
	{
		digits[i] = digits[i - 1];
	}
	digits[0] = '0';
	length++;
}

void BigDecimal::div10()
{
	for (int i = 0; i < length; i++)
	{
		digits[i] = digits[i + 1];
	}
	digits[length] = '\0';
	length--;
}

std::ostream& operator<< (std::ostream& stream, const BigDecimal& number)
{
	if (number.digits[N] == '9')
	{
		stream << '-';
	}
	for (int i = number.length - 1; i >= 0; i--)
	{
		stream << number.digits[i];
	}

	return stream;
}

std::istream& operator>> (std::istream& stream, BigDecimal& number)
{
	std::string str;
	stream >> str;
	number.from_str(str.data());
	return stream;
}

bool BigDecimal::isPositive() const
{
	if (digits[N] != '0')
	{
		return false;
	}

	if (length == 1 && digits[0] == '0')
	{
		return false;
	}

	return true;
}

bool BigDecimal::isNegative() const
{
	return digits[N] == '9';
}

const char* BigDecimal::operator ~ ()
{
	if (isPositive())
	{
		for (int i = N; i > 0; i--)
		{
			complement[i] = digits[N - i];
		}
	}
	else if (isNegative())
	{
		complement[0] = '9';
		for (int i = 1; i <= N; i++)
		{
			if (i == N)
			{
				complement[i] = '9' - digits[N - i] + '1';
			}
			else
			{
				complement[i] = '9' - digits[N - i] + '0';
			}
		}

		if (complement[N] == '9' + 1)
		{
			complement[N] = '0';
			bool isActive = true;
			for (int i = N - 1; i >= 0 && isActive; i--)
			{
				if (isActive)
				{
					if (complement[i] == '9')
					{
						complement[i] = '0';
					}
					else
					{
						isActive = false;
						complement[i]++;
					}
				}
			}
		}
	}

	return complement;
}

BigDecimal BigDecimal::operator + (BigDecimal number)
{
	auto c1 = ~*this;
	auto c2 = ~number;

	char str[N + 2] = {};
	char temp[N + 1] = {};

	// одинаковые знаки
	if (digits[N] == number.digits[N])
	{
		// положительные числа
		if (isPositive() && number.isPositive())
		{
			bool hasAdd = false;//показывает есть ли доп 1
			for (int i = 0; i < N; i++)
			{
				str[i] = c1[N - i] + c2[N - i] - '0' + hasAdd;
				if (str[i] > '9')
				{
					str[i] = str[i] - 10;
					hasAdd = true;
				}
				else
				{
					hasAdd = false;
				}
			}

			//разворачиваем строку
			for (int i = 0; i < N; i++)
			{
				temp[i] = str[N - i - 1];
			}
			auto ptr = temp;
			//удаляем первые нули
			while (*ptr == '0')
			{
				++ptr;
			}
			return BigDecimal(ptr);
		}
		else if (isNegative() && number.isNegative()) // оба отрицательных
		{
			bool hasAdd = false;
			for (int i = 0; i < N; i++)
			{
				str[i] = c1[N - i] + c2[N - i] - '0' + hasAdd;
				if (str[i] > '9')
				{
					str[i] = str[i] - 10;
					hasAdd = true;
				}
				else
				{
					hasAdd = false;
				}

				temp[i] = '0';
			}

			// получаем результат
			for (int i = 0; i < N; i++)
			{
				auto c = str[i];
				temp[N - 1 - i] = '9' - c + '0' + hasAdd;
				if (temp[N - 1 - i] > '9')
				{
					hasAdd = true;
					temp[N - 1 - i] = '0';
				}
				else
				{
					hasAdd = false;
				}
			}
			auto ptr = temp;
			while (*ptr == '0')
			{
				++ptr;
			}
			return BigDecimal(std::string(std::string("-") + ptr).data());
		}
		else
		{
			//сложение с 0
			if (isPositive())
			{
				return *this;
			}
			else
			{
				return number;
			}
		}

	}
	else // разные знаки
	{
		bool hasAdd = false;
		for (int i = 0; i < N; i++)
		{
			str[i] = c1[N - i] + c2[N - i] - '0' + hasAdd;
			if (str[i] > '9')
			{
				str[i] = str[i] - 10;
				hasAdd = true;
			}
			else
			{
				hasAdd = false;
			}
		}
		//результат - положительное число
		if (hasAdd)
		{
			//разворачиваем строку
			for (int i = 0; i < N; i++)
			{
				temp[i] = str[N - i - 1];
			}
			auto ptr = temp;
			while (*ptr == '0')
			{
				++ptr;
			}
			return BigDecimal(ptr);
		}
		else //отрицательное число
		{
			hasAdd = true; //занимаем разряд
			for (int i = 0; i < N; i++)
			{
				auto c = str[i];
				temp[N - 1 - i] = '9' - c + '0' + hasAdd;
				if (temp[N - 1 - i] > '9')
				{
					hasAdd = true;
					temp[N - 1 - i] = '0';
				}
				else
				{
					hasAdd = false;
				}
			}
			auto ptr = temp;
			while (*ptr == '0')
			{
				++ptr;
			}
			return BigDecimal(std::string(std::string("-") + ptr).data());
		}
	}

	return BigDecimal(str);
}

void BigDecimal::changeSign()
{
	if (isPositive())
	{
		digits[N] = '9';

	}
	else if (isNegative())
	{
		digits[N] = '0';

	}
}

BigDecimal BigDecimal::operator - (BigDecimal number)
{
	number.changeSign();
	return *this + number;
}


