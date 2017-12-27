#include "opt.h"
#include "float.h"
#include "rational.h"
#include "complex.h"
#include "number.h"
#include "boolean.h"
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

		Number *res = new Rational("0", "1");
		Number *last;
		for (; con; con = con->cdr)
		{
			if (con->car->type_>3 || con->car->type_<1)
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
				res = (conv = opr->convert(res))->add(opr);
			}

			delete last;
			delete conv;

		}
		return res;
	}
};
class Sub :public Opt{
	Number *calc(Cons *con)
	{
		Cons *tmp = con;
		int cnt = 0;
		for (; tmp; tmp = tmp->cdr)
		{
			if (tmp->car->type_>3 || tmp->car->type_<1)
			{
				throw 0;
			}
			cnt++;
		}
		Number *res = new Rational("0", "1"), *last;
		Number *opr = con->car, *conv;
		last = res;
		if (cnt == 1)
		{
			if (res->type_ > opr->type_)
				res = res->sub(conv = res->convert(opr));
			else
				res = (conv = opr->convert(res))->sub(opr);
			delete last;
			delete conv;
			return res;
		}
		if (res->type_ > opr->type_)
			res = res->add(conv = res->convert(opr));
		else
			res = (conv = opr->convert(res))->add(opr);
		con = con->cdr;
		delete last;
		delete conv;
		for (; con; con = con->cdr)
		{
			opr = con->car;
			last = res;
			if (res->type_>opr->type_)
				res = res->sub(conv = res->convert(opr));
			else
				res = (conv = opr->convert(res))->sub(opr);
			delete last;
			delete conv;
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
			if (con->car->type_>3 || con->car->type_<1)
			{
				throw 0;
			}
			Number *opr = con->car, *conv;
			last = res;
			if (res->type_ > opr->type_)
				res = res->mul(conv = res->convert(opr));
			else
				res = (conv = opr->convert(res))->mul(opr);
			delete last;
			delete conv;
		}
		return res;
	}
};
class Div :public Opt{
	Number *calc(Cons *con)
	{
		Cons *tmp = con;
		int cnt = 0;
		for (; tmp; tmp = tmp->cdr)
		{
			if (tmp->car->type_>3 || tmp->car->type_<1)
			{
				throw 0;
			}
			cnt++;
		}
		Number *res = new Rational("1", "1"), *last;
		Number *opr = con->car, *conv;
		last = res;
		Number *zero = new Float(0.0);
		if (cnt == 1)
		{
			if (res->type_>opr->type_)
				res = res->div(conv = res->convert(opr));
			else
				res = (conv = opr->convert(res))->div(opr);
			delete last;
			delete conv;
			return res;
		}
		if (res->type_>opr->type_)
			res = res->mul(conv = res->convert(opr));
		else
			res = (conv = opr->convert(res))->mul(opr);
		con = con->cdr;
		delete last;
		delete conv;
		for (; con; con = con->cdr)
		{
			opr = con->car;
			last = res;
			if (res->type_>opr->type_)
				res = res->div(conv = res->convert(opr));
			else
				res = (conv = opr->convert(res))->div(opr);
			delete last;
			delete conv;
		}
		return res;
	}
};
class Abs :public Opt{
	/* Use the lowest level type */
	Number *calc(Cons *con) {

		Number *res = new Rational("0", "1");


		if (con->car->type_>3 || con->car->type_<1)
		{
			throw 0;
		}
		res = con->car->ABS();

		return res;
	}
};
class Max :public Opt{
	Number *calc(Cons *con) {

		Number *res = con->car;
		Number *last;
		for (; con; con = con->cdr)
		{
			if (con->car->type_>3 || con->car->type_<1)
			{
				throw 0;
			}
			Number *opr = con->car, *conv;
			last = res;
			if (res->type_ > opr->type_)
			{
				res = res->Max(conv = res->convert(opr));
			}
			else
			{
				res = (conv = opr->convert(res))->Max(opr);
			}

			delete last;
			delete conv;

		}
		return res;
	}
};
class Min :public Opt{
	Number *calc(Cons *con) {

		Number *res = con->car;
		Number *last;
		for (con = con->cdr; con; con = con->cdr)
		{
			if (con->car->type_>3 || con->car->type_<1)
			{
				throw 0;
			}
			Number *opr = con->car, *conv;
			last = res;
			if (res->type_ > opr->type_)
			{
				res = res->Min(conv = res->convert(opr));
			}
			else
			{
				res = (conv = opr->convert(res))->Min(opr);
			}

			delete last;
			delete conv;

		}
		return res;
	}
};
class Sqrt :public Opt{
	/* Use the lowest level type */
	Number *calc(Cons *con) {

		Number *res = new Rational("1", "1");


		if (con->car->type_>3 || con->car->type_<1)
		{
			throw 0;
		}
		res = con->car->SQRT();

		return res;
	}
};
class Expt :public Opt{
	Number *calc(Cons *con) {

		Number *res = con->car;
		Number *last;
		for (con = con->cdr; con; con = con->cdr)
		{
			if (con->car->type_>3 || con->car->type_ < 1)
			{
				throw 0;
			}
			Number *opr = con->car, *conv;
			last = res;
			if (res->type_ > opr->type_)
			{
				res = res->EXPT(conv = res->convert(opr));
			}
			else
			{
				res = (conv = opr->convert(res))->EXPT(opr);
			}

			delete last;
			delete conv;

		}
		return res;
	}
};
class Lcm :public Opt{
	Number *calc(Cons *con) {

		Number *res = con->car;
		Number *last;
		for (con = con->cdr; con; con = con->cdr)
		{
			if (con->car->type_>3 || con->car->type_ < 1)
			{
				throw 0;
			}
			Number *opr = con->car, *conv;
			last = res;
			if (res->type_ > opr->type_)
			{
				res = res->LCM(conv = res->convert(opr));
			}
			else
			{
				res = (conv = opr->convert(res))->LCM(opr);
			}

			delete last;
			delete conv;

		}
		return res;
	}
};
class Gcd :public Opt{
	Number *calc(Cons *con) {

		Number *res = con->car;
		Number *last;
		for (con = con->cdr; con; con = con->cdr)
		{
			if (con->car->type_>3 || con->car->type_ < 1)
			{
				throw 0;
			}
			Number *opr = con->car, *conv;
			last = res;
			if (res->type_ > opr->type_)
			{
				res = res->GCD(conv = res->convert(opr));
			}
			else
			{
				res = (conv = opr->convert(res))->GCD(opr);
			}

			delete last;
			delete conv;

		}
		return res;
	}
};
class Quotient :public Opt{
	Number *calc(Cons *con) {

		Number *res = con->car;
		Number *last;
		for (con = con->cdr; con; con = con->cdr)
		{
			if (con->car->type_>3 || con->car->type_ < 1)
			{
				throw 0;
			}
			Number *opr = con->car, *conv;
			last = res;
			if (res->type_ > opr->type_)
			{
				res = res->QUOTIENT(conv = res->convert(opr));
			}
			else
			{
				res = (conv = opr->convert(res))->QUOTIENT(opr);
			}

			delete last;
			delete conv;

		}
		return res;
	}
};
class Remainder :public Opt{
	Number *calc(Cons *con) {

		Number *res = con->car;
		Number *last;
		for (con = con->cdr; con; con = con->cdr)
		{
			if (con->car->type_>3 || con->car->type_ < 1)
			{
				throw 0;
			}
			Number *opr = con->car, *conv;
			last = res;
			if (res->type_ > opr->type_)
			{
				res = res->REMAINDER(conv = res->convert(opr));
			}
			else
			{
				res = (conv = opr->convert(res))->REMAINDER(opr);
			}

			delete last;
			delete conv;

		}
		return res;
	}
};
class Modulo :public Opt{
	Number *calc(Cons *con) {

		Number *res = con->car;
		Number *last;
		for (con = con->cdr; con; con = con->cdr)
		{
			if (con->car->type_>3 || con->car->type_ < 1)
			{
				throw 0;
			}
			Number *opr = con->car, *conv;
			last = res;
			if (res->type_ > opr->type_)
			{
				res = res->MODULO(conv = res->convert(opr));
			}
			else
			{
				res = (conv = opr->convert(res))->MODULO(opr);
			}

			delete last;
			delete conv;

		}
		return res;
	}
};
class Floor :public Opt{
	/* Use the lowest level type */
	Number *calc(Cons *con) {

		Number *res = new Rational("0", "1");

		if (con->car->type_>3 || con->car->type_<1)
		{
			throw 0;
		}
		res = con->car->floor();

		return res;
	}
};
class Ceiling :public Opt{
	/* Use the lowest level type */
	Number *calc(Cons *con) {

		Number *res = new Rational("0", "1");

		if (con->car->type_>3 || con->car->type_<1)
		{
			throw 0;
		}
		res = con->car->ceiling();

		return res;
	}
};
class Round :public Opt{
	/* Use the lowest level type */
	Number *calc(Cons *con) {

		Number *res = new Rational("0", "1");

		if (con->car->type_>3 || con->car->type_<1)
		{
			throw 0;
		}
		res = con->car->ROUND();

		return res;
	}
};
class Truncate :public Opt{
	/* Use the lowest level type */
	Number *calc(Cons *con) {

		Number *res = new Rational("0", "1");

		if (con->car->type_>3 || con->car->type_<1)
		{
			throw 0;
		}
		res = con->car->truncate();

		return res;
	}
};
class Imagepart :public Opt{
	Number *calc(Cons *con)
	{
		Cons *tmp = con;
		int cnt = 0;
		for (; tmp; tmp = tmp->cdr)
		{
			if (tmp->car->type_>3 || tmp->car->type_<1)
			{
				throw 0;
			}
			cnt++;
		}
		if (cnt != 1) throw 0;
		Number *res = con->car;
		res = res->imagepart();
		return res;
	}
};
class Realpart :public Opt{
	Number *calc(Cons *con)
	{
		Cons *tmp = con;
		int cnt = 0;
		for (; tmp; tmp = tmp->cdr)
		{
			if (tmp->car->type_>3 || tmp->car->type_<1)
			{
				throw 0;
			}
			cnt++;
		}
		if (cnt != 1) throw 0;
		Number *res = con->car;
		res = res->realpart();
		return res;
	}
};
class Numerator :public Opt{
	Number *calc(Cons *con)
	{
		Cons *tmp = con;
		int cnt = 0;
		for (; tmp; tmp = tmp->cdr)
		{
			if (tmp->car->type_>3 || tmp->car->type_<1)
			{
				throw 0;
			}
			cnt++;
		}
		if (cnt != 1) throw 0;
		Number *res = con->car;
		res = res->NUMERATOR();
		if (!res) throw 0;
		return res;
	}
};
class Denominator :public Opt{
	Number *calc(Cons *con)
	{
		Cons *tmp = con;
		int cnt = 0;
		for (; tmp; tmp = tmp->cdr)
		{
			if (tmp->car->type_>3 || tmp->car->type_<1)
			{
				throw 0;
			}
			cnt++;
		}
		if (cnt != 1) throw 0;
		Number *res = con->car;
		res = res->DENOMINATOR();
		if (!res) throw 0;
		return res;
	}
};
class Exact :public Opt{
	Number *calc(Cons *con)
	{
		Cons *tmp = con;
		int cnt = 0;
		for (; tmp; tmp = tmp->cdr)
		{
			if (tmp->car->type_>3 || tmp->car->type_<1)
			{
				throw 0;
			}
			cnt++;
		}
		if (cnt != 1) throw 0;
		Number *res = con->car;
		res = res->exact();
		return res;
	}
};
class Inexact :public Opt{
	Number *calc(Cons *con)
	{
		Cons *tmp = con;
		int cnt = 0;
		for (; tmp; tmp = tmp->cdr)
		{
			if (tmp->car->type_>3 || tmp->car->type_<1)
			{
				throw 0;
			}
			cnt++;
		}
		if (cnt != 1) throw 0;
		Number *res = con->car;
		res = res->inexact();
		return res;
	}
};
class Less : public Opt {
	Number *calc(Cons *con) {
		Number *res = new Boolean(1);
		Number *former = con->car;
		for (con = con->cdr; con; con = con->cdr)
		{
			if (con->car->type_>3 || con->car->type_<1)
			{
				throw 0;
			}
			Number *opr = con->car;
			if (former->type_ > opr->type_)
			{
				res = former->reless(former->convert(opr));
				former = con->car;
				if ((SCAST_BOOLEAN(res)->judge) == 0) return res;
			}
			else
			{
				res = (opr->convert(former))->reless(opr);
				former = con->car;
				if (SCAST_BOOLEAN(res)->judge == 0) return res;
			}
		}
		return res;
	}
};
class Less_equ : public Opt {
	Number *calc(Cons *con) {
		Number *res = new Boolean(1);
		Number *former = con->car;
		for (con = con->cdr; con; con = con->cdr)
		{
			if (con->car->type_>3 || con->car->type_<1)
			{
				throw 0;
			}
			Number *opr = con->car;
			if (former->type_ > opr->type_)
			{
				res = former->relesseql(former->convert(opr));
				former = con->car;
				if ((SCAST_BOOLEAN(res)->judge) == 0) return res;
			}
			else
			{
				res = (opr->convert(former))->relesseql(opr);
				former = con->car;
				if (SCAST_BOOLEAN(res)->judge == 0) return res;
			}
		}
		return res;
	}
};
class Greater : public Opt {
	Number *calc(Cons *con) {
		Number *res = new Boolean(1);
		Number *former = con->car;
		for (con = con->cdr; con; con = con->cdr)
		{
			if (con->car->type_>3 || con->car->type_<1)
			{
				throw 0;
			}
			Number *opr = con->car;
			if (former->type_ > opr->type_)
			{
				res = former->regter(former->convert(opr));
				former = con->car;
				if ((SCAST_BOOLEAN(res)->judge) == 0) return res;
			}
			else
			{
				res = (opr->convert(former))->regter(opr);
				former = con->car;
				if (SCAST_BOOLEAN(res)->judge == 0) return res;
			}
		}
		return res;
	}
};
class Greater_equ : public Opt {
	Number *calc(Cons *con) {
		Number *res = new Boolean(1);
		Number *former = con->car;
		for (con = con->cdr; con; con = con->cdr)
		{
			if (con->car->type_>3 || con->car->type_<1)
			{
				throw 0;
			}
			Number *opr = con->car;
			if (former->type_ > opr->type_)
			{
				res = former->regtereql(former->convert(opr));
				former = con->car;
				if ((SCAST_BOOLEAN(res)->judge) == 0) return res;
			}
			else
			{
				res = (opr->convert(former))->regtereql(opr);
				former = con->car;
				if (SCAST_BOOLEAN(res)->judge == 0) return res;
			}
		}
		return res;
	}
};
class Jud_exact :public Opt{
	/* Use the lowest level type */
	Number *calc(Cons *con) {

		Number *res = new Rational("1", "1");


		if (con->car->type_>3 || con->car->type_<1)
		{
			throw 0;
		}
		res = con->car->IS_EXACT();

		return res;
	}
};
class Jud_inexact :public Opt{
	/* Use the lowest level type */
	Number *calc(Cons *con) {

		Number *res = new Rational("1", "1");


		if (con->car->type_>3 || con->car->type_<1)
		{
			throw 0;
		}
		res = con->car->IS_INEXACT();

		return res;
	}
};
class Jud_zero :public Opt{
	/* Use the lowest level type */
	Number *calc(Cons *con) {

		Number *res = new Rational("1", "1");


		if (con->car->type_>3 || con->car->type_<1)
		{
			throw 0;
		}
		res = con->car->IS_ZERO();

		return res;
	}
};
class Jud_negative :public Opt{
	/* Use the lowest level type */
	Number *calc(Cons *con) {

		Number *res = new Rational("1", "1");


		if (con->car->type_>3 || con->car->type_<1)
		{
			throw 0;
		}
		res = con->car->IS_NEGATIVE();

		return res;
	}
};
class Jud_positive :public Opt{
	/* Use the lowest level type */
	Number *calc(Cons *con) {

		Number *res = new Rational("1", "1");


		if (con->car->type_>3 || con->car->type_<1)
		{
			throw 0;
		}
		res = con->car->IS_POSITIVE();

		return res;
	}
};
class Jud_odd :public Opt{
	/* Use the lowest level type */
	Number *calc(Cons *con) {

		Number *res = new Rational("1", "1");


		if (con->car->type_>3 || con->car->type_<1)
		{
			throw 0;
		}
		res = con->car->IS_ODD();

		return res;
	}
};
class Jud_even :public Opt{
	/* Use the lowest level type */
	Number *calc(Cons *con) {

		Number *res = new Rational("1", "1");


		if (con->car->type_>3 || con->car->type_<1)
		{
			throw 0;
		}
		res = con->car->IS_EVEN();

		return res;
	}
};
class Sin :public Opt{
	/* Use the lowest level type */
	Number *calc(Cons *con) {

		Number *res = new Rational("1", "1");


		if (con->car->type_>3 || con->car->type_<1)
		{
			throw 0;
		}
		res = con->car->SIN();

		return res;
	}
};
class Cos :public Opt{
	/* Use the lowest level type */
	Number *calc(Cons *con) {

		Number *res = new Rational("1", "1");


		if (con->car->type_>3 || con->car->type_<1)
		{
			throw 0;
		}
		res = con->car->COS();

		return res;
	}
};
class Tan :public Opt{
	/* Use the lowest level type */
	Number *calc(Cons *con) {

		Number *res = new Rational("1", "1");


		if (con->car->type_>3 || con->car->type_<1)
		{
			throw 0;
		}
		res = con->car->TAN();

		return res;
	}
};
class Asin :public Opt{
	/* Use the lowest level type */
	Number *calc(Cons *con) {

		Number *res = new Rational("1", "1");


		if (con->car->type_>3 || con->car->type_<1)
		{
			throw 0;
		}
		res = con->car->ARCSIN();

		return res;
	}
};
class Acos :public Opt{
	/* Use the lowest level type */
	Number *calc(Cons *con) {

		Number *res = new Rational("1", "1");


		if (con->car->type_>3 || con->car->type_<1)
		{
			throw 0;
		}
		res = con->car->ARCCOS();

		return res;
	}
};
class Atan :public Opt{
	/* Use the lowest level type */
	Number *calc(Cons *con) {

		Number *res = new Rational("1", "1");


		if (con->car->type_>3 || con->car->type_<1)
		{
			throw 0;
		}
		res = con->car->ARCTAN();

		return res;
	}
};
class Exp :public Opt{
	/* Use the lowest level type */
	Number *calc(Cons *con) {

		Number *res = new Rational("1", "1");


		if (con->car->type_>3 || con->car->type_<1)
		{
			throw 0;
		}
		res = con->car->EXP();

		return res;
	}
};
class Log :public Opt{
	/* Use the lowest level type */
	Number *calc(Cons *con) {

		Number *res = new Rational("1", "1");


		if (con->car->type_>3 || con->car->type_<1)
		{
			throw 0;
		}
		res = con->car->LOG();

		return res;
	}
};
class Magnitude :public Opt{
	/* Use the lowest level type */
	Number *calc(Cons *con) {

		Number *res = new Rational("1", "1");


		if (con->car->type_>3 || con->car->type_<1)
		{
			throw 0;
		}
		res = con->car->MAGNITUDE();

		return res;
	}
};
class Angle :public Opt{
	/* Use the lowest level type */
	Number *calc(Cons *con) {

		Number *res = new Rational("1", "1");


		if (con->car->type_>3 || con->car->type_<1)
		{
			throw 0;
		}
		res = con->car->ANGLE();

		return res;
	}
};
class Make_rectangular : public Opt{
	/* Use the lowest level type */
	Number *calc(Cons *con) {
		Number *res = con->car;
		Number *opr = con->cdr->car;
		if (con->car->type_>3 || con->car->type_ < 1)
		{
			throw 0;
		}
		if (res->type_ > opr->type_)
		{
			res = res->MAKE_RECTANGULAR(res->convert(opr));
		}
		else
		{
			res = (opr->convert(res))->MAKE_RECTANGULAR(opr);
		}
		return res;
	}
};
class Make_polar : public Opt{
	/* Use the lowest level type */
	Number *calc(Cons *con) {
		Number *res = con->car;
		Number *opr = con->cdr->car;
		if (con->car->type_ > 3 || con->car->type_ < 1)
		{
			throw 0;
		}
		if (res->type_ > opr->type_)
		{
			res = res->MAKE_POLAR(res->convert(opr));
		}
		else
		{
			res = (opr->convert(res))->MAKE_POLAR(opr);
		}
		return res;
	}
};
class Jud_integer :public Opt{
	/* Use the lowest level type */
	Number *calc(Cons *con) {

		Number *res = new Rational("1", "1");


		if (con->car->type_>4 || con->car->type_<1)
		{
			throw 0;
		}
		res = con->car->IS_INTEGER();

		return res;
	}
};
class Jud_rational :public Opt{
	/* Use the lowest level type */
	Number *calc(Cons *con) {

		Number *res = new Rational("1", "1");


		if (con->car->type_>4 || con->car->type_<1)
		{
			throw 0;
		}
		res = con->car->IS_RATIONAL();

		return res;
	}
};
class Jud_real :public Opt{
	/* Use the lowest level type */
	Number *calc(Cons *con) {

		Number *res = new Rational("1", "1");


		if (con->car->type_>4 || con->car->type_<1)
		{
			throw 0;
		}
		res = con->car->IS_REAL();

		return res;
	}
};
class Jud_complex :public Opt{
	/* Use the lowest level type */
	Number *calc(Cons *con) {

		Number *res = new Rational("1", "1");


		if (con->car->type_>4 || con->car->type_<1)
		{
			throw 0;
		}
		res = con->car->IS_COMPLEX();

		return res;
	}
};
class Jud_number :public Opt{
	/* Use the lowest level type */
	Number *calc(Cons *con) {

		Number *res = new Rational("1", "1");


		if (con->car->type_>4 || con->car->type_<1)
		{
			throw 0;
		}
		res = con->car->IS_NUMBER();

		return res;
	}
};


