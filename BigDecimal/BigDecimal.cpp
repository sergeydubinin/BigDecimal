#include "BigDecimal.h"

void BigDecimal::init()
{
	for (int i = 0; i <= N; i++)
	{
		digits[i] = '0';
		complement[i] = '0';
	}
}

BigDecimal::BigDecimal()
{
	init();
	length = 1;
}

BigDecimal::BigDecimal(long number)
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
		digits[i] = rem - '0';
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

BigDecimal::BigDecimal(const char* str)
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

BigDecimal::~BigDecimal() = default;


	