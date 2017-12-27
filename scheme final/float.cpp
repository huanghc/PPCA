#include "float.h"
#include "rational.h"
#include "complex.h"
#include "boolean.h"
#include "string.h"
#include "char.h"
#include <cstdio>
#include <cstdlib>
#include <cassert>
#include <cstring>
#include <complex>
#include <cmath>
#include <iostream>
#include <algorithm>
#include <sstream>
#define Abs(x) ((x)<0?(-(x)):(x))
#define MAX2(x, y) (x>y? x : y)
#define MIN2(x, y) (x>y? y : x)
using namespace std;

Float::Float(double number) : number_(number){
	type_ = FLOAT;
}

Float::~Float(){

}

Number *Float::convert(Number *number2){
	assert(number2->type_ <= type_);
	Float *ttmp = new Float();
	switch (number2->type_){
	case RATIONAL:{
		Rational *tmp = SCAST_RATIONAL(number2);
		ttmp->number_ = (double)tmp->numerator_ / (double)tmp->denominator_;
		break;
	}
	case FLOAT:{
		Float *tmp = SCAST_FLOAT(number2);
		ttmp->number_ = tmp->number_;
		break;
	}
	default:
		assert(0 && "type_ not defined");
	}
	return ttmp;
}

Number *Float::add(Number *number2){
	Float *tmp = SCAST_FLOAT(number2);
	Float *ttmp = new Float(number_ + tmp->number_);
	return ttmp;
}

Number *Float::sub(Number *number2){
	Float *tmp = SCAST_FLOAT(number2);
	Float *ttmp = new Float(number_ - tmp->number_);
	return ttmp;
}

Number *Float::mul(Number *number2){
	Float *tmp = SCAST_FLOAT(number2);
	Float *ttmp = new Float(number_ * tmp->number_);
	return ttmp;
}

Number *Float::div(Number *number2){
	Float *tmp = SCAST_FLOAT(number2);
	assert(Abs(tmp->number_)>1e-999 && "divide zero");
	Float *ttmp = new Float(number_ / tmp->number_);
	return ttmp;
}

Number *Float::QUOTIENT(Number *number2){
    Float *tmp = SCAST_FLOAT(number2);
	assert(Abs(tmp->number_)>1e-999 && "divide zero");
	Float *ttmp = new Float(number_ / tmp->number_);
	return ttmp;
}

Number *Float::EXPT(Number *number2){
    Float *tmp = SCAST_FLOAT(number2);
    if (number_ ==0 && tmp->number_ ==0) return new Float(1.0);
    if (number_ ==0 ) return new Float(0.0);
    if (tmp->number_ ==0) return new Float(1.0);
    else { 
        double ttmp = pow(number_, tmp->number_);
        return new Float(ttmp);
    }
}

Number *Float::Max(Number *number2){
	Float *tmp = SCAST_FLOAT(number2);
	Float *ttmp = new Float(MAX2(number_, tmp->number_));
	return ttmp;
}

Number *Float::Min(Number *number2){
	Float *tmp = SCAST_FLOAT(number2);
	Float *ttmp = new Float(MIN2(number_, tmp->number_));
	return ttmp;
}

Number *Float::ABS(){
	if (this->number_ < 0) number_ = -number_;
	return this;
}

Number *Float::SQRT(){
   if (number_>=0){   
        return new Float(double(sqrt(number_)));
    }
    else{   
        double x=sqrt(-number_);
        return new Complex(new Float(0),new Float(x));
    }
}

Number *Float::NUMERATOR()
{
	Rational *ttmp = SCAST_RATIONAL(exact());
	return ttmp->NUMERATOR();
}

Number *Float::DENOMINATOR()
{
	Rational *ttmp = SCAST_RATIONAL(exact());
	return ttmp->DENOMINATOR();
}

Number *Float::exact()
{
	Rational *ttmp=new Rational();
	long long tmp=1;
	double x=number_;
	long long tmpx=(long double)number_;
    
    while (x!=tmpx){
        x*=2;
        tmpx=(long double)x;
        tmp*=2;
    }
    string num,den;
    stringstream s;
    s<<(long long)x;s>>num;
	s.clear();
    s<<tmp;s>>den;
	s.clear();    
    ttmp->numerator_=LongInt(num);
    ttmp->denominator_=LongInt(den);
    ttmp->reduce();
    return ttmp;
}

Number *Float::inexact()
{
	return this;
}

Number *Float::floor()
{
	double ttmp = std::floor(number_);
	return new Float(ttmp);
}

Number *Float::ceiling()
{
	double ttmp = std::ceil(number_);
	return new Float(ttmp);
}

Number *Float::truncate()
{
    if (number_<0)  this->ceiling();  
    else this->floor();  
}

Number *Float::ROUND()
{
    double tmpceil,tmpflor;
	tmpflor=std::floor(number_);
	tmpceil=std::ceil(number_);
    if ((number_-tmpflor)<(tmpceil-number_)) return new Float(tmpflor);
    if ((number_-tmpflor)>(tmpceil-number_)) return new Float(tmpceil);
    if ((number_-tmpflor)==(tmpceil-number_)) {
        if (((long long)tmpflor)%2==0) return new Float(tmpflor);
        else return new Float(tmpceil);
    }
}

