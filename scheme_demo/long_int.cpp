#include "long_int.h"
#include <cassert>
#include <cstdio>

LongInt::LongInt(int number) : number_(number){

}

LongInt::LongInt(const LongInt &long_int2) : number_(long_int2.number_){

}

LongInt::~LongInt(){

}

LongInt::operator bool(){
	return number_;
}

LongInt::operator double(){
	return number_;
}


bool LongInt::operator!=(const LongInt &long_int2) const{
	return number_ != long_int2.number_;
}

bool LongInt::operator<(const LongInt &long_int2) const{
	return number_ < long_int2.number_;
}


LongInt &LongInt::operator=(const LongInt &long_int2){
	number_ = long_int2.number_;
}

LongInt LongInt::operator+(const LongInt &long_int2) const{
	LongInt result(number_ + long_int2.number_);
	return result;
}

LongInt LongInt::operator-(const LongInt &long_int2) const{
	LongInt result(number_ - long_int2.number_);
	return result;
}

LongInt LongInt::operator*(const LongInt &long_int2) const{
	LongInt result(number_ * long_int2.number_);
	return result;
}

LongInt LongInt::operator/(const LongInt &long_int2) const{
	assert(long_int2.number_ && "devide zero");
	LongInt result(number_ / long_int2.number_);
	return result;
}

LongInt LongInt::operator%(const LongInt &long_int2) const{
	assert(long_int2.number_ && "devide zero");
	LongInt result(number_ % long_int2.number_);
	return result;
}

LongInt max(const LongInt &long_int1, const LongInt &long_int2){
	LongInt result(MAX(long_int1.number_, long_int2.number_));
	return result;
}

LongInt min(const LongInt &long_int1, const LongInt &long_int2){
	LongInt result(MIN(long_int1.number_, long_int2.number_));
	return result;
}

void LongInt::print(){
	printf("%d", number_);
}