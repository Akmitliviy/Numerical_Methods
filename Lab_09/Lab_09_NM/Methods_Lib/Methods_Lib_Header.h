#pragma once
#include <iostream>
#include <cmath>
#include <vector>

using namespace std;

class SystemSolver {
private:
	vector<double> B;
	vector<vector<double>> matrix;

	template <typename T>
	vector<vector<double>> CopyMatrix(const T matrix, const size_t size);
	template <typename T>
	size_t GetSize(const T matrix) const;
	vector<vector<double>> CreateMatrix(const size_t size) const;
	double FindDeterminant(const vector<vector<double>> matrix) const;
	void GaussItself(vector<vector<double>>& matrix, vector<double>& B);

public:

	template <typename T>
	SystemSolver(T matrix, vector<double> B);

	SystemSolver(vector<vector<double>> matrix, vector<double> B) {
		this->matrix = matrix;
		this->B = B;
	}

	vector<double> Gauss();
	vector<double> LU();

};

template <typename T>
size_t SystemSolver::GetSize(const T matrix) const {
	size_t result{ 0 };
	if (matrix != nullptr)
		result = sizeof(matrix[0]) / sizeof(matrix[0][0]);

	return result;
}

template <typename T>
vector<vector<double>> SystemSolver::CopyMatrix(const T matrix, const size_t size) {
	vector<vector<double>> new_vector(size, vector<double>(size));

	do {
		new_vector = CreateMatrix(size);

		if (new_vector.empty())
			break;

		for (int i = 0; i < size; i++) {
			for (int j = 0; j < size; j++) {
				new_vector[i][j] = matrix[i][j];
			}
		}



	} while (false);

	return new_vector;
}

template <typename T>
SystemSolver::SystemSolver(T matrix, vector<double> B) {
	this->matrix = CopyMatrix(matrix, GetSize(matrix));
	this->B = B;
}

void Show(vector<vector<double>> matrix, string name);
