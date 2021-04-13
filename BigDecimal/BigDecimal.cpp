#include <string>
#include <cstring>
#include "BigDecimal.h"

void BigDecimal::init()
{
	for (int i = 0; i <= N; i++)
	{
		digits[i] = '0';
	}
}

BigDecimal::BigDecimal() : length(1), digits{}
{
	init();
}

BigDecimal::BigDecimal(long number) : digits{}
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
	else if (n && str[0] == '+')
	{
		digits[N] = '0';
		n--;
	}

	for (; i >= 0 && str[i] >= '0' && str[i] <= '9'; i--, j++)
	{
		digits[j] = str[i];
	}
	length = j;

	if (length == 0 || length != n)
	{
		throw invalid_argument ("Invalid string passed to constructor");
	}

	if ((str[0] == '-' && length > N + 1) || (str[0] == '+' && length > N + 1) || (length > N))
	{
		throw logic_error ("Number overflow");
	}
}

BigDecimal::BigDecimal(const char* str) : digits{}
{
	init();
	from_str(str);
}

void BigDecimal::mul10()
{
	if (!isPositive() && !isNegative())
	{
		return;
	}

	if (length == N)
	{
		throw logic_error ("mul10 overflow");
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
	if (!isPositive() && !isNegative())
	{
		return;
	}
	for (int i = 0; i < length; i++)
	{
		digits[i] = digits[i + 1];
	}
	digits[length] = '0';
	length--;
}

std::ostream& operator<< (std::ostream& stream, const BigDecimal& number)
{
	if (number.digits[BigDecimal::N] == '9')
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
	try
	{
		number.from_str(str.data());
	}
	catch (std::exception& error)
	{
		stream.setstate(std::ios::failbit);
		return stream;
	}
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

char* BigDecimal::operator ~()const
{
	auto complement = new char[N + 2]();
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

BigDecimal operator + (const BigDecimal& a, const BigDecimal& b)
{
	auto cur = a;
	auto number = b;

	//получаем дополнительный код
	auto c1 = ~cur;
	auto c2 = ~number;

	char str[BigDecimal::N + 2] = {};
	char temp[BigDecimal::N + 1] = {};

	// одинаковые знаки
	if (cur.digits[BigDecimal::N] == number.digits[BigDecimal::N])
	{
		// положительные числа
		if (cur.isPositive() && number.isPositive())
		{
			bool hasAdd = false;//показывает есть ли доп 1
			for (int i = 0; i < BigDecimal::N; i++)
			{
				str[i] = c1[BigDecimal::N - i] + c2[BigDecimal::N - i] - '0' + hasAdd;
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

			if ((cur.length == BigDecimal::N || number.length == BigDecimal::N)
				&& cur.digits[BigDecimal::N] == number.digits[BigDecimal::N]
				&& hasAdd)
			{
				throw ("+ overflow");
			}

			//разворачиваем строку
			for (int i = 0; i < BigDecimal::N; i++)
			{
				temp[i] = str[BigDecimal::N - i - 1];
			}
			auto ptr = temp;
			//удаляем первые нули
			while (*ptr == '0')
			{
				++ptr;
			}
			delete[] c1;
			delete[] c2;
			return BigDecimal(ptr);
		}
		else if (cur.isNegative() && number.isNegative()) // оба отрицательных
		{
			bool hasAdd = false;
			for (int i = 0; i < BigDecimal::N; i++)
			{
				str[i] = c1[BigDecimal::N - i] + c2[BigDecimal::N - i] - '0' + hasAdd;
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
			for (int i = 0; i < BigDecimal::N; i++)
			{
				auto c = str[i];
				temp[BigDecimal::N - 1 - i] = '9' - c + '0' + hasAdd;
				if (temp[BigDecimal::N - 1 - i] > '9')
				{
					hasAdd = true;
					temp[BigDecimal::N - 1 - i] = '0';
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
			delete[] c1;
			delete[] c2;
			return BigDecimal(std::string(std::string("-") + ptr).data());
		}
		else
		{
			delete[] c1;
			delete[] c2;
			//сложение с 0
			if (cur.isPositive())
			{
				return cur;
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
		for (int i = 0; i < BigDecimal::N; i++)
		{
			str[i] = c1[BigDecimal::N - i] + c2[BigDecimal::N - i] - '0' + hasAdd;
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
			for (int i = 0; i < BigDecimal::N; i++)
			{
				temp[i] = str[BigDecimal::N - i - 1];
			}
			auto ptr = temp;
			while (*ptr == '0')
			{
				++ptr;
			}
			delete[] c1;
			delete[] c2;
			return BigDecimal(ptr);
		}
		else //отрицательное число
		{
			hasAdd = true; //занимаем разряд
			for (int i = 0; i < BigDecimal::N; i++)
			{
				auto c = str[i];
				temp[BigDecimal::N - 1 - i] = '9' - c + '0' + hasAdd;
				if (temp[BigDecimal::N - 1 - i] > '9')
				{
					hasAdd = true;
					temp[BigDecimal::N - 1 - i] = '0';
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
			delete[] c1;
			delete[] c2;
			return BigDecimal(std::string(std::string("-") + ptr).data());
		}
	}
	delete[] c1;
	delete[] c2;
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

BigDecimal operator - (const BigDecimal& a, const BigDecimal& b)
{
	BigDecimal number = b;
	number.changeSign();
	return a + number;
}

int BigDecimal::cmp(const BigDecimal& number) const
{
	if (digits[N] == number.digits[N])
	{
		if (isPositive() && number.isPositive() || isNegative() && number.isNegative())
		{
			if (N != number.N)
			{
				return (N > number.N) ? 1 : -1;
			}

			if (length != number.length)
			{
				return (length > number.length) ? 1 : -1;
			}
			auto ptr1 = digits;
			auto ptr2 = number.digits;
			while (*ptr1 == *ptr2 && *ptr1 != '\0')
			{
				++ptr1;
				++ptr2;
			}

			if (*ptr1 == '\0')
			{
				return 0;
			}

			return (*ptr1 > * ptr2) ? 1 : -1;
		}
		else
		{
			if (isPositive())
			{
				return 1;
			}
			else if (isNegative())
			{
				return -1;
			}
			else
			{
				if (number.isPositive())
				{
					return -1;
				}
				else if (number.isNegative())
				{
					return 1;
				}
				return 0;
			}
		}
	}
	else // разные знаки
	{
		//отрицательное число меньше
		if (isNegative())
		{
			return -1;
		}

		return 1;
	}
	return 0;
}

bool operator>(const BigDecimal& a, const BigDecimal& b)
{
	return a.cmp(b) > 0;
}

bool operator<(const BigDecimal& a, const BigDecimal& b)
{
	return a.cmp(b) < 0;
}

bool operator>=(const BigDecimal& a, const BigDecimal& b)
{
	return !(a < b);
}

bool operator<=(const BigDecimal& a, const BigDecimal& b)
{
	return !(a > b);
}

bool operator==(const BigDecimal& a, const BigDecimal& b)
{
	return a.cmp(b) == 0;
}

bool operator!=(const BigDecimal& a, const BigDecimal& b)
{
	return !(a == b);
}