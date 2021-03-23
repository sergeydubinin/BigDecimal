#include <iostream>
#include <string>

using namespace std;

const int N = 47;

class BigDecimal
{
private:
	int length;
	char digits[N + 2];
	char complement[N + 2];
	void init();
	void from_str(const char* str);
	void changeSign();

public:
	BigDecimal();
	BigDecimal(long number);
	BigDecimal(const char* str);
	void mul10();
	void div10();
	friend std::ostream& operator<< (std::ostream& stream, const BigDecimal& number);
	friend std::istream& operator>> (std::istream& stream, BigDecimal& number);
	bool isPositive() const;
	bool isNegative() const;
	const char* operator ~();
	BigDecimal operator + (BigDecimal number);
	BigDecimal operator - (BigDecimal number);
};
