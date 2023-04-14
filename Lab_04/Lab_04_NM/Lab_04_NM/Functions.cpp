#include "Header.h"

vector<vector<ldouble>> SystemSolver::CreateMatrix(const size_t size) const{
	vector<vector<ldouble>> new_matrix(size, vector<ldouble>(size));

	return new_matrix;
}
ldouble SystemSolver::FindDeterminant(const vector<vector<ldouble>> matrix) const {

	int index = 0;
	size_t matrix_size = matrix.size();

	if (matrix.size() == 1)
		return matrix[0][0];

	vector<vector<ldouble>> smaller_matrix = CreateMatrix(matrix_size - 1);

	ldouble determinant = 0;
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

vector<ldouble> SystemSolver::Gauss() {
	vector <ldouble> result(matrix[0].size());
	vector<vector<ldouble>> inside_matrix = CopyMatrix(this->matrix, matrix[0].size());
	vector<ldouble> inside_B = this->B;

	if (FindDeterminant(this->matrix) == 0) {
		cout << "Determinant is equal zero";
		return result;
	}

	GaussItself(inside_matrix, inside_B);

	for (int i = inside_matrix[0].size() - 1; i >= 0; i--) {
		result[i] = inside_B[i];
		for (int j = inside_matrix[0].size() - 1; j > i; j--) {
			result[i] -= result[j] * inside_matrix[i][j];
		}
		result[i] /= inside_matrix[i][i];
	}

	return result;

}
void SystemSolver::GaussItself(vector<vector<ldouble>>& matrix, vector<ldouble>& B) {
	int index_of_row_with_max_element{ 0 };
	ldouble max_element{ 0 };
	size_t size_of_matrix = matrix.size();
	while (size_of_matrix > 1) {
		size_t current_column = matrix[0].size() - size_of_matrix;
		for (int i = current_column; i < matrix[0].size(); i++) {
			if (fabs(matrix[i][current_column]) > max_element) {
				index_of_row_with_max_element = i;
				max_element = matrix[i][current_column];
			}
		}

		if (fabs(max_element) > 1e-13) {
			if (index_of_row_with_max_element != current_column) {
				vector<ldouble> temp_row(size_of_matrix);
				ldouble temp_B = B[index_of_row_with_max_element];
				B[index_of_row_with_max_element] = B[current_column];
				B[current_column] = temp_B;

				for (int i = current_column; i < size_of_matrix; i++) {
					temp_row[i] = matrix[index_of_row_with_max_element][i];
					matrix[index_of_row_with_max_element][i] = matrix[current_column][i];
					matrix[current_column][i] = temp_row[i];
				}
			}

			for (int i = current_column + 1; i < matrix.size(); i++) {
				ldouble multiplier = matrix[i][current_column] / matrix[current_column][current_column];

				matrix[i][current_column] = 0;
				for (int j = current_column + 1; j < matrix.size(); j++) {
					matrix[i][j] -= matrix[current_column][j] * multiplier;
				}
				B[i] -= B[current_column] * multiplier;
			}
		}

		index_of_row_with_max_element = 0;
		max_element = 0;
		size_of_matrix--;
	}
}
vector<ldouble> SystemSolver::LU() {
	size_t size = matrix[0].size();

	vector<vector<ldouble>> l(size, vector<ldouble>(size));
	vector<vector<ldouble>> u(size, vector<ldouble>(size));


	for (int i = 0; i < size; i++) {
		for (int j = 0; j < size; j++) {
			l[i][j] = 0;
			u[i][j] = (i == j) ? 1 : 0;
		}
	}

	for (int i = 0; i < size; i++)
		l[i][0] = matrix[i][0];

	for (int index = 1, switcher = 0; index < size; index++, switcher++) {
		if (switcher % 2) {
			for (int i = index; i < size; i++) {
				for (int k = 0; k < index; k++)
					l[i][index] += l[i][k] * u[k][index];
				l[i][index] = matrix[i][index] - l[i][index];
			}
		}
		else {
			for (int i = index - 1, j = index; j < size; j++) {
				for (int k = 0; k < index - 1; k++) {
					u[i][j] += l[i][k] * u[k][j];
				}
				u[i][j] = (matrix[i][j] - u[i][j]) / l[i][i];
			}
			index--;
		}
	}

	Show(l, string("L"));
	Show(u, string("U"));

	vector<ldouble> y(size);
	for (int i = 0; i < size; i++)
		y[i] = 0;

	for (int i = 0; i < size; i++) {
		for (int k = 0; k < i; k++)
			y[i] += y[k] * l[i][k];

		y[i] = (B[i] - y[i]) / l[i][i];
	}

	cout << "Free term is: " << endl << endl;
	for (int i = 0; i < size; i++)
		cout << B[i] << "\t";
	cout << endl << endl;

	cout << "Y is: " << endl << endl;
	for (int i = 0; i < size; i++)
		cout << y[i] << "\t";
	cout << endl << endl;

	vector<ldouble> result(size);
	for (int i = 0; i < size; i++)
		result[i] = 0;

	for (int i = size - 1; i >=0; i--) {
		for (int k = size - 1; k > i; k--)
			result[i] += result[k] * u[i][k];

		result[i] = (y[i] - result[i]) / u[i][i];
	}

	return result;
}


//////////

void Show(vector<vector<ldouble>> matrix, string name) {
	cout << name << " matrix: " << endl << endl;
	for (int i = 0; i < matrix.size(); i++) {
		for (int j = 0; j < matrix.size(); j++) {
			cout << matrix[i][j] << "\t";
		}
		cout << endl;
	}
	cout << endl << endl;
}