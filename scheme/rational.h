#pragma once
#include "number.h"
#include "long_int.h"

#define SCAST_RATIONAL(x) static_cast<Rational*>(x)

class Rational : public Number {
public:
	Rational(char numerator[] = "0", char denominator[] = "1");
	virtual ~Rational();
	void reduce();
	virtual Number *convert(Number *number2);
	virtual Number *add(Number *number2);
	virtual Number *sub(Number *number2);
	virtual Number *mul(Number *number2);
	virtual Number *div(Number *number2);
	virtual Number *quotient(Number *number2);
	virtual Number *remainder(Number *number2);
	virtual Number *modulo(Number *number2);
	virtual Number *gcd(Number *number2);
	virtual Number *lcm(Number *number2);
	virtual Number *EXPT(Number *number2);
	virtual Number *SQRT();
	virtual Number *NUM();
	virtual Number *DEN();
	virtual Number *floor();
	virtual Number *ceiling();
	virtual Number *truncate();
	virtual Number *ROU();
	virtual Number *exact();
	virtual Number *inexact();
	virtual Number *MAX(Number *number2);
	virtual Number *MIN(Number *number2);
	virtual Number *realpart();
	virtual Number *imagepart();
	virtual void abs();
	virtual bool shi();
	virtual bool interger();
	virtual void print();
	virtual int positive();
	static Rational *from_string(char *expression);
	LongInt numerator_;
	LongInt denominator_;

};
