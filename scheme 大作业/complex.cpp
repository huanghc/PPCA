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

Complex::Complex(Number *r, Number *i) :real(r), imag(i){
	type_ = COMPLEX;
}

Complex::~Complex(){

}

Number *Complex::convert(Number *number2){
	assert(number2->type_ <= type_);
	Complex *ttmp = new Complex();
	switch (number2->type_){
	case RATIONAL:{
		ttmp->real = number2;
		break;
	}
	case FLOAT:{
		ttmp->real = number2;
		break;
	}
	case COMPLEX:{
		Complex *tmp = SCAST_COMPLEX(number2);
		ttmp->real = tmp->real;
		ttmp->imag = tmp->imag;
	}
	default:
		break;
	}
	return ttmp;
}

Number *Complex::div(Number *number2)
{
	Complex *tmp = SCAST_COMPLEX(number2);
	Complex *ttmp = new Complex();
	int maxtype = MAX(MAX(real->type_, imag->type_),
	MAX(tmp->real->type_, tmp->imag->type_));
	if (maxtype == 2)
	{
		Number *tmpr, *tmpi, *tmpc;
		tmpr = new Float(0.0);
		tmpi = new Float(0.0);
		tmpc = new Float(0.0);
		tmpr = ((tmpr->convert(real))->mul(tmpr->convert(tmp->real)))
		->add((tmpi->convert(imag))->mul(tmpi->convert(tmp->imag)));
		tmpi = ((tmpi->convert(imag))->mul(tmpi->convert(tmp->real)))
		->sub((tmpi->convert(real))->mul(tmpi->convert(tmp->imag)));
		tmpc = ((tmpc->convert(tmp->real))->mul(tmpc->convert(tmp->real)))
		->add((tmpc->convert(tmp->imag))->mul(tmpc->convert(tmp->imag)));
		tmpr = tmpr->div(tmpc);
		tmpi = tmpi->div(tmpc);
		ttmp->real = tmpr;
		ttmp->imag = tmpi;
		return ttmp;
	}
	else
	{
		ttmp->real = ((real->mul(tmp->real))->add(imag->mul(tmp->imag)))
		->div(((tmp->real)->mul(tmp->real))->add((tmp->imag)->mul(tmp->imag)));
		ttmp->imag = ((imag->mul(tmp->real))->sub(real->mul(tmp->imag)))
		->div(((tmp->real)->mul(tmp->real))->add((tmp->imag)->mul(tmp->imag)));
		return ttmp;
	}
}

Number *Complex::add(Number *number2)
{
	Complex *tmp = SCAST_COMPLEX(number2);
	Complex *ttmp = new Complex();
	int maxtype = MAX(MAX(real->type_, imag->type_), 
	MAX(tmp->real->type_, tmp->imag->type_));
	if (maxtype == 2)
	{
		Number *tmpr, *tmpi;
		tmpr = new Float(0.0);
		tmpi = new Float(0.0);
		tmpr = (tmpr->convert(real))->add(tmpr->convert(tmp->real));
		tmpi = (tmpi->convert(imag))->add(tmpi->convert(tmp->imag));
		ttmp->real = tmpr;
		ttmp->imag = tmpi;
		return ttmp;
	}
	else
	{
		ttmp->real = real->add(tmp->real);
		ttmp->imag = imag->add(tmp->imag);
		return ttmp;
	}
}


Number *Complex::mul(Number *number2)
{
	Complex *tmp = SCAST_COMPLEX(number2);
	Complex *ttmp = new Complex();
	int maxtype = MAX(MAX(real->type_, imag->type_), 
	MAX(tmp->real->type_, tmp->imag->type_));
	if (maxtype == 2)
	{
		Number *tmpr, *tmpi;
		tmpr = new Float(0.0);
		tmpi = new Float(0.0);
		tmpr = ((tmpr->convert(real))->mul(tmpr->convert(tmp->real)))
		->sub((tmpi->convert(imag))->mul(tmpi->convert(tmp->imag)));
		tmpi = ((tmpi->convert(real))->mul(tmpi->convert(tmp->imag)))
		->add((tmpi->convert(imag))->mul(tmpi->convert(tmp->real)));
		ttmp->real = tmpr;
		ttmp->imag = tmpi;
		return ttmp;
	}
	else
	{
		ttmp->real = (real->mul(tmp->real))->sub(imag->mul(tmp->imag));
		ttmp->imag = (imag->mul(tmp->real))->add(real->mul(tmp->imag));
		return ttmp;
	}
}

