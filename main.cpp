#include "expression.hpp"
#include <iomanip>
#include <iostream>

using std::cout;
using std::setw;
using std::string;

int main()
{
	string expression;

	std::cin >> expression;

	boolExp_w(expression);

	cout << setw(5) << " " << "Input";
	return 0;
}
