#pragma once


#include <algorithm>
#include <cmath>
#include <iostream>
#include <functional>
#include <limits>
#include <sstream>
#include <stack>
#include <string>


using std::abs;
using std::exp;
using std::max;
using std::pow;
using std::sqrt;


// set the epsilon for each type
const long double ld_epsilon = std::numeric_limits<long double>::epsilon();
const double d_epsilon = std::numeric_limits<double>::epsilon();
const float f_epsilon = std::numeric_limits<float>::epsilon();


// set real valued function type name
typedef std::function<long double(long double)> realFx;


// calculate euler's constant
const long double E = std::exp(1);


// the identity function
constexpr long double ID(long double x) { return x; }


/****************\
	prototypes
\****************/

// purpose: determines if a string can be expressed as a number
// requires: a string
// returns: a boolean
bool isNumber(const std::string&);

// purpose: finds the derivative of a function at a given value
// requires: a function pointer and a value to find the instantaneous rate of
//	change
// returns: a floating point value
template<class number>
long double deriveAt(const realFx&, const number&);

// purpose: finds the definite integral of a function over a boundary
// requires: a function pointer, a left bound, and a right bound
// returns: a floating point value
template <class lB, class rB>
long double integrateOver(const realFx&, const lB&, const rB&);

// purpose: finds the composition of two real-valued functions
// requires: two real-valued functions, f and g, and a number
// returns: the composed function
realFx compose(realFx, realFx);

// purpose: creates a function that is just a constant
// requires: a number
// returns: a real-valued function
template <class number>
realFx constFx(number&);

// purpose: finds the derivative of a real-valued function
// requires: a real-valued function
// returns the derivative
realFx derivative(realFx);

// purpose: finds the antiderivative of a real-valued function
// requires: a real-valued function
// returns: the integral of the function that passes through the origin
realFx integral(realFx);

// purpose: reflects the function about the x-axis
// requires: a real-valued function
//	-f(x)
// returns: a new function
realFx reflectX(realFx);

// purpose: reflects the function about the y-axis
// requires: a real-valued function
//	f(-x)
// returns: a new function
realFx reflectY(realFx);

// purpose: scales a function in the x and y direction
// requires: a function and 2 scalars, cx and cy respectively
//	f(x / cx) * cy
// returns: a new function
realFx scale(realFx, long double, long double);

// purpose: scales a function in the x direction
// requires: a function and a scalar
//	f(x / c)
// returns: a new function
realFx scaleX(realFx, long double);

// purpose: scales a function in the y direction
// requires: a function and a scalar
//	f(x) * c
// returns a new function
realFx scaleY(realFx, long double);

// purpose: shifts a function in the x and y direction
// requires: a function and 2 scalars, dx and dy respectively
//	f(x - dx) + dy
// returns: a new function
realFx shift(realFx, long double, long double);

// purpose: shifts a function in the x direction
// requires: a function and a scalar
// returns: a new function
realFx shiftX(realFx, long double);

// purpose: shifts a function in the y direction
// requires: a function and a scalar
// returns: a new function
realFx shiftY(realFx, long double);

// purpose: adds a scalar value to a function
// requires: a scalar and a function
// returns: a new function
template <class number>
realFx operator+(number, realFx);

// purpose: adds a scalar value to a function
// requires: a scalar and a function
// returns: a new function
template <class number>
realFx operator+(realFx, number);

// purpose: adds two functions
// requires: two real valued functions
// returns: a new function
realFx operator+(realFx, realFx);

// purpose: subtracts a function from a scalar value
//	c - f(x)
// requires: a scalar and a function
// returns: a new function
template <class number>
realFx operator-(number, realFx);

// purpose: subtracts a scalar value from a function
//	f(x) - c
// requires: a scalar and a function
// returns: a new function
template <class number>
realFx operator-(realFx, number);

// purpose: subtracts a function from another
// requires: two real valued functions
// returns: a new function
realFx operator-(realFx, realFx);

// purpose: multiplies a function by a constant value
// requires: a scalar and a function
// returns: a new function
template <class number>
realFx operator*(number, realFx);

