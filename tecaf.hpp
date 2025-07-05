/*****************************************************************************\
*  _____  _____   ____   ___   _____                                          *
* |_   _||  ___| / ___) / _ \ |  ___|                                         *
*   | |  | |__  | /    / /_\ \| |__                                           *
*   | |  |  __| | |    |  _  ||  __|                                          *
*   | |  | |___ | \___ | | | || |                                             *
*   |_|  |_____| \____)|_| |_||_|                                             *
*                                                                             *
*   A collection of algorithms and functions that make for a more diverse C++ *
*   coding experience. Primarily centered around mathematical functions,      *
*   expressions, and evaluations, this library allows for user-creation and   *
*   analysis of numerical/analystical functions.                              *
*   This file mostly acts as a wrapper for other hpp files.                   *
*	Written in C++20.
\*****************************************************************************/

#pragma once


#include <algorithm>
#include <array>
#include <cmath>
#include <exception>
#include <functional>
#include <iostream>
#include <limits>
#include <map>
#include <sstream>
#include <stack>
#include <string>
#include <type_traits>
#include <vector>


using std::stack;
using std::string;

// calculate euler's constant
const long double E = std::exp(1);

// set the positive and negative infinity constants
constexpr long double INF = std::numeric_limits<long double>::infinity();
constexpr long double N_INF = -std::numeric_limits<long double>::infinity();

// set the epsilon for each type
const long double EPSILON =
std::sqrt(std::numeric_limits<long double>::epsilon());


		/* global fx prototypes */

// purpose: determines if a string can be expressed as a number
// requires: a string
// returns: a boolean
bool isNumber(const std::string&);

// purpose: prints the data to the console and breaks the line
// requires: anything that can be printed
// returns: nothing
template <class adt>
void print(adt data) { std::cout << data << '\n'; }

// purpose: print a line to the console
// requires: nothing
// returns: nothing
void print() { std::cout << '\n'; }


		/* classes */

	/* Expression */

// purpose: an abstract class that represents expressions
// invariants: none
// data members:
//	'result' is a pointer to the expression's result
//	'expression' is a string that represents the actual expression
template <typename adt>
class Expression
{
protected:

	/* member variables */

// assigns importance to each operator
	inline static const std::map<char, unsigned short> PEMDAS
		= { {'(', 0}, {'|', 1}, {'&', 2}, {'^', 3}, {'~', 4},
			{'+', 1}, {'-', 1}, {'*', 2}, {'/', 2} };

	// the result of the expression
	// nullptr means the expression has not been evaluated yet
	adt* result = nullptr;

	// the expression in postfix notation
	string expression;

	/* member functions */

// purpose: helper function for Dijkstra's algorithm, compares the
//	current operator with the stack wrt the order of operations and pushes
//	them onto the string i.e. the postfix expression
// requires: a char i.e. the operator, a stack that holds the current
//	operators, and a string i.e. the postfix expression
// returns: nothing, but pops elements onto the string
	virtual void compareAndPush(const char&, stack<char>&, string&) = 0;

	// purpose: evaluates an expression with two inputs
	// requires: an array of two values to evaluate,
	//	and a char i.e. the operator
	// returns: an adt
	virtual adt eval_simple_exp(
		const std::array<adt, 2>&,
		const char&
	) const = 0;

	// purpose: evaluates the top two values on a stack with a given operation
	// requires: a stack of values and a char that represents the operation
	// returns: nothing, but adjusts the stack
	virtual void getAndEval(stack<adt>&, const char&) = 0;

	// purpose: converts an expression from infix to postfix notation
	// requires: a string i.e. an expression in infix notation
	// returns: a string i.e. an expression in postfix notation
	virtual string infix_to_postfix(const string&) = 0;

	// purpose: converts an expression from postfix to infix notation
	// requires: a string i.e. an expression in postfix notation
	// returns: a string i.e. an expression in infix notation
	virtual string postfix_to_infix(const string&) = 0;

	// purpose: converts an expression from postfix to prefix notation
	// requires: a string i.e. an expression in postfix notation
	// returns: a string i.e. an expression in prefix notation
	virtual string postfix_to_prefix(const string&) = 0;

	// purpose: converts an expression from prefix to postfix notation
	// requires: a string i.e. an expression in prefix notation
	// returns: a string i.e. an expression in postfix notation
	virtual string prefix_to_postfix(const string&) = 0;

public:

