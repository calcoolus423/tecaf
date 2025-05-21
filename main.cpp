#include "expression.hpp"
#include <fstream>
#include <iomanip>
#include <iostream>

using std::cout;
using std::ifstream;
using std::setw;

constexpr unsigned short COLUMN_WIDTH = 20;

int main()
{
	bool result;
	ifstream infile("prog1Data.txt");
	string expression;
	string postfix;

	// header
	cout << setw(COLUMN_WIDTH + 3) << std::left << "Input";
	cout << setw(COLUMN_WIDTH) << std::left << "Output" << '\n';

	// get the expression
	while (!infile.eof())
	{
		std::getline(infile, expression);

		cout << setw(COLUMN_WIDTH) << std::right << expression << " | ";

		postfix = infix_to_postfix_bool(expression);
		result = eval_boolExp(postfix);

		cout << setw(COLUMN_WIDTH) << std::right << result << '\n';
	}

	return 0;
}
