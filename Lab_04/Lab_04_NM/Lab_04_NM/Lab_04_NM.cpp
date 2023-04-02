#include <iostream>
#include "Header.h"

using namespace std;

int main()
{
	double matrix[3][3]{{ 2, 1, 1},
						{ 4, 1, 0},
						{-2, 2, 1}};

	vector<ldouble> B{ 1, -2, 7 };

	SystemSolver ss(matrix, B);

	vector<ldouble> result = ss.Gauss();

	cout << "Roots are: ";
	for (int i = 0; i < result.size(); i++) {
		cout << result[i] << "   ";
	}
	cout << endl << endl;

	return 0;
}