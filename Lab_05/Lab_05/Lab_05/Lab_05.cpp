#include <iostream>
#include "SystemSolver_2_Header.h"

int main()
{

	const size_t size{ 4 };
	ldouble matrix[size][size] = { { 24.67, 3.24,  5.45, 4.13},
							{ 4.46,  34.86,  3.12, -2.43},
							{ 3.87,  6.54,  45.44, 3.45},
							{ 2.45,  4.25,  5.45, 32.72} };

	vector<ldouble> B{ 80.41, 85.44, 187.84, 152.86 };

	const ldouble epsilon = 0.0001;

	SystemSolver_2 solver(matrix, size, B, epsilon);

	cout << "Jacobi" << endl << endl;
	cout << "x1\t\tx2\t\tx3\t\tx4\n";
	vector<ldouble> result_jacobi = solver.Jacobi();
	cout << "Final result:\n";
	for (int i = 0; i < result_jacobi.size(); i++) {
		cout << "x" << i + 1 << ": " << result_jacobi[i] << endl;
	}
	cout << endl << endl;

	cout << "Seidel" << endl << endl;
	cout << "x1\t\tx2\t\tx3\t\tx4\n";
	vector<ldouble> result_seidel = solver.Seidel();
	cout << "Final result:\n";
	for (int i = 0; i < result_seidel.size(); i++) {
		cout << "x" << i + 1 << ": " << result_seidel[i] << endl;
	}
	cout << endl << endl;
}