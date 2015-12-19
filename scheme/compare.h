#include "opt.h"
#include "float.h"
#include "rational.h"
#include "complex.h"
#include "number.h"
#include <cmath>
#include <iomanip>
#include <sstream>
#include <complex>
#include <cstdlib>
#include <cmath>
#include <iostream>
#define SCAST_RATIONAL(x) static_cast<Rational*>(x)
#define SCAST_FLOAT(x) static_cast<Float*>(x)

class Add : public Opt {
    /* Use the lowest level type */
    Number *calc(Cons *con) {

		Number *res = new Rational("0","1");
		Number *last;
        for (; con; con = con->cdr)
        {
			if(con->car->type_>3||con->car->type_<1)
			{
				throw 0;
			}
            Number *opr = con->car, *conv;
            last = res;
            if (res->type_ > opr->type_)
			{
				res = res->add(conv = res->convert(opr));
			}
            else
			{
			    //std::cout<<0;
                res = (conv = opr->convert(res))->add(opr);
			}
        }
        return res;
    }
};
class Sub:public Opt{
	Number *calc(Cons *con)
	{
		Cons *tmp=con;
		int cnt=0;
		for(;tmp;tmp=tmp->cdr)
		{
			if(tmp->car->type_>3||tmp->car->type_<1)
			{
				throw 0;
			}
			cnt++;
		}
		Number *res=new Rational("0","1"),*last;
		Number *opr = con->car, *conv;
		last=res;
		if(cnt==1)
		{
			if (res->type_ > opr->type_)
				res = res->sub(conv = res->convert(opr));
			else
				res = (conv = opr->convert(res))->sub(opr);

			return res;
		}
		if (res->type_ > opr->type_)
            res = res->add(conv = res->convert(opr));
        else
            res = (conv = opr->convert(res))->add(opr);
        con=con->cdr;
        delete last;
        delete conv;
		for(;con;con=con->cdr)
		{
			opr=con->car;
			last=res;
			if(res->type_>opr->type_)
				res=res->sub(conv=res->convert(opr));
			else
				res=(conv=opr->convert(res))->sub(opr);

		}
		return res;
	}
};
class Mul : public Opt {
    /* Use the lowest level type */
    Number *calc(Cons *con) {
        Number *res = new Rational("1", "1"), *last;
        for (; con; con = con->cdr)
        {
			if(con->car->type_>3||con->car->type_<1)
			{
				throw 0;
			}
            Number *opr = con->car, *conv;
            last = res;
            if (res->type_ > opr->type_)
                res = res->mul(conv = res->convert(opr));
            else
                res = (conv = opr->convert(res))->mul(opr);

        }
        return res;
    }
};

class Div:public Opt{
	Number *calc(Cons *con)
	{
		Cons *tmp=con;
		int cnt=0;
		for(;tmp;tmp=tmp->cdr)
		{
			if(tmp->car->type_>3||tmp->car->type_<1)
			{
				throw 0;
			}
			cnt++;
		}
		Number *res=new Rational("1","1"),*last;
		Number *opr=con->car,*conv;
		last=res;
		if(cnt==1)
		{
			if(res->type_>opr->type_)
				res=res->div(conv=res->convert(opr));
			else
				res=(conv=opr->convert(res))->div(opr);
			delete last;
			delete conv;
			return res;
		}
		if(res->type_>opr->type_)
			res=res->mul(conv=res->convert(opr));
		else
			res=(conv=opr->convert(res))->mul(opr);
		con=con->cdr;
		delete last;
		delete conv;
		for(;con;con=con->cdr)
		{
			opr=con->car;
			last=res;
			if(res->type_>opr->type_)
				res=res->div(conv=res->convert(opr));
			else
				res=(conv=opr->convert(res))->div(opr);

		}
		return res;
	}
};
class Abs:public Opt{
    Number *calc(Cons *con)
    {
        Cons *tmp=con;
		int cnt=0;
		for(;tmp;tmp=tmp->cdr)
		{
			if(!tmp->car->shi())
			{
				throw 0;
			}
			cnt++;
		}
		if (cnt!=1) throw 0;
        Number *res=con->car;
        res->abs();
        return res;
    }
};

