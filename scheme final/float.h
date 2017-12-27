#pragma once
#include "number.h"


#define SCAST_FLOAT(x) static_cast<Float*>(x)

class Float : public Number {
public:
	Float(double number = 0);
	virtual ~Float();

	virtual Number *convert(Number *number2);
	virtual Number *add(Number *number2);
	virtual Number *sub(Number *number2);
	virtual Number *mul(Number *number2);
	virtual Number *div(Number *number2);
	virtual Number *ABS();
	virtual Number *QUOTIENT(Number *number2);
	virtual Number *REMAINDER(Number *number2);
	virtual Number *MODULO(Number *number2);
	virtual Number *GCD(Number *number2);
	virtual Number *LCM(Number *number2);
	virtual Number *EXPT(Number *number2);
	virtual Number *SQRT();
	virtual Number *NUMERATOR();
	virtual Number *DENOMINATOR();	
	virtual Number *Max(Number *number2);
	virtual Number *Min(Number *number2);
	virtual Number *floor();
	virtual Number *ceiling();
	virtual Number *truncate();
	virtual Number *ROUND();
	virtual Number *exact();
	virtual Number *reless(Number *number2);
	virtual Number *relesseql(Number *number2);
	virtual Number *regter(Number *number2);
	virtual Number *regtereql(Number *number2);		
	virtual Number *inexact();
	virtual Number *realpart();
	virtual Number *imagepart();
	virtual Number *IS_EXACT();
	virtual Number *IS_INEXACT();
	virtual Number *IS_ZERO();
	virtual Number *IS_NEGATIVE();
	virtual Number *IS_POSITIVE();
	virtual Number *IS_ODD();
	virtual Number *IS_EVEN();	
	virtual Number *SIN();
	virtual Number *COS();
	virtual Number *TAN();
	virtual Number *ARCSIN();
	virtual Number *ARCCOS();
	virtual Number *ARCTAN();
	virtual Number *EXP();
	virtual Number *LOG();
	virtual Number *MAGNITUDE();
	virtual Number *ANGLE();
	virtual Number *MAKE_RECTANGULAR(Number *number2);
	virtual Number *MAKE_POLAR(Number *number2);	
	virtual Number *IS_INTEGER();
	virtual Number *IS_RATIONAL();
	virtual Number *IS_REAL();
	virtual Number *IS_COMPLEX();
	virtual Number *IS_NUMBER();
	virtual Number *EQL(Number *number2);	
	virtual Number *STR_EQL(Number *number2);
	virtual Number *STR_CIEQL(Number *number2);
	virtual Number *STR_LESS(Number *number2);
	virtual Number *STR_CILESS(Number *number2);
	virtual Number *STR_LESSEQL(Number *number2);
	virtual Number *STR_CILESSEQL(Number *number2);
	virtual Number *CHA_EQL(Number *number2);
	virtual Number *CHA_CIEQL(Number *number2);
	virtual Number *CHA_LESS(Number *number2);
	virtual Number *CHA_CILESS(Number *number2);
	virtual Number *CHA_LESSEQL(Number *number2);
	virtual Number *CHA_CILESSEQL(Number *number2);
	
	virtual Number *IS_STR();
	virtual Number *MAK_STR();
	virtual Number *GET_STR();
	virtual Number *MAK_STR(Number *number2);
	virtual Number *GET_STR(Number *number2);	
	virtual Number *STR_LEN();
	virtual Number *STR_REF(Number *number2);
	virtual Number *STR_APP(Number *number2);
	virtual Number *STR_CPY();
	virtual Number *SUB_STR(Number *number1, Number *number2);
	virtual Number *IS_CHA();	
	virtual Number *CHA_ALPH();
	virtual Number *CHA_NUM();
	virtual Number *CHA_WHIT();
	virtual Number *IS_CHA_UPP();
	virtual Number *IS_CHA_LOW();
	virtual Number *CHA_UP();
	virtual Number *CHA_DOWN();
	
	virtual Number *CHA_INT();
	virtual Number *INT_CHA();
	virtual Number *STR_NUM();
	virtual Number *NUM_STR();
	virtual void print();
	static Float *from_string(char *expression);
	double number_;
};
