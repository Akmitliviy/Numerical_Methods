#include <iostream>
#include "Header.h"

using namespace std;

int main()
{
	const size_t size{ 3 };
	//ldouble matrix[size][size] = { { 24.67, 3.24,  5.45, 4.13},
	//						{ 4.46,  34.86,  3.12, -2.43},
	//						{ 3.87,  6.54,  45.44, 3.45},
	//						{ 2.45,  4.25,  5.45, 32.72} };

	//vector<ldouble> B{ 80.41, 85.44, 187.84, 152.86 };
	ldouble matrix[size][size] = { { 4, -9,  2},
							{ 2,  -4,  4},
							{ -1,  2,  2}};

	vector<ldouble> B{ 2, 3, 1};

	SystemSolver ss(matrix, B);

	vector<ldouble> result = ss.Gauss();

	cout << "Roots by Gauss are: " << endl << endl;
	for (int i = 0; i < result.size(); i++) {
		cout << "Root №" << i + 1 << ":   " << result[i] << endl;
	}
	cout << endl << endl << endl;

	result = ss.LU();

	cout << "Roots by LU are: " << endl << endl;
	for (int i = 0; i < result.size(); i++) {
		cout << "Root №" << i + 1 << ":   " << result[i] << endl;
	}
	cout << endl << endl << endl;

	cout << "Accuracy of the solution of the system: " << endl << endl << "method result \t free term" << endl;

	ldouble sum{ 0 };
	for (int i = 0; i < size; i++) {
		for (int j = 0; j < size; j++) {
			sum += matrix[i][j] * result[j];
		}

		cout << " " << sum << "\t\t  " << B[i] << endl;
		sum = 0;
	}



	return 0;
}