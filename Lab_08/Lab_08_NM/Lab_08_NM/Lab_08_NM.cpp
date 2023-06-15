#include <iostream>
#include "CInterpolation.h"

int main()
{
	const size_t m_size{ 10 };
	double m_x[m_size]{ 0.0, 0.1, 0.2, 0.3, 0.4, 0.5, 0.6, 0.7, 0.8, 0.9 };
	double m_y[m_size]{1.758203, 1.738744, 1.718369, 1.697320, 1.675834, 1.654140, 1.632460, 1.611005, 1.589975, 1.569559 };
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