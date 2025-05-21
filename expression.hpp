#pragma once


#include <iostream>
#include <map>
#include <stack>
#include <string>


using std::cout;
using std::stack;
using std::string;


// purpose: evaluates a boolean expression
// requires: an array of bools that has length 2, and a char that represents
//	the operation to do
// returns: a boolean i.e. the result of the expression
bool eval_boolExp(const bool[], const char&);

// purpose: converts an expression of bools from infix to postfix notation
// requires: a string i.e. an expression in infix notation
// returns: a string i.e. an expression on postfix notation
string infix_to_postfix(const string&);


bool eval_boolExp(const bool bee[], const char& be)
{
	/*************************************************************************\
	* Good news! We can finally be bees. This isn't your world, but we can    *
	* be bees. This is good news. You can be a bee. You'll live like a bee—   *
	* a pet! A pet? A pet, Mark. This is good news! You'll live for thirty    *
	* years! This is insane!                                                  *
	\*************************************************************************/
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
	}

}

// Dijkstra's shunting yard algorithm
// https://mathcenter.oxford.emory.edu/site/cs171/shuntingYardAlgorithm/
string infix_to_postfix_bool(const string& infix)
{
	char symbol;
	std::map<char, unsigned short> pemdas = 
	{
		{'|', 0}, {'&', 1}, {'^', 2}, {'~', 3}
	};
	stack<char> ops;
	string buffer = infix;
	string postfix = "";

	try
	{
		// while there is more to convert
		while (buffer.size() > 0)
		{
			// the symbol is the front of the string
			symbol = buffer.front();

			switch (symbol)
			{
			case '(':
				// push ( onto the stack
				ops.push(symbol);

				break;

			case ')':
				// while the top of the stack isn't (
				while (ops.top() != '(')
				{
					// discard )
					// get the top operator
					symbol = ops.top();

					// push the symbol onto the postfix
					postfix += symbol;

					// pop the top of the operator stack
					ops.pop();
				}

				// get rid of the (
				ops.pop();

				break;

			case '0': postfix += '0'; break;

			case '1': postfix += '1'; break;

			case '~': ops.push(symbol); break;

			case '^':
				// if the stack is empty
				if (ops.empty()) ops.push(symbol);
				// if the top of the stack is (
				else if (ops.top() == '(') ops.push(symbol);
				// if the top of the stack is more important than ^
				else if (pemdas[symbol] > pemdas[ops.top()]) ops.push(symbol);
				else
				{
					// while the operator on the top of the stack is more important
					// or of similar importance, and the stack is not empty
					while (pemdas[symbol] <= pemdas[ops.top()] && !ops.empty())
					{
						// write the operator to the 
						postfix += ops.top();

						ops.pop();
					}

					ops.push(symbol);
				}

				break;

			case '&':
				// if the stack is empty
				if (ops.empty()) ops.push(symbol);
				// if the top of the stack is (
				else if (ops.top() == '(') ops.push(symbol);
				// if the top of the stack is more important than ^
				else if (pemdas[symbol] > pemdas[ops.top()]) ops.push(symbol);
				else
				{
					// while the operator on the top of the stack is more important
					// or of similar importance, and the stack is not empty
					while (pemdas[symbol] <= pemdas[ops.top()] && !ops.empty())
					{
						// write the operator to the 
						postfix += ops.top();

						ops.pop();
					}

					ops.push(symbol);
				}

				break;

			case '|':
				// if the stack is empty
				if (ops.empty()) ops.push(symbol);
				// if the top of the stack is (
				else if (ops.top() == '(') ops.push(symbol);
				// if the top of the stack is more important than ^
				else if (pemdas[symbol] > pemdas[ops.top()]) ops.push(symbol);
				else
				{
					// while the operator on the top of the stack is more important
					// or of similar importance, and the stack is not empty
					while (!ops.empty())
					{
						if (pemdas[symbol] > pemdas[ops.top()])
							break;
						// write the operator to the 
						postfix += ops.top();

						ops.pop();
					}

					ops.push(symbol);
				}

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