Number *Complex::sub(Number *number2)
{
	Complex *tmp = SCAST_COMPLEX(number2);
	Complex *ttmp = new Complex();
	int maxtype = MAX(MAX(real->type_, imag->type_), 
	MAX(tmp->real->type_, tmp->imag->type_));
	if (maxtype == 2)
	{
		Number *tmpr, *tmpi;
		tmpr = new Float(0.0);
		tmpi = new Float(0.0);
		tmpr = (tmpr->convert(real))->sub(tmpr->convert(tmp->real));
		tmpi = (tmpi->convert(imag))->sub(tmpi->convert(tmp->imag));
		ttmp->real = tmpr;
		ttmp->imag = tmpi;
		return ttmp;
	}
	else
	{
		ttmp->real = real->sub(tmp->real);
		ttmp->imag = imag->sub(tmp->imag);
		return ttmp;
	}
}

Number *Complex::exact()
{
	real = real->exact();
	imag = imag->exact();
	return this;
}

Number *Complex::inexact()
{
	real = real->inexact();
	imag = imag->inexact();
	return this;
}

Number *Complex::realpart()
{
	return real;
}

Number *Complex::imagepart()
{
	return imag;
}

Number *Complex::Max(Number *number2)
{
	Complex *tmp = SCAST_COMPLEX(number2);
	Complex *ttmp = new Complex();
	if (tmp->real->type_ > real->type_)
	{
		ttmp->real = tmp->real->Max(real);
	}
	else
	{
		ttmp->real = real->Max(tmp->real);
	}
	return ttmp;
}

Number *Complex::Min(Number *number2)
{
	Complex *tmp = SCAST_COMPLEX(number2);
	Complex *ttmp = new Complex();
	if (tmp->real->type_ > real->type_)
	{
		ttmp->real = tmp->real->Min(real);
	}
	else
	{
		ttmp->real = real->Min(tmp->real);
	}
	return ttmp;
}

Number *Complex::ABS(){
	Float *ttmp = new Float();
	Complex *tmp;
	if (real->type_ == 1) {
		tmp = SCAST_COMPLEX(inexact());
	}
	else{
		tmp = this;
	}
	complex<double> x(SCAST_FLOAT(tmp->real)->number_, 
	SCAST_FLOAT(tmp->imag)->number_);
	double tmmp = pow(x.real(), 2);
	double tmpp = pow(x.imag(), 2);
	ttmp->number_ = sqrt(tmmp + tmpp);
	return ttmp;
}

Number *Complex::SQRT()
{
	Complex *ttmp = new Complex(),*tmp;
	if (real->type_ == 1) {
		tmp = SCAST_COMPLEX(inexact());
	}
	else{
		tmp = this;
	}
	complex<double> tmmp(SCAST_FLOAT(tmp->real)->number_, 
	SCAST_FLOAT(tmp->imag)->number_);
	complex<double> res = pow(tmmp,0.5);
	ttmp->imag = new Float(res.imag());
	ttmp->real = new Float(res.real());	
	if (real->type_ == 1){
		delete tmp;
	}
	return ttmp;
}

Number *Complex::QUOTIENT(Number *number2){
	Complex *tmp = SCAST_COMPLEX(number2);
	Complex *ttmp = new Complex();
	ttmp->real = real->QUOTIENT(tmp->real);
	return ttmp;
}