	/* destructor */

	virtual ~Expression() { delete result; result = nullptr; }

	/* member functions */

// purpose: evaluates the expression
// requires: nothing
// returns: an adt i.e. the result
	virtual adt evaluate() = 0;

	// purpose: gets the expression
	// requires: can pass in "infix", "prefix", or "postfix" to get the
	//	expression in one of those formats, by default "infix"
	// returns: a string i.e. the expression
	virtual string getExpression(const string & = "infix") = 0;

	// purpose: changes the expression to something new
	// requires: a string i.e. the new expression, and a string i.e. the
	//	format either "infix", "prefix", or "postfix", by default "infix"
	// returns: a string i.e. the expression
	virtual void setExpression(const string&, const string & = "infix") = 0;

};


	/* boolExp */

// purpose: represents a boolean expression
// invariants: expression must be boolean and uses operations &, |, ^, or ~
// data members:
//	'result' is a pointer to the expression's result
//	'expression' is a string that represents the actual expression
class boolExp : public Expression<bool>
{
protected:

	/* member functions */

	// purpose: evaluates a boolean expression with two inputs
	// requires: an array of two bools to evaluate,
	//	and a char i.e. the operator
	// returns: a bool
	bool eval_simple_exp
	(const std::array<bool, 2>&, const char&) const override;

	// purpose: evaluates the top two bools on a stack with a given operation
	// requires: a stack of bools and a char that represents the operation
	// returns: nothing, but adjusts the stack
	void getAndEval(stack<bool>&, const char&) override;

	// can be brought to parent
	// purpose: converts an expression from infix to postfix format
	// requires: a string i.e. the expression in infix format
	// returns: a string i.e. the expression in postfix format
	string infix_to_postfix(const string&) override;

	// can be brought to parent
	// purpose: converts an expression from postfix to infix format
	// requires: a string i.e. the expression in postfix format
	// returns: a string i.e. the expression in infix format
	string postfix_to_infix(const string&) override;

	// can be brought to parent
	// purpose: converts an expression from postfix to prefix format
	// requires: a string i.e. the expression in postfix format
	// returns: a string i.e. the expression in prefix format
	string postfix_to_prefix(const string&) override;

	// can be brought to parent
	// purpose: converts an expression from prefix to postfix format
	// requires: a string i.e. the expression in prefix format
	// returns: a string i.e. the expression in postfix format
	string prefix_to_postfix(const string&) override;

public:

	/* constructors */

	// default constructor
	// sets the expression to the additive identity,
	//	and consequentially the result too
	boolExp() { expression = "0"; }

	// parametrized constructor
	// takes in a string i.e. an expression in infix notation
	//	and the format of the expression being passed in, must be "infix",
	//	"prefix", or "postfix"
	boolExp(const string&, const string & = "infix");

	// copy constructor
	boolExp(const boolExp&);

	/* member functions */

	// purpose: evaluates the expression
	// requires: nothing
	// returns: a boolean value i.e. the result
	bool evaluate() override;

	// purpose: gets the expression
	// requires: can pass in "infix", "prefix", or "postfix" to get the
	//	expression in one of those formats, by default "infix"
	// returns: a string i.e. the expression
	string getExpression(const string & = "infix");

	// purpose: changes the expression to something new
	// requires: a string i.e. the new expression, and a string i.e. the
	//	format either "infix", "prefix", or "postfix", by default "infix"
	// returns: a string i.e. the expression
	void setExpression(const string&, const string & = "infix");

};


	/* realExp */
	/* a WIP */

// purpose: represents a real-valued expression
// invariants: expression must be representable as real numbers and uses
//	operations +, -, *, or /
// data members:
//	'result' is a pointer to the expression's result
//	'expression' is a string that represents the actual expression
class realExp : public Expression<long double>
{
protected:

	/* member functions */

	// purpose: evaluates a real expression with two inputs
	// requires: an array of two long doubles to evaluate,
	//	and a char i.e. the operator
	// returns: a long double that is the result
	long double eval_simple_exp
	(const std::array<long double, 2>&, const char&) const override;

public:

	/* constructors */

	// default constructor
	// sets the expression to the additive identity
	realExp() { expression = "0"; }

