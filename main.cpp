#include "expression.hpp"
#include <iomanip>
#include <iostream>

using std::cout;
using std::setw;

constexpr unsigned short COLUMN_WIDTH = 12;

int main()
{
	string expression;

	std::cout << ">> ";
	std::getline(std::cin, expression);

	std::cout << expression << '\n';
	std::cout << infix_to_postfix_bool(expression) << "\n";

	cout << setw(COLUMN_WIDTH) << std::left << "Input";
	cout << setw(COLUMN_WIDTH) << std::left << "Output" << '\n';

	cout << setw(COLUMN_WIDTH) << std::right << expression;
	cout << setw(COLUMN_WIDTH) << std::right << infix_to_postfix_bool(expression);
	return 0;
}
