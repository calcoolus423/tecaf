#pragma once


#include <array>
#include <exception>
#include <iostream>
#include <map>
#include <stack>
#include <string>


using std::cout;
using std::stack;
using std::string;


	/* prototypes */

// purpose: determines if a string can be expressed as a number
// requires: a string
// returns: a boolean
bool isNumber(const std::string&);

// purpose: evaluates a boolean expression
// requires: a string i.e. the boolean expression in postfix notation
// returns: a boolean i.e. the result of the expression
bool eval_boolExp(const string&);

// purpose: converts an expression of bools from infix to postfix notation
// requires: a string i.e. an expression in infix notation
// returns: a string i.e. an expression on postfix notation
string infix_to_postfix_bool(const string&);


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

	inline static const std::map<char, unsigned short> pemdas
		= { {'|', 0}, {'&', 1}, {'^', 2}, {'~', 3},
			{'+', 0}, {'-', 0}, {'*', 1}, {'/', 1}, {'^', 2} };
	
	adt* result = nullptr;

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

public:

		/* member functions */

	// purpose: evaluates the expression
	// requires: nothing
	// returns: an adt i.e. the result
	virtual adt evaluate() = 0;

};


	/* boolExp */

class boolExp : public Expression<bool>
{
protected:

		/* member functions */

	// purpose: helper function for Dijkstra's algorithm, compares the
	//	current operator with the stack wrt the order of operations and pushes
	//	them onto the string i.e. the postfix expression
	// requires: a char i.e. the operator, a stack that holds the current
	//	operators, and a string i.e. the postfix expression
	// returns: nothing, but pops elements onto the string
	void compareAndPush(const char&, stack<char>&, string&);

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

	// purpose: converts an expression from infix format to postfix format
	// requires: a string i.e. the expression in infix format
	// returns: a string i.e. the expression in postfix format
	string infix_to_postfix(const string&) override;

public:

		/* constructors */

	// default constructor
	// sets the expression to the additive identity,
	//	and consequentially the result too
	boolExp();

	// parametrized constructor
	// takes in a string i.e. an expression in infix notation
	boolExp(const string&);

	// copy constructor
	boolExp(const boolExp&);
	
		/* member functions */

	// purpose: evaluates the expression
	// requires: nothing
	// returns: a boolean value i.e. the result
	bool evaluate() override;

};


		/* boolExp */

	/* constructors */

// default constructor
boolExp::boolExp()
{
	expression = "";
}

// parametrized constructor
boolExp::boolExp(const string& infix)
{
	expression = infix_to_postfix(infix);
}

// copy constructor
boolExp::boolExp(const boolExp& other)
{
	expression = other.expression;
	result = other.result;
}


	/* methods */

/* protected */

// helper function for Dijkstra's algorithm UwU
void boolExp::compareAndPush
(const char& symbol, stack<char>& ops, string& postfix)
{
	// if the stack is empty
	if (ops.empty()) ops.push(symbol);
	// if the top of the stack is (
	else if (ops.top() == '(') ops.push(symbol);
	// if the top of the stack is more important than ^
	else if (pemdas.at(symbol) > pemdas.at(ops.top())) ops.push(symbol);
	else
	{
		// while the operator on the top of the stack is more
		// important or of similar importance, and the stack is
		// not empty
		while (pemdas.at(symbol) <= pemdas.at(ops.top()) && !ops.empty())
		{
			// write the operator to the 
			postfix += ops.top();

			ops.pop();
		}

		ops.push(symbol);
	}

	return;
}

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
			case '0': postfix += '0'; break;
			case '1': postfix += '1'; break;
			case '~': ops.push(symbol); break;
			case '^': case '&': case '|':
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

void boolExp::getAndEval(stack<bool>& vals, const char& op)
{
	std::array<bool, 2> holder;

	for(int i = 0; i < 2; i++)
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

	// if the string is empty
	try
	{
		if (expression == "")
		{
			throw std::logic_error("String must not be empty");
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

		return vals.top();
	}
	catch (const std::invalid_argument& e)
	{
		std::cerr << e.what();
		return false;
	}

}
