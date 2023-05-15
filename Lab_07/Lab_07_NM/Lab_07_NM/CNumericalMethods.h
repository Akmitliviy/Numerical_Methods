#pragma once

#include <iostream>
#include <vector>
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
	const double number_of_equasions{ 2 };
	SResult m_result;

	double Func1(double y) const;
	double Func2(double x) const;
	double GetDerivativeByX(double x) const;
	double GetDerivativeByY(double y) const;

	double FByXY(double x, double y) const;
	double GByXY(double x, double y) const;

	double FByXDerivative(double x, double y) const;
	double FByYDerivative(double x, double y) const;
	double GByXDerivative(double x, double y) const;
	double GByYDerivative(double x, double y) const;

	bool IsProcessConvergent(double first_derivative, double second_derivative) const;
	bool GetCloserIteration();
	bool GetCloserNewthon(vector<vector<double>>& matrix_j, vector<double> f);

	void SetTranspondedJNewthon(vector<vector<double>>& matrix_j, double x, double y) const;
	void SetTranspondedJ(vector<vector<double>>& matrix_j, double x, double y) const;
	double GetDeterminant(vector<vector<double>>& matrix_j) const;
	vector<double> MultiplyMatrixAndColumn(const vector<vector<double>> matrix, const vector<double> column) const;


};

