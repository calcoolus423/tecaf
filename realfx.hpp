#pragma once

#include <algorithm>
#include <cmath>
#include <functional>
#include <limits>

// set the epsilon for each type
constexpr long double EPSILON = std::numeric_limits<long double>::epsilon();

class realFx
{
private:

		/* member variables */

	std::function<long double(long double&)> foo;

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
	realFx(const auto&);

	// copy constructor
	// copies the function
	realFx(const realFx&);

	// destructor
	~realFx() {}

		/* member functions */

	// purpose: determines if the limit exists at a value
	// requires: a long double
	// returns: true if it exists, false if it doesn't
	bool limit_exists_at(const auto&);

	// purpose: find the left limit at a value
	// requires: a number
	// returns: the left limit of the function at that value
	long double left_limit(const auto&, long double = EPSILON);

	// purpose: find the left limit at a value
	// requires: a number
	// returns: the left limit of the function at that value
	long double right_limit(const auto&, long double = EPSILON);

	// purpose: finds the limit of a value
	// requires: a number
	// returns: the limit of the function at that value
	long double limit_at(const auto&);

		/* operators */

	// purpose: evaluates the function at a value
	// requires: a type that can be cast to long double
	// returns: a long double, i.e. the result
	long double operator()(const auto&) const;

	// purpose: composes this function at another function
	// requires: a realFx
	// returns: a new function, i.e. the composition
	realFx operator()(const realFx&) const;

};


	/* constructors */

// default constructor
realFx::realFx() : foo(std::identity{}) { }

// parametrized constructor
// referenced function
realFx::realFx(const std::function<long double(long double&)>& bar) : foo(bar)
{ }

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
realFx::realFx(const auto& number)
{
	try
	{
		long double val = number;

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

/* public */

// find the left limit
long double realFx::left_limit(const auto& num, long double h)
{
	long double eval = static_cast<long double>(num);

	h *= std::max(static_cast<long double>(1.0), std::abs(eval));

	eval -= h;

	return foo(eval);
}

// find the right limit
long double realFx::right_limit(const auto& num, long double h)
{
	long double eval = static_cast<long double>(num);

	h *= std::max(static_cast<long double>(1.0), std::abs(eval));

	eval += h;

	return foo(eval);
}

// determines if the limit exists
bool realFx::limit_exists_at(const auto& val)
{
	float left;
	float right;

	left = left_limit(val);
	right = right_limit(val);

	return (left == right);
}

long double realFx::limit_at(const auto& val)
{
	if (limit_exists_at(val))
		return left_limit(val);
	else
		return std::nan("");
}


	/* operators */

// function call operator
// casts x to a long double and evaluates
long double realFx::operator()(const auto& x) const
{
	long double val = x;
	return foo(val);
}

// function call operator
// creates a lambda function to be the 
realFx realFx::operator()(const realFx& other) const
{
	long double result;
	std::function<long double(long double&)> foo, bar, foo_o_bar;
	
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