Number *Complex::REMAINDER(Number *number2)
{
	Complex *tmp = SCAST_COMPLEX(number2);
	Complex *ttmp = new Complex();
	ttmp->real = real->REMAINDER(tmp->real);
	return ttmp;
}

Number *Complex::MODULO(Number *number2)
{
	Complex *tmp = SCAST_COMPLEX(number2);
	Complex *ttmp = new Complex();
	ttmp->real = real->MODULO(tmp->real);
	return ttmp;
}

Number *Complex::GCD(Number *number2)
{
}

Number *Complex::LCM(Number *number2)
{
}

Number *Complex::EXPT(Number *number2)
{
	Complex *ttmp = new Complex(), *tmp1, *tmp2;
	if (real->type_ == 1) {
		tmp1 = SCAST_COMPLEX(inexact());
		tmp2 = SCAST_COMPLEX(number2->inexact());
	}
	else{
		tmp1 = this;
		tmp2 = SCAST_COMPLEX(number2);
	}
	complex<double> tmmp(SCAST_FLOAT(tmp1->real)->number_, 
	SCAST_FLOAT(tmp1->imag)->number_);
	complex<double> tmpp(SCAST_FLOAT(tmp2->real)->number_, 
	SCAST_FLOAT(tmp2->imag)->number_);
	complex <double>res = pow(tmmp, tmpp);
	ttmp->real = new Float(res.real());
	ttmp->imag = new Float(res.imag());
	if (real->type_ == 1){
		delete tmp1;
		delete tmp2;
	}
	return ttmp;
}

Number *Complex::NUMERATOR()
{
	Complex *ttmp = new Complex();
	if (real->type_ == 2) return NULL;
	ttmp->real = real->NUMERATOR();
	return ttmp;
}

Number *Complex::DENOMINATOR()
{
	Complex *ttmp = new Complex();
	if (real->type_ == 2) return NULL;
	ttmp->real = real->DENOMINATOR();
	return ttmp;
}

Number *Complex::floor()
{
}

Number *Complex::ceiling()
{
}

Number *Complex::truncate()
{
}

Number *Complex::ROUND()
{
}

Number *Complex::SIN(){
	Complex *tmp1 = SCAST_COMPLEX(inexact());
	complex<double> tmpa(SCAST_FLOAT(tmp1->real)->number_,
	SCAST_FLOAT(tmp1->imag)->number_);
	complex<double> ans = sin(tmpa);

	Complex *result = new Complex();	
	result->real = new Float(ans.real());
	result->imag = new Float(ans.imag());
	return result;
}

Number *Complex::COS(){
	Complex *tmp1 = SCAST_COMPLEX(inexact());
	complex<double> tmpa(SCAST_FLOAT(tmp1->real)->number_,
	SCAST_FLOAT(tmp1->imag)->number_);
	complex<double> ans = cos(tmpa);

	Complex *result = new Complex();	
	result->real = new Float(ans.real());
	result->imag = new Float(ans.imag());
	return result;
}

Number *Complex::TAN(){
	Complex *tmp1 = SCAST_COMPLEX(inexact());
	complex<double> tmpa(SCAST_FLOAT(tmp1->real)->number_,
	SCAST_FLOAT(tmp1->imag)->number_);
	complex<double> ans = tan(tmpa);

	Complex *result = new Complex();	
	result->real = new Float(ans.real());
	result->imag = new Float(ans.imag());
	return result;
}

Number *Complex::ARCSIN(){
	Complex *tmp1 = SCAST_COMPLEX(inexact());
	complex<double> tmpa(SCAST_FLOAT(tmp1->real)->number_,
	SCAST_FLOAT(tmp1->imag)->number_);
	complex<double> ans = asin(tmpa);

	Complex *result = new Complex();	
	result->real = new Float(ans.real());
	result->imag = new Float(ans.imag());
	return result;
}