class Eql :public Opt{
	Number *calc(Cons *con) {

		Number *res = con->car;
		Number *last;
		for (con = con->cdr; con; con = con->cdr)
		{
			if (con->car->type_>6 || con->car->type_ < 1)
			{
				throw 0;
			}
			Number *opr = con->car, *conv;
			last = res;
			if (res->type_ <=3 && opr->type_ <=3)
			{	if (res->type_ > opr->type_)
				{
					res = res->EQL(conv = res->convert(opr));
				}
				else
				{
					res = (conv = opr->convert(res))->EQL(opr);
				}
			}
			else 
			{	if (res->type_ != opr->type_) res = new Boolean(false);
				else res = res->EQL(opr);
			}

		}
		return res;
	}
};

class Str_eql :public Opt{
	Number *calc(Cons *con) {
		Number *res = new Boolean();
		Number *last = con->car;
		for (con = con->cdr; con; con = con->cdr)
		{	
			if (con->car->type_>6 || con->car->type_ < 1)
			{
				throw 0;
			}
			Number *opr = con->car, *conv;
			if (last->type_ > opr->type_)
			{
				res = last->STR_EQL(conv = last->convert(opr));
				last = con->car;
				if ((SCAST_BOOLEAN(res)->judge) == false) return res;
			}
			else
			{
				res = (conv = opr->convert(last))->STR_EQL(opr);
				last = con->car;
				if ((SCAST_BOOLEAN(res)->judge) == false) return res;
			}
		}
		return res;
	}
};
class Str_cieql :public Opt{
	Number *calc(Cons *con) {
		Number *res = new Boolean();
		Number *last = con->car;
		for (con = con->cdr; con; con = con->cdr)
		{	
			if (con->car->type_>6 || con->car->type_ < 1)
			{
				throw 0;
			}
			Number *opr = con->car, *conv;
			if (last->type_ > opr->type_)
			{
				res = last->STR_CIEQL(conv = last->convert(opr));
				last = con->car;
				if ((SCAST_BOOLEAN(res)->judge) == false) return res;
			}
			else
			{
				res = (conv = opr->convert(last))->STR_CIEQL(opr);
				last = con->car;
				if ((SCAST_BOOLEAN(res)->judge) == false) return res;
			}
		}
		return res;
	}
};

