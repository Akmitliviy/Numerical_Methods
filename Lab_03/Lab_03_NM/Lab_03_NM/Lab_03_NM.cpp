#include <iostream>
#include "..\Methods_Lib\MethodsHeader.h"

int main() {
	const size_t size{ 4 };

	ldouble matrix[size][size] = {{ 24.67, 3.24,  5.45, 4.13},
							{ 4.46,  34.86,  3.12, -2.43},
							{ 3.87,  6.54,  45.44, 3.45},
							{ 2.45,  4.25,  5.45, 32.72}};

	ldouble free_terms[size] = {80.41, 85.44, 187.84, 152.86};
	
	FunctionHolder<ldouble(*)[size]> Fh(matrix, free_terms, size);
	SColumn kramer = Fh.Kramer();
	SColumn matrix_method = Fh.MatrixMethod();

	cout << "Kramer: " << endl << endl;
	for (int i = 0; i < kramer.number_of_values; i++) {
		cout << "Root №" << i + 1 << ":   " << kramer.values[i] << endl;
	}
	cout << endl << endl << endl;

	cout << "Matrix Method: " << endl << endl;
	for (int i = 0; i < matrix_method.number_of_values; i++) {
		cout << "Root №" << i + 1 << ":   " << matrix_method.values[i] << endl;
	}
	cout << endl << endl << endl;

	cout << "Accuracy of the solution of the system: " << endl << endl << "method result \t free term" << endl;
	
	ldouble sum{ 0 };
	for (int i = 0; i < size; i++) {
		for (int j = 0; j < size; j++) {
			sum += matrix[i][j] * kramer.values[j];
		}

		cout << " " << sum << "\t\t  " << free_terms[i] << endl;
		sum = 0;
	}

	return 0;
}


