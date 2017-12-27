#include <cassert>
#include <cstdlib>
#include <cstdio>
#include <cmath>
#include <cstring>
#include <sstream>
#include "float.h"
#include "rational.h"
#include "complex.h"
#include "boolean.h"
#include "string.h"
#include "char.h"
#include <iostream>
Rational::Rational(string numerator, string denominator) :
 numerator_(numerator), denominator_(denominator){
	type_ = RATIONAL;
	reduce();
}

Rational::~Rational(){

}

void Rational::reduce(){
	assert(denominator_ && "denominator is zero");
	if (!numerator_){
		denominator_ = (LongInt)"1";
		return;
	}
	LongInt big, small, tmp;
	big = max(numerator_, denominator_);
	small = min(numerator_, denominator_);
	while (tmp = big % small){
		big = small;
		small = tmp;
	}
	numerator_ = numerator_ / small;
	denominator_ = denominator_ / small;
	if (denominator_ < LongInt("0")){
		numerator_ = LongInt("0") - numerator_;
		denominator_ = LongInt("0") - denominator_;
	}
}


Number *Rational::convert(Number *number2){
	assert(number2->type_ <= type_);
	Rational *ttmp = new Rational();
	switch (number2->type_){
	case RATIONAL:{
		Rational *tmp = SCAST_RATIONAL(number2);
		ttmp->numerator_ = tmp->numerator_;
		ttmp->denominator_ = tmp->denominator_;
		break;
	}
	default:
		assert(0 && "type_ not defined");
	}
	ttmp->reduce();
	return ttmp;
}

Number *Rational::add(Number *number2) {
	Rational *tmp = SCAST_RATIONAL(number2);
	Rational *ttmp = new Rational();
	ttmp->numerator_ = numerator_*tmp->denominator_ + denominator_*tmp->numerator_;
	ttmp->denominator_ = denominator_ * tmp->denominator_;
	ttmp->reduce();
	return ttmp;
}

Number *Rational::sub(Number *number2) {
	Rational *tmp = SCAST_RATIONAL(number2);
	Rational *ttmp = new Rational();
	ttmp->numerator_ = numerator_*tmp->denominator_ - denominator_*tmp->numerator_;
	ttmp->denominator_ = denominator_ * tmp->denominator_;
	ttmp->reduce();
	return ttmp;
}

Number *Rational::mul(Number *number2) {
	Rational *tmp = SCAST_RATIONAL(number2);
	Rational *ttmp = new Rational();
	ttmp->numerator_ = numerator_ * tmp->numerator_;
	ttmp->denominator_ = denominator_ * tmp->denominator_;
	ttmp->reduce();
	return ttmp;
}

Number *Rational::div(Number *number2) {
	Rational *tmp = SCAST_RATIONAL(number2);
	Rational *ttmp = new Rational();
	ttmp->numerator_ = numerator_ * tmp->denominator_;
	ttmp->denominator_ = denominator_ * tmp->numerator_;
	ttmp->reduce();
	return ttmp;
}

Number *Rational::ABS(){
	Rational *ttmp = new Rational();
	ttmp->numerator_ = ABs(numerator_);
	ttmp->denominator_ = ABs(denominator_);
	ttmp->reduce();
	return ttmp;
}

Number *Rational::QUOTIENT(Number *number2){
    Rational *tmp = SCAST_RATIONAL(number2);
	Rational *ttmp = new Rational();
	ttmp->numerator_=numerator_/tmp->numerator_;
	ttmp->reduce();
	return ttmp;
}

Number *Rational::REMAINDER(Number *number2){
	Rational *tmp = SCAST_RATIONAL(number2);
	LongInt ttmp = numerator_ / (tmp->numerator_);
	Rational *ans = new Rational("1", "1");
	ans->numerator_ = numerator_-ttmp*tmp->numerator_;
	return ans;
}

Number *Rational::MODULO(Number *number2)
{
	Rational *tmp = SCAST_RATIONAL(number2);
	LongInt ttmp = numerator_ / (tmp->numerator_);
	if (ttmp.number_[0] == '-') ttmp = ttmp - LongInt("1");
	Rational *ans = new Rational("1", "1");
	ans->numerator_ = numerator_ - ttmp*tmp->numerator_;
	return ans;
}

Number *Rational::GCD(Number *number2){
	Rational *tmp = SCAST_RATIONAL(number2);
	if (!(tmp->numerator_!=LongInt("0"))) return this;
	if (!(numerator_!=LongInt("0"))) return tmp;
	Rational *tmpre= new Rational();
	tmpre->numerator_ = numerator_;
	tmpre->denominator_ = tmp->numerator_;
	tmpre->reduce();
	Rational *ttmp = new Rational("1","1");
	ttmp->numerator_ = numerator_/tmpre->numerator_;
	ttmp->ABS();
	return ttmp;
}

