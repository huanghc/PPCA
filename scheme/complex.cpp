#include "float.h"
#include "rational.h"
#include "complex.h"
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <cassert>
#include <cstring>
#include <iostream>
#include <algorithm>
using namespace std;

Complex::Complex(Number *r, Number *i):real(r),image(i)
{
    type_ = COMPLEX;
}

Complex::~Complex(){

}

Number *Complex::convert(Number *number2)
{
    assert(number2->type_ <= type_);
    Complex *result = new Complex();
    switch(number2->type_){
		case RATIONAL:{
			result->real = number2;
			break;
		}
		case FLOAT:{
			result->real = number2;
			break;
		}
		case COMPLEX:{
            Complex *tmp = SCAST_COMPLEX(number2);
            result->real = tmp->real;
            result->image = tmp->image;
            break;
		}
		default:
			assert(0 && "type_ not defined");
	}
	return result;
}

Number *Complex::add(Number *number2)
{
    Complex *tmp = SCAST_COMPLEX(number2);
	Complex *result = new Complex();
    int maxtype =max(max(real->type_, image->type_), max(tmp->real->type_, tmp->image->type_));
    if (maxtype==2)
    {
        Number *tmpr,*tmpi;
        tmpr=new Float(0.0);
        tmpi=new Float(0.0);
        tmpr=(tmpr->convert(real))->add(tmpr->convert(tmp->real));
        tmpi=(tmpi->convert(image))->add(tmpi->convert(tmp->image));
        result->real = tmpr;
        result->image = tmpi;
        return result;
    }
    else
    {
        result->real=real->add(tmp->real);
        result->image=image->add(tmp->image);
        return result;
    }
}

