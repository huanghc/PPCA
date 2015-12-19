#include "rational.h"
#include <cassert>
#include <cstdlib>
#include <cstdio>
#include <cstring>

Rational::Rational(int numerator, int denominator) : numerator_(numerator),
	denominator_(denominator){
	type_ = RATIONAL;
	reduce();
}

Rational::~Rational(){

}

void Rational::reduce(){
	assert(denominator_ && "denominator is zero");
	if(!numerator_){
		denominator_ = 1;
		return;
	}
	LongInt big, small, tmp;
	big = max(numerator_, denominator_);
	small = min(numerator_, denominator_);
	while(tmp = big % small){
		big = small;
		small = tmp;
	}
	numerator_ = numerator_ / small;
	denominator_ = denominator_ / small;
	if(denominator_ < LongInt(0)){
		numerator_ = LongInt(0)-numerator_;
		denominator_ = LongInt(0)-denominator_;
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

void Rational::print(){
	numerator_.print();
	if(denominator_ != (LongInt)1){
		printf("/");
		denominator_.print();
	}
	printf("\n");
}

Rational *Rational::from_string(char *expression){
    char* end_pointerr;
    char *separate_pos = strchr(expression, '/');
    if(separate_pos){
        int numerator = (int)strtol(expression,&end_pointerr,10);
        if( end_pointerr == expression || end_pointerr != separate_pos )
        	return NULL;
        int denominator = (int)strtol(separate_pos + 1,&end_pointerr,10);
        if( end_pointerr == separate_pos + 1 || end_pointerr != expression + strlen(expression) )
        	return NULL;
        return new Rational(numerator,denominator);
    }else{
    	int numerator = (int)strtol(expression,&end_pointerr,10);
        if( end_pointerr == expression || end_pointerr != expression + strlen(expression) )
        	return NULL;
        return new Rational(numerator , 1);
    }
}

// int main(){
// 	Rational *a = new Rational(-18,18);
// 	// Rational *b = new Rational(4,5);
// 	printf("%d %d\n", a->numerator_.number_, a->denominator_.number_);
// 	// (a->div(b))->print();
// }