Number *Rational::LCM(Number *number2){
	Rational *tmp = SCAST_RATIONAL(number2);
	if (!(tmp->numerator_!=LongInt("0"))) return tmp;
	if (!(numerator_!=LongInt("0"))) return this;
	Rational *tmpre= new Rational();
	tmpre->numerator_ = numerator_;
	tmpre->denominator_ = tmp->numerator_;
	tmpre->reduce();
	
	Rational *ttmp = new Rational("1","1");
	ttmp->numerator_ = tmpre->denominator_*tmpre->numerator_*numerator_/tmpre->numerator_;
	ttmp->ABS();
	return ttmp;
}

Number *Rational::EXPT(Number *number2){
  Rational *tmp = SCAST_RATIONAL(number2);
	double x,y;
	x=((double)this->numerator_)/((double)this->denominator_);
	y=((double)tmp->numerator_)/((double)tmp->denominator_);
	x=pow(x,y);
    return new Float(x);
}

Number *Rational::SQRT(){
	double x;
	x=((double)this->numerator_)/((double)this->denominator_);
    if (x>=0){    
        x=sqrt(x);
        return new Float(x);
    }
    else{    
        x=sqrt(-x);
        return new Complex(new Float(0),new Float(x));
    }
}

Number *Rational::Max(Number *number2){
	Rational *tmp = SCAST_RATIONAL(number2);
	Rational *ttmp = new Rational();
	Rational *result1 = new Rational();
	ttmp->numerator_ = numerator_*tmp->denominator_ - denominator_*tmp->numerator_;
	ttmp->denominator_ = denominator_ * tmp->denominator_;
	ttmp->reduce();
	if (ttmp->numerator_ < LongInt("0")) return tmp;
	else
	{
		result1->numerator_ = numerator_;
		result1->denominator_ = denominator_;
		result1->reduce();
		return result1;
	}
}

Number *Rational::Min(Number *number2){
 	Rational *tmp = SCAST_RATIONAL(number2);
	Rational *ttmp = new Rational();
	Rational *result1 = new Rational();
	ttmp->numerator_ = numerator_*tmp->denominator_ - denominator_*tmp->numerator_;
	ttmp->denominator_ = denominator_ * tmp->denominator_;
	ttmp->reduce();
	if (ttmp->numerator_ < LongInt("0"))
	{
		result1->numerator_ = numerator_;
		result1->denominator_ = denominator_;
		result1->reduce();
		return result1;
	}
	else	return tmp;
}

Number *Rational::NUMERATOR(){
	denominator_ = (LongInt) "1";
	return this;
}

Number *Rational::DENOMINATOR(){
	numerator_ = denominator_;
	denominator_ = (LongInt)"1";
	return this;
}

Number *Rational::floor(){
    double ttmp = std::floor(double (numerator_) / double(denominator_));
    string num;
    stringstream s;
    s<<int(ttmp);s>>num;
	return new Rational (num,"1");
}

Number *Rational::ceiling(){
   	double ttmp = std::ceil(double (numerator_) / double(denominator_));
	string num;
    stringstream s;
    s<<int(ttmp);s>>num;
	return new Rational (num,"1");
}

Number *Rational::truncate(){
    if (numerator_.number_[0]=='-')  this->ceiling();  
    else this->floor();  
}

Number *Rational::ROUND(){
	Rational *ttmp = new Rational("0","1");
	double numden=double(numerator_)/double(denominator_);
	double tmp,tmp1,tmp2;
	tmp1 = std::floor(numden);
	tmp2 = std::ceil(numden);
	if (tmp2 - numden > numden - tmp1) tmp = tmp1;
	if (tmp2 - numden < numden - tmp1) tmp = tmp2;
	if (tmp2 - numden == numden - tmp1){
		if ( (long long)(tmp2) % 2 == 0) tmp = tmp2;
		else tmp = tmp1;
	}
	string num;
    stringstream s;
    s<<(long long)tmp;s>>num;
	ttmp->numerator_ = LongInt(num);
	return ttmp;
}

Number *Rational::exact(){
	return this;
}

Number *Rational::inexact(){
	double tmp = (double)numerator_ / (double)denominator_;
	return new Float(tmp);
}

Number *Rational::realpart(){
	return this;
}

Number *Rational::imagepart(){
	Rational *ttmp = new Rational("0", "1");
	return ttmp;
}

