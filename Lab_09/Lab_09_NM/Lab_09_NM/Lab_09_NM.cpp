#include <iostream>
#include "LeastSquares.h"

int main()
{
	vector<double> x{ 0.0, 0.1, 0.2, 0.3, 0.4, 0.5, 0.6, 0.7, 0.8, 0.9 };
	vector<double> y{ 1.758203, 1.738744, 1.718369, 1.697320, 1.675834, 1.654140, 1.632460, 1.611005, 1.589975, 1.569559 };

	vector<double> func_0 = Find(x, y, 1);
	vector<double> func_1 = Find(x, y, 2);
	vector<double> func_2 = Find(x, y, 3);

	double difference{ 0 };

	cout << "Linear:\t";
	for(int i = 0; i < func_0.size(); i++)
	{
		if (func_0[i] >= 0)
			cout << "+";
		cout << func_0[i] << "x^" << i << " ";

		difference += func_0[i] * pow(x[3], i);
	}
	difference -= y[3];
	cout << "\n\nPrecision is: " << fabs(difference) << "\n\n\n\n";

	difference = 0;
	cout << "Quadratic:\t";
	for(int i = 0; i < func_1.size(); i++)
	{
		if (func_1[i] >= 0)
			cout << "+";
		cout << func_1[i] << "x^" << i << " ";

		difference += func_1[i] * pow(x[3], i);
	}
	difference -= y[3];
	cout << "\n\nPrecision is: " << fabs(difference) << "\n\n\n\n";

	difference = 0;
	cout << "Сubic:\t";
	for(int i = 0; i < func_2.size(); i++)
	{
		if (func_2[i] >= 0)
			cout << "+";
		cout << func_2[i] << "x^" << i << " ";

		difference += func_2[i] * pow(x[3], i);
	}
	difference -= y[3];
	cout << "\n\nPrecision is: " << fabs(difference) << "\n\n\n\n";
}