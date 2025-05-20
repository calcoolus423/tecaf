#pragma once


#include <iostream>
#include <stack>


using std::cout;
using std::stack;
using std::string;


// boolean expression using a while loop
bool boolExp_w(std::string);


bool boolExp_w(std::string xpr)
{
	char symbol;
	stack<char> ops;
	stack<bool> val;

	while (xpr.size() > 0)
	{
		symbol = xpr.front();

		switch (symbol)
		{
		case '0':
			(ops.top() == '~') ? val.push(true) : val.push(false);
			break;

		case '1':
			break;

		case '~':
			break;

		case '&':
			break;

		case ' ':
			break;

		case '(':
			break;
		}

		xpr = xpr.substr(1);

	}

	return true;

}