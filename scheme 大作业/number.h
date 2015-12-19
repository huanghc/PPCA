#pragma once

#define SCAST_NUMBER(x) static_cast<Number*>(x)

class Number {
public:
	enum{
		RATIONAL = 1,
		FLOAT = 2,
		COMPLEX = 3,
		BOOLEAN = 4,
		CHAR = 5,
		STRING = 6
	} type_;
	Number(){}
	virtual ~Number(){}
	virtual Number *convert(Number *number2) = 0;
	virtual Number *add(Number *number2) = 0;
	virtual Number *sub(Number *number2) = 0;
	virtual Number *mul(Number *number2) = 0;
	virtual Number *div(Number *number2) = 0;
	virtual Number *ABS() = 0;
	virtual Number *QUOTIENT(Number *number2) = 0;
	virtual Number *REMAINDER(Number *number2) = 0;
	virtual Number *MODULO(Number *number2) = 0;
	virtual Number *GCD(Number *number2) = 0;
	virtual Number *LCM(Number *number2) = 0;
	virtual Number *EXPT(Number *number2) = 0;
	virtual Number *SQRT() = 0;
	virtual Number *Max(Number *number2) = 0;
	virtual Number *Min(Number *number2) = 0;
	virtual Number *NUMERATOR() = 0;
	virtual Number *DENOMINATOR() = 0;
	virtual Number *floor() = 0;
	virtual Number *ceiling() = 0;
	virtual Number *truncate() = 0;
	virtual Number *ROUND() = 0;
	virtual Number *exact() = 0;
	virtual Number *inexact() = 0;
	virtual Number *realpart() = 0;
	virtual Number *imagepart() = 0;
	virtual Number *IS_EXACT() = 0;
	virtual Number *IS_INEXACT() = 0;
	virtual Number *IS_ZERO() = 0;
	virtual Number *IS_NEGATIVE() = 0;
	virtual Number *IS_POSITIVE() = 0;
	virtual Number *IS_ODD() = 0;
	virtual Number *IS_EVEN() = 0;	
	virtual Number *SIN() = 0;
	virtual Number *COS() = 0;
	virtual Number *TAN() = 0;
	virtual Number *ARCSIN() = 0;
	virtual Number *ARCCOS() = 0;
	virtual Number *ARCTAN() = 0;
	virtual Number *reless(Number *number2) = 0;
	virtual Number *relesseql(Number *number2) = 0;
	virtual Number *regter(Number *number2) = 0;
	virtual Number *regtereql(Number *number2) = 0;
	virtual Number *EXP() = 0;
	virtual Number *LOG() = 0;
	virtual Number *MAGNITUDE() = 0;
	virtual Number *ANGLE() = 0;
	virtual Number *MAKE_RECTANGULAR(Number *number2) = 0;
	virtual Number *MAKE_POLAR(Number *number2) = 0;
	virtual Number *IS_INTEGER() = 0;
	virtual Number *IS_RATIONAL() = 0;
	virtual Number *IS_REAL() = 0;
	virtual Number *IS_COMPLEX() = 0;
	virtual Number *IS_NUMBER() = 0;
	
	virtual Number *EQL(Number *number2) = 0;	
	virtual Number *STR_EQL(Number *number2) = 0;
	virtual Number *STR_CIEQL(Number *number2) = 0;
	virtual Number *STR_LESS(Number *number2) = 0;
	virtual Number *STR_CILESS(Number *number2) = 0;
	virtual Number *STR_LESSEQL(Number *number2) = 0;
	virtual Number *STR_CILESSEQL(Number *number2) = 0;
	virtual Number *CHA_EQL(Number *number2) = 0;
	virtual Number *CHA_CIEQL(Number *number2) = 0;
	virtual Number *CHA_LESS(Number *number2) = 0;
	virtual Number *CHA_CILESS(Number *number2) = 0;
	virtual Number *CHA_LESSEQL(Number *number2) = 0;
	virtual Number *CHA_CILESSEQL(Number *number2) = 0;
	
	virtual Number *IS_STR() = 0;
	virtual Number *MAK_STR() = 0;
	virtual Number *GET_STR() = 0;
	virtual Number *MAK_STR(Number *number2) = 0;
	virtual Number *GET_STR(Number *number2) = 0;
	virtual Number *STR_LEN() = 0;
	virtual Number *STR_REF(Number *number2) = 0;
	virtual Number *STR_APP(Number *number2) = 0;
	virtual Number *STR_CPY() = 0;
	virtual Number *SUB_STR(Number *number1, Number *number2) = 0;
	virtual Number *IS_CHA() = 0;	
	virtual Number *CHA_ALPH() = 0;
	virtual Number *CHA_NUM() = 0;
	virtual Number *CHA_WHIT() = 0;
	virtual Number *IS_CHA_UPP() = 0;
	virtual Number *IS_CHA_LOW() = 0;
	virtual Number *CHA_UP() = 0;
	virtual Number *CHA_DOWN() = 0;
	
	virtual Number *CHA_INT() = 0;
	virtual Number *INT_CHA() = 0;
	virtual Number *STR_NUM() = 0;
	virtual Number *NUM_STR() = 0;
	
	virtual void print() = 0;
};
