#include <iostream>
#include "..\Methods_Lib\MethodsHeader.h"

int main() {
	ldouble matrix[3][3] = {{ 1, -1,  1},
							{ 2,  1,  1},
							{ -1, -2, 2}};

	ldouble free_terms[3] = {4, 7, -1};
	
	FunctionHolder<ldouble(*)[3]> Fh(matrix, free_terms, 3);
	SColumn kramer = Fh.Kramer();
	SColumn matrix_method = Fh.MatrixMethod();

	cout << "Kramer: ";
	for (int i = 0; i < kramer.number_of_values; i++) {
		cout << kramer.values[i] << "\t";
	}
	cout << endl << endl;


	cout << "Matrix Method: ";
	for (int i = 0; i < matrix_method.number_of_values; i++) {
		cout << matrix_method.values[i] << "\t";
	}
	cout << endl << endl;

	return 0;
}


