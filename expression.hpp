#pragma once


#include <iostream>
#include <map>
#include <stack>
#include <string>


using std::cout;
using std::stack;
using std::string;


	/* prototypes */

// purpose: evaluates a simple boolean expression
// requires: an array of bools that has length 2, and a char that represents
//	the operation to do
// returns: a boolean i.e. the result of the expression
bool eval_simple_boolExp(const bool[], const char&);

// purpose: evaluates a boolean expression
// requires: a string i.e. the boolean expression in postfix notation
// returns: a boolean i.e. the result of the expression
bool eval_boolExp(const string&);

// purpose: a helper function for eval_boolExp, compares the top two booleans
//	in the stack with an operator
// requires: a stack of booleans, and a char i.e. the operator
// returns: the evaluated expression
void getAndEval(stack<bool>&, const char&);

// purpose: converts an expression of bools from infix to postfix notation
//	using a while loop
// requires: a string i.e. an expression in infix notation
// returns: a string i.e. an expression on postfix notation
string infix_to_postfix_bool(const string&);

// purpose: a helper function for infix_to_postfix, compares an operator with
//	those already on the stack
// requires: a char that represents the current operator, the stack of
//	operators, and a string i.e. the current postfix expression
void compareAndPush(const char&, stack<char>&, string&);


	/* definitions */

/*****************************************************************************\
*  Good news! We can finally be bees. This isn't your world, but we can be    *
*  bees. This is good news. You can be a bee. You'll live like a bee — a pet! *
*  A pet?                                                                     *
*  A pet, Mark. This is good news! You'll live for thirty years!              *
*  This is insane!                                                            *
\*****************************************************************************/
bool eval_simple_boolExp(const bool bee[], const char& be)
{
	try
	{
		switch (be)
		{
		case '&': return bee[0] && bee[1]; break;

		case '|': return bee[0] || bee[1]; break;

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

bool eval_boolExp(const string& postfix)
{
	bool temp;
	stack<bool> vals;
	string xpr = postfix;

	if (postfix == "")
	{
		return false;
	}
	try
	{
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
			case '&':
				getAndEval(vals, symbol);
				break;
			case '|':
				getAndEval(vals, symbol);
				break;
			case '^':
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

void getAndEval(stack<bool>& vals, const char& symbol)
{
	bool holder[2];

	holder[0] = vals.top();
	vals.pop();
	holder[1] = vals.top();
	vals.pop();
	vals.push(eval_simple_boolExp(holder, symbol));
}

// Dijkstra's Shunting Yard Algorithm
// https://mathcenter.oxford.emory.edu/site/cs171/shuntingYardAlgorithm/
string infix_to_postfix_bool(const string& infix)
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
			case '^': compareAndPush(symbol, ops, postfix); break;
			case '&': compareAndPush(symbol, ops, postfix); break;
			case '|': compareAndPush(symbol, ops, postfix); break;
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

// helper function for Dijkstra's algorithm UwU
void compareAndPush(const char& symbol, stack<char>& ops, string& postfix)
{
	std::map<char, unsigned short> pemdas =
	{
		{'|', 0}, {'&', 1}, {'^', 2}, {'~', 3}
	};

	// if the stack is empty
	if (ops.empty()) ops.push(symbol);
	// if the top of the stack is (
	else if (ops.top() == '(') ops.push(symbol);
	// if the top of the stack is more important than ^
	else if (pemdas[symbol] > pemdas[ops.top()]) ops.push(symbol);
	else
	{
		// while the operator on the top of the stack is more
		// important or of similar importance, and the stack is
		// not empty
		while (pemdas[symbol] <= pemdas[ops.top()] && !ops.empty())
		{
			// write the operator to the 
			postfix += ops.top();

			ops.pop();
		}

		ops.push(symbol);
	}

	return;
}