	// parametrized constructor
	// takes in a string i.e. an expression in infix notation
	//	and the format of the expression being passed in, must be "infix",
	//	"prefix", or "postfix", but is "infix" by default
	realExp(const string&, const string & = "infix");

	// copy constructor
	realExp(const realExp&);
};


	/* realFx */

// purpose: represents a real-valued function
// invariants: the function takes in a long double passed by reference
//	and returns a long double by value
// data members:
//	foo is a functional object i.e. the representative function
class realFx
{
private:
	/* prerequisites */

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

	// purpose: finds an antiderivative
	// requires: nothing, but the x-intercept can be passed through
	// returns: a realFx i.e. the integral
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

	// purpose: reflects the function about the x-axis
	// requires: nothing
	// returns: a new function
	realFx reflectX();

	// purpose: reflects the function about the y-axis
	// requires: nothing
	// returns: a new function
	realFx reflectY();

	// purpose: scales a function in the x and y direction
	// requires: a function and 2 scalars, cx and cy respectively
	//	f(x / cx) * cy
	// returns: a new function
	realFx scale(long double, long double);

	// purpose: scales a function in the x direction
	// requires: a function and a scalar
	//	f(x / c)
	// returns: a new function
	realFx scaleX(long double);

	// purpose: scales a function in the y direction
	// requires: a function and a scalar
	//	f(x) * c
	// returns a new function
	realFx scaleY(long double);

	// purpose: shifts a function in the x and y direction
	// requires: a function and 2 scalars, dx and dy respectively
	//	f(x - dx) + dy
	// returns: a new function
	realFx shift(long double, long double);

	// purpose: shifts a function in the x direction
	// requires: a function and a scalar
	// returns: a new function
	realFx shiftX(long double);

	// purpose: shifts a function in the y direction
	// requires: a function and a scalar
	// returns: a new function
	realFx shiftY(long double);

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

	/* boolExp */

// parametrized constructor
boolExp::boolExp(const string& xpr, const string& format)
{
	try
	{
		if (format == "infix")
			expression = infix_to_postfix(xpr);
		else if (format == "postfix")
			expression = xpr;
		else if (format == "prefix")
			expression = prefix_to_postfix(xpr);
		else
			throw std::invalid_argument("Format must be 'infix', 'prefix' or"
				"'postfix'\n");
	}
	catch (const std::invalid_argument& e)
	{
		std::cerr << e.what();
	}

}

// copy constructor
boolExp::boolExp(const boolExp& other)
{
	expression = other.expression;
	result = other.result;
}


	/* realExp */

// parametrized constructor
realExp::realExp(const string& xpr, const string& format)
{

}


	/* realFx */

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
	
