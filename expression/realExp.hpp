#pragma once


#include "expression.hpp"


	/* realExp */

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


		/* realExp */

	/* constructors */

// parametrized constructor
realExp::realExp(const string& xpr, const string& format)
{

}
