#pragma once
#include <iostream>
#include <cmath>
#include <vector>

using namespace std;

typedef long double ldouble;

class SystemSolver {
private:
	vector<ldouble> B;
	vector<vector<ldouble>> matrix;

	template <typename T>
	vector<vector<ldouble>> CopyMatrix(const T matrix, const size_t size);
	template <typename T>
	size_t GetSize(const T matrix) const;
	vector<vector<ldouble>> CreateMatrix(const size_t size) const;
	ldouble FindDeterminant(const vector<vector<ldouble>> matrix) const;
	void GaussItself(vector<vector<ldouble>>& matrix, vector<ldouble>& B);

public:

	template <typename T>
	SystemSolver(T matrix, vector<ldouble> B);

	vector<ldouble> Gauss();
	//vector<ldouble> LU();

};

template <typename T>
size_t SystemSolver::GetSize(const T matrix) const {
	size_t result{ 0 };
	if(matrix != nullptr)
		result = sizeof(matrix[0]) / sizeof(matrix[0][0]);
	
	return result;
}

template <typename T>
vector<vector<ldouble>> SystemSolver::CopyMatrix(const T matrix, const size_t size) {
	vector<vector<ldouble>> new_vector(size, vector<ldouble>(size));
	
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
SystemSolver::SystemSolver(T matrix, vector<ldouble> B) {
	this->matrix = CopyMatrix(matrix, GetSize(matrix));
	this->B = B;
}
