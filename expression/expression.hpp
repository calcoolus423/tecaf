#pragma once


#include <algorithm>
#include <array>
#include <exception>
#include <iostream>
#include <map>
#include <sstream>
#include <stack>
#include <string>
#include <vector>


using std::stack;
using std::string;


/* prototypes */

// purpose: determines if a string can be expressed as a number
// requires: a string
// returns: a boolean
bool isNumber(const std::string&);


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


	/* definitions */

// written by Gemini
bool isNumber(const std::string& str)
{
	std::istringstream iss(str);
	double d;
	iss >> std::noskipws >> d;
	return iss.eof() && !iss.fail();
}