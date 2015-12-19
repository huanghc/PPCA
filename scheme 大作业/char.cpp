#include "float.h"
#include "rational.h"
#include "complex.h"
#include "boolean.h"
#include "string.h"
#include "char.h"
#include <cassert>
#include <cstdlib>
#include <cstdio>
#include <sstream>
#include <cstring>
#include <string>
#include <cmath> 
#include <complex>
#include <iostream>
using namespace std;

#define MAX(x,y) ((x)<(y)?(y):(x))
#define MIN(x,y) ((x)<(y)?(x):(y))

Char::Char(char cc):ch(cc)
{	type_ = CHAR;
}

Number *Char::EQL(Number *number2){
	Char *tmp = SCAST_CHAR(number2);
	Boolean *result = new Boolean;
	result->judge = true;
	if (ch != tmp->ch ) result->judge = false;
	return result;
}	

Number *Char::STR_EQL(Number *number2){}
Number *Char::STR_CIEQL(Number *number2){}
Number *Char::STR_LESS(Number *number2){}
Number *Char::STR_CILESS(Number *number2){}
Number *Char::STR_LESSEQL(Number *number2){}
Number *Char::STR_CILESSEQL(Number *number2){}
Number *Char::CHA_EQL(Number *number2){
	Char *tmp = SCAST_CHAR(number2);
	Boolean *result = new Boolean;
	result->judge = true;
	if (ch != tmp->ch ) result->judge = false;
	return result;
}

Number *Char::CHA_CIEQL(Number *number2){
	Char *tmp = SCAST_CHAR(number2);
	Boolean *result = new Boolean;
	result->judge = true;
	if (ch >= 'A' && ch <= 'Z'){
		ch = ch-'A'+'a';
	}	
	if (tmp->ch >= 'A' && tmp->ch <= 'Z'){
		tmp->ch = tmp->ch-'A'+'a';
	}//cout<<ch<<endl<<tmp->ch<<endl;
	if (ch != tmp->ch ) result->judge = false;
	return result;
}

Number *Char::CHA_LESS(Number *number2){
	Char *tmp = SCAST_CHAR(number2);
	Boolean *result = new Boolean;
	result->judge = false;
	if (ch < tmp->ch ) result->judge = true;
	return result;
}

Number *Char::CHA_CILESS(Number *number2){
	Char *tmp = SCAST_CHAR(number2);
	Boolean *result = new Boolean;
	result->judge = false;
	if (ch >= 'A' && ch <= 'Z'){
		ch = ch-'A'+'a';
	}	
	if (tmp->ch >= 'A' && tmp->ch <= 'Z'){
		tmp->ch = tmp->ch-'A'+'a';
	}
	if (ch < tmp->ch ) result->judge = true;
	return result;
}

Number *Char::CHA_LESSEQL(Number *number2){
	Char *tmp = SCAST_CHAR(number2);
	Boolean *result = new Boolean;
	result->judge = false;
	if (ch <= tmp->ch ) result->judge = true;
	return result;
}
Number *Char::CHA_CILESSEQL(Number *number2){
	Char *tmp = SCAST_CHAR(number2);
	Boolean *result = new Boolean;
	result->judge = false;
	if (ch >= 'A' && ch <= 'Z'){
		ch = ch-'A'+'a';
	}	
	if (tmp->ch >= 'A' && tmp->ch <= 'Z'){
		tmp->ch = tmp->ch-'A'+'a';
	}
	if (ch <= tmp->ch ) result->judge = true;
	return result;
}
	
Number *Char::IS_STR(){
	Boolean *result = new Boolean();
	result->judge = false;
	return result;
}

Number *Char::MAK_STR(){}
Number *Char::GET_STR(){
	String *result = new String();
	result->str += ch;
	return result;
}
Number *Char::MAK_STR(Number *number2){}
Number *Char::GET_STR(Number *number2){}

Number *Char::STR_LEN(){}
Number *Char::STR_REF(Number *number2){}
Number *Char::STR_APP(Number *number2){}
Number *Char::STR_CPY(){}
Number *Char::SUB_STR(Number *number1, Number *number2){}

Number *Char::IS_CHA(){
	Boolean *result = new Boolean();
	result->judge = true;
	return result;
}	

Number *Char::CHA_ALPH(){
	Boolean *result = new Boolean();
	result->judge = false;
	if ((ch >= 'a' && ch <= 'z') || (ch >= 'A' && ch <= 'Z'))  result->judge = true;
	return result;
}

Number *Char::CHA_NUM(){
	Boolean *result = new Boolean();
	result->judge = false;
	if (ch >= '0' && ch <= '9')  result->judge = true;
	return result;
}

Number *Char::CHA_WHIT(){
	Boolean *result = new Boolean();
	result->judge = false;
	if (ch == ' ')  result->judge = true;
	return result;
}

Number *Char::IS_CHA_UPP(){
	Boolean *result = new Boolean();
	result->judge = false;
	if (ch >= 'A' && ch <= 'Z'){
		result->judge = true;
	}		
	return result;
}

Number *Char::IS_CHA_LOW(){
	Boolean *result = new Boolean();
	result->judge = false;
	if (ch >= 'a' && ch <= 'z'){
		result->judge = true;
	}		
	return result;
}

