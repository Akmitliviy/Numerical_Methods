#include "LeastSquares.h"

int main()
{
	const double result_accuracy = 0.0001;
	const size_t num_of_equations{ 5 };
	const size_t num_of_variables{ 3 };
	double matrix[num_of_equations][num_of_variables] ={{ 1,  3, -2},
														{-1,  2,  1},
														{ 3, -2, -2},
														{ 3,  1, -3},
														{ 1, -1, -7} };

	vector<double> free_terms{ -5, 1, -5, 1, 5 };



	LeastSquares ls(matrix, num_of_variables, num_of_equations, free_terms);
	vector<double> result = ls.Find();

	cout << "Initial matrix:\n\n";
	for (int i = 0; i < num_of_equations; i++) {
		for (int j = 0; j < num_of_variables; j++) {
			if (matrix[i][j] >= 0)
				cout << " ";
			cout << matrix[i][j] << "\t";
		}
		cout << "\t";
		if (free_terms[i] >= 0)
			cout << " ";
		cout << free_terms[i] << endl;
	}
	cout << "\n\n";

	cout << "Result:\n\n";
	for (int i = 0; i < result.size(); i++) {
		cout << "x" << i + 1 << ": " << result[i] << "\n";
	}
	cout << endl;
}