Number *Complex::ARCCOS(){
	Complex *tmp1 = SCAST_COMPLEX(inexact());
	complex<double> tmpa(SCAST_FLOAT(tmp1->real)->number_,
	SCAST_FLOAT(tmp1->imag)->number_);
	complex<double> ans = acos(tmpa);

	Complex *result = new Complex();	
	result->real = new Float(ans.real());
	result->imag = new Float(ans.imag());
	return result;
}

Number *Complex::ARCTAN(){
	Complex *tmp1 = SCAST_COMPLEX(inexact());
	complex<double> tmpa(SCAST_FLOAT(tmp1->real)->number_,
	SCAST_FLOAT(tmp1->imag)->number_);
	complex<double> ans = atan(tmpa);

	Complex *result = new Complex();	
	result->real = new Float(ans.real());
	result->imag = new Float(ans.imag());
	return result;
}

Number *Complex::EXP(){
	Complex *tmp1 = SCAST_COMPLEX(inexact());
	complex<double> tmpa(SCAST_FLOAT(tmp1->real)->number_,
	SCAST_FLOAT(tmp1->imag)->number_);
	complex<double> ans = exp(tmpa);

	Complex *result = new Complex();	
	result->real = new Float(ans.real());
	result->imag = new Float(ans.imag());
	return result;
}

Number *Complex::LOG(){
	Complex *tmp1 = SCAST_COMPLEX(inexact());
	complex<double> tmpa(SCAST_FLOAT(tmp1->real)->number_,
	SCAST_FLOAT(tmp1->imag)->number_);
	complex<double> ans = log(tmpa);

	Complex *result = new Complex();	
	result->real = new Float(ans.real());
	result->imag = new Float(ans.imag());
	return result;
}

Number *Complex::MAGNITUDE(){
	Float *ttmp = new Float();
	Complex *tmp = this;
	if (real->type_ == 1) {
		tmp = SCAST_COMPLEX(inexact());
	}
	complex<double> x(SCAST_FLOAT(tmp->real)->number_, 
	SCAST_FLOAT(tmp->imag)->number_);
	double tmmp = pow(x.real(), 2);
	double tmpp = pow(x.imag(), 2);
	ttmp->number_ = sqrt(tmmp + tmpp);
	return ttmp;
}

Number *Complex::ANGLE(){
	Number *result = new Float(0.0);
	if (real->type_ == 1 && imag->type_ == 1)
	{	Number *tmp1,*tmp2,*tmp3;
		tmp1 = real;
		tmp2 = imag;
		tmp3 = tmp2->div(tmp1);
		result = tmp3->ARCTAN();
	}
	else
	{	double tmp4,tmp5;
		Complex *tmp = this;
		complex<double> x(SCAST_FLOAT(tmp->real)->number_, 
		SCAST_FLOAT(tmp->imag)->number_);
		tmp4 = x.real();
		tmp5 = x.imag();
		result = new Float(atan(tmp5/tmp4));
	}
	return result;
}

Number *Complex::IS_EXACT(){
	Boolean *boolfg = new Boolean();
	if (real->type_ == 2 || imag->type_ == 2) boolfg->judge = false;
	else boolfg->judge = true;
	return boolfg;
}

Number *Complex::IS_INEXACT(){
	Boolean *boolfg = new Boolean();
	if (real->type_ == 2 || imag->type_ == 2) boolfg->judge = true;
	else boolfg->judge = false;
	return boolfg;
}

Number *Complex::IS_ZERO(){
	Boolean *boolfg = new Boolean();
	boolfg->judge = true;
	if (!SCAST_BOOLEAN(real->IS_ZERO())->judge) boolfg->judge = false;
	if (!SCAST_BOOLEAN(imag->IS_ZERO())->judge) boolfg->judge = false;
	return boolfg;
}

Number *Complex::IS_NEGATIVE(){
	Boolean *boolfg = new Boolean();
	boolfg->judge = true;
	if (!SCAST_BOOLEAN(real->IS_NEGATIVE())->judge) boolfg->judge = false;
	if (!SCAST_BOOLEAN(imag->IS_ZERO())->judge) boolfg->judge = false;
	return boolfg;
}

