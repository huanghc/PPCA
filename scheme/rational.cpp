#include "rational.h"
#include "float.h"
#include "complex.h"
#include <cassert>
#include <cstdlib>
#include <cstdio>
#include <cstring>
#include <cmath>
#include <iostream>

Rational::Rational(char numerator[], char denominator[]) : numerator_(numerator),
	denominator_(denominator){
	type_ = RATIONAL;
	reduce();
}

Rational::~Rational(){

}

void Rational::reduce(){

	assert(denominator_ && "denominator is zero");
	if(!numerator_){
		denominator_ = "1";
		return;
	}
	if (!(numerator_ != denominator_))
    {
        numerator_ = "1";
        denominator_ = "1";
        return ;
    }
	LongInt big, small, tmp;
	big = Max(numerator_, denominator_);
	small = Min(numerator_, denominator_);
	while(tmp = big % small){
		big = small;
		small = tmp;
	}
	numerator_ = numerator_ / small;
	denominator_ = denominator_ / small;
	if(denominator_ < LongInt("0")){
		numerator_ = LongInt("0")-numerator_;
		denominator_ = LongInt("0")-denominator_;
	}
}


Number *Rational::convert(Number *number2){
	assert(number2->type_ <= type_);
	Rational *result = new Rational();
	switch(number2->type_){
		case RATIONAL:{
			Rational *tmp = SCAST_RATIONAL(number2);
			result->numerator_ = tmp->numerator_;
			result->denominator_ = tmp->denominator_;
			break;
		}
		default:
			assert(0 && "type_ not defined");
	}
	result->reduce();
	return result;
}

Number *Rational::add( Number *number2) {
	Rational *tmp = SCAST_RATIONAL(number2);
	Rational *result = new Rational();
	result->numerator_ = numerator_*tmp->denominator_ + denominator_*tmp->numerator_;
	result->denominator_ = denominator_ * tmp->denominator_;
	result->reduce();
	return result;
}

Number *Rational::sub(Number *number2) {
	Rational *tmp = SCAST_RATIONAL(number2);
	Rational *result = new Rational();
	result->numerator_ = numerator_*tmp->denominator_ - denominator_*tmp->numerator_;
	result->denominator_ = denominator_ * tmp->denominator_;
	result->reduce();
	return result;
}

Number *Rational::mul(Number *number2) {
	Rational *tmp = SCAST_RATIONAL(number2);
	Rational *result = new Rational();
	result->numerator_ = numerator_ * tmp->numerator_;
	result->denominator_ = denominator_ * tmp->denominator_;
	result->reduce();
	return result;
}

Number *Rational::div(Number *number2) {
	Rational *tmp = SCAST_RATIONAL(number2);
	Rational *result = new Rational();
	result->numerator_ = numerator_ * tmp->denominator_;
	result->denominator_ = denominator_ * tmp->numerator_;
	result->reduce();
	return result;
}

Number *Rational::quotient(Number *number2){
    Rational *tmp = SCAST_RATIONAL(number2);
	Rational *result = new Rational();
	result->numerator_=numerator_/tmp->numerator_;
	result->reduce();
	return result;
}

Number *Rational::remainder(Number *number2){
    Rational *tmp = SCAST_RATIONAL(number2);
	Rational *result = new Rational();
	result->numerator_=numerator_%tmp->numerator_;
	if (result->numerator_.number_[0]==numerator_.number_[0]){result->reduce();return result;}
	else
    {
        result->numerator_=result->numerator_+tmp->numerator_;
        if (result->numerator_.number_[0]==numerator_.number_[0]) {result->reduce();return result;}
        else
        {
            result->numerator_=result->numerator_-tmp->numerator_-tmp->numerator_;
            result->reduce();
            return result;
        }
    }
}

Number *Rational::modulo(Number *number2){
    Rational *tmp = SCAST_RATIONAL(number2);
	Rational *result = new Rational();
	result->numerator_=numerator_%tmp->numerator_;
	if (result->numerator_.number_[0]==tmp->numerator_.number_[0]){result->reduce();return result;}
	else
    {
        result->numerator_=result->numerator_+tmp->numerator_;
        if (result->numerator_.number_[0]==tmp->numerator_.number_[0]) {result->reduce();return result;}
        else
        {
            result->numerator_=result->numerator_-tmp->numerator_-tmp->numerator_;
            result->reduce();
            return result;
        }
    }
}

