#pragma once
#include "number.h"
#include "long_int.h"

#define SCAST_RATIONAL(x) static_cast<Rational*>(x)

class Rational : public Number {
public:
	Rational(int numerator = 0, int denominator = 1);
	virtual ~Rational();

	void reduce();
	virtual Number *convert(Number *number2);
	virtual Number *add(Number *number2);
	virtual Number *sub(Number *number2);
	virtual Number *mul(Number *number2);
	virtual Number *div(Number *number2);
	virtual void print();
	static Rational *from_string(char *expression);
	LongInt numerator_;
	LongInt denominator_;

};
