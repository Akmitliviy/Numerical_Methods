#include <iostream>
#include "LeastSquares.h"

int main()
{
	vector<double> x{ 0.0, 0.1, 0.2, 0.3, 0.4, 0.5, 0.6, 0.7, 0.8, 0.9};
	vector<double> y{ 0.979498, 1.060831, 1.138837, 1.213312, 1.284076, 1.350965, 1.413842, 1.472590, 1.527116, 1.577391 };

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