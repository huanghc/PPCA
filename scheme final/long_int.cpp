#include "long_int.h"
#include <cassert>
#include <cstdio>
#include <sstream>
#include <iostream>
#include <string>
using namespace std;

string add(string s1, string s2){
   int len1=s1.length(),len2=s2.length();
	int p,i; 

	if (len1>len2) p=len1;
	else p=len2;
	int a[p+1],b[p+1];
	string s3;	
	
	for (i=0;i<len1;++i) a[i]=s1[len1-1-i]-'0';
	for (i=len1;i<p+1;++i) a[i]=0;
	for (i=0;i<len2;++i) b[i]=s2[len2-1-i]-'0';
	for (i=len2;i<p+1;++i) b[i]=0;
		
	for(i=0;i<p;++i){
		a[i]+=b[i]; 
		a[i+1]+=a[i]/10;
		a[i]%=10; 
	} 
    p=p+1;
	while((a[p-1]==0)&&(p>1)) --p; 
	for(i=0;i<p;++i){
		char tmp=a[p-1-i]+'0';s3+=tmp;
	}
	return s3;
}

string sub(string str1, string str2){
	string str;
	int tmp=str1.length()-str2.length();
	int tmp1=0;
	for (int i=str2.length()-1; i>= 0; i--){	
		if (str1[tmp + i]<str2[i] + tmp1){		
			str=char(str1[tmp+i]-str2[i]-tmp1+'0'+10)+str;
			tmp1 = 1;
		}
		else{		
			str=char(str1[tmp+i]-str2[i]-tmp1+'0')+str;
			tmp1=0;
		}
	}
	for (int i=tmp-1;i>=0;i--){	
		if (str1[i]-tmp1>='0'){		
			str=char(str1[i]-tmp1)+str;
			tmp1=0;
		}
		else{		
			str=char(str1[i]-tmp1+10)+str;
			tmp1=1;
		}
	}
	str.erase(0,str.find_first_not_of('0'));
	return str;
}

string mul(string s1, string s2){
	string s3;
	int len1 = s1.length();
	int len2 = s2.length();
	string tmp2;
	for (int i = len2 - 1; i >= 0; i--){	
		tmp2 = "";
		int temp = s2[i] - '0';
		int t = 0;
		int tmp1 = 0;
		if (temp != 0){		
			for (int j=1; j<=len2-1-i;j++)
				tmp2 += "0";
			for (int j = len1-1; j>=0; j--){			
				t=(temp*(s1[j] - '0') + tmp1) % 10;
				tmp1=(temp*(s1[j] - '0') + tmp1) / 10;
				tmp2=char(t + '0') + tmp2;
			}
			if (tmp1 != 0) tmp2 = char(tmp1 + '0') + tmp2;
		}
		s3 = add(s3, tmp2);
	}
	s3.erase(0, s3.find_first_not_of('0'));
	return s3;
}

int cmp(string str1, string str2){
	if (str1.length()>str2.length()) return 1;
	else if (str1.length()<str2.length())  return -1;
	else return (str1>str2);
}

string div(string str1, string str2){
	string qout = "";
	if (str1 == "0"){	
		qout = "0";return qout;		
	}
	if (cmp(str1, str2)<0){	
		qout = "0";
		return qout;
	}
	else if (cmp(str1, str2) == 0){	
		qout = "1";
		return qout;
	}
	else{	
		int len1 = str1.length();
		int len2 = str2.length();
		string tempstr;
		tempstr.append(str1, 0, len2 - 1);
		for (int i = len2 - 1; i<len1; i++){		
			tempstr = tempstr + str1[i];
			tempstr.erase(0, tempstr.find_first_not_of('0'));
			if (tempstr.empty())
				tempstr = "0";
			for (char ch = '9'; ch >= '0'; ch--){			
				string str, tmp;
				str = str + ch;
				tmp = mul(str2, str);
				if (cmp(tmp, tempstr) <= 0){				
					qout = qout + ch;
					tempstr = sub(tempstr, tmp);
					break;
				}
			}
		}
	}
	qout.erase(0, qout.find_first_not_of('0'));
	if (qout.empty()) qout = "0";
	return qout;
}

LongInt::LongInt(string num) {
	number_ = num;
}

LongInt::LongInt(const LongInt &long_int2){
	number_ = long_int2.number_;
}

LongInt::~LongInt(){

}

LongInt::operator bool(){
	return (number_ != "0");
}

LongInt::operator double(){
	stringstream ss;
	double n;
	ss << number_;
	ss >> n;
	return n;
}

bool LongInt::operator!=(const LongInt &long_int2) const{
	return number_ != long_int2.number_;
}