Number *Char::CHA_UP(){
	Char *result = new Char();
	if (ch >= 'A' && ch <= 'Z'){
		result->ch = ch;
	}		
	if (ch >= 'a' && ch <= 'z'){
		result->ch = ch-'a'+'A';
	}	
	return result;
}

Number *Char::CHA_DOWN(){
	Char *result = new Char();
	if (ch >= 'A' && ch <= 'Z'){
		result->ch = ch-'A'+'a';
	}		
	if (ch >= 'a' && ch <= 'z'){
		result->ch = ch;
	}	
	return result;
}
	
Number *Char::CHA_INT(){
	Rational *result = new Rational("0","1");
	int tmp = int(ch);
	string num;
	stringstream s;
    s<<tmp;s>>num;
	result->numerator_ = LongInt(num);
	return result;
}

Number *Char::INT_CHA(){}
Number *Char::STR_NUM(){}
Number *Char::NUM_STR(){}
void Char::print(){
	cout<< "#\\";
	if (ch == '\n') cout << "newline";
	else if (ch == '\b') cout << "backspace";	
	else if (ch == '\f') cout << "page";
	else if (ch == '\r') cout << "return";
	else if (ch == '\t') cout << "tab";
	else if (ch == '\v') cout << "vtab";
	else cout << ch;
}

Char *Char::from_string(char *expr){
	string str(expr);
	char ch;
	if (str[0] != '#') return NULL;
	if (str[1] != '\\') return NULL;
	if (str.length() == 2) ch = ' ';
	else if (str.length() == 3) ch = str[2];
	else if (str == "#\\space")
		ch = ' ';
	else if (str == "#\\newline")
		ch = '\n';
	else if (str == "#\\return")
		ch = '\r';
	else if (str == "#\\page")
		ch = '\f';
	else if (str == "#\\tab")
		ch = '\t';
	else if (str == "#\\backspace")
		ch = '\b';
	else return NULL;
	return new Char(ch);
}

Char::~Char(){
}
Number *Char::IS_INTEGER(){
	Boolean *result = new Boolean();
	result->judge = false;
	return result;
}
Number *Char::IS_RATIONAL(){
	Boolean *result = new Boolean();
	result->judge = false;
	return result;
}
Number *Char::IS_REAL(){
	Boolean *result = new Boolean();
	result->judge = false;
	return result;
}
Number *Char::IS_COMPLEX(){
	Boolean *result = new Boolean();
	result->judge = false;
	return result;
}
Number *Char::IS_NUMBER(){
	Boolean *result = new Boolean();
	result->judge = false;
	return result;
}
Number *Char::reless(Number *number2){
}
Number *Char::relesseql(Number *number2){
}
Number *Char::regter(Number *number2){
}
Number *Char::regtereql(Number *number2){
}
Number *Char::convert(Number *number2){
	if (number2->type_ == 5)
	{	Char *tmp = SCAST_CHAR(number2);
		return new Char(tmp->ch);
	}
}
Number *Char::add(Number *number2){
}
Number *Char::sub(Number *number2){
}
Number *Char::mul(Number *number2){
}
Number *Char::div(Number *number2){
}
Number *Char::ABS(){
}
Number *Char::QUOTIENT(Number *number2){
}
Number *Char::REMAINDER(Number *number2){
}
Number *Char::MODULO(Number *number2){
}
Number *Char::GCD(Number *number2){
}
Number *Char::LCM(Number *number2){
}
Number *Char::EXPT(Number *number2){
}
Number *Char::SQRT(){
}
Number *Char::Max(Number *number2){
}
Number *Char::Min(Number *number2){
}
Number *Char::NUMERATOR(){
}
Number *Char::DENOMINATOR(){
}
Number *Char::floor(){
}
Number *Char::ceiling(){
}
Number *Char::truncate(){
}
Number *Char::ROUND(){
}
Number *Char::exact(){
}
Number *Char::inexact(){
}
Number *Char::realpart(){
}
Number *Char::imagepart(){
}
Number *Char::SIN(){
}
Number *Char::COS(){
}
Number *Char::TAN(){
}
Number *Char::ARCSIN(){
}
Number *Char::ARCCOS(){
}
Number *Char::ARCTAN(){
}
Number *Char::EXP(){
}
Number *Char::LOG(){
}
Number *Char::MAGNITUDE(){
}
Number *Char::ANGLE(){
}
Number *Char::MAKE_RECTANGULAR(Number *number2){
}
Number *Char::MAKE_POLAR(Number *number2){
}
Number *Char::IS_EXACT(){
	Boolean *result = new Boolean();
	result->judge = false;
	return result;
}
Number *Char::IS_INEXACT(){
	Boolean *result = new Boolean();
	result->judge = false;
	return result;
}
Number *Char::IS_ZERO(){
	Boolean *result = new Boolean();
	result->judge = false;
	return result;
}
Number *Char::IS_NEGATIVE(){
	Boolean *result = new Boolean();
	result->judge = false;
	return result;
}
Number *Char::IS_POSITIVE(){
	Boolean *result = new Boolean();
	result->judge = false;
	return result;
}
Number *Char::IS_ODD(){
	Boolean *result = new Boolean();
	result->judge = false;
	return result;
}
Number *Char::IS_EVEN(){
	Boolean *result = new Boolean();
	result->judge = false;
	return result;
}
