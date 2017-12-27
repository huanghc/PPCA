#include "calc_exp.h"
#include "opt.h"
#include "compare.h"
#include "next_token.h"
#include <cstdio>

Number *calc_exp(){
	char *tk0 = next_token();
	Number *res;
	if (*tk0 == '(')
	{
		char *tk1 = next_token();
		Opt *opt;
		Cons *cons = new Cons(NULL, NULL), *tail = cons;
		Number *val;
		if (tk1 == NULL){ printf("123"); throw 0; }
		if (strcmp(tk1, "+") == 0)opt = new Add();
		else if (strcmp(tk1, "-") == 0)opt = new Sub();
		else if (strcmp(tk1, "*") == 0)opt = new Mul();
		else if (strcmp(tk1, "/") == 0)opt = new Div();
		else if (strcmp(tk1, "abs") == 0)opt = new Abs();
		else if (strcmp(tk1, "quotient") == 0)opt = new Quotient();
		else if (strcmp(tk1, "remainder") == 0)opt = new Remainder();
		else if (strcmp(tk1, "modulo") == 0)opt = new Modulo();
		else if (strcmp(tk1, "gcd") == 0)opt = new Gcd();
		else if (strcmp(tk1, "lcm") == 0)opt = new Lcm();
		else if (strcmp(tk1, "expt") == 0)opt = new Expt();
		else if (strcmp(tk1, "sqrt") == 0)opt = new Sqrt();
		else if (strcmp(tk1, "max") == 0)opt = new Max();
		else if (strcmp(tk1, "min") == 0)opt = new Min();
		else if (strcmp(tk1, "<") == 0)opt = new Less();
		else if (strcmp(tk1, "<=") == 0)opt = new Less_equ();
		else if (strcmp(tk1, ">") == 0)opt = new Greater();
		else if (strcmp(tk1, ">=") == 0)opt = new Greater_equ();
		else if (strcmp(tk1, "exact?") == 0)opt = new Jud_exact();
		else if (strcmp(tk1, "inexact?") == 0)opt = new Jud_inexact();
		else if (strcmp(tk1, "zero?") == 0)opt = new Jud_zero();
		else if (strcmp(tk1, "negative?") == 0)opt = new Jud_negative();
		else if (strcmp(tk1, "positive?") == 0)opt = new Jud_positive();
		else if (strcmp(tk1, "odd?") == 0)opt = new Jud_odd();
		else if (strcmp(tk1, "even?") == 0)opt = new Jud_even();
		else if (strcmp(tk1, "numerator") == 0)opt = new Numerator();
		else if (strcmp(tk1, "denominator") == 0)opt = new Denominator();
		else if (strcmp(tk1, "floor") == 0)opt = new Floor();
		else if (strcmp(tk1, "ceiling") == 0)opt = new Ceiling();
		else if (strcmp(tk1, "truncate") == 0)opt = new Truncate();
		else if (strcmp(tk1, "round") == 0)opt = new Round();
		else if (strcmp(tk1, "inexact->exact") == 0)opt = new Exact();
		else if (strcmp(tk1, "exact->inexact") == 0)opt = new Inexact();
		else if (strcmp(tk1, "real-part") == 0)opt = new Realpart();
		else if (strcmp(tk1, "imag-part") == 0)opt = new Imagepart();
		else if (strcmp(tk1, "sin") == 0)opt = new Sin();
		else if (strcmp(tk1, "cos") == 0)opt = new Cos();
		else if (strcmp(tk1, "tan") == 0)opt = new Tan();
		else if (strcmp(tk1, "asin") == 0)opt = new Asin();
		else if (strcmp(tk1, "acos") == 0)opt = new Acos();
		else if (strcmp(tk1, "atan") == 0)opt = new Atan();
		else if (strcmp(tk1, "exp") == 0)opt = new Exp();
		else if (strcmp(tk1, "log") == 0)opt = new Log();
		else if (strcmp(tk1, "make-rectangular") == 0)opt = new Make_rectangular();
		else if (strcmp(tk1, "make-polar") == 0)opt = new Make_polar();
		else if (strcmp(tk1, "magnitude") == 0)opt = new Magnitude();
		else if (strcmp(tk1, "angle") == 0)opt = new Angle();
		else if (strcmp(tk1, "integer?") == 0)opt = new Jud_integer();
		else if (strcmp(tk1, "rational?") == 0)opt = new Jud_rational();
		else if (strcmp(tk1, "real?") == 0)opt = new Jud_real();
		else if (strcmp(tk1, "complex?") == 0)opt = new Jud_complex();
		else if (strcmp(tk1, "number?") == 0)opt = new Jud_number();
		else if(strcmp(tk1,"equal?")==0)opt=new Eql();
		else if(strcmp(tk1,"string=?")==0)opt=new Str_eql();
		else if(strcmp(tk1,"string-ci=?")==0)opt=new Str_cieql();
		else if(strcmp(tk1,"string<?")==0)opt=new Str_less();
		else if(strcmp(tk1,"string-ci<?")==0)opt=new Str_ciless();
		else if(strcmp(tk1,"string<=?")==0)opt=new Str_lesseql();
		else if(strcmp(tk1,"string-ci<=?")==0)opt=new Str_cilesseql();		
		else if(strcmp(tk1,"char=?")==0)opt=new Cha_eql();
		else if(strcmp(tk1,"char-ci=?")==0)opt=new Cha_cieql();
		else if(strcmp(tk1,"char<?")==0)opt=new Cha_less();
		else if(strcmp(tk1,"char-ci<?")==0)opt=new Cha_ciless();
		else if(strcmp(tk1,"char<=?")==0)opt=new Cha_lesseql();
		else if(strcmp(tk1,"char-ci<=?")==0)opt=new Cha_cilesseql();		
		else if(strcmp(tk1,"string?")==0)opt=new Isstr();
		else if(strcmp(tk1,"make-string")==0)opt=new Mak_str();
		else if(strcmp(tk1,"string")==0)opt=new Get_str();
		else if(strcmp(tk1,"string-length")==0)opt=new Str_len();		
		else if(strcmp(tk1,"string-ref")==0)opt=new Str_ref();
		else if(strcmp(tk1,"string-append")==0)opt=new Str_app();
		else if(strcmp(tk1,"string-copy")==0)opt=new Str_cpy();		
		else if(strcmp(tk1,"substring")==0)opt=new Str_sub();
		else if(strcmp(tk1,"char?")==0)opt=new Ischa();
		else if(strcmp(tk1,"char-alphabetic?")==0)opt=new Car_alph();
		else if(strcmp(tk1,"char-numeric?")==0)opt=new Car_num();
		else if(strcmp(tk1,"char-whitespace?")==0)opt=new Car_whi();
		else if(strcmp(tk1,"char-upper-case?")==0)opt=new Is_chaupp();
		else if(strcmp(tk1,"char-lower-case?")==0)opt=new Is_chalow();
		else if(strcmp(tk1,"char-upcase")==0)opt=new Car_up();
		else if(strcmp(tk1,"char-downcase")==0)opt=new Car_down();
		else if(strcmp(tk1,"char->integer")==0)opt=new Cha_int();
		else if(strcmp(tk1,"integer->char")==0)opt=new Int_cha();
		else if(strcmp(tk1,"number->string")==0)opt=new Num_str();
		else if(strcmp(tk1,"string->number")==0)opt=new Str_num();		
		else throw 0;
		while ((val = calc_exp()))
		{
			tail->cdr = new Cons(val, NULL);
			tail = tail->cdr;
		}
		res = opt->calc(cons->cdr);
		for (Cons *np; cons; cons = np)
		{
			np = cons->cdr;
			delete cons;
		}
	}
	else if (*tk0 == ')')
	{
		return NULL;
	}
	else
	{	res=Rational::from_string(tk0);
		if(!res) 
		{	res = Float::from_string(tk0);
			if (!res) 
			{	res = Complex::from_string(tk0);
				if (!res)
				{	res = String::from_string(tk0);
					if (!res)
					{	res = Boolean::from_string(tk0);
						if (!res) 
						{	res = Char::from_string(tk0);
						} 
					}
				}
			} 
		}
		if(res == NULL){throw 0;}
//		string tmp(tk0);
//		if (tmp.find('#') != tmp.npos){
//			res = Boolean::from_string(tk0);
//		}
//		else if (tmp.find('i') != tmp.npos)
//		{
//			string t1;
//			int pos_f = 0;
//			if (tmp.find('+') != tmp.npos) pos_f = tmp.find('+');
//			else if (tmp.find('-') != tmp.npos) pos_f = tmp.find('-');
//			else pos_f = -1;
//			char ex[1000];
//			memset(ex, '0', sizeof(ex));
//			if (pos_f == -1)
//			{
//				t1 = "0+" + tmp;
//			}
//			if (tmp.find('i') == pos_f + 1)
//			{
//				t1 = tmp.substr(0, pos_f + 1) + "1i";
//			}
//			else t1 = tmp;
//			//cout<<t1<<endl;
//			for (int i = 0; i < t1.length(); ++i)
//			{
//				ex[i] = t1[i];
//			}
//			ex[t1.length()] = '\0';
//			res = Complex::from_string(ex);
//		}
//		else if (tmp.find('.') != tmp.npos || tmp.find('e') != tmp.npos || tmp.find('E') != tmp.npos)
//		{
//			res = Float::from_string(tk0);
//		}
//		else res = Rational::from_string(tk0);
	}
	return res;
}
