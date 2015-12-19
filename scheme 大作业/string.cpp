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
#include <string>
#include <sstream>
#include <cmath> 
#include <complex>
#include <iostream>
using namespace std;

#define MAX(x,y) ((x)<(y)?(y):(x))
#define MIN(x,y) ((x)<(y)?(x):(y))

String::String(string tmpstr) :str(tmpstr){
	type_ = STRING;
}

void String::lower(){
	int len = str.length();
	for (int i=0;i<len;++i){
		if (str[i] >= 'A' && str[i] <= 'Z'){
			str[i] = str[i]-'A'+'a';
		}
	}
}

Number *String::EQL(Number *number2){
	Boolean *boolfg = new Boolean();
	String *tmp = SCAST_STRING(number2);
	if (str==tmp->str) boolfg->judge = true;
	else boolfg->judge = false;
	return boolfg;
}
	
Number *String::STR_EQL(Number *number2){
	Boolean *boolfg = new Boolean();
	String *tmp = SCAST_STRING(number2);
	if (str==tmp->str) boolfg->judge = true;
	else boolfg->judge = false;
	return boolfg;
}

Number *String::STR_CIEQL(Number *number2){
	Boolean *boolfg = new Boolean();
	String *tmp = SCAST_STRING(number2);
	tmp->lower();this->lower();
	if (str==tmp->str) boolfg->judge = true;
	else boolfg->judge = false;
	return boolfg;
}

Number *String::STR_LESS(Number *number2){
	Boolean *boolfg = new Boolean();
	String *tmp = SCAST_STRING(number2);
	if (str<tmp->str) boolfg->judge = true;
	else boolfg->judge = false;
	return boolfg;
}

Number *String::STR_CILESS(Number *number2){
	Boolean *boolfg = new Boolean();
	String *tmp = SCAST_STRING(number2);
	tmp->lower();this->lower();
	if (str<tmp->str) boolfg->judge = true;
	else boolfg->judge = false;
	return boolfg;
}

Number *String::STR_LESSEQL(Number *number2){
	Boolean *boolfg = new Boolean();
	String *tmp = SCAST_STRING(number2);
	if (str<=tmp->str) boolfg->judge = true;
	else boolfg->judge = false;
	return boolfg;
}

Number *String::STR_CILESSEQL(Number *number2){
	Boolean *boolfg = new Boolean();
	String *tmp = SCAST_STRING(number2);
	tmp->lower();this->lower();
	if (str<=tmp->str) boolfg->judge = true;
	else boolfg->judge = false;
	return boolfg;
}

Number *String::CHA_EQL(Number *number2){}
Number *String::CHA_CIEQL(Number *number2){}
Number *String::CHA_LESS(Number *number2){}
Number *String::CHA_CILESS(Number *number2){}
Number *String::CHA_LESSEQL(Number *number2){}
Number *String::CHA_CILESSEQL(Number *number2){}
	
Number *String::IS_STR(){
	Boolean *result = new Boolean();
	result->judge = true;
	return result;
}

Number *String::MAK_STR(){
}

Number *String::MAK_STR(Number *number2){
}

Number *String::GET_STR(){

}
Number *String::GET_STR(Number *number2){
	Char *tmp = SCAST_CHAR(number2);
	String *result = new String();
	result->str = str;
	result->str += tmp->ch;
	return result;
}

Number *String::STR_LEN(){
	long long len=str.length();//cout<<len<<endl;cout<<str<<endl;
	string num;
	stringstream s;
    s<<len;s>>num;
	s.clear();
	return new Rational(num,"1");
}

Number *String::STR_REF(Number *number2){
	Rational *tmp1 = SCAST_RATIONAL(number2);
	int tmp = double(tmp1->numerator_); 
	Char *result = new Char(str[tmp]);
	return result;
}

Number *String::STR_APP(Number *number2){
	String *tmp = SCAST_STRING(number2);
	str += tmp->str;
	String *result = new String(str);
	return result;
}

Number *String::STR_CPY(){
	String *result = new String(str);
	return result;
}

Number *String::SUB_STR(Number *number1, Number *number2){
	Rational *tmp1 = SCAST_RATIONAL(number1);
	int a = double(tmp1->numerator_);
	Rational *tmp2 = SCAST_RATIONAL(number2);
	int b = double(tmp2->numerator_);
//cout<<a<<" "<<b<<" "<<endl;
	int len1 = str.length();
	String *result = new String();
	if (a>b || a>len1 || b>len1 || a<0 || b<0) return result;
	string tmp = str.substr(a,b-a);
	result->str = tmp;
	return result;
}

Number *String::IS_CHA(){
	Boolean *result = new Boolean();
	result->judge = false;
	return result;
}	
Number *String::CHA_ALPH(){
	Boolean *result = new Boolean();
	result->judge = false;
	return result;
}
Number *String::CHA_NUM(){
	Boolean *result = new Boolean();
	result->judge = false;
	return result;
}
Number *String::CHA_WHIT(){
	Boolean *result = new Boolean();
	result->judge = false;
	return result;
}

Number *String::IS_CHA_UPP(){
	Boolean *result = new Boolean();
	result->judge = false;
	return result;
}
Number *String::IS_CHA_LOW(){
	Boolean *result = new Boolean();
	result->judge = false;
	return result;
}

Number *String::CHA_UP(){}
Number *String::CHA_DOWN(){}
	