Number *Rational::reless(Number *number2){
	Boolean *boolfg = new Boolean();
	Rational *tmp = SCAST_RATIONAL(number2);
	Rational *ttmp = new Rational();
	ttmp->numerator_ = numerator_*tmp->denominator_ - denominator_*tmp->numerator_;
	ttmp->denominator_ = denominator_ * tmp->denominator_;
	ttmp->reduce();
	if (ttmp->numerator_.number_ == "0") boolfg->judge = false;
	else if ((ttmp->numerator_.number_[0] == '-'&&ttmp->denominator_.number_[0] == '-') 
	|| (ttmp->numerator_.number_[0] != '-'&&ttmp->denominator_.number_[0] != '-'))
	{
		boolfg->judge = false;
	}
	else boolfg->judge = true;
	return boolfg;
}

Number *Rational::relesseql(Number *number2){
	Boolean *boolfg = new Boolean();
	Rational *tmp = SCAST_RATIONAL(number2);
	Rational *ttmp = new Rational();
	ttmp->numerator_ = numerator_*tmp->denominator_ - denominator_*tmp->numerator_;
	ttmp->denominator_ = denominator_ * tmp->denominator_;
	ttmp->reduce();
	if (ttmp->numerator_.number_ == "0") boolfg->judge = true;
	else if ((ttmp->numerator_.number_[0] == '-'&&ttmp->denominator_.number_[0] == '-') 
	|| (ttmp->numerator_.number_[0] != '-'&&ttmp->denominator_.number_[0] != '-'))
	{
		boolfg->judge = false;
	}
	else boolfg->judge = true;
	return boolfg;
}

Number *Rational::regter(Number *number2){
	Boolean *boolfg = new Boolean();
	Rational *tmp = SCAST_RATIONAL(number2);
	Rational *ttmp = new Rational();
	ttmp->numerator_ = numerator_*tmp->denominator_ - denominator_*tmp->numerator_;
	ttmp->denominator_ = denominator_ * tmp->denominator_;
	ttmp->reduce();
	if (ttmp->numerator_.number_ == "0") boolfg->judge = false;
	else if ((ttmp->numerator_.number_[0] == '-' && ttmp->denominator_.number_[0] == '-') 
	|| (ttmp->numerator_.number_[0] != '-' && ttmp->denominator_.number_[0] != '-'))
	{
		boolfg->judge = true;
	}
	else boolfg->judge = false;
	return boolfg;
}

Number *Rational::regtereql(Number *number2){
	Boolean *boolfg = new Boolean();
	Rational *tmp = SCAST_RATIONAL(number2);
	Rational *ttmp = new Rational();
	ttmp->numerator_ = numerator_*tmp->denominator_ - denominator_*tmp->numerator_;
	ttmp->denominator_ = denominator_ * tmp->denominator_;
	ttmp->reduce();
	if (ttmp->numerator_.number_ == "0") boolfg->judge = true;
	else if ((ttmp->numerator_.number_[0] == '-'&&ttmp->denominator_.number_[0] == '-') 
	|| (ttmp->numerator_.number_[0] != '-'&&ttmp->denominator_.number_[0] != '-'))
	{
		boolfg->judge = true;
	}
	else boolfg->judge = false;
	return boolfg;
}

Number *Rational::SIN(){
	Float *tmp = new Float();
	tmp->number_ = double(numerator_) / double(denominator_);
	return tmp->SIN();
}

Number *Rational::COS(){
	Float *tmp = new Float();
	tmp->number_ = double(numerator_) / double(denominator_);
	return tmp->COS();
}

Number *Rational::TAN(){
	Float *tmp = new Float();
	tmp->number_ = double(numerator_) / double(denominator_);
	return tmp->TAN();
}

Number *Rational::ARCSIN(){
	Float *tmp = new Float();
	tmp->number_ = double(numerator_) / double(denominator_);
	return tmp->ARCSIN();
}

Number *Rational::ARCCOS(){
	Float *tmp = new Float();
	tmp->number_ = double(numerator_) / double(denominator_);
	return tmp->ARCCOS();
}

Number *Rational::ARCTAN(){
	Float *tmp = new Float();
	tmp->number_ = double(numerator_) / double(denominator_);
	return tmp->ARCTAN();
}

Number *Rational::IS_EXACT(){
	Boolean *boolfg = new Boolean();
	boolfg->judge = true;
	return boolfg;
}

Number *Rational::IS_INEXACT(){
	Boolean *boolfg = new Boolean();
	boolfg->judge = false;
	return boolfg;
}

