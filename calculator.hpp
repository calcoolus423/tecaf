#pragma once


#include <iostream>
#include <stack>


using std::string;

class Calculator
{
protected:
	std::stack<string> operand;
	std::stack<string> value;
	std::string expression;

public:
	Calculator() {}
};


class BitwiseCalc : private Calculator
{
public:
	BitwiseCalc();
	BitwiseCalc(string);
};


BitwiseCalc::BitwiseCalc()
{
	expression = "1";
}

BitwiseCalc::BitwiseCalc(string expr)
{
	expression = expr;
}