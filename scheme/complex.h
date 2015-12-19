#pragma once
#include "number.h"
#define SCAST_COMPLEX(x) static_cast<Complex*>(x)

class Complex : public Number {
public:
	Complex(Number *r =new Rational("0","1") , Number *i=new Rational("0","1"));
	virtual ~Complex();
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
	virtual int positive();
	virtual void print();
	static Complex *from_string(char *expression);
	Number *real;
	Number *image;
};