Number *Float::realpart(){
	return this;
}

Number *Float::imagepart(){
	return new Float(0.0);
}


Number *Float::EXP(){
	Float *ttmp = new Float();
	ttmp->number_ = exp(number_);
	return ttmp;
}

Number *Float::LOG(){
	Float *ttmp = new Float();
	ttmp->number_ = log(number_);
	return ttmp;
}

Number *Float::reless(Number *number2){
	Boolean *boolfg = new Boolean();
	Float *tmp = SCAST_FLOAT(number2);
	if (number_ < tmp->number_) boolfg->judge = true;
	else boolfg->judge = false;
	return boolfg;
}

Number *Float::regter(Number *number2){
	Boolean *boolfg = new Boolean();
	Float *tmp = SCAST_FLOAT(number2);
	if (number_ > tmp->number_) boolfg->judge = true;
	else boolfg->judge = false;
	return boolfg;
}

Number *Float::relesseql(Number *number2){
	Boolean *boolfg = new Boolean();
	Float *tmp = SCAST_FLOAT(number2);
	if (number_ <= tmp->number_) boolfg->judge = true;
	else boolfg->judge = false;
	return boolfg;
}

Number *Float::regtereql(Number *number2){
	Boolean *boolfg = new Boolean();
	Float *tmp = SCAST_FLOAT(number2);
	if (number_ >= tmp->number_) boolfg->judge = true;
	else boolfg->judge = false;
	return boolfg;
}

Number *Float::IS_ZERO(){
	Boolean *boolfg = new Boolean();
	if (number_ == 0) boolfg->judge = true;
	else boolfg->judge = false;
	return boolfg;
}

Number *Float::IS_NEGATIVE(){
	Boolean *boolfg = new Boolean();
	if (number_ < 0) boolfg->judge = true;
	else boolfg->judge = false;
	return boolfg;
}

Number *Float::IS_POSITIVE(){
	Boolean *boolfg = new Boolean();
	if (number_ > 0) boolfg->judge = true;
	else boolfg->judge = false;
	return boolfg;
}

Number *Float::IS_ODD(){
	Boolean *boolfg = new Boolean();
	if (number_ == int(number_))
	{
		if (int(number_) % 2 == 0) boolfg->judge = false;
		else boolfg->judge = true;
	}
	else throw 0;
	return boolfg;
}

Number *Float::IS_EVEN(){
	Boolean *boolfg = new Boolean();
	if (number_ == int(number_))
	{
		if (int(number_) % 2 == 0) boolfg->judge = true;
		else boolfg->judge = false;
	}
	else throw 0;
	return boolfg;
}

Number *Float::SIN(){
	Float *ttmp = new Float();
	ttmp->number_ = sin(number_);
	return ttmp;
}

Number *Float::COS(){
	Float *ttmp = new Float();
	ttmp->number_ = cos(number_);
	return ttmp;
}

Number *Float::TAN(){
	Float *ttmp = new Float();
	ttmp->number_ = tan(number_);
	return ttmp;
}

Number *Float::ARCSIN(){
	Complex *result = new Complex();
	complex<double> a(number_,0);
	complex<double> res=asin(a);
	result->real=new Float(res.real());
	result->imag=new Float(res.imag());
	if (res.imag()==0.0){
		return new Float(res.real());
	}
	return result;
}

Number *Float::ARCCOS(){
	Complex *result = new Complex();
	complex<double> a(number_,0);
	complex<double> res=acos(a);
	result->real=new Float(res.real());
	result->imag=new Float(res.imag());
	if (res.imag()==0.0){
		return new Float(res.real());
	}
	return result;
}

Number *Float::ARCTAN(){
	Complex *result = new Complex();
	complex<double> a(number_,0);
	complex<double> res=atan(a);
	result->real=new Float(res.real());
	result->imag=new Float(res.imag());
	if (res.imag()==0.0){
		return new Float(res.real());
	}
	return result;
}

Number *Float::MAGNITUDE(){
	Float *ttmp = new Float();
	ttmp->number_ = abs(number_);
	return ttmp;
}

Number *Float::ANGLE(){
	Float *ttmp = new Float(0.0);
	if (number_<0) ttmp->number_=3.14159265358979323;
	return ttmp;
}

Number *Float::MAKE_POLAR(Number *number2){
	Complex *ttmp = new Complex();
	Float *tmpp = SCAST_FLOAT(number2);
	ttmp->real = tmpp->COS()->mul(this);
	ttmp->imag = tmpp->SIN()->mul(this);
	return ttmp;
}

Number *Float::MAKE_RECTANGULAR(Number *number2){
	Complex *ttmp = new Complex();
	Float *tmpp = SCAST_FLOAT(number2);
	ttmp->real = this;
	ttmp->imag = tmpp;
	return ttmp;
}

