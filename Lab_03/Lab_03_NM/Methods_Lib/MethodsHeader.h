#pragma once
#include <cmath>

using namespace std;

typedef long double ldouble;

struct SMatrix {
	ldouble** matrix;
	int size;
};

struct SColumn {
	ldouble* values;
	int number_of_values;
};

template <class T>
class FunctionHolder {
private:
	SMatrix matrix;
	SColumn free_term;
	SColumn result;

	ldouble FindDeterminant(const SMatrix matrix) const {
		int index = 0;
		if (matrix.size == 1)
			return matrix.matrix[0][0];

		SMatrix smaller_matrix = GetNewSMatrix(matrix.size - 1);

		ldouble determinant = 0;
		int column = 0;
		bool wrong_k_found = false;

		for (int i = 0; i < matrix.size; i++)
		{
			for (int j = 1; j < matrix.size; j++) {
				for (int k = 0; k < matrix.size; k++) {
					if (k == index) {
						wrong_k_found = true;
						continue;
					}

					if (wrong_k_found)
						column = k - 1;
					else
						column = k;

					smaller_matrix.matrix[j - 1][column] = matrix.matrix[j][k];
				}
				wrong_k_found = false;
			}

			determinant += pow(-1, i) * matrix.matrix[0][i] * FindDeterminant(smaller_matrix);
			index++;
		}

		return determinant;
	}
	ldouble FindDeterminant(const SMatrix matrix, int row, int column) const {
		if (matrix.size == 1)
			return matrix.matrix[0][0];

		SMatrix smaller_matrix = GetNewSMatrix(matrix.size - 1);

		ldouble determinant = 0;
		int row_index = 0, column_index = 0;
		bool wrong_i_found = false, wrong_j_found = false;

		for (int i = 0; i < matrix.size; i++) {
			if (i == row) {
				wrong_i_found = true;
				continue;
			}
			if (wrong_i_found)
				row_index = i - 1;
			else
				row_index = i;

			for (int j = 0; j < matrix.size; j++) {
				if (j == column) {
					wrong_j_found = true;
					continue;
				}
				if (wrong_j_found)
					column_index = j - 1;
				else
					column_index = j;

				smaller_matrix.matrix[row_index][column_index] = matrix.matrix[i][j];
			}
			wrong_j_found = false;
		}

		determinant = pow(-1, row + column) * FindDeterminant(smaller_matrix);
		if (fabs(determinant) <= 1e-13)
			determinant = 0;
		return determinant;
	}
	ldouble FindDeterminantKramer(const SMatrix& matrix, const SColumn& column, const  int position) const {
		SMatrix current = CopySMatrix(matrix);

		for (int i = 0; i < current.size; i++) {
			current.matrix[i][position] = column.values[i];
		}

		return FindDeterminant(current);
	}
	SMatrix FindReversedMatrix(const SMatrix& matrix) const {
		SMatrix local_matrix = { nullptr, 0 };
		ldouble determinant = FindDeterminant(matrix);

		if (fabs(determinant) <= 1e-13) {
			cout << "Reversed matrix does not exist. Try another method" << endl << endl;
		}
		else {
			local_matrix = GetNewSMatrix(matrix.size);

			for (int i = 0; i < matrix.size; i++) {
				for (int j = 0; j < matrix.size; j++) {
					local_matrix.matrix[j][i] = FindDeterminant(matrix, i, j) * (1 / determinant);
				}
			}
		}
		return local_matrix;

	}
	SColumn FindMultiplicationOfMatrixAndColumn(const SMatrix& matrix, const SColumn& column) const {
		SColumn local_column = { nullptr, column.number_of_values };
		local_column.values = new ldouble[local_column.number_of_values];
		ldouble sum = 0;
		for (int i = 0; i < matrix.size; i++) {
			for (int j = 0; j < matrix.size; j++) {
				sum += matrix.matrix[i][j] * column.values[j];
			}
			local_column.values[i] = sum;
			sum = 0;
		}

		return local_column;
	}
	SMatrix AssignSMatrix(const T matrix, int size) {
		SMatrix values = { nullptr, 0 };
		bool is_allocated = true;

		ldouble** local_matrix = new ldouble * [size];
		if (local_matrix) {
			for (int i = 0; i < size; i++) {
				if (local_matrix + i) {
					local_matrix[i] = new ldouble[size];
					for (int j = 0; j < size; j++)
						local_matrix[i][j] = matrix[i][j];
				}
				else {
					is_allocated = false;
				}
			}
		}
		else {
			is_allocated = false;
		}

		if (is_allocated) {
			values.matrix = local_matrix;
			values.size = size;
		}
		return values;
	}
	SMatrix GetNewSMatrix(const int size) const {
		SMatrix values = { nullptr, 0 };
		bool is_allocated = true;

		ldouble** matrix = new ldouble * [size];
		if (matrix) {
			for (int i = 0; i < size; i++) {
				if (matrix + i) {
					matrix[i] = new ldouble[size];
				}
				else {
					is_allocated = false;
				}
			}
		}
		else {
			is_allocated = false;
		}

		if (is_allocated) {
			values.matrix = matrix;
			values.size = size;
		}
		return values;
	}
	SMatrix CopySMatrix(const SMatrix& arr) const {
		SMatrix values = { nullptr, 0 };
		bool is_allocated = true;

		ldouble** matrix = new ldouble * [arr.size];
		if (matrix) {
			for (int i = 0; i < arr.size; i++) {
				if (matrix + i) {
					matrix[i] = new ldouble[arr.size];
					for (int j = 0; j < arr.size; j++)
						matrix[i][j] = arr.matrix[i][j];
				}
				else {
					is_allocated = false;
				}
			}
		}
		else {
			is_allocated = false;
		}

		if (is_allocated) {
			values.matrix = matrix;
			values.size = arr.size;
		}
		return values;
	}
public:
	FunctionHolder(const T matrix, const ldouble* free_term, const int size) {
		this->matrix = AssignSMatrix(matrix, size);

		this->free_term.values = new ldouble[size];
		this->free_term.number_of_values = size;

		for (int i = 0; i < size; i++)
			this->free_term.values[i] = free_term[i];

		result.number_of_values = size;
		result.values = new ldouble[size];
	}
	FunctionHolder(const FunctionHolder& other) {
		this->matrix = AssignSMatrix(other.matrix.matrix, other.matrix.size);

		this->free_term.number_of_values = other.free_term.number_of_values;
		this->free_term.values = new ldouble[this->free_term.number_of_values];

		for (int i = 0; i < this->free_term.number_of_values; i++)
			this->free_term.values[i] = other.free_term.values[i];

		result.number_of_values = this->matrix.size;
		result.values = new ldouble[size];
	}
	~FunctionHolder() {
		delete[] free_term.values;
		delete[] result.values;

		for (int i = 0; i < matrix.size; i++)
			delete[] matrix.matrix[i];
		delete[] matrix.matrix;
	}

