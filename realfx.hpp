#pragma once


#include <algorithm>
#include <cmath>
#include <functional>
#include <limits>
#include <type_traits>


// set the positive and negative infinity constants
constexpr long double INF = std::numeric_limits<long double>::infinity();
constexpr long double N_INF = -std::numeric_limits<long double>::infinity();

// set the epsilon for each type
const long double EPSILON = std::sqrt(std::numeric_limits<long double>::epsilon());


// purpose: represents a real-valued function
// invariants: the function takes in a long double passed by reference
//	and returns a long double by value
// data members: foo is a functional object i.e. the representative function
class realFx
{
private:

	typedef std::function<long double(long double&)> real_fx_type;


		/* member variables */

	real_fx_type foo;


		/* member functions */

	// purpose: find the derivative of this function
	// requires: nothing
	// returns: a std::function i.e. the derivative
	real_fx_type _derivative();

	// purpose: finds the antiderivative of this function
	// requires: a left bound and a right bound
	// returns: a long double, that is the integral from
	//	the left bound to the right bound
	template <typename S,
		typename = std::enable_if_t<std::is_convertible_v<S, long double>>,
		typename T,
		typename = std::enable_if_t<std::is_convertible_v<T, long double>>>
	long double _def_integral(const S&, const T&);

public:

		/* constructors */

	// default constructor
	// assigns the identity function to foo
	realFx();

	// parametrized constructor
	// assigns this function using a std::function that takes in a reference
	//	to a long double and returns a long double
	realFx(const std::function<long double(long double&)>&);

	// parametrized constructor
	// assigns this function using a std::function that takes in a long double
	//	and returns a long double
	realFx(const std::function<long double(long double)>&);

	// parametrized constructor
	// assigns this function using a function pointer that takes in a reference
	//	to a long double and returns a long double
	realFx(long double(*)(long double&));

	// parametrized constructor
	// assigns this function using a function pointer that takes in a
	//	long double and returns a long double
	realFx(long double(*)(long double));
	
	// parametrized constructor
	// creates a constant valued function
	template <typename T,
		typename = std::enable_if_t<std::is_convertible_v<T, long double>>>
	realFx(const T&);

	// copy constructor
	// copies the function
	realFx(const realFx&);

	// destructor
	~realFx() {}


		/* member functions */
	
	// purpose: finds the derivative function
	// requires: nothing
	// returns: a realFx i.e. the derivative
	realFx derivative() { return realFx(_derivative()); }

	// purpose: calculates the derivative at a given value
	// requires: a number to take the derivative at, and an epsilon,
	//	by default the standard limit
	// returns: a long double i.e. the instantaneous rate of change
	template <typename T,
		typename = std::enable_if_t<std::is_convertible_v<T, long double>>>
	long double derive_at(const T&);

	template <typename T,
		typename = std::enable_if_t<std::is_convertible_v<T, long double>>>
	realFx integral(const T & = 0.0l);

	// purpose: find the left limit at a value
	// requires: a number
	// returns: the left limit of the function at that value
	template <typename T,
		typename = std::enable_if_t<std::is_convertible_v<T, long double>>>
	long double left_limit(const T&, const long double& = EPSILON);
	
	// purpose: finds the limit of a value
	// requires: a number
	// returns: the limit of the function at that value
	template <typename T,
		typename = std::enable_if_t<std::is_convertible_v<T, long double>>>
	long double limit_at(const T&, const long double& = EPSILON);

	// purpose: find the left limit at a value
	// requires: a number
	// returns: the left limit of the function at that value
	template <typename T,
		typename = std::enable_if_t<std::is_convertible_v<T, long double>>>
	long double right_limit(const T&, const long double& = EPSILON);

	// purpose: determines if the limit exists at a value
	// requires: a long double
	// returns: true if it exists, false if it doesn't
	template <typename T,
		typename = std::enable_if_t<std::is_convertible_v<T, long double>>>
	bool limit_exists_at(const T&, const long double& = EPSILON);


		/* operators */

	// purpose: adds a scalar value to a function
	// requires: a scalar
	// returns: a new function
	template <typename T,
		typename = std::enable_if_t<std::is_convertible_v<T, long double>>>
	realFx operator+(const T&);

	// purpose: adds a scalar value to a function
	// requires: a scalar
	// returns: a new function
	template <typename T, typename>
	friend realFx operator+(const T&, const realFx&);