Number *Complex::IS_POSITIVE(){
	Boolean *boolfg = new Boolean();
	boolfg->judge = true;
	if (!SCAST_BOOLEAN(real->IS_POSITIVE())->judge) boolfg->judge = false;
	if (!SCAST_BOOLEAN(imag->IS_ZERO())->judge) boolfg->judge = false;
	return boolfg;
}

Number *Complex::IS_ODD(){
	Boolean *boolfg = new Boolean();
	boolfg->judge = true;
	if (!SCAST_BOOLEAN(real->IS_ODD())->judge) boolfg->judge = false;
	if (!SCAST_BOOLEAN(imag->IS_ZERO())->judge) boolfg->judge = false;
	return boolfg;
}

Number *Complex::IS_EVEN(){
	Boolean *boolfg = new Boolean();
	boolfg->judge = true;
	if (!SCAST_BOOLEAN(real->IS_EVEN())->judge) boolfg->judge = false;
	if (!SCAST_BOOLEAN(imag->IS_ZERO())->judge) boolfg->judge = false;
	return boolfg;
}

Number *Complex::IS_INTEGER(){
	Boolean *boolfg = new Boolean();
	boolfg->judge = true;
	if (!SCAST_BOOLEAN(real->IS_INTEGER())->judge) boolfg->judge = false;
	if (!SCAST_BOOLEAN(imag->IS_ZERO())->judge) boolfg->judge = false;
	return boolfg;
}

Number *Complex::IS_RATIONAL(){
	Boolean *boolfg = new Boolean();
	boolfg->judge = true;
	if (!SCAST_BOOLEAN(real->IS_RATIONAL())->judge) boolfg->judge = false;
	if (!SCAST_BOOLEAN(imag->IS_ZERO())->judge) boolfg->judge = false;
	return boolfg;
}

Number *Complex::IS_REAL(){
	Boolean *boolfg = new Boolean();
	boolfg->judge = true;
	if (!SCAST_BOOLEAN(imag->IS_ZERO())->judge) boolfg->judge = false;
	return boolfg;
}

Number *Complex::IS_COMPLEX(){
	Boolean *boolfg = new Boolean();
	boolfg->judge = true;
	return boolfg;
}

Number *Complex::IS_NUMBER(){
	Boolean *boolfg = new Boolean();
	boolfg->judge = true;
	return boolfg;
}

void Complex::print(){
	bool boolfg = true;
	switch (real->type_){	
	case RATIONAL:{
		Rational *ttmp = new Rational();
		Rational *tmp = SCAST_RATIONAL(real);
		if (tmp->numerator_.number_ == "0"){		
			boolfg = false;
			break;
		}
		else{		
			ttmp = tmp;
			ttmp->print();
			break;
		}
	}
	case FLOAT:{
		Float *ttmp = new Float();
		Float *tmp = SCAST_FLOAT(real);
		if (tmp->number_ == 0){		
			boolfg = false;
			break;
		}
		else{		
			ttmp = tmp;
			ttmp->print();
			break;
		}

	}
	default: break;
	}
	switch (imag->type_){	
	case RATIONAL:{
		Rational *ttmp = new Rational();
		Rational *tmp = SCAST_RATIONAL(imag);
		if (tmp->numerator_.number_ == "0"&& boolfg) break;
		else if (tmp->numerator_.number_ == "0" && !boolfg)
		{
			printf("0");
			break;
		}
		else if (boolfg && ((tmp->numerator_.number_[0] != '-'&& tmp->denominator_.number_[0] != '-')
		 || (tmp->numerator_.number_[0] == '-'&& tmp->denominator_.number_[0] == '-'))){		
			ttmp = tmp;
			printf("+");
			if (ttmp->numerator_.number_ == "1"&&ttmp->denominator_.number_ == "1") cout << 'i';
			else{			
				ttmp->print();
				printf("i");
			}
			break;
		}
		else{		
			printf("-");
			if (tmp->numerator_.number_[0] == '-'){			
				ttmp->numerator_.number_ = tmp->numerator_.number_.substr(1, tmp->numerator_.number_.length() - 1);
				ttmp->denominator_.number_ = tmp->denominator_.number_;
			}
			else{			
				ttmp->numerator_.number_ = tmp->numerator_.number_;
				ttmp->denominator_.number_ = tmp->denominator_.number_.substr(1, tmp->denominator_.number_.length() - 1);
			}
			if (ttmp->numerator_.number_ == "1"&&ttmp->denominator_.number_ == "1") cout << 'i';
			else{			
				ttmp->print();
				printf("i");
			}
			break;
		}
	}
	case FLOAT: {
		Float *ttmp = new Float();
		Float *tmp = SCAST_FLOAT(imag);
		if (tmp->number_ == 0){
			if (!boolfg){			
				printf("0");
				break;
			}
	    else break;
		}
		else if (tmp->number_ > 0){		
			printf("+");
			ttmp = tmp;
			ttmp->print();
			printf("i");
		}
		else{		
			ttmp = tmp;
			ttmp->print();
			printf("i");
		}
		break;
	}
	default: break;
	}
}