class Str_less :public Opt{
	Number *calc(Cons *con) {
		Number *res = new Boolean();
		Number *last = con->car;
		for (con = con->cdr; con; con = con->cdr)
		{	
			if (con->car->type_>6 || con->car->type_ < 1)
			{
				throw 0;
			}
			Number *opr = con->car, *conv;
			if (last->type_ > opr->type_)
			{
				res = last->STR_LESS(conv = last->convert(opr));
				last = con->car;
				if ((SCAST_BOOLEAN(res)->judge) == false) return res;
			}
			else
			{
				res = (conv = opr->convert(last))->STR_LESS(opr);
				last = con->car;
				if ((SCAST_BOOLEAN(res)->judge) == false) return res;
			}
		}
		return res;
	}
};

class Str_ciless :public Opt{
	Number *calc(Cons *con) {
		Number *res = new Boolean();
		Number *last = con->car;
		for (con = con->cdr; con; con = con->cdr)
		{	
			if (con->car->type_>6 || con->car->type_ < 1)
			{
				throw 0;
			}
			Number *opr = con->car, *conv;
			if (last->type_ > opr->type_)
			{
				res = last->STR_CILESS(conv = last->convert(opr));
				last = con->car;
				if ((SCAST_BOOLEAN(res)->judge) == false) return res;
			}
			else
			{
				res = (conv = opr->convert(last))->STR_CILESS(opr);
				last = con->car;
				if ((SCAST_BOOLEAN(res)->judge) == false) return res;
			}
		}
		return res;
	}
};