Number *Complex::sub(Number *number2)
{
    Complex *tmp = SCAST_COMPLEX(number2);
	Complex *result = new Complex();
    int maxtype =max(max(real->type_, image->type_), max(tmp->real->type_, tmp->image->type_));
    if (maxtype==2)
    {
        Number *tmpr,*tmpi;
        tmpr=new Float(0.0);
        tmpi=new Float(0.0);
        tmpr=(tmpr->convert(real))->sub(tmpr->convert(tmp->real));
        tmpi=(tmpi->convert(image))->sub(tmpi->convert(tmp->image));
        result->real = tmpr;
        result->image = tmpi;
        return result;
    }
    else
    {
        result->real=real->sub(tmp->real);
        result->image=image->sub(tmp->image);
        return result;
    }
}
Number *Complex::mul(Number *number2)
{
    Complex *tmp = SCAST_COMPLEX(number2);
	Complex *result = new Complex();
    int maxtype =max(max(real->type_, image->type_), max(tmp->real->type_, tmp->image->type_));
    if (maxtype==2)
    {
        Number *tmpr,*tmpi;
        tmpr=new Float(0.0);
        tmpi=new Float(0.0);
        tmpr=((tmpr->convert(real))->mul(tmpr->convert(tmp->real)))->sub((tmpi->convert(image))->mul(tmpi->convert(tmp->image)));
        tmpi=((tmpi->convert(real))->mul(tmpi->convert(tmp->image)))->add((tmpi->convert(image))->mul(tmpi->convert(tmp->real)));
        result->real = tmpr;
        result->image = tmpi;
        return result;
    }
    else
    {
        result->real=(real->mul(tmp->real))->sub(image->mul(tmp->image));
        result->image=(image->mul(tmp->real))->add(real->mul(tmp->image));
        return result;
    }
}
Number *Complex::div(Number *number2)
{
    Complex *tmp = SCAST_COMPLEX(number2);
	Complex *result = new Complex();
    int maxtype =max(max(real->type_, image->type_), max(tmp->real->type_, tmp->image->type_));
    if (maxtype==2)
    {
        Number *tmpr,*tmpi,*tmpc;
        tmpr=new Float(0.0);
        tmpi=new Float(0.0);
        tmpc=new Float(0.0);
        tmpr=((tmpr->convert(real))->mul(tmpr->convert(tmp->real)))->add((tmpi->convert(image))->mul(tmpi->convert(tmp->image)));
        tmpi=((tmpi->convert(image))->mul(tmpi->convert(tmp->real)))->sub((tmpi->convert(real))->mul(tmpi->convert(tmp->image)));
        tmpc = ((tmpc->convert(tmp->real))->mul(tmpc->convert(tmp->real)))->add((tmpc->convert(tmp->image))->mul(tmpc->convert(tmp->image)));
        tmpr=tmpr->div(tmpc);
        tmpi=tmpi->div(tmpc);
        result->real = tmpr;
        result->image = tmpi;
        return result;
    }
    else
    {
        result->real=((real->mul(tmp->real))->add(image->mul(tmp->image)))->div(((tmp->real)->mul(tmp->real))->add((tmp->image)->mul(tmp->image)));
        result->image=((image->mul(tmp->real))->sub(real->mul(tmp->image)))->div(((tmp->real)->mul(tmp->real))->add((tmp->image)->mul(tmp->image)));
        return result;
    }
}
Number *Complex::quotient(Number *number2)
{
    Complex *tmp = SCAST_COMPLEX(number2);
	Complex *result = new Complex();
    result->real=real->quotient(tmp->real);
    return result;
}
Number *Complex::remainder(Number *number2)
{
    Complex *tmp = SCAST_COMPLEX(number2);
	Complex *result = new Complex();
	result->real=real->remainder(tmp->real);
    return result;
}
Number *Complex::modulo(Number *number2)
{
    Complex *tmp = SCAST_COMPLEX(number2);
	Complex *result = new Complex();
	result->real=real->modulo(tmp->real);
    return result;
}
Number *Complex::gcd(Number *number2)
{
    Complex *tmp = SCAST_COMPLEX(number2);
	Complex *result = new Complex();
	result->real=real->gcd(tmp->real);
    return result;
}
Number *Complex::lcm(Number *number2)
{
    Complex *tmp = SCAST_COMPLEX(number2);
	Complex *result = new Complex();
	result->real=real->lcm(tmp->real);
    return result;
}
Number *Complex::EXPT(Number *number2)
{
    Complex *tmp = SCAST_COMPLEX(number2);
	Complex *result = new Complex();
	result->real=real->EXPT(tmp->real);
    return result;
}
Number *Complex::SQRT()
{
	Complex *result = new Complex();
	result->real=real->SQRT();
    return result;
}
Number *Complex::NUM()
{
	Complex *result = new Complex();
	if (real->type_ == 2) return NULL;
	result->real=real->NUM();
    return result;
}
Number *Complex::DEN()
{
	Complex *result = new Complex();
	if (real->type_ == 2) return NULL;
	result->real=real->DEN();
    return result;
}
Number *Complex::floor()
{
	Complex *result = new Complex();
	result->real=real->floor();
    return result;
}
Number *Complex::ceiling()
{
	Complex *result = new Complex();
	result->real=real->ceiling();
    return result;
}
Number *Complex::truncate()
{
	Complex *result = new Complex();
	result->real=real->truncate();
    return result;
}
Number *Complex::ROU()
{
	Complex *result = new Complex();
	result->real=real->ROU();
    return result;
}

Number *Complex::exact()
{
    real=real->exact();
    image=image->exact();
    return this;
}

Number *Complex::inexact()
{
    real=real->inexact();
    image=image->inexact();
    return this;
}

Number *Complex::MAX(Number *number2)
{
    Complex *tmp = SCAST_COMPLEX(number2);
	Complex *result = new Complex();
	if (tmp->real->type_ > real->type_)
    {
        result->real=tmp->real->MAX(real);
    }
    else
    {
        result->real=real->MAX(tmp->real);
    }
    return result;
}

