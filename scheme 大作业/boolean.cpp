#include "float.h"
#include "rational.h"
#include "complex.h"
#include "boolean.h"
#include "string.h"
#include "char.h"
#include <cassert>
#include <cstdlib>
#include <cstdio>
#include <cstring>
#include <cmath> 
#include <complex>
#include <iostream>
using namespace std;

#define MAX(x,y) ((x)<(y)?(y):(x))
#define MIN(x,y) ((x)<(y)?(x):(y))

Boolean::Boolean(bool boolfg) :judge(boolfg){
	type_ = BOOLEAN;
}

Boolean::~Boolean(){
}

Number *Boolean::IS_INTEGER(){
	Boolean *boolfg = new Boolean();
	boolfg->judge = false;
	return boolfg;
}

Number *Boolean::IS_RATIONAL(){
	Boolean *boolfg = new Boolean();
	boolfg->judge = false;
	return boolfg;
}

Number *Boolean::IS_REAL(){
	Boolean *boolfg = new Boolean();
	boolfg->judge = false;
	return boolfg;
}

Number *Boolean::IS_COMPLEX(){
	Boolean *boolfg = new Boolean();
	boolfg->judge = false;
	return boolfg;
}

Number *Boolean::IS_NUMBER(){
	Boolean *boolfg = new Boolean();
	boolfg->judge = false;
	return boolfg;
}

Number *Boolean::reless(Number *number2){
}

Number *Boolean::relesseql(Number *number2){
}

Number *Boolean::regter(Number *number2){
}

Number *Boolean::regtereql(Number *number2){
}

Number *Boolean::convert(Number *number2){
}
Number *Boolean::add(Number *number2){
}
Number *Boolean::sub(Number *number2){
}
Number *Boolean::mul(Number *number2){
}
Number *Boolean::div(Number *number2){
}
Number *Boolean::ABS(){
}
Number *Boolean::QUOTIENT(Number *number2){
}
Number *Boolean::REMAINDER(Number *number2){
}
Number *Boolean::MODULO(Number *number2){
}
Number *Boolean::GCD(Number *number2){
}
Number *Boolean::LCM(Number *number2){
}
Number *Boolean::EXPT(Number *number2){
}
Number *Boolean::SQRT(){
}
Number *Boolean::Max(Number *number2){
}
Number *Boolean::Min(Number *number2){
}
Number *Boolean::NUMERATOR(){
}
Number *Boolean::DENOMINATOR(){
}
Number *Boolean::floor(){
}
Number *Boolean::ceiling(){
}
Number *Boolean::truncate(){
}
Number *Boolean::ROUND(){
}
Number *Boolean::exact(){
}
Number *Boolean::inexact(){
}
Number *Boolean::realpart(){
}
Number *Boolean::imagepart(){
}
Number *Boolean::SIN(){
}
Number *Boolean::COS(){
}
Number *Boolean::TAN(){
}
Number *Boolean::ARCSIN(){
}
Number *Boolean::ARCCOS(){
}
Number *Boolean::ARCTAN(){
}
Number *Boolean::EXP(){
}
Number *Boolean::LOG(){
}
Number *Boolean::MAGNITUDE(){
}
Number *Boolean::ANGLE(){
}
Number *Boolean::MAKE_RECTANGULAR(Number *number2){
}
Number *Boolean::MAKE_POLAR(Number *number2){
}
Number *Boolean::IS_EXACT(){
}
Number *Boolean::IS_INEXACT(){
}
Number *Boolean::IS_ZERO(){
}
Number *Boolean::IS_NEGATIVE(){
}
Number *Boolean::IS_POSITIVE(){
}
Number *Boolean::IS_ODD(){
}
Number *Boolean::IS_EVEN(){
}
Number *Boolean::EQL(Number *number2){
	Boolean *result = new Boolean();
	result->judge = false;
	Boolean *tmp = SCAST_BOOLEAN(number2);
	if (judge==tmp->judge) result->judge = true;	
	return result;
}	
Number *Boolean::STR_EQL(Number *number2){}
Number *Boolean::STR_CIEQL(Number *number2){}
Number *Boolean::STR_LESS(Number *number2){}
Number *Boolean::STR_CILESS(Number *number2){}
Number *Boolean::STR_LESSEQL(Number *number2){}
Number *Boolean::STR_CILESSEQL(Number *number2){}
Number *Boolean::CHA_EQL(Number *number2){}
Number *Boolean::CHA_CIEQL(Number *number2){}
Number *Boolean::CHA_LESS(Number *number2){}
Number *Boolean::CHA_CILESS(Number *number2){}
Number *Boolean::CHA_LESSEQL(Number *number2){}
Number *Boolean::CHA_CILESSEQL(Number *number2){}
	
Number *Boolean::IS_STR(){
	Boolean *result = new Boolean();
	result->judge = false;
	return result;
}
Number *Boolean::MAK_STR(){}
Number *Boolean::GET_STR(){}
Number *Boolean::MAK_STR(Number *number2){}
Number *Boolean::GET_STR(Number *number2){}
Number *Boolean::STR_LEN(){}
Number *Boolean::STR_REF(Number *number2){}
Number *Boolean::STR_APP(Number *number2){}
Number *Boolean::STR_CPY(){}
Number *Boolean::SUB_STR(Number *number1, Number *number2){}
Number *Boolean::IS_CHA(){
	Boolean *result = new Boolean();
	result->judge = false;
	return result;
}	
Number *Boolean::CHA_ALPH(){
	Boolean *result = new Boolean();
	result->judge = false;
	return result;
}
Number *Boolean::CHA_NUM(){
	Boolean *result = new Boolean();
	result->judge = false;
	return result;
}
Number *Boolean::CHA_WHIT(){
	Boolean *result = new Boolean();
	result->judge = false;
	return result;
}
Number *Boolean::IS_CHA_UPP(){
	Boolean *result = new Boolean();
	result->judge = false;
	return result;
}
Number *Boolean::IS_CHA_LOW(){
	Boolean *result = new Boolean();
	result->judge = false;
	return result;
}
Number *Boolean::CHA_UP(){}
Number *Boolean::CHA_DOWN(){}
	
Number *Boolean::CHA_INT(){}
Number *Boolean::INT_CHA(){}
Number *Boolean::STR_NUM(){}
Number *Boolean::NUM_STR(){}
void Boolean::print(){
	if (judge) printf("%s", "#t");
	else printf("%s", "#f");
}

Boolean *Boolean::from_string(char *expr){
	string s(expr);
	char ch;
	int find_gang = s.find('\\');
	if (find_gang != s.npos) return NULL;
	
	if (s[0] != '#' ) return NULL;
	if (s[1] == 't') return new Boolean(true);
	else if (s[1] == 'f') return new Boolean(false);
	else return NULL;	
}

