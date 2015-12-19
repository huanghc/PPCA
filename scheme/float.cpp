#include "float.h"
#include "rational.h"
#include "complex.h"
#include <cstdio>
#include <cstdlib>
#include <cassert>
#include <cmath>
#include <cstring>
#include <iostream>
#include <algorithm>
#include <sstream>
#define ABS(x) ((x)<0?(-(x)):(x))
using namespace std;

Float::Float(double number) : number_(number){
	type_ = FLOAT;
}

Float::~Float(){

}

Number *Float::convert(Number *number2){
	assert(number2->type_ <= type_);
	Float *result = new Float();
	switch(number2->type_){
		case RATIONAL:{
			Rational *tmp = SCAST_RATIONAL(number2);
			result->number_ = (double)tmp->numerator_ / (double)tmp->denominator_;
			break;
		}
		case FLOAT:{
			Float *tmp = SCAST_FLOAT(number2);
			result->number_ = tmp->number_;
			break;
		}
		default:
			assert(0 && "type_ not defined");
	}
	return result;
}

Number *Float::add(Number *number2){
	Float *tmp = SCAST_FLOAT(number2);
	Float *result = new Float(number_ + tmp->number_);
	return result;
}

Number *Float::sub(Number *number2){
	Float *tmp = SCAST_FLOAT(number2);
	Float *result = new Float(number_ - tmp->number_);
	return result;
}

Number *Float::mul(Number *number2){
	Float *tmp = SCAST_FLOAT(number2);
	Float *result = new Float(number_ * tmp->number_);
	return result;
}

Number *Float::div(Number *number2){
	Float *tmp = SCAST_FLOAT(number2);
	assert(ABS(tmp->number_)>1e-9999 && "divide zero");
	Float *result = new Float(number_ / tmp->number_);
	return result;
}

Number *Float::quotient(Number *number2)
{
    Float *tmp = SCAST_FLOAT(number2);
	assert(ABS(tmp->number_)>1e-9999 && "divide zero");
	Float *result = new Float(number_ / tmp->number_);
	return result;
}

Number *Float::remainder(Number *number2)
{

}

Number *Float::modulo(Number *number2)
{

}

Number *Float::gcd(Number *number2)
{

}

Number *Float::lcm(Number *number2)
{

}

Number *Float::EXPT(Number *number2)
{
    Float *tmp = SCAST_FLOAT(number2);
    if (number_ ==0 && tmp->number_ ==0) return new Float(1.0);
    if (number_ ==0 ) return new Float(0.0);
    else
    {
        if (tmp->number_ ==0) return new Float(1.0);
        else
        {
            double result = pow(number_, tmp->number_);
            return new Float(result);
        }
    }
}

Number *Float::SQRT()
{
    double x;
    if (number_>=0)
    {
        double x=sqrt(number_);
        return new Float(x);
    }
    else
    {
        double x=sqrt(-number_);
        return new Complex(new Float(0),new Float(x));
    }
}

Number *Float::NUM()
{
    Rational *result=SCAST_RATIONAL(exact());
    return result->NUM();
}

Number *Float::DEN()
{
    Rational *result=SCAST_RATIONAL(exact());
    return result->DEN();
}

Number *Float::floor()
{
    double result = std::floor(number_);
    return new Float(result);
}

Number *Float::ceiling()
{
    double result = std::ceil(number_);
    return new Float(result);
}

Number *Float::truncate()
{
    double result1 = std::ceil(number_);
    double result2 = std::floor(number_);
    if (std::fabs(result1)<=std::fabs(number_)) return new Float(result1);
    else return new Float(result2);
}

Number *Float::ROU()
{
    double result,tmp;
    tmp=number_;
    if ((tmp-std::floor(tmp))<(std::ceil(tmp)-tmp)) return new Float(std::floor(tmp));
    if ((tmp-std::floor(tmp))>(std::ceil(tmp)-tmp)) return new Float(std::ceil(tmp));
    if ((tmp-std::floor(tmp))==(std::ceil(tmp)-tmp) && (tmp-std::floor(tmp))==0) return new Float(std::floor(tmp));
    else
    {
        if (((long long)std::floor(tmp))%2==0) return new Float(std::floor(tmp));
        else return new Float(std::ceil(tmp));
    }
}

