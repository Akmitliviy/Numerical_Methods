#pragma once

#include <iostream>
#include <vector>
#include <string>
#include <cmath>

using namespace std;

typedef long double ldouble;

class SystemSolver_2 {
public:
	SystemSolver_2() = delete;

	template <class T>
	SystemSolver_2(const T matrix, const size_t matrix_size, const vector<ldouble> free_terms);
	template <class T>
	SystemSolver_2(const T matrix, const size_t matrix_size, const vector<ldouble> free_terms, const ldouble epsilon);

	vector<ldouble> Jacobi();
	vector<ldouble> Seidel();

private:
	vector<vector<ldouble>> m_matrix;
	vector<ldouble> m_free_terms;
	size_t m_matrix_size;
	bool m_is_roots_found;
	ldouble m_epsilon;

	template <typename T>
	vector<vector<ldouble>> CopyMatrix(const T matrix, const size_t size);

	bool IsMatrixConvergent() const;
	void DivideByMaxElement();
	void SetHollowMatrix(vector<vector<ldouble>>& hollow_matrix, vector<ldouble>& new_free_terms) const;
	void CheckIfRootsFound(const vector<ldouble> roots, const vector<ldouble> previous_roots);
	vector<ldouble> FindCloserJacobi(const vector<vector<ldouble>> hollow_matrix, const vector<ldouble> new_free_terms, vector<ldouble> previous_roots);
	vector<ldouble> FindCloserSeidel(const vector<vector<ldouble>> hollow_matrix, const vector<ldouble> new_free_terms, vector<ldouble> previous_roots);

};

template <class T>
SystemSolver_2::SystemSolver_2(const T matrix, const size_t matrix_size, const vector<ldouble> free_terms) {
	m_matrix = CopyMatrix(matrix, matrix_size);
	m_free_terms = free_terms;
	m_matrix_size = matrix_size;
	m_is_roots_found = false;
	m_epsilon = 0.001;
}
template <class T>
SystemSolver_2::SystemSolver_2(const T matrix, const size_t matrix_size, const vector<ldouble> free_terms, const ldouble epsilon) {
	m_matrix = CopyMatrix(matrix, matrix_size);
	m_free_terms = free_terms;
	m_matrix_size = matrix_size;
	m_is_roots_found = false;
	m_epsilon = epsilon;
}

template <typename T>
vector<vector<ldouble>> SystemSolver_2::CopyMatrix(const T matrix, const size_t size) {
	vector<vector<ldouble>> new_vector(size, vector<ldouble>(size));

	do {
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