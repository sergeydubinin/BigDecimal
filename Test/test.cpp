#include "pch.h"
#include "..\BigDecimal\BigDecimal.cpp"

TEST(BigDecimalConstructor, DefaultConstructor)
{
	BigDecimal a;
	ASSERT_EQ(a, 0);
}

TEST(BigDecimalConstructor, LongConstructor)
{
	BigDecimal a(12345);
	ASSERT_EQ(a, "12345");
	BigDecimal b(-5786);
	ASSERT_EQ(b, "-5786");
}

TEST(BigDecimalConstructor, StringConstructor)
{
	BigDecimal a("12345");
	BigDecimal b("-8963");
	BigDecimal c("+78696");
	ASSERT_EQ(a, 12345);
	ASSERT_EQ(b, -8963);
	ASSERT_EQ(c, 78696);
	ASSERT_THROW(BigDecimal(""), invalid_argument);
	ASSERT_THROW(BigDecimal("jdfhksdj"), invalid_argument);
	ASSERT_THROW(BigDecimal("-dededede"), invalid_argument);
	ASSERT_THROW(BigDecimal("111111111111111111111111111111111111111111111111111111111111111111111111111111"), logic_error);
}

TEST(BigDecimalMetods, Addition)
{
	BigDecimal a(1234);
	BigDecimal b(11111);
	ASSERT_EQ(a + b, 12345);
	a = 7654;
	b = 3111;
	ASSERT_EQ(a + b, 10765);
	a = -7123;
	b = -4321;
	ASSERT_EQ(a + b, -11444);
	a = 55123;
	b = -55012;
	ASSERT_EQ(a + b, 111);
	a = "99999999999999999999999999999999999999999999999";
	b = "123";
	ASSERT_THROW(a + b, logic_error);
	a = "-99999999999999999999999999999999999999999999999";
	b = "-785654";
	ASSERT_THROW(a + b, logic_error);
	a = "456978";
	b = "0";
	ASSERT_EQ(a + b, 456978);
	a = "325689";
	b = "-325689";
	ASSERT_EQ(a + b, 0);
}

TEST(BigDecimalMetods, Subtraction)
{
	BigDecimal a(11111);
	BigDecimal b(1111);
	ASSERT_EQ(a - b, 10000);
	a = -11111;
	b = 1456;
	ASSERT_EQ(a - b, -12567);
	a = -58796;
	b = -2569;
	ASSERT_EQ(a - b, -56227);
	a = "99999999999999999999999999999999999999999999999";
	b = "-1458";
	ASSERT_THROW(a - b, logic_error);
	a = "-99999999999999999999999999999999999999999999999";
	b = "565984";
	ASSERT_THROW(a - b, logic_error);
	a = "23568";
	b = "0";
	ASSERT_EQ(a - b, 23568);
	a = "78638941";
	b = "78638941";
	ASSERT_EQ(a - b, 0);
}

TEST(BigDecimalMetods, Mul10)
{
	BigDecimal a(1234);
	a.mul10();
	ASSERT_EQ(a, 12340);
	BigDecimal b("0");
	b.mul10();
	ASSERT_EQ(b, 0);
	BigDecimal c("-8978");
	c.mul10();
	ASSERT_EQ(c, -89780);
	BigDecimal d("99999999999999999999999999999999999999999999999");
	ASSERT_THROW(d.mul10(), logic_error);
}

TEST(BigDecimalMetods, Div10)
{
	BigDecimal a(1234);
	a.div10();
	ASSERT_EQ(a, 123);
	BigDecimal b("0");
	b.div10();
	ASSERT_EQ(b, 0);
	BigDecimal c("-65874");
	c.div10();
	ASSERT_EQ(c, -6587);
}

TEST(IOMetods, Input)
{
	stringstream ss;
	ss << "12345\n";
	BigDecimal a;
	ss >> a;
	ASSERT_EQ(a, 12345);
	ss << "-12345\n";
	ss >> a;
	ASSERT_EQ(a, -12345);
	ss << "rtrtttfs\n";
	ss >> a;
	ASSERT_TRUE(ss.fail());
}

TEST(IOMetods, Output)
{
	stringstream ss;
	BigDecimal a(12345);
	ss << a;
	ASSERT_EQ(ss.str(), "12345");
	ss.str(string());
	a = -12345;
	ss << a;
	ASSERT_EQ(ss.str(), "-12345");
}