Complex *Complex::from_string(char *expr){
	string s(expr);
	int jing = s.find('#');
	int yin = s.find('"');
	if (jing != s.npos) return NULL;
	if (yin != s.npos) return NULL;
    char *ii = strchr(expr,'i');
	if (ii &&(strlen(expr)+expr-1)!=ii) return NULL;
    char *jiah = strchr(expr+1,'+');
    char *fuhao;
    if (jiah) fuhao=jiah;
    else{   
        for (int i=1;i<strlen(expr);++i){       
            if (*(expr+i)=='e') i+=2;
            if (*(expr+i)=='-'){     
				fuhao=expr+i;break;                      
            }
        }
    }
    
    if (fuhao) {  
        char *lh,*rh;
        lh=new char[5000];
        rh=new char[5000];
        strncpy(lh,expr,fuhao-expr);
        lh[fuhao-expr]='\0';
        int n=ii-fuhao-1;
        if (fuhao == jiah) {
			strncpy(rh,fuhao+1,n);rh[n]='\0';
		}
        else {
			strncpy(rh,fuhao,n+1);rh[n+1]='\0';
		}
        
        Number *tmpr,*tmpi;
        tmpr=Rational::from_string(lh);
        if(!tmpr) {
            tmpr = Float::from_string(lh);
        }
        if(tmpr==NULL){throw 0;}
        tmpi=Rational::from_string(rh);
        if(!tmpi) {
            tmpi = Float::from_string(rh);
        }
        if(tmpi==NULL){throw 0;}
        return new Complex(tmpr,tmpi);
    }
    else{   
        char *rh;
        rh=new char[5000];
        strncpy(rh,expr,strlen(expr)-1);
        rh[strlen(expr)-1]='\0';
        Number *tmpi;
        tmpi=Rational::from_string(rh);
        if(!tmpi) {
            tmpi = Float::from_string(rh);
        }
        if(tmpi==NULL){throw 0;}
        return new Complex(new Rational("0","1"),tmpi);
    }
}

Number *Complex::reless(Number *number2){
}

Number *Complex::relesseql(Number *number2){
}

Number *Complex::regter(Number *number2){
}

Number *Complex::regtereql(Number *number2){
}

Number *Complex::MAKE_RECTANGULAR(Number *number2){
}

