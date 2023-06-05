#pragma once
#include <iostream>
#include <vector>
#include <cmath>
#include <numbers>
#include <algorithm>
#include <numeric>

using namespace std;

enum ETypes {
	e_riemann,
	e_trapezoidal,
	e_simpson

};

class Integration
{
public:
	Integration() = delete;
	Integration(double left_border, double right_border, unsigned int n, double (*func)(double x));

	double RiemannRightSum();
	double RiemannLeftSum();
	double RiemannMiddleSum();

	double Trapezoidal();

	double Simpson();

	double GetError(ETypes type);

	double FindStep(double epsilon);

private:
	vector<double> m_x, m_y;
	double m_left_border, m_right_border, m_step, m_num_of_steps;
	double (*m_func)(double x);

	double GetSecondDerivative(double x);
	double GetFourthDerivative(double x);
	double GetM();
};

