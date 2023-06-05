#include <iostream>
#include "CInterpolation.h"

int main()
{
	const size_t m_size{ 5 };
	double m_x[m_size]{ -3, -1, 0, 1, 3 };
	double m_y[m_size]{ -4, -0.8, 1.6, 2.3, 1.5 };
	const double x{ -2 };

	CInterpolation in(m_x, m_y, m_size);

	vector<double> lagrange_polynom = in.Lagrange();
	double lagrange_result = in.FindByLagrange(x);

	vector<double> newthon_polynom = in.Newthon(x);
	double newthon_result = in.FindByNewthon(x);


	cout << "LAGRANGE:\n\nPolynom: ";
	for (int i = 0; i < m_size; i++) {

		if (lagrange_polynom[i] >= 0)
			cout << "+";
		cout << lagrange_polynom[i] << "x^" << m_size - i - 1 << " ";
	}
	cout << "\nSolution for " << x << ": " << lagrange_result << "\n\n\n";

	cout << "NEWTHON:\n\nPolynom: ";
	for (int i = 0; i < m_size; i++) {

		if (newthon_polynom[i] >= 0)
			cout << "+";
		cout << newthon_polynom[i] << "x^" << m_size - i - 1 << " ";
	}
	cout << "\nSolution for " << x << ": " << newthon_result << "\n\n\n";
}