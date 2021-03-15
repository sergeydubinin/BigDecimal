#include <iostream>

using namespace std;

const int N = 3;

class BigDecimal
{
private:
	int length;
	char digits[N + 2];
	char complement[N + 2];
	void init();
	void from_str(const char* str);

public:
	BigDecimal();
	BigDecimal(long number);
	BigDecimal(const char* str);
	int get_length() const { return length; };
	std::string get_digits() const { return std::string(digits).substr(0, length); };
	void mul10();
	void div10();
	friend std::ostream& operator<< (std::ostream& stream, const BigDecimal& number);
	friend std::istream& operator>> (std::istream& stream, BigDecimal& number);
	~BigDecimal();
};
