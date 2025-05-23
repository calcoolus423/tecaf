#include "expression.hpp"
#include <fstream>
#include <iomanip>

using std::ifstream;
using std::setw;

constexpr unsigned short COLUMN_WIDTH = 21;

int main()
{
	bool result;
	ifstream infile("prog1Data.txt");
	string expression;
	string prefix;
	string postfix;

	boolExp* myExp;

	// header
	cout << setw(static_cast<unsigned short>(COLUMN_WIDTH + 3)) << std::left << "Original (Infix)";
	cout << setw(static_cast<unsigned short>(COLUMN_WIDTH + 3)) << std::left << "Postfix";
	cout << setw(static_cast<unsigned short>(COLUMN_WIDTH + 3)) << std::left << "Prefix";
	// cout << setw(static_cast<unsigned short>(COLUMN_WIDTH + 3)) << std::left << "Prefix";
	cout << setw(COLUMN_WIDTH) << std::left << "Output" << '\n';

	// get the expression
	while (!infile.eof())
	{
		// get the expression to evaluate in infix notation
		std::getline(infile, expression);

		// create a new boolean expression object
		myExp = new boolExp(expression);

		// write the original expression
		cout << setw(COLUMN_WIDTH) << std::right << expression << " | ";

		// find the result
		result = myExp->evaluate();

		postfix = myExp->getExpression("postfix");

		cout << setw(COLUMN_WIDTH) << std::right << postfix << " | ";

		prefix = myExp->getExpression("prefix");

		cout << setw(COLUMN_WIDTH) << std::right << prefix << " | ";

		// print the result
		cout << setw(COLUMN_WIDTH) << std::right << result << '\n';

		myExp->

		delete myExp;
	}

	myExp = nullptr;

	return 0;
}
