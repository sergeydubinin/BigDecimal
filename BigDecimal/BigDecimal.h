#include <iostream>
#include <string>

using namespace std;

class BigDecimal
{
private:
	const static int N = 47;
	int length;
	char digits[N + 2];
	void init();
	void from_str(const char* str);
	char* operator ~()const;
	void changeSign();
	int cmp(const BigDecimal& number) const;

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
	friend BigDecimal operator + (const BigDecimal& a, const BigDecimal& b);
	friend BigDecimal operator - (const BigDecimal& a, const BigDecimal& b);

	friend bool operator> (const BigDecimal& a, const BigDecimal& b);
	friend bool operator< (const BigDecimal& a, const BigDecimal& b);
	friend bool operator>= (const BigDecimal& a, const BigDecimal& b);
	friend bool operator<= (const BigDecimal& a, const BigDecimal& b);
	friend bool operator== (const BigDecimal& a, const BigDecimal& b);
	friend bool operator!= (const BigDecimal& a, const BigDecimal& b);
};