class Str_lesseql :public Opt{
	Number *calc(Cons *con) {
		Number *res = new Boolean();
		Number *last = con->car;
		for (con = con->cdr; con; con = con->cdr)
		{	
			if (con->car->type_>6 || con->car->type_ < 1)
			{
				throw 0;
			}
			Number *opr = con->car, *conv;
			if (last->type_ > opr->type_)
			{
				res = last->STR_LESSEQL(conv = last->convert(opr));
				last = con->car;
				if ((SCAST_BOOLEAN(res)->judge) == false) return res;
			}
			else
			{
				res = (conv = opr->convert(last))->STR_LESSEQL(opr);
				last = con->car;
				if ((SCAST_BOOLEAN(res)->judge) == false) return res;
			}
		}
		return res;
	}
};

class Str_cilesseql :public Opt{
	Number *calc(Cons *con) {
		Number *res = new Boolean();
		Number *last = con->car;
		for (con = con->cdr; con; con = con->cdr)
		{	
			if (con->car->type_>6 || con->car->type_ < 1)
			{
				throw 0;
			}
			Number *opr = con->car, *conv;
			if (last->type_ > opr->type_)
			{
				res = last->STR_CILESSEQL(conv = last->convert(opr));
				last = con->car;
				if ((SCAST_BOOLEAN(res)->judge) == false) return res;
			}
			else
			{
				res = (conv = opr->convert(last))->STR_CILESSEQL(opr);
				last = con->car;
				if ((SCAST_BOOLEAN(res)->judge) == false) return res;
			}
		}
		return res;
	}
};