Number *Complex::MIN(Number *number2)
{
    Complex *tmp = SCAST_COMPLEX(number2);
	Complex *result = new Complex();
	if (tmp->real->type_ > real->type_)
    {
        result->real=tmp->real->MIN(real);
    }
    else
    {
        result->real=real->MIN(tmp->real);
    }
    return result;
}

Number *Complex::realpart()
{
    return real;
}

Number *Complex::imagepart()
{
   return image;
}

bool Complex::shi()
{
    if (image->positive()) return false;
    else return true;
}

void Complex::abs()
{
    real->abs();
}
bool Complex::interger()
{
    if (!image->positive() && real->interger()) return true;
    else return false;
}

int Complex::positive()
{
    return 0;
}

void Complex::print()
{
    int maxtype = max(real->type_, image->type_);
    if (maxtype ==2)
    {
        Number *pr,*qr;
        pr=new Float(0.0);
        qr=new Float(0.0);
        qr=qr->convert(real);
        if (qr->positive()) qr->print();
        pr=pr->convert(image);
        if (pr->positive()==1 && qr->positive()!=0)
        {
            cout<<"+";
            pr->print();
            cout<<"i";
            return;
        }
        if (pr->positive()==1 && qr->positive()==0)
        {
            pr->print();
            cout<<"i";
            return;
        }
        if (pr->positive()==0);
        else
        {
            pr->print();
            cout<<"i";
        }
    }
    else
    {
        if (real->positive()) real->print();
        if (image->positive()==1 && real->positive()!=0)
        {
            cout<<"+";
            image->print();
            cout<<"i";
            return;
        }

        if (image->positive()==1 && real->positive()==0)
        {
            image->print();
            cout<<"i";
            return;
        }

        if (image->positive()==0);
        else
        {
            image->print();
            cout<<"i";
        }

    }
}

Complex *Complex::from_string(char *expression)
{

    char *find_i = strchr(expression,'i');
    char *find_1 = strchr(expression+1,'+');
    char *find_2 = strchr(expression+1,'-');
    char *find_f;
    if (find_1) find_f=find_1;
    else
    {
        bool finde=false;
        int i;
        for (i=1;i<strlen(expression);++i)
        {
            if (*(expression+i)=='e') {finde=true;i+=2;break;}
            if (*(expression+i)=='-' && !finde)
            {
                find_f=expression+i;break;
            }
        }
        if (finde)
        {
            for (;i<strlen(expression);++i)
            {
                if (*(expression+i)=='-')
                {
                    find_f=expression+i;break;
                }
            }
        }
    }
    if (find_i &&(strlen(expression)+expression-1)!=find_i) return NULL;
    if (find_f)
    {
        char *qian,*hou;
        qian=new char[5000];
        hou=new char[5000];
        strncpy(qian,expression,find_f-expression);
        qian[find_f-expression]='\0';
        int n=find_i-find_f-1;
        if (find_f == find_1) {strncpy(hou,find_f+1,n);hou[n]='\0';}
        else {strncpy(hou,find_f,n+1);hou[n+1]='\0';}
        //cout<<expression<<" "<<qian<<" "<<hou;
        Number *treal,*timage;
        treal=Rational::from_string(qian);
        if(!treal) {
            treal = Float::from_string(qian);
        }
        if(treal==NULL){throw 0;}
        timage=Rational::from_string(hou);
        if(!timage) {
            timage = Float::from_string(hou);
        }
        if(timage==NULL){throw 0;}
        return new Complex(treal,timage);
    }
    else
    {
        char *hou;
        hou=new char[5000];
        strncpy(hou,expression,strlen(expression)-1);
        hou[strlen(expression)-1]='\0';
        Number *timage;
        timage=Rational::from_string(hou);
        if(!timage) {
            timage = Float::from_string(hou);
        }
        if(timage==NULL){throw 0;}
        return new Complex(new Rational("0","1"),timage);
    }

}