Number *Rational::gcd(Number *number2){
    Rational *tmp = SCAST_RATIONAL(number2);
	Rational *result = new Rational();
	LongInt big, small, tmpl;
	big = Max(numerator_, tmp->numerator_);
	small = Min(numerator_, tmp->numerator_);
	if (big !="0" && small!="0")
    {
        while(tmpl = big % small){
		big = small;
		small = tmpl;
        }
        result->numerator_=small;
    }
    result->reduce();
    return result;
}

Number *Rational::lcm(Number *number2){
    Rational *tmp = SCAST_RATIONAL(number2);
	Rational *result = new Rational();
	LongInt big, small, tmpl;
	big = Max(numerator_, tmp->numerator_);
	small = Min(numerator_, tmp->numerator_);
	if (big !="0" && small!="0")
    {
        while(tmpl = big % small){
		big = small;
		small = tmpl;
        }
        result->numerator_=numerator_*tmp->numerator_/small;
    }
    result->reduce();
    return result;
}

Number *Rational::EXPT(Number *number2){
    Rational *tmp = SCAST_RATIONAL(number2);
	double x,y;
	x=((double)this->numerator_)/((double)this->denominator_);
	y=((double)tmp->numerator_)/((double)tmp->denominator_);
	x=pow(x,y);
    return new Float(x);
}

Number *Rational::NUM(){
    denominator_="1";
    return this;
}

Number *Rational::DEN(){
    numerator_=denominator_;
    denominator_="1";
    return this;
}

Number *Rational::SQRT(){
	double x;
	x=((double)this->numerator_)/((double)this->denominator_);
    if (x>=0)
    {
        double x=sqrt(x);
        return new Float(x);
    }
    else
    {
        double x=sqrt(-x);
        return new Complex(new Float(0),new Float(x));
    }
}

Number *Rational::floor(){
    while (numerator_%denominator_ !=(LongInt)"0") numerator_=numerator_-"1";
    reduce();
    return this;
}

Number *Rational::ceiling(){
    while ((numerator_%denominator_) !=(LongInt)"0") numerator_=numerator_+(LongInt)"1";
    reduce();
    return this;
}

Number *Rational::truncate(){
    if (numerator_.number_[0]=='+')
    {
        while ((numerator_%denominator_) !=(LongInt)"0") numerator_=numerator_-(LongInt)"1";
    }
    else
    {
        while ((numerator_%denominator_) !=(LongInt)"0") numerator_=numerator_+(LongInt)"1";
    }
    reduce();
    return this;
}

Number *Rational::ROU(){
    LongInt cntjia,cntjian,tmp;
    tmp=numerator_;
    while ((tmp%denominator_) !=(LongInt)"0") {cntjian=cntjian+(LongInt)"1"; tmp=tmp-(LongInt)"1";}
    tmp=numerator_;
    while ((tmp%denominator_) !=(LongInt)"0") {cntjia=cntjia+(LongInt)"1";tmp=tmp+(LongInt)"1";}
    if (!(denominator_%(LongInt)"2"))
    {
        if (cntjian<cntjia) while ((numerator_%denominator_) !=(LongInt)"0") numerator_=numerator_-(LongInt)"1";
        else if (cntjia < cntjian) while ((numerator_%denominator_) !=(LongInt)"0") numerator_=numerator_+(LongInt)"1";
        else
        {
            tmp=numerator_;
            while ((tmp%denominator_) !=(LongInt)"0") {tmp=tmp-(LongInt)"1";}
            if (((tmp/denominator_)%(LongInt)"2")!=(LongInt)"0") while ((numerator_%denominator_) !=(LongInt)"0") numerator_=numerator_+(LongInt)"1";
            else while ((numerator_%denominator_) !=(LongInt)"0") numerator_=numerator_-(LongInt)"1";
        }
    }
    else
    {
        if (cntjian < cntjia) while ((numerator_%denominator_) !=(LongInt)"0") numerator_=numerator_-(LongInt)"1";
        else if (cntjia < cntjian) while ((numerator_%denominator_) !=(LongInt)"0") numerator_=numerator_+(LongInt)"1";
    }
    reduce();
    return this;
}

Number *Rational::exact(){
    return this;
}

Number *Rational::inexact(){
    double tmp = (double)numerator_/(double) denominator_;
    return new Float(tmp);
}

Number *Rational::MAX(Number *number2){
    Rational *tmp = SCAST_RATIONAL(number2);
	if ( !(numerator_!="0") && !(tmp->numerator_!="0")) return this;
	if ( !(numerator_!="0") && tmp->numerator_!="0")
    {
        if (tmp->numerator_.number_[0]=='+') return tmp;
        else return this;
    }
    if (numerator_!="0" && !(tmp->numerator_!="0") )
    {
        if (numerator_.number_[0]=='+') return this;
        else return tmp;
    }
    else
    {
        Rational *cha= SCAST_RATIONAL(this->sub(tmp));
        if (cha->numerator_<(LongInt)"0") return tmp;
        else return this;
    }
}