class Cha_eql :public Opt{
	Number *calc(Cons *con) {
		Number *res = new Boolean();
		Number *last = con->car;
		for (con = con->cdr; con; con = con->cdr)
		{	
			if (con->car->type_>6 || con->car->type_ < 1)
			{
				throw 0;
			}
			Number *opr = con->car, *conv;
			if (last->type_ > opr->type_)
			{
				res = last->CHA_EQL(conv = last->convert(opr));
				last = con->car;
				if ((SCAST_BOOLEAN(res)->judge) == false) return res;
			}
			else
			{
				res = (conv = opr->convert(last))->CHA_EQL(opr);
				last = con->car;
				if ((SCAST_BOOLEAN(res)->judge) == false) return res;
			}
		}
		return res;
	}
};
class Cha_cieql :public Opt{
	Number *calc(Cons *con) {
		Number *res = new Boolean();
		Number *last = con->car;
		for (con = con->cdr; con; con = con->cdr)
		{	
			if (con->car->type_>6 || con->car->type_ < 1)
			{
				throw 0;
			}
			Number *opr = con->car, *conv;
			if (last->type_ > opr->type_)
			{
				res = last->CHA_CIEQL(conv = last->convert(opr));
				last = con->car;
				if ((SCAST_BOOLEAN(res)->judge) == false) return res;
			}
			else
			{
				res = (conv = opr->convert(last))->CHA_CIEQL(opr);
				last = con->car;
				if ((SCAST_BOOLEAN(res)->judge) == false) return res;
			}
		}
		return res;
	}
};

