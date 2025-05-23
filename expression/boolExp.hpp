#pragma once


#include "expression.hpp"


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


		/* constructors */

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


		/* methods */

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