bool LongInt::operator<(const LongInt &long_int2) const{
	if (number_[0] == '-' && long_int2.number_[0] != '-') return true;		
	if (number_[0] != '-' && long_int2.number_[0] == '-') return false;
	if (number_[0] != '-' && long_int2.number_[0] != '-'){	
		if (number_.length() < long_int2.number_.length()) return true;		
		if (number_.length() > long_int2.number_.length()) return false;			
		else return (number_<long_int2.number_);
	}
	else{	
		if (number_.length() < long_int2.number_.length()) return false;			
		else if (number_.length() > long_int2.number_.length()) return true;			
		else{		
			for (int i = 1; i < number_.length(); ++i){			
				if (number_[i] < long_int2.number_[i]) return false;					
				else if (number_[i] > long_int2.number_[i]) return true;					
			}
			return false;
		}
	}
}

LongInt ABs(const LongInt &long_int1)
{
	if (long_int1.number_[0] == '-')
	{
		string tmp;
		for (int i = 1; i < long_int1.number_.length(); ++i)
			tmp += long_int1.number_[i];
		LongInt result(tmp);
		return result;
	}
	else
	{
		string tmp;
		tmp = long_int1.number_;
		LongInt result(tmp);
		return result;
	}
}

LongInt &LongInt::operator=(const LongInt &long_int2){
	number_ = long_int2.number_;
	return *this;
}

LongInt LongInt::operator+(const LongInt &long_int2) const{
	LongInt result;
	int t=long_int2.number_.length()-1;
	int q=number_.length()-1;
	if (number_[0] != '-' && long_int2.number_[0] != '-'){	
		result.number_ = add(number_, long_int2.number_);
	}
	else if (number_[0] == '-' && long_int2.number_[0] == '-'){	
		result.number_ += '-';
		result.number_ += add(number_.substr(1,q), long_int2.number_.substr(1,t));
	}
	else if (long_int2.number_[0] == '-' && number_[0] != '-'){	
		LongInt tmp;
		tmp.number_= long_int2.number_.substr(1,t);
		result = *this - tmp;
	}
	else{	
		LongInt tmp;
		tmp.number_=number_.substr(1,q);
		result = long_int2 - tmp;
	}
	return result;
}

LongInt LongInt::operator-(const LongInt &long_int2) const{
	LongInt result;
	int t=long_int2.number_.length()-1;
	int q=number_.length()-1;
	if (long_int2.number_[0] == '-' && number_[0] != '-'){	
		LongInt tmp;
		tmp.number_= long_int2.number_.substr(1,t);
		result = *this + tmp;
	}
	else if (number_[0] == '-'&&long_int2.number_[0] != '-'){	
		LongInt tmp, tmp2;
		tmp.number_=number_.substr(1,q);
		result.number_ += '-';
		tmp2 = tmp + long_int2;
		result.number_ += tmp2.number_;
	}
	else if (number_ == long_int2.number_){	
		result.number_ = "0";
	}
	else if (number_[0] != '-' && long_int2.number_[0] != '-'){
		if (long_int2 < *this)	result.number_ += sub(number_, long_int2.number_);	
		else {
			result.number_ += '-';
			result.number_ += sub(long_int2.number_, number_);
		}	
	}
	else if (number_[0] == '-' && long_int2.number_[0] == '-'){
		if (*this < long_int2){
			result.number_ += '-';
			result.number_ += sub(number_.substr(1,q), long_int2.number_.substr(1, t));
		}
		else {
			result.number_ += sub(long_int2.number_.substr(1, t), number_.substr(1, q));
		}		
	}
	return result;
}

LongInt LongInt::operator*(const LongInt &long_int2) const{
	LongInt result;
	string s1, s2;
	int tmp = 0;
	if (number_[0] == '-'){	
		tmp++;
		s1 = number_.substr(1, number_.length() - 1);
	}
	else s1 = number_;
	if (long_int2.number_[0] == '-'){	
		tmp++;
		s2 = long_int2.number_.substr(1, long_int2.number_.length() - 1);
	}
	else s2 = long_int2.number_;
	if (tmp==1){	
		result.number_ += '-';
	}
	result.number_ += mul(s1, s2);
	return result;
}

LongInt LongInt::operator/(const LongInt &long_int2) const{
	LongInt result;
	result.number_ = "";
	string s1, s2;
	int flag = 0;
	if (number_[0] == '-'){	
		flag++;
		s1 = number_.substr(1, number_.length() - 1);
	}
	else s1 = number_;
	if (long_int2.number_[0] == '-'){	
		flag++;
		s2 = long_int2.number_.substr(1, long_int2.number_.length() - 1);
	}
	else s2 = long_int2.number_;
	if (flag==1){	
		result.number_ += '-';
	}
	result.number_ += div(s1,s2);
	return result;
}

LongInt LongInt::operator%(const LongInt &long_int2) const{
	LongInt result;
	assert((long_int2.number_ != "0") && "divide zero");
	result = *this - (*this / long_int2)*long_int2;
	return result;
}

LongInt max(const LongInt &long_int1, const LongInt &long_int2){
	if (long_int1 < long_int2) return long_int2;
	else return long_int1;
}

LongInt min(const LongInt &long_int1, const LongInt &long_int2){
	if (long_int1 < long_int2) return long_int1;
	else return long_int2;
}

void LongInt::print(){
	string str;
	for (int i = 0; i<number_.length(); ++i){	
		str+=number_[i];
	}
	cout<< str;
}