class Cha_less :public Opt{
	Number *calc(Cons *con) {
		Number *res = new Boolean();
		Number *last = con->car;
		for (con = con->cdr; con; con = con->cdr)
		{	
			if (con->car->type_>6 || con->car->type_ < 1)
			{
				throw 0;
			}
			Number *opr = con->car, *conv;
			if (last->type_ > opr->type_)
			{
				res = last->CHA_LESS(conv = last->convert(opr));
				last = con->car;
				if ((SCAST_BOOLEAN(res)->judge) == false) return res;
			}
			else
			{
				res = (conv = opr->convert(last))->CHA_LESS(opr);
				last = con->car;
				if ((SCAST_BOOLEAN(res)->judge) == false) return res;
			}
		}
		return res;
	}
};
class Cha_ciless :public Opt{
	Number *calc(Cons *con) {
		Number *res = new Boolean();
		Number *last = con->car;
		for (con = con->cdr; con; con = con->cdr)
		{	
			if (con->car->type_>6 || con->car->type_ < 1)
			{
				throw 0;
			}
			Number *opr = con->car, *conv;
			if (last->type_ > opr->type_)
			{
				res = last->CHA_CILESS(conv = last->convert(opr));
				last = con->car;
				if ((SCAST_BOOLEAN(res)->judge) == false) return res;
			}
			else
			{
				res = (conv = opr->convert(last))->CHA_CILESS(opr);
				last = con->car;
				if ((SCAST_BOOLEAN(res)->judge) == false) return res;
			}
		}
		return res;
	}
};
class Cha_lesseql :public Opt{
	Number *calc(Cons *con) {
		Number *res = new Boolean();
		Number *last = con->car;
		for (con = con->cdr; con; con = con->cdr)
		{	
			if (con->car->type_>6 || con->car->type_ < 1)
			{
				throw 0;
			}
			Number *opr = con->car, *conv;
			if (last->type_ > opr->type_)
			{
				res = last->CHA_LESSEQL(conv = last->convert(opr));
				last = con->car;
				if ((SCAST_BOOLEAN(res)->judge) == false) return res;
			}
			else
			{
				res = (conv = opr->convert(last))->CHA_LESSEQL(opr);
				last = con->car;
				if ((SCAST_BOOLEAN(res)->judge) == false) return res;
			}
		}
		return res;
	}
};
class Cha_cilesseql :public Opt{
	Number *calc(Cons *con) {
		Number *res = new Boolean();
		Number *last = con->car;
		for (con = con->cdr; con; con = con->cdr)
		{	
			if (con->car->type_>6 || con->car->type_ < 1)
			{
				throw 0;
			}
			Number *opr = con->car, *conv;
			if (last->type_ > opr->type_)
			{
				res = last->CHA_CILESSEQL(conv = last->convert(opr));
				last = con->car;
				if ((SCAST_BOOLEAN(res)->judge) == false) return res;
			}
			else
			{
				res = (conv = opr->convert(last))->CHA_CILESSEQL(opr);
				last = con->car;
				if ((SCAST_BOOLEAN(res)->judge) == false) return res;
			}
		}
		return res;
	}
};
class Isstr :public Opt{
	Number *calc(Cons *con) {

		Number *res = new Rational("0", "1");

		if (con->car->type_>6 || con->car->type_<1)
		{
			throw 0;
		}
		res = con->car->IS_STR();

		return res;
	}
};
class Mak_str :public Opt{
	Number *calc(Cons *con) {
		Number *res = con->car;
		if (con->cdr)
		{	con = con->cdr;
			if (con->car->type_ != 5)
			{
				throw 0;
			}
			Number *opr = con->car, *conv;
			res = res->MAK_STR(opr);

		}
		else
		{	if (con->car->type_ != 1)
			{
				throw 0;
			}
			res = res->MAK_STR();
		}
		return res;
	}
};
class Get_str :public Opt{
	
