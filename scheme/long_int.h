#pragma once
#include <cassert>
#include <cstdio>
#include <cstring>
#include <cstdio>
#include <iostream>
#include <sstream>
#include <string>

class LongInt {
public:
	LongInt(char number[] = "0");
	LongInt(const LongInt &long_int2);
	~LongInt();
	operator bool() const;
	operator double() const;
	bool operator!=(const LongInt &long_int2) const;
	bool operator<(const LongInt &long_int2) const;
	LongInt &operator=(const LongInt &long_int2);
	LongInt operator+(const LongInt &long_int2) const;
	LongInt operator-(const LongInt &long_int2) const;
	LongInt operator*(const LongInt &long_int2) const;
	LongInt operator/(const LongInt &long_int2) const;
	LongInt operator%(const LongInt &long_int2) const;
	friend LongInt Max(const LongInt &long_int1, const LongInt &long_int2);
	friend LongInt Min(const LongInt &long_int1, const LongInt &long_int2);
	void print();

	char *number_;
};