	// purpose: adds two functions
	// requires: a real valued function
	// returns: a new function
	realFx operator+(const realFx&);

	// purpose: subtracts a scalar value from a function
	//	f(x) - c
	// requires: a scalar
	// returns: a new function
	template <typename T,
		typename = std::enable_if_t<std::is_convertible_v<T, long double>>>
	realFx operator-(const T&);

	// purpose: subtracts a function from a scalar value
	//	c - f(x)
	// requires: a scalar
	// returns: a new function
	template <typename T, typename>
	friend realFx operator-(const T&, const realFx&);

	// purpose: subtracts a function from another
	// requires: a real valued function
	// returns: a new function
	realFx operator-(const realFx&);

	// purpose: multiplies a function by a constant value
	// requires: a scalar
	// returns: a new function
	template <typename T,
		typename = std::enable_if_t<std::is_convertible_v<T, long double>>>
	realFx operator*(const T&);

	// purpose: multiplies a function by a constant value
	// requires: a scalar
	// returns: a new function
	template <typename T, typename>
	friend realFx operator*(const T&, const realFx&);

	// purpose: multiplies a function by another function
	// requires: a real valued function
	// returns: a new function
	realFx operator*(const realFx&);

	// purpose: divides a function by a number
	//	f(x) / c
	// requires: a scalar and a function
	// returns: a new function
	template <typename T,
		typename = std::enable_if_t<std::is_convertible_v<T, long double>>>
	realFx operator/(const T&);

	// purpose: divides a number by a function
	//	c / f(x)
	// requires: a scalar and a function
	// returns: a new function
	template <typename T, typename>
	friend realFx operator/(const T&, const realFx&);

	// purpose: divides a function by another function
	// requires: two real valued functions
	// returns: a new function
	realFx operator/(const realFx&);

	// purpose: raises a function to the power a number
	//	f(x) ^ c
	// requires: a scalar and a function
	// returns: a new function
	template <typename T,
		typename = std::enable_if_t<std::is_convertible_v<T, long double>>>
	realFx operator^(const T&);

	// purpose: raises a function to the power a number
	//	c ^ f(x)
	// requires: a scalar and a function
	// returns: a new function
	template <typename T, typename>
	friend realFx operator^(const T&, const realFx&);

	// purpose: raises a function to the power of another function
	//	f(x) ^ g(x)
	// requires: two real valued functions
	// returns: a new function
	realFx operator^(const realFx&);

	// purpose: evaluates the function at a value
	// requires: a type that can be cast to long double
	// returns: a long double, i.e. the result
	template <typename T,
		typename = std::enable_if_t<std::is_convertible_v<T, long double>>>
	long double operator()(const T&) const;

	// purpose: composes this function at another function
	// requires: a realFx
	// returns: a new function, i.e. the composition
	realFx operator()(const realFx&) const;

	// purpose: assigns a function to this one
	// requires: a real function
	// returns: a real function
	realFx& operator=(const realFx&);

};


	/* constructors */

// default constructor
realFx::realFx() : foo(std::identity{}) {}

// parametrized constructor
// referenced function
realFx::realFx(const realFx::real_fx_type& bar) : foo(bar) {}

// parametrized constructor
// unreferenced function
realFx::realFx(const std::function<long double(long double)>& bar) : foo(bar)
{ }

// parametrized constructor
// referenced function pointer
realFx::realFx(long double(*bar)(long double&)) : foo(bar) {}

// parametrized constructor
// unreferenced function pointer
realFx::realFx(long double(*bar)(long double)) : foo(bar) {}

// parametrized constructor
// makes a constant-valued function
template <typename T, typename>
realFx::realFx(const T& number)
{
	long double val;
	try
	{
		val = static_cast<long double>(number);

		foo = [val](long double&) -> long double
			{
				return val;
			};
	}
	catch (const std::exception& e)
	{
		std::cerr << e.what();
	}

}

// copy constuctor
realFx::realFx(const realFx& other) : foo(other.foo) {}


	/* methods */

/* private */

// calculate the derivative
realFx::real_fx_type realFx::_derivative()
{
	return [this](long double& x) -> long double
		{
			long double del_x;

			if (limit_exists_at(x))
			{
				del_x = x;
				del_x += EPSILON;
				return (this->foo(del_x) - this->foo(x)) / EPSILON;
			}
			else
				return std::nan("");
		};
}