	void SetSMatrix(const T matrix, const int size) {
		FunctionHolder(matrix, size);
	}
	SMatrix GetSMatrix() const {
		return matrix;
	}

	SColumn Kramer() {

		ldouble main_determinant = 0;
		ldouble* var_determinants = new ldouble[free_term.number_of_values];

		if (!matrix.matrix || !var_determinants) {
			cout << "Set a matrix!" << endl << endl;

		}
		else {

			main_determinant = FindDeterminant(matrix);

			for (int i = 0; i < free_term.number_of_values; i++) {
				var_determinants[i] = FindDeterminantKramer(matrix, free_term, i);
			}


			if (main_determinant == 0) {
				bool var_are_all_zeros = true;
				for (int i = 0; i < free_term.number_of_values; i++) {
					if (var_determinants[i] != 0) {
						var_are_all_zeros = false;
						break;
					}
				}
				if (var_are_all_zeros) {
					cout << "System is undefined. Try to use other method" << endl << endl;
					result.number_of_values = 0;
					delete[] result.values;
					result.values = nullptr;
				}
				else {
					cout << "System is incompatible." << endl << endl;
					result.number_of_values = 0;
					delete[] result.values;
					result.values = nullptr;
				}
			}
			else {
				for (int i = 0; i < free_term.number_of_values; i++)
					result.values[i] = var_determinants[i] / main_determinant;
			}

			return result;
		}
	}
	SColumn MatrixMethod() {
		SMatrix reversed = FindReversedMatrix(matrix);

		if (reversed.matrix) {
			result = FindMultiplicationOfMatrixAndColumn(reversed, free_term);
			
			for (int i = 0; i < result.number_of_values; i++)
				if (fabs(result.values[i]) <= 1e-13)
					result.values[i] = 0;
		}
		else {
			delete[] result.values;
			result.values = nullptr;
			result.number_of_values = 0;
		}

		return result;

	}


};