// purpose: multiplies a function by a constant value
// requires: a scalar and a function
// returns: a new function
template <class number>
realFx operator*(realFx, number);

// purpose: multiplies a function by another function
// requires: two real valued functions
// returns: a new function
realFx operator*(realFx, realFx);

// purpose: divides a number by a function
//	c / f(x)
// requires: a scalar and a function
// returns: a new function
template <class number>
realFx operator/(number, realFx);

// purpose: divides a function by a number
//	f(x) / c
// requires: a scalar and a function
// returns: a new function
template <class number>
realFx operator/(realFx, number);

// purpose: divides a function by another function
// requires: two real valued functions
// returns: a new function
realFx operator/(realFx, realFx);

// purpose: raises a number to the power of a function
//	c ^ f(x)
// requires: a scalar and a function
// returns: a new function
template <class number>
realFx operator^(number, realFx);

// purpose: raises a function to the power a number
//	f(x) ^ c
// requires: a scalar and a function
// returns: a new function
template <class number>
realFx operator^(realFx, number);

// purpose: raises a function to the power of another function
//	f(x) ^ g(x)
// requires: two real valued functions
// returns: a new function
realFx operator^(realFx, realFx);

// purpose: takes an expression and finds the sub-expression inside the
//	parentheses
// requires: a string that is an expression
// returns: the expression inside the parentheses
std::string get_first_sub_expression(std::string);

// purpose: prints the data to the console and breaks the line
// requires: anything that can be printed
// returns: nothing
template <class adt>
void print(adt data) { std::cout << data << '\n'; }

// purpose: print a line to the console
// requires: nothing
// returns: nothing
void print() { std::cout << '\n'; }


/*****************\
	definitions
\*****************/

// written by Gemini
bool isNumber(const std::string& str)
{
	std::istringstream iss(str);
	double d;
	iss >> std::noskipws >> d;
	return iss.eof() && !iss.fail();
}

template <class number>
long double deriveAt(const realFx& foo, const number& x)
{
	long double dFoo_dx;
	long double h;
	long double val;

	// find our limit
	h = sqrt(ld_epsilon);
	h *= std::max(1.0, std::abs(static_cast<double>(x)));

	// statically cast the value to a double
	val = static_cast<long double>(x);

	// find the derivative
	dFoo_dx = (foo(val + h) - foo(val - h)) / (2 * h);

	return dFoo_dx;
}

template <class lB, class rB>
long double integrateOver(const realFx& foo, const lB& left, const rB& right)
{
	if (left == right)
	{
		return 0.0;
	}
	// ensure that the left bound is to the left of the right bound
	else if (left > right)
	{
		return -1 * integrateOver(foo, right, left);
	}
	else
	{
		int multiple;
		int count;
		long double del_x;
		long double difference;
		long double integral;
		long double pos;

		integral = 0.0;
		pos = static_cast<long double>(left);

		difference = right - left;

		// proceed with simposon's rule
		del_x = sqrt(ld_epsilon);
		del_x *= std::max(static_cast<long double>(1.0), difference);

		// find the y value at the left
		integral += foo(pos);

		count = 0;

		while (pos + 2 * del_x < right)
		{
			// move along the curve
			pos += del_x;

			// simposon's rule shenanigans
			multiple = (count % 2 == 0) ? 4 : 2;
			count++;

			// add to the integral
			integral += foo(pos) * multiple;
		}

		// move along the curve
		pos += del_x;

		integral += foo(pos);

		// simpson's rule shenanigans
		integral /= 3.0;

		// multiply by dx
		integral *= del_x;

		return integral;
	}
	
}

realFx compose(const realFx& foo, const realFx& bar)
{
	// make the lambda function
	// using foo and bar,
	// we take in x, which is a long double
	// and we return a long double, foo(bar(x))
	return [foo, bar](long double x) -> long double
		{
			return foo(bar(x));
		};
}

template <class number>
realFx constFx(const number& num)
{
	return [num](long double x) -> long double
		{
			return num;
		};
}