	/* boolExp */

/* protected */

/*****************************************************************************\
*  Good news! We can finally be bees. This isn't your world, but we can be    *
*  bees. This is good news. You can be a bee. You'll live like a bee--a pet!  *
*  A pet?                                                                     *
*  A pet, Mark. This is good news! You'll live for thirty years!              *
*  This is insane!                                                            *
\*****************************************************************************/
// the code does not work without the above comment
// evaluate a simple boolean expression
bool boolExp::eval_simple_exp
(const std::array<bool, 2>& bee, const char& be) const
{
	try
	{
		// which be is it
		switch (be)
		{
			// if the be is &
			// get 2 bees and and them
		case '&': return bee[0] && bee[1]; break;
			// if the be is |
			// get 2 bees and or them
		case '|': return bee[0] || bee[1]; break;
			// if the be is ^
			// get 2 bees and xor them
		case '^': return bee[0] && !bee[1] || bee[1] && !bee[0]; break;
		default:
			throw std::invalid_argument
			("Operation must be '&', '|', or '^'\n");
			break;
		}

	}
	catch (const std::invalid_argument& e)
	{
		std::cerr << e.what();
		return bee[0];
	}

}

// Dijkstra's Shunting Yard Algorithm
// https://mathcenter.oxford.emory.edu/site/cs171/shuntingYardAlgorithm/
string boolExp::infix_to_postfix(const string& infix)
{
	char symbol;
	stack<char> ops;
	string buffer = infix;
	string postfix = "";

	try
	{
		while (buffer.size() > 0) // while there is more to convert
		{
			symbol = buffer.front(); // the symbol is the front of the string

			switch (symbol)
			{
			case '(': ops.push(symbol); break;
			case ')':
				// while the top of the stack isn't (
				while (ops.top() != '(')
				{
					symbol = ops.top(); // get the top operator
					postfix += symbol; // push the symbol onto the postfix
					ops.pop(); // pop the top of the operator stack
				}
				ops.pop(); // get rid of the (
				break;
			case '0': postfix += '0'; break; // append 0 to the string
			case '1': postfix += '1'; break; // append 1 to the string
			case '~': ops.push(symbol); break;
			case '^': case '&': case '|': // order of operations
				compareAndPush(symbol, ops, postfix);
				break;
			case ' ': break;
			default:
				string errMsg = "";
				errMsg += symbol;
				errMsg += " is not a valid character"
					" in a boolean expression\n";
				throw std::invalid_argument(errMsg);
				break;
			}

			buffer = buffer.substr(1);
		}

	}
	catch (const std::invalid_argument& e)
	{
		std::cerr << e.what();
		return infix;
	}

	while (!ops.empty())
	{
		postfix += ops.top();
		ops.pop();
	}

	return postfix;
}

// https://www.prepbytes.com/blog/stacks/conversion-of-postfix-expression-to-infix-expression/
string boolExp::postfix_to_infix(const string& post)
{
	stack<string> inf;
	string mini;

	for (const char& symbol : post)
	{
		mini = "";
		switch (symbol)
		{
		case '0': case '1':
			mini += symbol;
			inf.push(mini);
			break;
		case '&': case '|': case '^':
			mini += inf.top();
			inf.pop();

			mini = symbol + mini;

			mini = inf.top() + mini;
			inf.pop();

			mini = '(' + mini + ')';
			inf.push(mini);
			break;
		case '~':
			mini = symbol;
			mini += inf.top();
			inf.pop();
			inf.push(mini);
			break;
		default: break;
		}

	}

	if (!inf.empty())
	{
		return inf.top();
	}
	else
	{
		return "";
	}

}

// https://www.prepbytes.com/blog/stacks/postfix-to-prefix-conversion/
string boolExp::postfix_to_prefix(const string& post)
{
	stack<string> pre;
	string mini;

	for (const char& symbol : post)
	{
		mini = "";
		switch (symbol)
		{
		case '0': case '1':
			mini += symbol;
			// push it onto the stack
			pre.push(mini);
			break;
		case '&': case '|': case '^':
			for (int i = 0; i < 2; i++)
			{
				mini = pre.top() + mini;
				pre.pop();
			}
			mini = symbol + mini;
			pre.push(mini);
			break;
		case '~':
			mini += symbol;
			mini += pre.top();
			pre.pop();
			pre.push(mini);
			break;
		default: break;
		}

	}

	if (!pre.empty())
	{
		return pre.top();
	}
	else
	{
		return "";
	}
};

// https://www.prepbytes.com/blog/stacks/conversion-of-prefix-to-postfix-notation/
string boolExp::prefix_to_postfix(const string& pre)
{
	stack<string> post;
	string erp;
	string mini;

	// reverse the string
	erp = pre;
	std::reverse(erp.begin(), erp.end());

	for (const char& symbol : erp)
	{
		mini = "";
		switch (symbol)
		{
		case '0': case '1':
			mini += symbol;
			post.push(mini);
			break;
		case '~':
			mini += post.top();
			post.pop();
			mini += symbol;
			post.push(mini);
			break;
		case '&': case '|': case '^':
			for (int i = 0; i < 2; i++)
			{
				mini += post.top();
				post.pop();
			}
			mini += symbol;
			post.push(mini);
			break;
		default: break;
		}

	}

	if (!post.empty())
	{
		return post.top();
	}
	else
	{
		return "";
	}

};

void boolExp::getAndEval(stack<bool>& vals, const char& op)
{
	std::array<bool, 2> holder;

	for (int i = 0; i < 2; i++)
	{
		// get the top value
		holder[i] = vals.top();
		// pop the top
		vals.pop();
	}

	// evaluate them wrt the operator
	vals.push(eval_simple_exp(holder, op));
}


/* public */

// evaluate the full expression
bool boolExp::evaluate()
{
	bool temp;
	stack<bool> vals;
	string xpr = expression;

	if (result)
		return *result;
	else
	{
		// if the string is empty
		try
		{
			if (expression == "")
			{
				//throw std::invalid_argument("Expression is empty");
				return false;
			}

			for (char& symbol : xpr)
			{
				switch (symbol)
				{
				case '0': vals.push(false); break;
				case '1': vals.push(true); break;
				case '~':
					temp = vals.top();
					vals.pop();
					vals.push(!temp);
					break;
				case '&': case '|': case '^':
					getAndEval(vals, symbol);
					break;
				default:
					throw std::invalid_argument
					("Invalid char in postfix expression\n");
					break;
				}

			}

			result = new bool(vals.top());

			return *result;
		}
		catch (const std::invalid_argument& e)
		{
			std::cerr << e.what();
			return false;
		}

	}

}

// return the Expression's expression as a string in a given format
string boolExp::getExpression(const string& format)
{
	try
	{
		if (format == "postfix") // if the user wants postfix format
		{
			return expression;
		}
		else if (format == "infix") // if the user wants infix format
		{

			return postfix_to_infix(expression);
		}
		else if (format == "prefix") // if the user wants prefix format
		{
			return postfix_to_prefix(expression);
		}
		else
		{
			throw std::invalid_argument("Input of getExpression must be"
				"\"postfix\", \"infix\", or \"prefix\"\n");
		}

	}
	catch (const std::invalid_argument& e)
	{
		std::cerr << e.what();
	}

}

// set the expression that is in a given format
void boolExp::setExpression(const string& xpr, const string& format)
{
	try
	{
		if (format == "postfix")
		{
			expression = xpr;
		}
		else if (format == "infix")
		{
			expression = infix_to_postfix(xpr);
		}
		else if (format == "prefix")
		{
			expression = prefix_to_postfix(xpr);
		}
		else
		{
			throw std::invalid_argument("Input must be"
				"\"postfix\", \"infix\", or \"prefix\"\n");
		}
	}
	catch (const std::invalid_argument& e)
	{
		std::cerr << e.what();
	}

}


