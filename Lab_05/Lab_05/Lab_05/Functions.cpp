#include "SystemSolver_2_Header.h"

vector<ldouble> SystemSolver_2::Jacobi() {

	if (!IsMatrixConvergent())
		DivideByMaxElement();

	vector<vector<ldouble>> hollow_matrix(m_matrix_size, vector<ldouble>(m_matrix_size));
	vector<ldouble> new_free_terms(m_matrix_size);

	SetHollowMatrix(hollow_matrix, new_free_terms);

	vector<ldouble> roots(new_free_terms);
	do {
		roots = FindCloserJacobi(hollow_matrix, new_free_terms, roots);
	} while (!m_is_roots_found);

	return roots;
}

vector<ldouble> SystemSolver_2::Seidel() {

	if (!IsMatrixConvergent())
		DivideByMaxElement();

	vector<vector<ldouble>> hollow_matrix(m_matrix_size, vector<ldouble>(m_matrix_size));
	vector<ldouble> new_free_terms(m_matrix_size);

	SetHollowMatrix(hollow_matrix, new_free_terms);

	vector<ldouble> roots(new_free_terms);
	do {
		roots = FindCloserSeidel(hollow_matrix, new_free_terms, roots);
	} while (!m_is_roots_found);

	return roots;
}

bool SystemSolver_2::IsMatrixConvergent() const {


	//Sum of elements of each row less than 1:
	ldouble sum_of_row{ 0 };
	bool is_all_rows_less_than_1{true};
	for (int i = 0; i < m_matrix_size; i++) {
		for (int j = 0; j < m_matrix_size; j++) {
			sum_of_row += m_matrix[i][j];
		}

		if (sum_of_row > 1) {
			is_all_rows_less_than_1 = false;
			break;
		}

		sum_of_row = 0;
	}

	if (is_all_rows_less_than_1)
		return true;

	//Sum of elements of each column less than 1:
	ldouble sum_of_column{ 0 };
	bool is_all_columns_less_than_1{true};
	for (int i = 0; i < m_matrix_size; i++) {
		for (int j = 0; j < m_matrix_size; j++) {
			sum_of_column += m_matrix[j][i];
		}

		if (sum_of_column > 1) {
			is_all_columns_less_than_1 = false;
			break;
		}

		sum_of_column = 0;
	}

	if (is_all_columns_less_than_1)
		return true;

	//Sum of elements of each row less than diagonal element:
	ldouble sum_of_incompete_row{ 0 };
	bool is_all_rows_less_than_diagonal{ true };
	for (int i = 0; i < m_matrix_size; i++) {
		for (int j = 0; j < m_matrix_size; j++) {
			if (i != j)
				sum_of_incompete_row += m_matrix[i][j];
		}

		if (sum_of_incompete_row > m_matrix[i][i]) {
			is_all_rows_less_than_diagonal = false;
			break;
		}

		sum_of_incompete_row = 0;
	}

	if (is_all_rows_less_than_diagonal)
		return true;



	//Sum of elements of each column less than diagonal element:
	ldouble sum_of_incompete_column{ 0 };
	bool is_all_columns_less_than_diagonal{ true };
	for (int i = 0; i < m_matrix_size; i++) {
		for (int j = 0; j < m_matrix_size; j++) {
			if (i != j)
				sum_of_incompete_column += m_matrix[i][j];
		}

		if (sum_of_incompete_column > m_matrix[i][i]) {
			is_all_columns_less_than_diagonal = false;
			break;
		}

		sum_of_incompete_column = 0;
	}

	if (is_all_columns_less_than_diagonal)
		return true;


	return false;
}

void SystemSolver_2::DivideByMaxElement() {

	ldouble max_element{ 0 };
	for (int i = 0; i < m_matrix_size; i++) {
		for (int j = 0; j < m_matrix_size; j++) {
			if (m_matrix[i][j] > max_element)
				max_element = m_matrix[i][j];
		}
	}

	max_element *= m_matrix_size + 1;

	for (int i = 0; i < m_matrix_size; i++) {
		for (int j = 0; j < m_matrix_size; j++) {
			m_matrix[i][j] /= max_element;
		}
		m_free_terms[i] /= max_element;
	}

}

void SystemSolver_2::SetHollowMatrix(vector<vector<ldouble>>& hollow_matrix, vector<ldouble>& new_free_terms) const {

	for (int i = 0; i < m_matrix_size; i++) {
		new_free_terms[i] = m_free_terms[i] / m_matrix[i][i];
		hollow_matrix[i][i] = 0;

		for (int j = 0; j < m_matrix_size; j++) {
			if (i == j)
				continue;

			hollow_matrix[i][j] = -(m_matrix[i][j] / m_matrix[i][i]);
		}
	}
}

vector<ldouble> SystemSolver_2::FindCloserJacobi(
	const vector<vector<ldouble>> hollow_matrix,
	const vector<ldouble> new_free_terms, 
	vector<ldouble> previous_roots) {

	vector<ldouble> roots(m_matrix_size);

	for (int i = 0; i < m_matrix_size; i++) {
		roots[i] = 0;
		for (int j = 0; j < m_matrix_size; j++) {
			roots[i] += hollow_matrix[i][j] * previous_roots[j];
		}
		roots[i] += new_free_terms[i];
	}

	CheckIfRootsFound(roots, previous_roots);

	return roots;
}

vector<ldouble> SystemSolver_2::FindCloserSeidel(
	const vector<vector<ldouble>> hollow_matrix,
	const vector<ldouble> new_free_terms, 
	vector<ldouble> previous_roots) {

	vector<ldouble> roots(m_matrix_size);
	vector<ldouble> previous_roots_copy(previous_roots);

	for (int i = 0; i < m_matrix_size; i++) {
		roots[i] = 0;
		for (int j = 0; j < m_matrix_size; j++) {
			roots[i] += hollow_matrix[i][j] * previous_roots_copy[j];
		}
		roots[i] += new_free_terms[i];
		previous_roots_copy[i] = roots[i];
	}

	CheckIfRootsFound(roots, previous_roots);

	return roots;
}
void SystemSolver_2::CheckIfRootsFound(const vector<ldouble> roots, const vector<ldouble> previous_roots) {


	// first condition
	ldouble random_bullshit{ 0 };
	for (int i = 0; i < m_matrix_size; i++) {
		random_bullshit += pow(roots[i] - previous_roots[i], 2);
	}
	random_bullshit = pow(random_bullshit, 0.5);

	if (random_bullshit < m_epsilon)
		m_is_roots_found = true;


	// second condition
	random_bullshit = 0;
	for (int i = 0; i < m_matrix_size; i++) {
		if (fabs(roots[i] - previous_roots[i]) > random_bullshit)
			random_bullshit = fabs(roots[i] - previous_roots[i]);
	}

	if (random_bullshit < m_epsilon)
		m_is_roots_found = true;

}