Number *Float::exact()
{
    char fenzi[1000],fenmu[1000];
    char shu[100];
    int fz=0,fm=0;
    stringstream s;
    s<<number_;
    s>>shu;
    s.clear();
    char *find_e=strchr(shu,'e');
    char *find_d=strchr(shu,'.');
    int dian;
    if (find_e && find_d)
    {
        dian=find_e-find_d-1;
        int n=find_e-shu;
        for (int i=0;i<n;++i)
        {
            if (shu[i]!='.') fenzi[fz++]=shu[i];
        }
        fenzi[fz]='\0';
        ++find_e;
        char tmp[100];
        int p;
        if (*find_e=='-')
        {
            ++find_e;int i;
            for ( i=0;i<(strlen(shu)-n-2);++i,++find_e) tmp[i]=*find_e;
            tmp[i]='\0';
            s<<tmp;
            s>>p;
            s.clear();
            p=p+dian;
            fenmu[fm++]='1';
            for (int j=0;j<p;++j)
            {
                fenmu[fm++]='0';
            }
            fenmu[fm]='\0';
            return new Rational(fenzi,fenmu);
        }
        else
        {
            int i;
            for ( i=0;i<(strlen(shu)-n-2);++i,++find_e) tmp[i]=*find_e;
            tmp[i]='\0';
            s<<tmp;
            s>>p;
            s.clear();
            p=p-dian;
            if (p>=0)
            {
                for (int j=0;j<p;++j)
                {
                    fenzi[fz++]='0';
                }
                fenzi[fz]='\0';
                return new Rational(fenzi,"1");
            }
            else
            {
                p=0-p;
                fenmu[fm++]='1';
                for (int j=0;j<p;++j)
                {
                    fenmu[fm++]='0';
                }
                fenzi[fm]='\0';
                return new Rational(fenzi,fenmu);
            }
        }
    }
    if (!find_e && find_d)
    {
        dian=find_d-shu;
        dian=strlen(shu)-dian-1;
        for (int i=0;i<strlen(shu);++i)
        {
            if (shu[i]!='.') fenzi[fz++]=shu[i];
        }
        fenzi[fz]='\0';
        fenmu[fm++]='1';
        for (int i=0;i<dian;++i) fenmu[fm++]='0';
        fenmu[fm]='\0';
        return new Rational(fenzi,fenmu);
    }
    if (find_e && !find_d)
    {
        int n=find_e-shu;
        for (int i=0;i<n;++i)
        {
            if (shu[i]!='.') fenzi[fz++]=shu[i];
        }
        fenzi[fz]='\0';
        ++find_e;
        char tmp[100];
        int p;
        if (*find_e=='-')
        {
            ++find_e;int i;
            for ( i=0;i<(strlen(shu)-n-2);++i,++find_e) tmp[i]=*find_e;
            tmp[i]='\0';
            s<<tmp;
            s>>p;
            s.clear();
            p=p;
            fenmu[fm++]='1';
            for (int j=0;j<p;++j)
            {
                fenmu[fm++]='0';
            }
            fenzi[fm]='\0';
            return new Rational(fenzi,fenmu);
        }
        else
        {
            int i;
            for ( i=0;i<(strlen(shu)-n-2);++i,++find_e) tmp[i]=*find_e;
            tmp[i]='\0';
            s<<tmp;
            s>>p;
            s.clear();
            p=p;
            for (int j=0;j<p;++j)
            {
                fenzi[fz++]='0';
            }
            fenzi[fz]='\0';
            return new Rational(fenzi,"1");
        }
    }
    if (!find_e && !find_d)
    {
        strcpy(fenzi,shu);
        return new Rational(fenzi,"1");
    }
}

Number *Float::inexact()
{
    return this;
}

Number *Float::MAX(Number *number2)
{
    Float *tmp = SCAST_FLOAT(number2);
    if (tmp->number_>number_) return tmp;
    else return this;
}

Number *Float::MIN(Number *number2)
{
    Float *tmp = SCAST_FLOAT(number2);
    if (tmp->number_ > number_) return this;
    else return tmp;
}

Number *Float::realpart()
{
    return this;
}

Number *Float::imagepart()
{
    return new Float(0.0);
}

void Float::abs()
{
    number_=ABS(number_);
}

bool Float::shi()
{
    return true;
}

bool Float::interger()
{
    if (number_<((1<<31)-1))
    {
        if (number_==((double)((long long) (number_)))) return true;
        else return false;
    }
    else return true;
}

int Float::positive()
{
    if (number_>0) return 1;
    if (number_==0.0) return 0;
    else return -1;
}

void Float::print(){
	printf("%lf",number_);
}

Float *Float::from_string(char *expression){
    char *end_pointer;
    double val = strtod(expression, &end_pointer);
    if (end_pointer == expression || end_pointer != expression + strlen(expression))
	    return NULL;
    return new Float(val);
}


