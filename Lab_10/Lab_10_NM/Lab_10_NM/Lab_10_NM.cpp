#include <iostream>
#include "Integration.h"


double f(double x) {
	return pow(x, 3) * sin(x);
}

int main()
{
	double epsilon = 0.001;
	double left_border = numbers::pi / 3.0;
	double right_border = numbers::pi / 2.0;
	unsigned int division = 100;

	Integration integral(left_border, right_border, division, f);

	cout << "Minimal step for epsilon equal " << epsilon << " is: " << integral.FindStep(epsilon) << "\n\n\n\n";

	cout << "Left sum: " << integral.RiemannLeftSum() << "\n\n";
	cout << "Right sum: " << integral.RiemannRightSum() << "\n\n";
	cout << "Middle sum: " << integral.RiemannMiddleSum() << "\n\n\n";
	cout << "Approximational error: " << integral.GetError(e_riemann) << "\n\n\n\n";

	cout << "Trapezoidal sum: " << integral.Trapezoidal() << "\n\n\n";
	cout << "Approximational error: " << integral.GetError(e_trapezoidal) << "\n\n\n\n";

	cout << "Simpson sum: " << integral.Simpson() << "\n\n\n";
	cout << "Approximational error: " << integral.GetError(e_simpson) << "\n\n\n\n";
}

