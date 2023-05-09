#include "LeastSquares.h"

// Гадаю, методи досить тривіальні і пояснення не потребують

vector<vector<double>> LeastSquares::TranspondMatrix(const vector<vector<double>> matrix) const {
	vector<vector<double>> transponded(matrix[0].size(), vector<double>(matrix.size()));

	for (int i = 0; i < matrix[0].size(); i++) {
		for (int j = 0; j < matrix.size(); j++) {
			transponded[i][j] = matrix[j][i];
		}
	}

	return transponded;
}

vector<double> LeastSquares::MultiplyMatrixAndColumn(const vector<vector<double>> matrix, const vector<double> column) const {
	vector<double> local_column(column.size());

	double sum = 0;
	for (int i = 0; i < matrix.size(); i++) {
		for (int j = 0; j < matrix[0].size(); j++) {
			local_column[i] += matrix[i][j] * column[j];
		}
	}

	return local_column;
}

double LeastSquares::FindDeterminant(const vector<vector<double>> matrix) const {

	int index = 0;
	size_t matrix_size = matrix.size();

	if (matrix.size() == 1)
		return matrix[0][0];

	vector<vector<double>> smaller_matrix(matrix_size - 1, vector<double>(matrix_size - 1));

	double determinant = 0;
	int column = 0;
	bool wrong_k_found = false;

	for (int i = 0; i < matrix_size; i++)
	{
		for (int j = 1; j < matrix_size; j++) {
			for (int k = 0; k < matrix_size; k++) {
				if (k == index) {
					wrong_k_found = true;
					continue;
				}

				if (wrong_k_found)
					column = k - 1;
				else
					column = k;

				smaller_matrix[j - 1][column] = matrix[j][k];
			}
			wrong_k_found = false;
		}

		determinant += pow(-1, i) * matrix[0][i] * FindDeterminant(smaller_matrix);
		index++;
	}

	return determinant;
}

vector<vector<double>> LeastSquares::MultiplyMatrixes(const vector<vector<double>> first_matrix, const vector<vector<double>> second_matrix) const {
	vector<vector<double>> multiplication(first_matrix.size(), vector<double>(second_matrix[0].size()));

	for (int i = 0; i < first_matrix.size(); i++) {
		for (int j = 0; j < second_matrix[0].size(); j++) {
			multiplication[i][j] = 0;
			for (int k = 0; k < first_matrix[0].size(); k++) {
				multiplication[i][j] += first_matrix[i][k] * second_matrix[k][j];
			}
		}
	}

	return multiplication;
}

vector<vector<double>> LeastSquares::SplitMatrixIntoToTransponded(const vector<vector<double>> matrix) const {
	vector<vector<double>> square_matrix(matrix.size(), vector<double>(matrix.size()));

	for (int i = 0; i < matrix.size(); i++) {

		square_matrix[i][i] = matrix[i][i];
		for (int j = 0; j < i; j++) {
			square_matrix[i][i] -= pow(square_matrix[j][i], 2);
		}
		square_matrix[i][i] = sqrt(square_matrix[i][i]);

		for (int j = i + 1; j < matrix.size(); j++) {

			square_matrix[i][j] = matrix[i][j];
			for (int k = 0; k < i; k++) {
				square_matrix[i][j] -= square_matrix[k][i] * square_matrix[k][j];
			}
			square_matrix[i][j] /= square_matrix[i][i];
		}
	}

	return square_matrix;
}

vector<double> LeastSquares::GetY(const vector<vector<double>> matrix, const vector<double> new_free_terms) const {
	vector<double> y(matrix.size());

	for (int i = 0; i < matrix.size(); i++) {
		for (int k = 0; k < i; k++)
			y[i] += y[k] * matrix[i][k];

		y[i] = (new_free_terms[i] - y[i]) / matrix[i][i];
	}

	return y;
}

vector<double> LeastSquares::GetX(const vector<vector<double>> matrix, const vector<double> y) const {
	vector<double> x(matrix.size());

	for (int i = matrix.size() - 1; i >= 0; i--) {
		for (int k = matrix.size() - 1; k > i; k--)
			x[i] += x[k] * matrix[i][k];

		x[i] = (y[i] - x[i]) / matrix[i][i];
	}

	return x;
}

vector<double> LeastSquares::Find() {

	// Тут просто послідовна реалізація алгоритму з методички
	// Якщо що, знову ж таки, мені легше то буде пояснити по телефону
	vector<vector<double>> transponded_matrix = TranspondMatrix(m_matrix);
	vector<vector<double>> multiplied = MultiplyMatrixes(transponded_matrix, m_matrix);
	vector<double> new_free_terms = MultiplyMatrixAndColumn(transponded_matrix, m_free_terms);

	if (!FindDeterminant(multiplied)) {
		cout << "Determinant is equal zero, try another method";
		return vector<double>(multiplied.size());
	}

	vector<vector<double>> splited_upper = SplitMatrixIntoToTransponded(multiplied);
	vector<vector<double>> splited_lower = TranspondMatrix(splited_upper);

	vector<double> y = GetY(splited_lower, new_free_terms);
	vector<double> x = GetX(splited_upper, y);

	return x;
}