Number *Rational::MIN(Number *number2){
    Rational *tmp = SCAST_RATIONAL(number2);
	if ( !(numerator_!="0") && !(tmp->numerator_!="0")) return this;
	if ( !(numerator_!="0") && tmp->numerator_!="0")
    {
        if (tmp->numerator_.number_[0]=='+') return this;
        else return tmp;
    }
    if (numerator_!="0" && !(tmp->numerator_!="0") )
    {
        if (numerator_.number_[0]=='+') return tmp;
        else return this;
    }
    else
    {
        Rational *cha= SCAST_RATIONAL(this->sub(tmp));
        if (cha->numerator_<(LongInt)"0") return this;
        else return tmp;
    }
}

Number *Rational::realpart(){
    return this;
}

Number *Rational::imagepart(){
    return new Rational();
}

bool Rational::shi()
{
    return true;
}

void Rational::abs()
{
    numerator_.number_[0]='+';
    denominator_.number_[0]='+';
}
bool Rational::interger()
{
    if (denominator_ !="1") return false;
    else return true;
}

int Rational::positive()
{
    if (numerator_!="0")
    {
        if (numerator_.number_[0]==denominator_.number_[0]) return 1;
        else return -1;
    }
    else return 0;
}

void Rational::print(){
	numerator_.print();
	if(denominator_ != (LongInt)"1"){
		printf("/");
		denominator_.print();
	}
}

Rational *Rational::from_string(char *expression){
    char* end_pointerr;
    char *separate_pos = strchr(expression, '/');
    char *find_i=strchr(expression,'i');
    if (find_i) return NULL;
    if(separate_pos){
        char *numerator,*denominator;
        numerator = new char [500];
        denominator = new char [500];
        char *now = expression;
        bool nflag0 = false, dflag0=false;
        int cnt = 0, num = 0, den = 0;
        while ((*now == ' ' || *now == '0') && cnt < strlen(expression))
        {
            if (*now == '0') nflag0 = true;
            ++now;++cnt;
        }
        bool fei0 = false;
        while (((*now <= '9' && *now >='0') || *now == '+' || *now == '-') && (cnt < strlen(expression)))
        {
            if (*now == '-') numerator[num++] = *now;
            if (*now <= '9' && *now >'0') fei0 = true;
            if (fei0) numerator[num++] = *now;
            ++now;++cnt;
        }

        numerator[num++] = '\0';
        if (*now == '/' && cnt++ < strlen(expression)) ++now;
        else return NULL;
        while ((*now == ' ' || *now == '0') && cnt < strlen(expression))
        {
            if (*now == '0') dflag0 = true;
            ++now;++cnt;
        }

        fei0 = false;
        while (((*now <= '9' && *now >='0') || *now == '+' || *now =='-') && (cnt < strlen(expression)))
        {
            if (*now == '-') denominator[den++] = *now;
            if (*now <= '9' && *now >'0') fei0 = true;
            if (fei0) denominator[den++] = *now;
            ++now;++cnt;
        }

        denominator[den++] = '\0';
        if ((denominator[0] == '\0' && !dflag0) || (numerator[0] == '\0' && !nflag0)) return NULL;
        if (numerator[0] == '\0' && nflag0){strcpy(numerator,"0");}
        if (denominator[0] == '\0' && dflag0){strcpy(denominator,"0");}
        return new Rational(numerator,denominator);
    }else{
        bool flag0=false;
        char *numerator;
        numerator = new char [500];
        char *now = expression;
        int cnt = 0, num = 0;
        while ((*now == ' ' || *now == '0') && cnt < strlen(expression))
        {
            if (*now == '0') flag0=true;
            ++now;++cnt;
        }
        bool fei0 = false;
        while (((*now <= '9' && *now >='0') || *now == '+' || *now =='-') && (cnt < strlen(expression)))
        {
            if (*now == '-') numerator[num++] = *now;
            if (*now <= '9' && *now >'0') fei0 = true;
            if (fei0) numerator[num++] = *now;
            ++now;++cnt;
        }
        numerator[num++] = '\0';
        if (cnt == strlen(expression)) ;
        else return NULL;
        //printf("%s\n", numerator);
        if (numerator[0] == '\0' && flag0) return new Rational("0", "1");
        if (numerator[0] == '\0' && !flag0) return NULL;
        return new Rational(numerator , "1");
    }
}