	/* realFx */

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

		for (count = 0; pos + 2 * del_x < right; count++)
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
	if (left != right &&
		std::abs(h) > std::numeric_limits<long double>::epsilon())
	{
		// recursive call
		return limit_exists_at(val, h / 2.);
	}
	// if the limits are equal
	// and there is a valid limitting value
	else if (left == right)
	{
		return (left == right && !std::isnan(left));
	}
	// if the limits are unequal
	// and we've reached epsilon
	else if (left != right &&
		std::abs(h) <= std::numeric_limits<long double>::epsilon())
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

realFx realFx::reflectX()
{
	real_fx_type bar = [this](long double x) ->long double
		{
			return -1 * foo(x);
		};

	return realFx(bar);
}

realFx realFx::reflectY()
{
	real_fx_type bar = [this](long double x) ->long double
		{
			long double new_x = -1 * x;
			return foo(new_x);
		};

	return realFx(bar);
}

realFx realFx::scale(long double cx, long double cy)
{
	real_fx_type bar = [this, &cx, &cy](long double x) -> long double
		{
			long double new_x = x / cx;
			return cy * foo(new_x);
		};

	return realFx(bar);
}

realFx realFx::scaleX(long double c)
{
	real_fx_type bar = [this, &c](long double x) -> long double
		{
			long double new_x = x / c;
			return foo(new_x);
		};

	return realFx(bar);
}

realFx realFx::scaleY(long double c)
{
	real_fx_type bar = [this, &c](long double x) -> long double
		{
			return c * foo(x);
		};

	return realFx(bar);
}

realFx realFx::shift(long double dx, long double dy)
{
	real_fx_type bar = [this, &dx, &dy](long double x) -> long double
		{
			long double new_x = x - dx;
			return foo(new_x) + dy;
		};

	return realFx(bar);
}

realFx realFx::shiftX(long double dx)
{
	real_fx_type bar = [this, &dx](long double x) -> long double
		{
			long double new_x = x - dx;
			return foo(new_x);
		};

	return realFx(bar);
}

realFx realFx::shiftY(long double dy)
{
	real_fx_type bar = [this, &dy](long double x) -> long double
		{
			return foo(x) + dy;
		};

	return realFx(bar);
}


		/* operators */

	/* realFx */

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


		/* global fx definitions */

// written by Gemini
bool isNumber(const std::string& str)
{
	std::istringstream iss(str);
	double d;
	iss >> std::noskipws >> d;
	return iss.eof() && !iss.fail();
}
