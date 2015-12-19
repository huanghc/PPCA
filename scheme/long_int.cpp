#include "long_int.h"
#include <cassert>
#include <cstdio>
#include <cstring>
#include <cstdio>
#include <iostream>
using namespace std;

LongInt::LongInt(char number[])  {
    if (number[0] == '-')
    {
        number_ = new char [500];
        strcpy(number_, number);
        if (strlen(number_) == 1) {number_[0]='+';number_[1]='0';number_[2]='\0';}
        if (number_[1] == '0') number_[0] == '+';
        return;
    }
    if (number[0] == '0')
    {
        number_ = new char [500];
        number_[0] = '+';
        number_[1] = '0';
        number_[2] = '\0';
    }
    else
    {
        number_ = new char [500];
        number_[0] = '+';
        strcpy(number_ + 1, number);
    }
}

LongInt::LongInt(const LongInt &long_int2)  {
    //delete [] number_;
    number_ = new char [500];
    strcpy(number_, long_int2.number_);
}

LongInt::~LongInt(){
    delete [] number_;
}

LongInt::operator bool() const {
	if (number_[1] == '0') return false;
	else return true;
}

LongInt::operator double() const {
	double tmp = number_[1]-'0';
	for (int i = 2; number_[i] != '\0'; ++i)
    {
        tmp = tmp * 10 + number_[i] -'0' ;
    }
    if (number_[0] == '+') return tmp;
    else return -tmp;
}


bool LongInt::operator!=(const LongInt &long_int2) const{
	if (strlen(number_) != strlen(long_int2.number_)) return true;
	for (int i = 0; i < strlen(number_); ++i)
    {
        if (number_[i] != long_int2.number_[i]) return true;
    }
    return false;

}

bool LongInt::operator<(const LongInt &long_int2) const{
    if (number_[0] == '+' && long_int2.number_[0] == '-') return false;

    if (number_[0] == '-' && long_int2.number_[0] == '+') return true;

    if (number_[0] == '+' && long_int2.number_[0] == '+')
    {
        if (strlen(number_) < strlen(long_int2.number_)) return true;
        if (strlen(number_) > strlen(long_int2.number_)) return false;
        for (int i = 1; i < strlen(number_); ++i)
        {
            if (number_[i] < long_int2.number_[i]) return true;
            if (number_[i] > long_int2.number_[i]) return false;
        }
        return false;
    }
    else
    {
        if (strlen(number_) < strlen(long_int2.number_)) return false;
        if (strlen(number_) > strlen(long_int2.number_)) return true;
        for (int i = 1; i < strlen(number_); ++i)
        {
            if (number_[i] < long_int2.number_[i]) return false;
            if (number_[i] > long_int2.number_[i]) return true;
        }
        return false;
    }
}


LongInt &LongInt::operator=(const LongInt &long_int2){
	if (this == &long_int2) return *this;
	delete [] number_;
    number_ = new char [500];
    strcpy(number_, long_int2.number_);
    return *this;
}

LongInt LongInt::operator+(const LongInt &long_int2) const{
    if (number_[0] == long_int2.number_[0])
    {
        LongInt tmp;
        int *sum;
        bool flag = true;
        char *l,*s;
        if (strlen(number_) >= strlen(long_int2.number_))
        {
            l = number_ + 1;
            s = long_int2.number_ + 1;
        }
        else
        {
            l = long_int2.number_ + 1;
            s = number_ + 1;
        }

        sum = new int[strlen(l) + 1];

        for(int i = 0;i < (strlen(l) + 1); ++i)
        {
            sum[i] = 0;
        }

        for (int i = 0;i < strlen(s); ++i)
        {
            sum[i] = (l[strlen(l) - i - 1] - '0')+(s[strlen(s) - i - 1] - '0');
        }

        for (int j = strlen(s); j < strlen(l); ++j)
        {
            sum[j] = l[strlen(l) - j - 1] - '0';
        }
        for(int i = 1; i < (strlen(l) + 1); ++i)
        {
            sum[i] += sum[i-1] / 10;
            sum[i-1] = sum[i-1] % 10;
        }
        int k = 1;
        for (int i = 0; i < (strlen(l) + 1); ++i)
        {
            if (((sum[strlen(l) - i]) == 0) && flag);
            else
            {
                flag = false;
                tmp.number_[k++] = sum[strlen(l) - i] + '0';
            }
        }
        delete [] sum;
        if (k == 1) ;
        else tmp.number_[k] = '\0';
        tmp.number_[0] = number_[0];
        return tmp;
    }
    else
    {
        if (*this < long_int2)
        {
            LongInt tmp;
            tmp = *this;
            tmp.number_[0] = '+';
            return (long_int2 - tmp);
        }
        else
        {
            LongInt tmp;
            tmp = long_int2;
            tmp.number_[0] = '+';
            return (*this - tmp);
        }
    }

}

