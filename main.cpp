#include <iomanip>
#include <iostream>
#include "realfx.hpp"

using std::cout;
using std::string;

constexpr long double M = -2;
constexpr long double B = 10;

long double inverse_sq(long double&);

int main()
{
	long double val = -14;
	realFx f(inverse_sq);

	cout << f.limit_at(0);

	return 0;
}

long double inverse_sq(long double& x)
{
	return 1 / x;
}