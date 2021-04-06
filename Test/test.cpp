#include "pch.h"
#include "..\BigDecimal\BigDecimal.cpp"

TEST(BigDecConstructor, DefaultConstructor) 
{
	BigDecimal a;
	ASSERT_EQ(a, 0);
}

TEST(BigDecConstructor, LongConstructor)
{
	BigDecimal a(12345);
	BigDecimal b(-12345);
	ASSERT_EQ(a, 12345);
	ASSERT_EQ(b, -12345);
}

TEST(BigDecConstructor, StringConstructor)
{
	BigDecimal a("12345");
	BigDecimal b("-12345");
	BigDecimal c("+12345");
	ASSERT_EQ(a, 12345);
	ASSERT_EQ(b, -12345);
	ASSERT_EQ(c, 12345);
	ASSERT_ANY_THROW(BigDecimal("jdfhksdj"));
	ASSERT_ANY_THROW(BigDecimal("-jdfhksdj"));
	ASSERT_ANY_THROW(BigDecimal(""));
	ASSERT_ANY_THROW(BigDecimal("111111111111111111111111111111111111111111111111111111111111111111111111111111"));
}

TEST(BigDecMetods, Addition) 
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
}

TEST(BigDecMetods, Subtraction) 
{
	BigDecimal a(11111);
	BigDecimal b(1111);
	ASSERT_EQ(a - b, 10000);
	a = -11111;
	b = 1111;
	ASSERT_EQ(a - b, -12222);
	a = -11111;
	b = -1111;
	ASSERT_EQ(a - b, -10000);
}

TEST(BigDecMetods, Mul10)
{
	BigDecimal a(1234);
	a.mul10();
	ASSERT_EQ(a, 12340);
}

TEST(BigDecMetods, Div10) 
{
	BigDecimal a(1234);
	a.div10();
	ASSERT_EQ(a, 123);
}