Number *Rational::IS_ZERO(){
	Boolean *boolfg = new Boolean();
	if (numerator_ != (LongInt)"0") boolfg->judge = false;
	else boolfg->judge = true;
	return boolfg;
}

Number *Rational::IS_NEGATIVE(){
	Boolean *boolfg = new Boolean();
	if ((numerator_.number_[0] == '-'&&denominator_.number_[0] != '-') || (numerator_.number_[0] != '-'&&denominator_.number_[0] == '-')) boolfg->judge = true;
	else boolfg->judge = false;
	return boolfg;
}

Number *Rational::IS_POSITIVE(){
	Boolean *boolfg = new Boolean();
	if ((numerator_.number_[0] == '-'&&denominator_.number_[0] == '-') || (numerator_.number_[0] != '-'&&denominator_.number_[0] != '-')) boolfg->judge = true;
	else boolfg->judge = false;
	return boolfg;
}

Number *Rational::IS_ODD(){
	Boolean *boolfg = new Boolean();
	if (denominator_ != (LongInt)"1") throw 0;
	else
	{
		if (numerator_ % (LongInt)"2" != (LongInt)"0") boolfg->judge = true;
		else boolfg->judge = false;
	}
	return boolfg;
}

Number *Rational::IS_EVEN(){
	Boolean *boolfg = new Boolean();
	if (denominator_ != (LongInt)"1") throw 0;
	else
	{
		if (numerator_ % (LongInt)"2" != (LongInt)"0") boolfg->judge = false;
		else boolfg->judge = true;
	}
	return boolfg;
}

Number *Rational::EXP(){
	Float *tmp = new Float();
	tmp->number_ = double(numerator_) / double(denominator_);
	return tmp->EXP();
}

Number *Rational::LOG(){
	Float *tmp = new Float();
	tmp->number_ = double(numerator_) / double(denominator_);
	return tmp->LOG();
}

Number *Rational::MAGNITUDE(){
	return ABS();
}

Number *Rational::ANGLE(){
	Float *tmp = new Float();
	tmp->number_ = double(numerator_) / double(denominator_);
	return tmp->ANGLE();
}

Number *Rational::MAKE_RECTANGULAR(Number *number2){
	Rational *tmp_2 = SCAST_RATIONAL(number2);
	Complex *ttmp = new Complex();
	ttmp->real = this;
	ttmp->imag = tmp_2;
	return ttmp;
}

Number *Rational::MAKE_POLAR(Number *number2){	
	Rational *tmp = SCAST_RATIONAL(number2);
	double tmp1,tmp2;
	tmp1 = double(numerator_)/double(denominator_);
	tmp2 = tmp->numerator_;
	Complex *result = new Complex(new Float(tmp1*cos(tmp2)),new Float(tmp1*sin(tmp2)));	
	return result;
}

Number *Rational::IS_INTEGER(){
	Boolean *boolfg = new Boolean();
	if (denominator_ != (LongInt)"1")
	{
		boolfg->judge = false;
	}
	else boolfg->judge = true;
	return boolfg;
}

Number *Rational::IS_RATIONAL(){
	Boolean *boolfg = new Boolean();
	boolfg->judge = true;
	return boolfg;
}

Number *Rational::IS_REAL(){
	Boolean *boolfg = new Boolean();
	boolfg->judge = true;
	return boolfg;
}

Number *Rational::IS_COMPLEX(){
	Boolean *boolfg = new Boolean();
	boolfg->judge = true;
	return boolfg;
}

Number *Rational::IS_NUMBER(){
	Boolean *boolfg = new Boolean();
	boolfg->judge = true;
	return boolfg;
}

void Rational::print(){
	numerator_.print();
	if(denominator_ != (LongInt)"1"){
		printf("/");
		denominator_.print();
	}
}

Rational *Rational::from_string(char *expr){
    string numerator, denominator;
    string expr_(expr);
 	int jing = expr_.find('#');
	int yinhao = expr_.find('"');
	if (jing != expr_.npos) return NULL;
	if (yinhao != expr_.npos) return NULL;
	   
	int xiegang = expr_.find('/');
    int dian = expr_.find('.');
    int ee=0;
	if (expr_.find('E')<expr_.find('e')) ee=expr_.find('E');
	else ee=expr_.find('e');
	int ii = expr_.find('i');
    
	if (ee != expr_.npos) return NULL;
	if (ii != expr_.npos) return NULL;
    if (xiegang != expr_.npos && dian == expr_.npos){   
        for (int i = 0; i < xiegang; ++i){
        	if ((expr_[i] <= '9' && expr_[i] >='0') || expr_[i] =='-'){
        		numerator += expr_[i];
			}        	
		}          
        for (int i = xiegang + 1; i < expr_.length(); ++i){
        	if ((expr_[i] <= '9' && expr_[i] >='0') || expr_[i] =='-'){
        		denominator += expr_[i];
			}           	
		}            
        return new Rational(numerator,denominator);
    }
    else if (xiegang == expr_.npos && dian == expr_.npos){
    	return new Rational(expr_, "1");
	}        
    else if (xiegang == expr_.npos && dian != expr_.npos){
    	return NULL;
	}      
    else throw 0;        
}