realFx derivative(const realFx& foo)
{
	return [&foo](long double x) -> long double
		{
			return deriveAt(foo, x);
		};

}

realFx integral(const realFx& foo)
{
	return [&foo](long double x) -> long double
		{
			return integrateOver(foo, 0, x);
		};

}

realFx reflectX(realFx foo)
{
	return [foo](long double x) ->long double
		{
			return -1 * foo(x);
		};
}

realFx reflectY(realFx foo)
{
	return [foo](long double x) ->long double
		{
			return foo(-1 * x);
		};
}

realFx scale(realFx foo, long double cx, long double cy)
{
	return [foo, cx, cy](long double x) -> long double
		{
			return cy * foo(x / cx);
		};

}

realFx scaleX(realFx foo, long double c)
{
	return [foo, c](long double x) -> long double
		{
			return foo(x / c);
		};

}

realFx scaleY(realFx foo, long double c)
{
	return[foo, c](long double x) -> long double
		{
			return c * foo(x);
		};

}

realFx shift(realFx foo, long double dx, long double dy)
{
	return [foo, dx, dy](long double x) -> long double
		{
			return foo(x - dx) + dy;
		};

}

realFx shiftX(realFx foo, long double dx)
{
	return [foo, dx](long double x) -> long double
		{
			return foo(x - dx);
		};

}

realFx shiftY(realFx foo, long double dy)
{
	return [foo, dy](long double x) -> long double
		{
			return foo(x) + dy;
		};

}

template <class number>
realFx operator+(number c, realFx foo)
{
	return [c, foo](long double x) -> long double
		{
			return c + foo(x);
		};

}

template <class number>
realFx operator+(realFx foo, number c)
{
	return [c, foo](long double x) -> long double
		{
			return c + foo(x);
		};

}

realFx operator+(realFx foo, realFx bar)
{
	return [foo, bar](long double x) -> long double
		{
			return foo(x) + bar(x);
		};

}

template <class number>
realFx operator-(number c, realFx foo)
{
	return [c, foo](long double x) -> long double
		{
			return c - foo(x);
		};

}

template <class number>
realFx operator-(realFx foo, number c)
{
	return [c, foo](long double x) -> long double
		{
			return foo(x) - c;
		};

}

realFx operator-(realFx foo, realFx bar)
{
	return [foo, bar](long double x) -> long double
		{
			return foo(x) - bar(x);
		};

}

template <class number>
realFx operator*(realFx foo, number c)
{
	return [c, foo](long double x) -> long double
		{
			return c * foo(x);
		};

}

template <class number>
realFx operator*(number c, realFx foo)
{
	return [c, foo](long double x) -> long double
		{
			return c * foo(x);
		};

}

realFx operator*(realFx foo, realFx bar)
{
	return [foo, bar](long double x) -> long double
		{
			return foo(x) * bar(x);
		};

}

template <class number>
realFx operator/(realFx foo, number c)
{
	try
	{
		// don't allow a divide by zero
		if (c == 0)
			throw std::runtime_error("Divide by 0");

		return [c, foo](long double x) -> long double
			{
				return foo(x) / c;
			};

	}
	catch (const std::runtime_error e)
	{
		std::cout << "Error in real-valued division\n";
		std::cerr << e.what();
		// return the og fx
		return foo;
	}

}

template <class number>
realFx operator/(number c, realFx foo)
{
	return [c, foo](long double x) -> long double
		{
			return c / foo(x);
		};

}

realFx operator/(realFx foo, realFx bar)
{
	return [foo, bar](long double x) -> long double
		{
			return foo(x) / bar(x);
		};

}

template <class number>
realFx operator^(number c, realFx foo)
{
	return [c, foo](long double x) -> long double
		{
			return pow(c, foo(x));
		};
}

template <class number>
realFx operator^(realFx foo, number c)
{
	return [c, foo](long double x) -> long double
		{
			return pow(foo(x), c);
		};
}

realFx operator^(realFx foo, realFx bar)
{
	return [foo, bar](long double x) -> long double
		{
			return pow(foo(x), bar(x));
		};
}
