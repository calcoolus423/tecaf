#pragma once


#include <iostream>
#include "realfx.hpp"
#include <sstream>
#include <stack>
#include <string>


using std::abs;
using std::exp;
using std::max;
using std::pow;
using std::sqrt;


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