Number *Rational::EQL(Number *number2){
	Boolean *boolfg = new Boolean();
	boolfg->judge = false;	
	Rational *tmp = SCAST_RATIONAL(number2);
	double tmp1,tmp2;
	tmp1 = double(numerator_)/double(denominator_);
	tmp2 = double(tmp->numerator_)/double(tmp->denominator_);
	if (abs((tmp1-tmp2))<=1e-10) boolfg->judge = true;
	return boolfg;
}
	
Number *Rational::STR_EQL(Number *number2){}
Number *Rational::STR_CIEQL(Number *number2){}
Number *Rational::STR_LESS(Number *number2){}
Number *Rational::STR_CILESS(Number *number2){}
Number *Rational::STR_LESSEQL(Number *number2){}
Number *Rational::STR_CILESSEQL(Number *number2){}
Number *Rational::CHA_EQL(Number *number2){}
Number *Rational::CHA_CIEQL(Number *number2){}
Number *Rational::CHA_LESS(Number *number2){}
Number *Rational::CHA_CILESS(Number *number2){}
Number *Rational::CHA_LESSEQL(Number *number2){}
Number *Rational::CHA_CILESSEQL(Number *number2){}
	
Number *Rational::IS_STR(){
	Boolean *result = new Boolean();
	result->judge = false;
	return result;
}

Number *Rational::MAK_STR(){
	String *result = new String();
	long long a;
	LongInt *tmp =  new LongInt((numerator_)/(denominator_));
	stringstream s;
    s<<tmp->number_;
	s>>a;
	for (long long i=0;i<a;++i){
		char tmp = NULL;
		result->str += tmp;
	}
	return result;
}

Number *Rational::MAK_STR(Number *number2){
	Char *tmp = SCAST_CHAR(number2);
	long long a;
	LongInt *tmp2 =  new LongInt((numerator_)/(denominator_));
	stringstream s;
    s<<tmp2->number_;
	s>>a;s.clear();
	String *result = new String();
	for (long long i=0;i<a;++i){
		result->str += tmp->ch;
	}
	return result;
}

Number *Rational::GET_STR(Number *number2){}
Number *Rational::GET_STR(){}
Number *Rational::STR_LEN(){}
Number *Rational::STR_REF(Number *number2){}
Number *Rational::STR_APP(Number *number2){}
Number *Rational::STR_CPY(){}
Number *Rational::SUB_STR(Number *number1, Number *number2){}
Number *Rational::IS_CHA(){
	Boolean *result = new Boolean();
	result->judge = false;
	return result;
}	
Number *Rational::CHA_ALPH(){
	Boolean *result = new Boolean();
	result->judge = false;
	return result;
}
Number *Rational::CHA_NUM(){
	Boolean *result = new Boolean();
	result->judge = false;
	return result;
}
Number *Rational::CHA_WHIT(){
	Boolean *result = new Boolean();
	result->judge = false;
	return result;
}
Number *Rational::IS_CHA_UPP(){
	Boolean *result = new Boolean();
	result->judge = false;
	return result;
}
Number *Rational::IS_CHA_LOW(){
	Boolean *result = new Boolean();
	result->judge = false;
	return result;
}
Number *Rational::CHA_UP(){}
Number *Rational::CHA_DOWN(){}
	
Number *Rational::CHA_INT(){}
Number *Rational::INT_CHA(){
	Char *result = new Char();
	int tmp1;
	tmp1 = double(numerator_)/double(denominator_);
	result->ch = tmp1;
	//cout<<tmp1<<endl;
	return result;
}
Number *Rational::STR_NUM(){}

Number *Rational::NUM_STR(){
	string result;
	if ((numerator_.number_[0] == '-' && denominator_.number_[0] != '-')
	 || (numerator_.number_[0] != '-' && denominator_.number_[0] == '-')){
	 	result += "-";
	}
	result +=  ABs(numerator_).number_;	
	if (denominator_!=LongInt("1")){
		result += "/";
		result +=  ABs(denominator_).number_;			
	}

	return new String(result);
}
