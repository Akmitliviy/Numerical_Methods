#include "LeastSquares.h"
#include "..//Methods_Lib/Methods_Lib_Header.h"

vector<double> Find(vector<double> x, vector<double> y, unsigned int m) {
	
	vector<double> working_x(x.size());
	vector<double> coefficients;
	vector<vector<double>> matrix_coefficients(m + 1, vector<double>(m + 1));
	vector<double> free_terms;

	for (int i = 0; i <= m * 2; i++) {

		copy(x.begin(), x.end(), working_x.begin());

		for (double& element : working_x) {
			element = pow(element, i); 
		}

		coefficients.push_back(accumulate(working_x.begin(), working_x.end(), 0.0));

		if (i <= m) {
			free_terms.push_back(inner_product(y.begin(), y.end(), working_x.begin(), 0.0));
		}
	}

	for (int i = 0; i <= m; i++) {
		copy(coefficients.begin() + i, coefficients.begin() + m + 1 + i, matrix_coefficients[i].begin());
	}

	SystemSolver holder(matrix_coefficients, free_terms);

	return  holder.LU();
}