	Number *calc(Cons *con) {

		Number *res;

		if (con->car->type_ != 5)
		{
			throw 0;
		}
		res = con->car->GET_STR();
		Number *last;
		for (con = con->cdr; con; con = con->cdr)
		{	if (con->car->type_ != 5)
			{
				throw 0.5;
			}
			Number *opr = con->car, *conv;
			res = res->GET_STR(opr); 
		}
		return res;
	}
};
class Str_len :public Opt{
	Number *calc(Cons *con) {

		Number *res = new Rational("0", "1");

		if (con->car->type_>6 || con->car->type_<1)
		{
			throw 0;
		}
		res = con->car->STR_LEN();	

		return res;
	}
};
class Str_ref :public Opt{
	Number *calc(Cons *con) {

		Number *res = con->car;
		con = con->cdr;
		Number *opr = con->car;
		if (res->type_ != 6 || opr->type_ >3)
		{	throw 0;
		}
		res = res->STR_REF(opr);

		return res;
	}
};
class Str_app :public Opt{
	Number *calc(Cons *con) {

		Number *res = con->car;
		for (con = con->cdr; con; con = con->cdr)
		{
			if (con->car->type_<5 || con->car->type_ >6)
			{
				throw 0;
			}
			Number *opr = con->car, *conv;
			if (res->type_ > opr->type_)
			{
				res = res->STR_APP(conv = res->convert(opr));
			}
			else
			{
				res = (conv = opr->convert(res))->STR_APP(opr);
			}

		}
		return res;
	}
};
class Str_cpy :public Opt{
	Number *calc(Cons *con) {

		Number *res = new Rational("0", "1");

		if (con->car->type_>6 || con->car->type_<1)
		{
			throw 0;
		}
		res = con->car->STR_CPY();

		return res;
	}
};

