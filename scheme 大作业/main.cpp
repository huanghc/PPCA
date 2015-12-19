#include "calc_exp.h"
#include <iostream>
using namespace std;

int main() {
    try {
		Number *res;
			res = calc_exp();
			res->print(); 
	}
	catch(int){cerr<<"Wrong";}
    return 0;
}