Number *String::CHA_INT(){}
Number *String::INT_CHA(){}
Number *String::STR_NUM(){
	char tmp[str.length()+10];
	for (int i=0;i<str.length();++i) tmp[i] = str[i];
	tmp[str.length()] = '\0';
	Number *result;
	result=Rational::from_string(tmp);
	if(!result) 
	{	result = Float::from_string(tmp);
		if (!result){
			result = Complex::from_string(tmp);
		}
	}
	if(result == NULL){throw 0;}
	return result;
}

Number *String::NUM_STR(){}

void String::print(){
	cout << "\"" ;
	for (long long i=0;i<str.length();++i)
	{	if (str[i] == '\b') cout << "\\b";
		else if (str[i] == '\f') cout << "\\f";
		else if (str[i] == '\n') cout << "\\n";
		else if (str[i] == '\r') cout << "\\r";
		else if (str[i] == '\t') cout << "\\t";
		else if (str[i] == '\v') cout << "\\v";		
		else if (str[i] == '\\') cout << "\\\\";	
		else if (str[i] == '\'') cout << "\\'";
		else if (str[i] == '\"') cout << "\\\"";
		else cout << str[i];
	}
	cout << "\"";
}

String *String::from_string(char *expr){
	string s(expr);
	String *tmp = new String();
	tmp->str="";
	int a = s.find('#');
	if (a != s.npos) return NULL;
	int flag=0;
	for (long long i = 0;;++i)
	{	if (s[i] == '"') ++flag;		
		else if (s[i] == '\\') {
			++i;
			if (s[i] == 'b') tmp->str+='\b';
			else if (s[i] == 'f') tmp->str+='\f';
			else if (s[i] == 'n') tmp->str+='\n';
			else if (s[i] == 'r') tmp->str+='\r';
			else if (s[i] == 't') tmp->str+='\t';
			else if (s[i] == 'v') tmp->str+='\v';
			else if (s[i] == '\\') tmp->str+='\\';
			else if (s[i] == '\'') tmp->str+='\'';
			else if (s[i] == '"') tmp->str+='"';
			else throw 0;
		}
		else tmp->str+=s[i];
		if (flag>=2) break;
	}
	return tmp;
}

String::~String(){
}
Number *String::IS_INTEGER(){
	Boolean *result = new Boolean();
	result->judge = false;
	return result;
}
Number *String::IS_RATIONAL(){
	Boolean *result = new Boolean();
	result->judge = false;
	return result;
}
Number *String::IS_REAL(){
	Boolean *result = new Boolean();
	result->judge = false;
	return result;
}
Number *String::IS_COMPLEX(){
	Boolean *result = new Boolean();
	result->judge = false;
	return result;
}
Number *String::IS_NUMBER(){
	Boolean *result = new Boolean();
	result->judge = false;
	return result;
}
Number *String::reless(Number *number2){
}
Number *String::relesseql(Number *number2){
}
Number *String::regter(Number *number2){
}
Number *String::regtereql(Number *number2){
}
Number *String::convert(Number *number2){
	if (number2->type_ == 5)
	{	Char *tmp5 = SCAST_CHAR(number2);
		String *result = new String();
		result->str += tmp5->ch;
		return result;
	}
	if (number2->type_ == 6)
	{	String *tmp6 = SCAST_STRING(number2);
		String *result = new String();
		result->str = tmp6->str;
		return result;
	}
}
Number *String::add(Number *number2){
}
Number *String::sub(Number *number2){
}
Number *String::mul(Number *number2){
}
Number *String::div(Number *number2){
}
Number *String::ABS(){
}
Number *String::QUOTIENT(Number *number2){
}
Number *String::REMAINDER(Number *number2){
}
Number *String::MODULO(Number *number2){
}
Number *String::GCD(Number *number2){
}
Number *String::LCM(Number *number2){
}
Number *String::EXPT(Number *number2){
}
Number *String::SQRT(){
}
Number *String::Max(Number *number2){
}
Number *String::Min(Number *number2){
}
Number *String::NUMERATOR(){
}
Number *String::DENOMINATOR(){
}
Number *String::floor(){
}
Number *String::ceiling(){
}
Number *String::truncate(){
}
Number *String::ROUND(){
}
Number *String::exact(){
}
Number *String::inexact(){
}
Number *String::realpart(){
}
Number *String::imagepart(){
}
Number *String::SIN(){
}
Number *String::COS(){
}
Number *String::TAN(){
}
Number *String::ARCSIN(){
}
Number *String::ARCCOS(){
}
Number *String::ARCTAN(){
}
Number *String::EXP(){
}
Number *String::LOG(){
}
Number *String::MAGNITUDE(){
}
Number *String::ANGLE(){
}
Number *String::MAKE_RECTANGULAR(Number *number2){
}
Number *String::MAKE_POLAR(Number *number2){
}
Number *String::IS_EXACT(){
	Boolean *result = new Boolean();
	result->judge = false;
	return result;
}
Number *String::IS_INEXACT(){
	Boolean *result = new Boolean();
	result->judge = false;
	return result;
}
Number *String::IS_ZERO(){
	Boolean *result = new Boolean();
	result->judge = false;
	return result;
}
Number *String::IS_NEGATIVE(){
	Boolean *result = new Boolean();
	result->judge = false;
	return result;
}
Number *String::IS_POSITIVE(){
	Boolean *result = new Boolean();
	result->judge = false;
	return result;
}
Number *String::IS_ODD(){
	Boolean *result = new Boolean();
	result->judge = false;
	return result;
}
Number *String::IS_EVEN(){
	Boolean *result = new Boolean();
	result->judge = false;
	return result;
}