class Quotient:public Opt{
    Number *calc(Cons *con)
    {
        Cons *tmp=con;
		int cnt=0;
		for(;tmp;tmp=tmp->cdr)
		{
			if (!tmp->car->interger())
			{
				throw 0;
			}
			cnt++;
		}
		if (cnt!=2) throw 0;
		Number *res=new Rational("1","1"),*last;
		Number *opr=con->car,*conv;
		last=res;
		if(res->type_>opr->type_)
			res=res->mul(conv=res->convert(opr));
		else
			res=(conv=opr->convert(res))->mul(opr);
		con=con->cdr;
		delete last;
		delete conv;
		for(;con;con=con->cdr)
		{
			opr=con->car;
			last=res;
			if(res->type_>opr->type_)
				res=res->quotient(conv=res->convert(opr));
			else
				res=(conv=opr->convert(res))->quotient(opr);

		}
		return res;
    }

};

class Remainder:public Opt{
    Number *calc(Cons *con)
    {
        Cons *tmp=con;
		int cnt=0;
		for(;tmp;tmp=tmp->cdr)
		{
			if (tmp->car->type_ == 2 || !tmp->car->interger())
			{
				throw 0;
			}
			cnt++;
		}
		if (cnt!=2) throw 0;
		Number *res=new Rational("1","1"),*last;
		Number *opr=con->car,*conv;
		last=res;
		if(res->type_>opr->type_)
			res=res->mul(conv=res->convert(opr));
		else
			res=(conv=opr->convert(res))->mul(opr);
		con=con->cdr;
		delete last;
		delete conv;
		for(;con;con=con->cdr)
		{
			opr=con->car;
			last=res;
			if(res->type_>opr->type_)
				res=res->remainder(conv=res->convert(opr));
			else
				res=(conv=opr->convert(res))->remainder(opr);

		}
		return res;
    }
};

class Modulo:public Opt{
    Number *calc(Cons *con)
    {
        Cons *tmp=con;
		int cnt=0;
		for(;tmp;tmp=tmp->cdr)
		{
			if (tmp->car->type_ == 2 || !tmp->car->interger())
			{
				throw 0;
			}
			cnt++;
		}
		if (cnt!=2) throw 0;
		Number *res=new Rational("1","1"),*last;
		Number *opr=con->car,*conv;
		last=res;
		if(res->type_>opr->type_)
			res=res->mul(conv=res->convert(opr));
		else
			res=(conv=opr->convert(res))->mul(opr);
		con=con->cdr;
		delete last;
		delete conv;
		for(;con;con=con->cdr)
		{
			opr=con->car;
			last=res;
			if(res->type_>opr->type_)
				res=res->modulo(conv=res->convert(opr));
			else
				res=(conv=opr->convert(res))->modulo(opr);

		}
		return res;
    }
};

class Gcd:public Opt{
    Number *calc(Cons *con)
    {
        Cons *tmp=con;
		int cnt=0;
		for(;tmp;tmp=tmp->cdr)
		{
			if (tmp->car->type_ == 2 || !tmp->car->interger())
			{
				throw 0;
			}
			cnt++;
		}
		if (cnt==1) throw 0;
		if (cnt==0) return new Rational("0","1");
		Number *res=new Rational("1","1"),*last;
		Number *opr=con->car,*conv;
		last=res;
		if(res->type_>opr->type_)
			res=res->mul(conv=res->convert(opr));
		else
			res=(conv=opr->convert(res))->mul(opr);
		con=con->cdr;
		delete last;
		delete conv;
		for(;con;con=con->cdr)
		{
			opr=con->car;
			last=res;
			if(res->type_>opr->type_)
				res=res->gcd(conv=res->convert(opr));
			else
				res=(conv=opr->convert(res))->gcd(opr);

		}
		return res;
    }
};

