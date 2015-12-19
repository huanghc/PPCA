#pragma once
#define SCAST_NUMBER(x) static_cast<Number*>(x)

class Number {
public:
	enum{
		RATIONAL = 1,
		FLOAT = 2,
		COMPLEX = 3
	} type_;
	Number(){}
	virtual ~Number(){}
	virtual Number *convert(Number *number2) = 0;
	virtual Number *add(Number *number2)  = 0;
	virtual Number *sub(Number *number2)  = 0;
	virtual Number *mul(Number *number2)  = 0;
	virtual Number *div(Number *number2)  = 0;
	virtual Number *quotient(Number *number2)  = 0;
	virtual Number *remainder(Number *number2)  = 0;
	virtual Number *modulo(Number *number2)  = 0;
	virtual Number *gcd(Number *number2)  = 0;
	virtual Number *lcm(Number *number2)  = 0;
	virtual Number *EXPT(Number *number2)  = 0;
	virtual Number *SQRT()  = 0;
	virtual Number *NUM()  = 0;
	virtual Number *DEN()  = 0;
	virtual Number *floor()  = 0;
	virtual Number *ceiling()  = 0;
	virtual Number *truncate()  = 0;
	virtual Number *ROU()=0;
	virtual Number *exact()=0;
	virtual Number *inexact()=0;
	virtual Number *realpart()=0;
	virtual Number *imagepart()=0;
	virtual Number *MAX(Number *number2)=0;
	virtual Number *MIN(Number *number2)=0;
	virtual void abs()  = 0;
	virtual bool shi()  = 0;
	virtual bool interger()=0;
	virtual int positive()=0;
	virtual void print() = 0;
};