LongInt LongInt::operator-(const LongInt &long_int2) const{
    LongInt tmp;
    LongInt tmp1 = *this; tmp1.number_[0] = '+';
    LongInt tmp2 = long_int2; tmp2.number_[0] = '+';
	if (number_[0] == long_int2.number_[0])
    {
        char *a, *b;
        bool flag = true;
        if (tmp1 < tmp2)
        {
            b = tmp1.number_ + 1;
            a = tmp2.number_ + 1;
        }
        else
        {
            a = tmp1.number_ + 1;
            b = tmp2.number_ + 1;
        }
        int *c;
        c = new int [strlen(a)];
        for (int i = 0; i < strlen(b); ++i)
        {
            c[i] = a[strlen(a) -i - 1] - b[strlen(b) - i - 1];
        }
        for (int i = strlen(b); i < strlen(a); ++i)
        {
            c[i] = a[strlen(a) - i - 1] - '0';
        }

        for (int i = 0; i < (strlen(a) - 1); ++i)
        {
            c[i] += 10;
            c[i + 1] += c[i] / 10 - 1;
            c[i] = c[i] % 10;
        }
        int k = 1;
        for (int i = 1; i <= (strlen(a)); ++i)
        {
            if (((c[strlen(a) - i]) == 0) && flag) ;
            else
            {
                flag = false;
                tmp.number_[k++] = c[strlen(a) - i] + '0';
            }
        }
        delete [] c;
        if (k == 1);
        else tmp.number_[k] = '\0';
        if (*this < long_int2) tmp.number_[0] = '-';
        else tmp.number_[0] = '+';
        return tmp;
    }
    else
    {
        if (*this < long_int2)
        {
            tmp = tmp1 + tmp2;
            tmp.number_[0] = '-';
            return tmp;
        }
        else
        {
            tmp = tmp1 + tmp2;
            return tmp;
        }
    }
}

LongInt LongInt::operator*(const LongInt &long_int2) const{
	LongInt tmp;
	int *c;
    bool flag=true;
    int position;
    char *a, *b;
    a = number_ + 1;
    b = long_int2.number_ + 1;
    c=new int[strlen(a) + strlen(b)];
    for(int i = 0; i < strlen(a) + strlen(b); ++i)
    {
        c[i] = 0;
    }
    for (int i = 0; i < strlen(a); ++i)
    {
        for (int j = 0; j < strlen(b); ++j)
        {
            c[i + j] += (a[strlen(a) - i - 1] - '0') * (b[strlen(b) - j - 1] - '0');
        }
    }

    for(int i = 1; i < (strlen(a) + strlen(b)); ++i)
    {
        c[i] += c[i - 1] / 10;
        c[i - 1] = c[i - 1] % 10;
    }


    int k = 1;
    for (int i = 0; i < (strlen(a) + strlen(b)); ++i)
    {
        if (((c[(strlen(a) + strlen(b)) - i - 1]) == 0) && flag) ;
        else
        {
            flag = false;
            tmp.number_[k++] = c[(strlen(a) + strlen(b)) - i - 1] + '0';
        }
    }
    if (k == 1) ;
    else tmp.number_[k] = '\0';
	if (number_[0] == long_int2.number_[0]);
    else tmp.number_[0] = '-';
    return tmp;
}

LongInt LongInt::operator/(const LongInt &long_int2) const{
	assert(long_int2 && "divede 0");
    LongInt tmp;
    char A[500], B[500];
    int lenA = 0, lenB = 0;
    int res[500] = {0};
    strcpy(A, number_ + 1);
    strcpy(B, long_int2.number_ + 1);
    lenA = strlen(A);
    lenB = strlen(B);

    if(lenA < lenB or (lenA==lenB and (strncmp(A, B, lenB) < 0))){
        return tmp;
    }
    int res_i = 0;
    while(1){
        while(strncmp(A, B, lenB) >= 0){
            int i, begi = 0;
            for (i = 0; A[i] == '0'; ++i)
            begi = i;

            for (; i < lenB; ++i)
                A[i] = A[i] - B[i] +'0';

            for (int i = lenB-1; i >0; --i) if(A[i] < '0')
            {
                A[i] += 10;
                A[i-1]--;
            }
            ++res[res_i];
        }
        ++res_i;

        if(lenA == lenB)
            break;

        int j;
        for ( j = lenB++; j > 0 ; --j)
            B[j] = B[j-1];
        B[j] = '0';
    }
    bool flag = true;
    int k = 1;
    for (int i = 0; i < res_i; ++i)
    {
        if(flag and res[i]!=0)
            flag = false;
        if(res[i]==0){
            if(!flag)
                tmp.number_[k++] = '0';
        }else
            tmp.number_[k++] = res[i] + '0';
    }
    if (k == 1) ;
    else tmp.number_[k] = '\0';
    if (number_[0] == long_int2.number_[0]);
    else tmp.number_[0] = '-';
    return tmp;

}

LongInt LongInt::operator%(const LongInt &long_int2) const{
	assert(long_int2 && "divede 0");
    LongInt tmp;
    if (strlen(number_) < strlen(long_int2.number_)) return tmp;

    LongInt tmp1, tmp2;
    tmp1 = *this; tmp1.number_[0] = '+';
    tmp2 = long_int2; tmp2.number_[0] = '+';
    tmp = *this - ((*this / long_int2) * long_int2);
    if (number_[0] == long_int2.number_[0]) tmp.number_[0] = number_[0];
    else
    {
        if (number_[0] == '+') tmp.number_[0] = '+';
        else tmp.number_[0] = '-';
    }
    if (tmp.number_[1]=='0') tmp.number_[0]='+';
    return tmp;
}

LongInt Max(const LongInt &long_int1, const LongInt &long_int2){
	LongInt tmp1; tmp1 = long_int1; tmp1.number_[0] = '+';
    LongInt tmp2; tmp2 = long_int2; tmp2.number_[0] = '+';
    if (tmp1 < tmp2) return tmp2;
    else return tmp1;
}

LongInt Min(const LongInt &long_int1, const LongInt &long_int2){
	LongInt tmp1; tmp1 = long_int1; tmp1.number_[0] = '+';
    LongInt tmp2; tmp2 = long_int2; tmp2.number_[0] = '+';
    if (tmp1 < tmp2) return tmp1;
    else return tmp2;
}

void LongInt::print(){
	if (number_[0] == '+') cout << number_ + 1;
	else cout << number_;
}
/*
int main()
{
    LongInt x("5555555555555555999999999999999999999999999"),y("-5");

    cout<<double(x);
}*/
