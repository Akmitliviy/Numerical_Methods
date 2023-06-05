#pragma once
#include <iostream>
#include <vector>

using namespace std;

class CInterpolation
{
public:
	CInterpolation() = delete;
	CInterpolation(double* m_x, double* m_y, size_t m_size);

	vector<double> Lagrange() const;
	double FindByLagrange(double x) const;

	vector<double> Newthon(double x) const;
	double FindByNewthon(double x) const;
	
private:
	vector<double> m_x;
	vector<double> m_y;
	size_t m_size;

	double FindDifferences(int difference_index, int x_index) const;
	double FindQ(double x, double movable_x, double interpolation_step) const;
	vector<double> Forward(double interpolation_step) const;
	double Factorial(int x) const;
};