class Lcm:public Opt{
    Number *calc(Cons *con)
    {
        Cons *tmp=con;
		int cnt=0;
		for(;tmp;tmp=tmp->cdr)
		{
			if (tmp->car->type_ == 2 || !tmp->car->interger())
			{
				throw 0;
			}
			cnt++;
		}
		if (cnt==1) throw 0;
		if (cnt==0) return new Rational("1","1");
		Number *res=new Rational("1","1"),*last;
		Number *opr=con->car,*conv;
		last=res;
		if(res->type_>opr->type_)
			res=res->mul(conv=res->convert(opr));
		else
			res=(conv=opr->convert(res))->mul(opr);
		con=con->cdr;
		delete last;
		delete conv;
		for(;con;con=con->cdr)
		{
			opr=con->car;
			last=res;
			if(res->type_>opr->type_)
				res=res->lcm(conv=res->convert(opr));
			else
				res=(conv=opr->convert(res))->lcm(opr);

		}
		return res;
    }
};

class Expt:public Opt{
    Number *calc(Cons *con)
    {
        Cons *tmp=con;
		int cnt=0;
		for(;tmp;tmp=tmp->cdr)
		{
			if (!tmp->car->shi())
			{
				throw 0;
			}
			cnt++;
		}
		if (cnt!=2) throw 0;
		Number *res=new Rational("1","1"),*last;
		Number *opr=con->car,*conv;
		last=res;
		if(res->type_>opr->type_)
			res=res->mul(conv=res->convert(opr));
		else
			res=(conv=opr->convert(res))->mul(opr);
		con=con->cdr;
		delete last;
		delete conv;
		for(;con;con=con->cdr)
		{
			opr=con->car;
			last=res;
			if(res->type_>opr->type_)
				res=res->EXPT(conv=res->convert(opr));
			else
				res=(conv=opr->convert(res))->EXPT(opr);
		}
		return res;
    }
};

class Sqrt:public Opt{
    Number *calc(Cons *con)
    {
        Cons *tmp=con;
		int cnt=0;
		for(;tmp;tmp=tmp->cdr)
		{
			if (!tmp->car->shi())
			{
				throw 0;
			}
			cnt++;
		}
		if (cnt!=1) throw 0;
		Number *res=con->car;
		res=res->SQRT();
		return res;
    }
};

class Numerator:public Opt{
    Number *calc(Cons *con)
    {
        Cons *tmp=con;
		int cnt=0;
		for(;tmp;tmp=tmp->cdr)
		{
			if (!tmp->car->shi())
			{
				throw 0;
			}
			cnt++;
		}
		if (cnt!=1) throw 0;
		Number *res=con->car;
		res=res->NUM();
		if (!res) throw 0;
		return res;
    }
};

class Denominator:public Opt{
    Number *calc(Cons *con)
    {
        Cons *tmp=con;
		int cnt=0;
		for(;tmp;tmp=tmp->cdr)
		{
			if (!tmp->car->shi())
			{
				throw 0;
			}
			cnt++;
		}
		if (cnt!=1) throw 0;
		Number *res=con->car;
		res=res->DEN();
		if (!res) throw 0;
		return res;
    }
};

class Floor:public Opt{
    Number *calc(Cons *con)
    {
        Cons *tmp=con;
		int cnt=0;
		for(;tmp;tmp=tmp->cdr)
		{
			if (!tmp->car->shi())
			{
				throw 0;
			}
			cnt++;
		}
		if (cnt!=1) throw 0;
		Number *res=con->car;
		res=res->floor();
		return res;
    }
};

class Ceiling:public Opt{
    Number *calc(Cons *con)
    {
        Cons *tmp=con;
		int cnt=0;
		for(;tmp;tmp=tmp->cdr)
		{
			if (!tmp->car->shi())
			{
				throw 0;
			}
			cnt++;
		}
		if (cnt!=1) throw 0;
		Number *res=con->car;
		res=res->ceiling();
		return res;
    }
};