// calculates the antiderivative
template <typename S, typename, typename T, typename>
long double realFx::_def_integral(const S& l, const T& r)
{
	int count, multiple;
	long double del_x, difference, integral, left, right, pos;

	left = static_cast<long double>(l);
	right = static_cast<long double>(r);

	// if the left and right bound are equal
	if (left == right) return 0.0;
	// ensure that the left bound is to the left of the right bound
	else if (left > right) return -1 * _def_integral(right, left);
	// if we have infinite bounds on the left
	else if (left == N_INF || right == INF)
	{
		// start on the right and move left
		std::cout << "infinite bounds not defined yet\n";
	}
	else
	{
		pos = static_cast<long double>(left);
		difference = right - left;
		integral = 0.0;

		// proceed with simposon's rule
		del_x = EPSILON;
		del_x *= std::max(static_cast<long double>(1.0), difference);

		// find the y value at the left
		integral += foo(pos);

		for(count = 0; pos + 2 * del_x < right; count++)
		{
			// move along the curve
			pos += del_x;

			// simpson's rule shenanigans
			multiple = (count % 2 == 0) ? 4 : 2;

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

/* public */

// find the derivative at a value
template <typename T, typename>
long double realFx::derive_at(const T& num)
{
	real_fx_type bar = _derivative();
	long double eval = static_cast<long double>(num);
	
	return bar(eval);
}

// find the antiderivative of the function
// the x-intercept is passed in 
template <typename T, typename>
realFx realFx::integral(const T& x_inter)
{
	real_fx_type bar;

	bar = [this, &x_inter](long double& x) -> long double
		{
			long double val;
			val = static_cast<long double>(x_inter);
			return _def_integral(val, x);
		};

	return bar;
}

// determines if the limit exists
// truncates the left and right values to 4 byte floats and compares them
template <typename T, typename>
bool realFx::limit_exists_at(const T& val, const long double& h)
{
	float left;
	float right;

	left = left_limit(val, h);
	right = right_limit(val, h);

	// if the left and right limits are unequal
	// and we have a valid limitting value
	if (left != right && std::abs(h) > std::numeric_limits<long double>::epsilon())
	{
		// recursive call
		return limit_exists_at(val, h / 2.);
	}
	// if the limits are equal
	// and there is a valid limitting value
	else if(left == right)
	{
		return (left == right && !std::isnan(left));
	}
	// if the limits are unequal
	// and we've reached epsilon
	else if (left != right && std::abs(h) <= std::numeric_limits<long double>::epsilon())
	{
		return false;
	}
}

// find the left limit
template <typename T, typename>
long double realFx::left_limit(const T& num, const long double& h)
{
	long double eval = static_cast<long double>(num);
	long double epsilon = h;

	epsilon *= std::max(static_cast<long double>(1.0), std::abs(eval));

	eval -= epsilon;

	return foo(eval);
}

// evaluates the limit
// determines if the limit exists first
template <typename T, typename>
long double realFx::limit_at(const T& val, const long double& h)
{
	if (limit_exists_at(val, h))
		return left_limit(val, h);
	else
		return std::nan("");
}

// find the right limit
template <typename T, typename>
long double realFx::right_limit(const T& num, const long double& h)
{
	long double eval = static_cast<long double>(num);
	long double epsilon = h;

	epsilon *= std::max(static_cast<long double>(1.0), std::abs(eval));

	eval += epsilon;

	return foo(eval);
}


	/* operators */

// binary addition
template <typename T, typename>
realFx realFx::operator+(const T& offset)
{
	long double num;

	num = static_cast<long double>(offset);

	real_fx_type bar = [&foo, &num](long double& x) -> long double
		{
			return foo(x) + num;
		};

	return realFx(bar);
}

// binary addition
// friend operator
template <typename T,
	typename = std::enable_if_t<std::is_convertible_v<T, long double>>>
realFx operator+(const T& num, const realFx& foo)
{
	realFx::real_fx_type bar;
	long double eval;

	eval = static_cast<long double>(num);

	bar = [&foo, &eval](long double& x) -> long double
		{
			return foo(x) + eval;
		};

	return realFx(bar);
}

// binary addition
realFx realFx::operator+(const realFx& other)
{
	real_fx_type foo_bar = [this, &other](long double& x) -> long double
		{
			return this->foo(x) + other.foo(x);
		};

	return realFx(foo_bar);
}

// binary subtraction
template <typename T, typename>
realFx realFx::operator-(const T& offset)
{
	long double num;

	num = static_cast<long double>(offset);

	real_fx_type bar = [&foo, &num](long double& x) -> long double
		{
			return foo(x) - num;
		};

	return realFx(bar);
}

// binary subtraction
// friend operator
template <typename T,
	typename = std::enable_if_t<std::is_convertible_v<T, long double>>>
realFx operator-(const T& num, const realFx& foo)
{
	realFx::real_fx_type bar;
	long double eval;

	eval = static_cast<long double>(num);

	bar = [&foo, &eval](long double& x) -> long double
		{
			return eval - foo(x);
		};

	return realFx(bar);
}

// binary subtraction
realFx realFx::operator-(const realFx& other)
{
	real_fx_type foo_bar = [this, other](long double& x) -> long double
		{
			return this->foo(x) - other.foo(x);
		};

	return realFx(foo_bar);
}

// binary multiplication
template <typename T, typename>
realFx realFx::operator*(const T& scalar)
{
	long double num;

	num = static_cast<long double>(scalar);

	real_fx_type bar = [&foo, &num](long double& x) -> long double
		{
			return foo(x) * num;
		};

	return realFx(bar);
}

// binary multiplication
// friend operator
template <typename T,
	typename = std::enable_if_t<std::is_convertible_v<T, long double>>>
realFx operator*(const T& num, const realFx& foo)
{
	realFx::real_fx_type bar;
	long double eval;

	eval = static_cast<long double>(num);

	bar = [&foo, &eval](long double& x) -> long double
		{
			return eval * foo(x);
		};

	return realFx(bar);
}

// binary multiplication
realFx realFx::operator*(const realFx& other)
{
	real_fx_type foo_bar = [this, other](long double& x) -> long double
		{
			return this->foo(x) * other.foo(x);
		};

	return realFx(foo_bar);
}

// binary division
template <typename T, typename>
realFx realFx::operator/(const T& scalar)
{
	long double num;

	num = static_cast<long double>(scalar);

	real_fx_type bar = [&foo, &num](long double& x) -> long double
		{
			return foo(x) / num;
		};

	return realFx(bar);
}

// binary division
// friend operator
template <typename T,
	typename = std::enable_if_t<std::is_convertible_v<T, long double>>>
realFx operator/(const T& num, const realFx& foo)
{
	realFx::real_fx_type bar;
	long double eval;

	eval = static_cast<long double>(num);

	bar = [&foo, &eval](long double& x) -> long double
		{
			return eval / foo(x);
		};

	return realFx(bar);
}

// binary division
realFx realFx::operator/(const realFx& other)
{
	real_fx_type foo_bar = [this, other](long double& x) -> long double
		{
			return this->foo(x) / other.foo(x);
		};

	return realFx(foo_bar);
}

// bitwise exponentiation
template <typename T, typename>
realFx realFx::operator^(const T& power)
{
	long double num;

	num = static_cast<long double>(power);

	real_fx_type bar = [&foo, &num](long double& x) -> long double
		{
			return pow(foo(x), num);
		};

	return realFx(bar);
}

// bitwise exponentiation
// friend operator
template <typename T,
	typename = std::enable_if_t<std::is_convertible_v<T, long double>>>
realFx operator^(const T& num, const realFx& foo)
{
	realFx::real_fx_type bar;
	long double eval;

	eval = static_cast<long double>(num);

	bar = [&foo, &eval](long double& x) -> long double
		{
			return eval ^ foo(x);
		};

	return realFx(bar);
}

// bitwise exponentiation
realFx realFx::operator^(const realFx& other)
{
	auto foo_bar = [this, other](long double& x) -> long double
		{
			return pow(this->foo(x), other.foo(x));
		};

	return realFx(foo_bar);
}

// function call operator
// casts x to a long double and evaluates
template <typename T, typename>
long double realFx::operator()(const T& x) const
{
	long double val = x;
	return foo(val);
}

// function call operator
// creates a lambda function to be the 
realFx realFx::operator()(const realFx& other) const
{
	long double result;
	real_fx_type foo, bar, foo_o_bar;
	
	foo = this->foo;
	bar = other.foo;

	foo_o_bar = [foo, bar, &result](long double& x) -> long double&
		{
			long double bar_x = bar(x);
			result = foo(bar_x);

			return result;
		};

	return realFx(foo_o_bar);
}

// assignment operator
realFx& realFx::operator=(const realFx& other)
{
	if (this != &other)
	{
		foo = other.foo;
	}
	return *this;
}