Number *Complex::MAKE_POLAR(Number *number2){
}
Number *Complex::EQL(Number *number2){
	Complex *tmp = SCAST_COMPLEX(number2);
	Boolean *result = new Boolean(false);
//	tmp->real->print();real->print();cout<<endl;
//	tmp->imag->print();imag->print();cout<<endl;
	if (real->type_ > tmp->real->type_)
	{	tmp->real = real->convert(tmp->real);
	}
	else if (real->type_ < tmp->real->type_)
	{	real = tmp->real->convert(real);
	}		

	if (imag->type_ > tmp->imag->type_)
	{	tmp->imag = imag->convert(tmp->imag);
	}
	else if (imag->type_ < tmp->imag->type_)
	{	imag = tmp->imag->convert(imag);
	}	
	Boolean *result1 = SCAST_BOOLEAN(tmp->real->EQL(real));
	Boolean *result2 = SCAST_BOOLEAN(tmp->imag->EQL(imag));
	if (result1->judge==true && result2->judge==true) result->judge=true;	
	return result;
}	
Number *Complex::STR_EQL(Number *number2){}
Number *Complex::STR_CIEQL(Number *number2){}
Number *Complex::STR_LESS(Number *number2){}
Number *Complex::STR_CILESS(Number *number2){}
Number *Complex::STR_LESSEQL(Number *number2){}
Number *Complex::STR_CILESSEQL(Number *number2){}
Number *Complex::CHA_EQL(Number *number2){}
Number *Complex::CHA_CIEQL(Number *number2){}
Number *Complex::CHA_LESS(Number *number2){}
Number *Complex::CHA_CILESS(Number *number2){}
Number *Complex::CHA_LESSEQL(Number *number2){}
Number *Complex::CHA_CILESSEQL(Number *number2){}
	
Number *Complex::IS_STR(){
	Boolean *result = new Boolean();
	result->judge = false;
	return result;
}
Number *Complex::STR_NUM(){}
Number *Complex::NUM_STR(){
	String *result = new String();	
	String *tmp1 = new String();
	String *tmp2 = new String();
	if(real->type_ == imag->type_)
	{	tmp1 = SCAST_STRING(real->NUM_STR());
		tmp2 = SCAST_STRING(imag->NUM_STR());
	}
	else
	{	if (real->type_ > imag->type_)
		{	imag = real->convert(imag);
			tmp1 = SCAST_STRING(real->NUM_STR());
			tmp2 = SCAST_STRING(imag->NUM_STR());
		}
		else
		{	real = imag->convert(real);
			tmp1 = SCAST_STRING(real->NUM_STR());
			tmp2 = SCAST_STRING(imag->NUM_STR());
		}
	}
	result->str += tmp1->str;
	bool flag1=SCAST_BOOLEAN(imag->IS_ZERO())->judge;
	if (!flag1){
		if (tmp2->str[0] != '-'){ 
			result->str += '+';
		}
		result->str += tmp2->str;
		result->str += 'i';		
	}
	return result;	
}
Number *Complex::MAK_STR(){}
Number *Complex::GET_STR(){}
Number *Complex::MAK_STR(Number *number2){}
Number *Complex::GET_STR(Number *number2){}
Number *Complex::STR_LEN(){}
Number *Complex::STR_REF(Number *number2){}
Number *Complex::STR_APP(Number *number2){}
Number *Complex::STR_CPY(){}
Number *Complex::SUB_STR(Number *number1, Number *number2){}
Number *Complex::IS_CHA(){
	Boolean *result = new Boolean();
	result->judge = false;
	return result;
}	
Number *Complex::CHA_ALPH(){
	Boolean *result = new Boolean();
	result->judge = false;
	return result;
}
Number *Complex::CHA_NUM(){
	Boolean *result = new Boolean();
	result->judge = false;
	return result;
}
Number *Complex::CHA_WHIT(){
	Boolean *result = new Boolean();
	result->judge = false;
	return result;
}
Number *Complex::IS_CHA_UPP(){
	Boolean *result = new Boolean();
	result->judge = false;
	return result;
}
Number *Complex::IS_CHA_LOW(){
	Boolean *result = new Boolean();
	result->judge = false;
	return result;
}
Number *Complex::CHA_UP(){}
Number *Complex::CHA_DOWN(){}
	
Number *Complex::CHA_INT(){}
Number *Complex::INT_CHA(){}