class Truncate:public Opt{
    Number *calc(Cons *con)
    {
        Cons *tmp=con;
		int cnt=0;
		for(;tmp;tmp=tmp->cdr)
		{
			if (!tmp->car->shi())
			{
				throw 0;
			}
			cnt++;
		}
		if (cnt!=1) throw 0;
		Number *res=con->car;
		res=res->truncate();
		return res;
    }
};

class Round:public Opt{
    Number *calc(Cons *con)
    {
        Cons *tmp=con;
		int cnt=0;
		for(;tmp;tmp=tmp->cdr)
		{
			if (!tmp->car->shi())
			{
				throw 0;
			}
			cnt++;
		}
		if (cnt!=1) throw 0;
		Number *res=con->car;
		res=res->ROU();
		return res;
    }
};

class Exact:public Opt{
    Number *calc(Cons *con)
    {
        Cons *tmp=con;
		int cnt=0;
		for(;tmp;tmp=tmp->cdr)
		{
			if (tmp->car->type_>3 || tmp->car->type_<1)
			{
				throw 0;
			}
			cnt++;
		}
		if (cnt!=1) throw 0;
		Number *res=con->car;
		res=res->exact();
		return res;
    }
};

class Inexact:public Opt{
    Number *calc(Cons *con)
    {
        Cons *tmp=con;
		int cnt=0;
		for(;tmp;tmp=tmp->cdr)
		{
			if (tmp->car->type_>3 || tmp->car->type_<1)
			{
				throw 0;
			}
			cnt++;
		}
		if (cnt!=1) throw 0;
		Number *res=con->car;
		res=res->inexact();
		return res;
    }
};

class MAx:public Opt{
    Number *calc(Cons *con)
    {
        Cons *tmp=con;
		int cnt=0;
		for(;tmp;tmp=tmp->cdr)
		{
			if (!tmp->car->shi())
			{
				throw 0;
			}
		}
		Number *res=new Rational("1","1"),*last;
		Number *opr=con->car,*conv;
		last=res;
		if(res->type_>opr->type_)
			res=res->mul(conv=res->convert(opr));
		else
			res=(conv=opr->convert(res))->mul(opr);
		con=con->cdr;
		delete last;
		delete conv;
		for(;con;con=con->cdr)
		{
			opr=con->car;
			last=res;
			if(res->type_>opr->type_)
				res=res->MAX(conv=res->convert(opr));
			else
				res=(conv=opr->convert(res))->MAX(opr);
		}
		return res;
    }
};

class MIn:public Opt{
    Number *calc(Cons *con)
    {
        Cons *tmp=con;
		int cnt=0;
		for(;tmp;tmp=tmp->cdr)
		{
			if (!tmp->car->shi())
			{
				throw 0;
			}
		}
		Number *res=new Rational("1","1"),*last;
		Number *opr=con->car,*conv;
		last=res;
		if(res->type_>opr->type_)
			res=res->mul(conv=res->convert(opr));
		else
			res=(conv=opr->convert(res))->mul(opr);
		con=con->cdr;
		delete last;
		delete conv;
		for(;con;con=con->cdr)
		{
			opr=con->car;
			last=res;
			if(res->type_>opr->type_)
				res=res->MIN(conv=res->convert(opr));
			else
				res=(conv=opr->convert(res))->MIN(opr);
		}
		return res;
    }
};

class Imagepart:public Opt{
    Number *calc(Cons *con)
    {
        Cons *tmp=con;
		int cnt=0;
		for(;tmp;tmp=tmp->cdr)
		{
			if (tmp->car->type_>3 || tmp->car->type_<1)
			{
				throw 0;
			}
			cnt++;
		}
		if (cnt!=1) throw 0;
		Number *res=con->car;
		res=res->imagepart();
		return res;
    }
};

class Realpart:public Opt{
    Number *calc(Cons *con)
    {
        Cons *tmp=con;
		int cnt=0;
		for(;tmp;tmp=tmp->cdr)
		{
			if (tmp->car->type_>3 || tmp->car->type_<1)
			{
				throw 0;
			}
			cnt++;
		}
		if (cnt!=1) throw 0;
		Number *res=con->car;
		res=res->realpart();
		return res;
    }
};