Number *Float::IS_EXACT(){
	Boolean *boolfg = new Boolean();
	boolfg->judge = false;
	return boolfg;
}

Number *Float::IS_INEXACT(){
	Boolean *boolfg = new Boolean();
	boolfg->judge = true;
	return boolfg;
}

Number *Float::IS_INTEGER(){
	Boolean *boolfg = new Boolean();
	if (number_ == int(number_))
	{
		boolfg->judge = true;
	}
	else boolfg->judge = false;
	return boolfg;
}

Number *Float::IS_RATIONAL(){
	Boolean *boolfg = new Boolean();
	boolfg->judge = true;
	return boolfg;
}

Number *Float::IS_REAL(){
	Boolean *boolfg = new Boolean();
	boolfg->judge = true;
	return boolfg;
}

Number *Float::IS_COMPLEX(){
	Boolean *boolfg = new Boolean();
	boolfg->judge = true;
	return boolfg;
}

Number *Float::IS_NUMBER(){
	Boolean *boolfg = new Boolean();
	boolfg->judge = true;
	return boolfg;
}

void Float::print(){
	printf("%.16g", number_);
}

Float *Float::from_string(char *expr){
	char *end_pointer;
	string s(expr);
	int findi = s.find('i');
    int jing = s.find('#');
	int yinhao = s.find('"');
	if (jing != s.npos) return NULL;
	if (yinhao != s.npos) return NULL;
    if (findi != s.npos) return NULL;
	double val = strtod(expr, &end_pointer);
	if (end_pointer == expr || end_pointer != expr + strlen(expr))
		return NULL;
	return new Float(val);
}

Number *Float::REMAINDER(Number *number2){
}

Number *Float::MODULO(Number *number2){
}

Number *Float::GCD(Number *number2){
}

Number *Float::LCM(Number *number2){
}
Number *Float::EQL(Number *number2){
	Boolean *result = new Boolean();
	result->judge = false;
	Float *tmp = SCAST_FLOAT(number2);
	double tmp1 = number_ - tmp->number_;
	if (abs(tmp1) <= 1e-10) result->judge = true;
	return result;
}	
Number *Float::STR_EQL(Number *number2){}
Number *Float::STR_CIEQL(Number *number2){}
Number *Float::STR_LESS(Number *number2){}
Number *Float::STR_CILESS(Number *number2){}
Number *Float::STR_LESSEQL(Number *number2){}
Number *Float::STR_CILESSEQL(Number *number2){}
Number *Float::CHA_EQL(Number *number2){}
Number *Float::CHA_CIEQL(Number *number2){}
Number *Float::CHA_LESS(Number *number2){}
Number *Float::CHA_CILESS(Number *number2){}
Number *Float::CHA_LESSEQL(Number *number2){}
Number *Float::CHA_CILESSEQL(Number *number2){}
	
Number *Float::IS_STR(){
	Boolean *result = new Boolean();
	result->judge = false;
	return result;
}
Number *Float::MAK_STR(){
	String *result = new String();
	int tmp = int(number_);
	for (int i=0;i<tmp;++i)
	{	char c = NULL;
		result->str += c;
	}
	return result;
}
Number *Float::GET_STR(){}

Number *Float::MAK_STR(Number *number2){
	Char *tmp = SCAST_CHAR(number2);
	String *result = new String();
	int tmp1 = int(number_);
	for (int i=0;i<tmp1;++i)
	{	result->str += tmp->ch;
	}
	return result;
}

Number *Float::GET_STR(Number *number2){}
Number *Float::STR_LEN(){}
Number *Float::STR_REF(Number *number2){}
Number *Float::STR_APP(Number *number2){}
Number *Float::STR_CPY(){}
Number *Float::SUB_STR(Number *number1, Number *number2){}
Number *Float::IS_CHA(){
	Boolean *result = new Boolean();
	result->judge = false;
	return result;
}	
Number *Float::CHA_ALPH(){
	Boolean *result = new Boolean();
	result->judge = false;
	return result;
}
Number *Float::CHA_NUM(){
	Boolean *result = new Boolean();
	result->judge = false;
	return result;
}
Number *Float::CHA_WHIT(){
	Boolean *result = new Boolean();
	result->judge = false;
	return result;
}
Number *Float::IS_CHA_UPP(){
	Boolean *result = new Boolean();
	result->judge = false;
	return result;
}
Number *Float::IS_CHA_LOW(){
	Boolean *result = new Boolean();
	result->judge = false;
	return result;
}
Number *Float::CHA_UP(){}
Number *Float::CHA_DOWN(){}
	
Number *Float::CHA_INT(){}
Number *Float::INT_CHA(){
	Char *result = new Char();
	int tmp = int(number_);
	result->ch = tmp;
	return result;
}
Number *Float::STR_NUM(){}
Number *Float::NUM_STR(){
	string result;
	stringstream tmp;
	tmp << number_;
	tmp >> result;
	return new String(result);
}