class Str_sub : public Opt {
    Number *calc(Cons *con) {
        Number *res = con->car;
        if (!con->cdr) throw 0;
        con = con->cdr;
        Number *opr1 = con->car;
        if (!con->cdr) throw 0;
        con = con->cdr;
        Number *opr2 = con->car;
        if (res->type_ != 6 || opr1->type_ >3 || opr2->type_ >3) throw 0;
        res = res->SUB_STR(opr1,opr2);
        return res;
    }
};

class Ischa :public Opt{
	Number *calc(Cons *con) {

		Number *res = new Rational("0", "1");

		if (con->car->type_>6 || con->car->type_<1)
		{
			throw 0;
		}
		res = con->car->IS_CHA();

		return res;
	}
};
class Car_alph :public Opt{
	Number *calc(Cons *con) {

		Number *res = new Rational("0", "1");

		if (con->car->type_>6 || con->car->type_<1)
		{
			throw 0;
		}
		res = con->car->CHA_ALPH();

		return res;
	}
};
class Car_num :public Opt{
	Number *calc(Cons *con) {

		Number *res = new Rational("0", "1");

		if (con->car->type_>6 || con->car->type_<1)
		{
			throw 0;
		}
		res = con->car->CHA_NUM();

		return res;
	}
};
class Car_whi :public Opt{
	Number *calc(Cons *con) {

		Number *res = new Rational("0", "1");

		if (con->car->type_>6 || con->car->type_<1)
		{
			throw 0;
		}
		res = con->car->CHA_WHIT();

		return res;
	}
};
class Is_chaupp :public Opt{
	Number *calc(Cons *con) {

		Number *res = new Rational("0", "1");

		if (con->car->type_>6 || con->car->type_<1)
		{
			throw 0;
		}
		res = con->car->IS_CHA_UPP();

		return res;
	}
};
class Is_chalow :public Opt{
	Number *calc(Cons *con) {

		Number *res = new Rational("0", "1");

		if (con->car->type_>6 || con->car->type_<1)
		{
			throw 0;
		}
		res = con->car->IS_CHA_LOW();

		return res;
	}
};
class Car_up :public Opt{
	Number *calc(Cons *con) {

		Number *res = new Rational("0", "1");

		if (con->car->type_>6 || con->car->type_<1)
		{
			throw 0;
		}
		res = con->car->CHA_UP();

		return res;
	}
};
class Car_down :public Opt{
	Number *calc(Cons *con) {

		Number *res = new Rational("0", "1");

		if (con->car->type_>6 || con->car->type_<1)
		{
			throw 0;
		}
		res = con->car->CHA_DOWN();

		return res;
	}
};
class Cha_int :public Opt{
	Number *calc(Cons *con) {

		Number *res = new Rational("0", "1");

		if (con->car->type_>6 || con->car->type_<1)
		{
			throw 0;
		}
		res = con->car->CHA_INT();

		return res;
	}
};
class Int_cha :public Opt{
	Number *calc(Cons *con) {

		Number *res = new Rational("0", "1");

		if (con->car->type_>6 || con->car->type_<1)
		{
			throw 0;
		}
		res = con->car->INT_CHA();

		return res;
	}
};
class Str_num :public Opt{
	Number *calc(Cons *con) {
		Number *res = con->car;

		if (con->car->type_ != 6)
		{
			throw 0;
		}
		res = res->STR_NUM();
		
		return res;
	}
};
class Num_str :public Opt{
	Number *calc(Cons *con) {
		Number *res = con->car;
		if (con->car->type_ > 3)
		{
			throw 0;
		}
		res = res->NUM_STR();
		
		return res;
	}
};
