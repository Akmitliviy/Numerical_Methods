#pragma once

#include <iostream>
#include <cmath>

using namespace std;
struct SResult {
	double x;
	double y;
};
class CNumericalMethods
{
public:
	CNumericalMethods() = delete;
	CNumericalMethods(double x, double y);
	CNumericalMethods(double x, double y, double epsilon);

	SResult Iteration();
	SResult Newthon();

private:
	double m_epsilon;
	SResult m_result;

	double GetDerivativeByX(double x);
	double GetDerivativeByY(double y);

	bool IsProcessConvergent(double first_derivative, double second_derivative);
	bool GetCloser();

};

