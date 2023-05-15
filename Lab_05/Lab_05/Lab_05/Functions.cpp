#include "SystemSolver_2_Header.h"

// Метод Якобі
vector<ldouble> SystemSolver_2::Jacobi() {

	// Якщо матриця така, що процес збіжний - йдемо далі, якщо ні -
	// змінюємо матрицю, щб процес був збіжним і йдемо далі
	if (!IsMatrixConvergent()) 
		DivideByMaxElement();

	// Створюємо каркас для матриці, в якій потім будуть нулі на головній діагоналі
	// і стовпець вільних членів
	vector<vector<ldouble>> hollow_matrix(m_matrix_size, vector<ldouble>(m_matrix_size));
	vector<ldouble> new_free_terms(m_matrix_size);

	//Задаємо цю матрицю і її вільні члени
	SetHollowMatrix(hollow_matrix, new_free_terms);

	//Запускаємо ітераційний процес, поки не знайдемо корені
	vector<ldouble> roots(new_free_terms);
	do {
		roots = FindCloserJacobi(hollow_matrix, new_free_terms, roots);
	} while (!m_is_roots_found);

	m_is_roots_found = false;
	return roots;
}

// Метод Зейделя
vector<ldouble> SystemSolver_2::Seidel() {
	//Тут все те саме окрім..
	if (!IsMatrixConvergent())
		DivideByMaxElement();

	vector<vector<ldouble>> hollow_matrix(m_matrix_size, vector<ldouble>(m_matrix_size));
	vector<ldouble> new_free_terms(m_matrix_size);

	SetHollowMatrix(hollow_matrix, new_free_terms);

	
	vector<ldouble> roots(new_free_terms);
	do {
		//... цього методу
		roots = FindCloserSeidel(hollow_matrix, new_free_terms, roots);
	} while (!m_is_roots_found);

	m_is_roots_found = false;
	return roots;
}

bool SystemSolver_2::IsMatrixConvergent() const {
	// Ці коменти нижче я для себе писав, перекладеш. Суть в тому,
	// що є 4 умови збіжності і ми шукаємо, щоб хоч одна виконалася

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
	// Одна з умов збіжності ітераційного процесу - сума усіх елементів
	// стрічки менша за 1. Ми знаходимо найбільший елемент (1), ділимо
	// його на розмір стрічки (2) і потім ділимо на отримане число кожен
	// елемент матриці і стовпця вільних членів (3). Це забезпечує нам те,
	// що сума всіх елементів кожної стрічки буде меншою за 1, і ітераційний
	// процес буде збіжним


	//(1)
	ldouble max_element{ 0 };
	for (int i = 0; i < m_matrix_size; i++) {
		for (int j = 0; j < m_matrix_size; j++) {
			if (m_matrix[i][j] > max_element)
				max_element = m_matrix[i][j];
		}
	}

	//(2)
	max_element *= m_matrix_size + 1;

	//(3)
	for (int i = 0; i < m_matrix_size; i++) {
		for (int j = 0; j < m_matrix_size; j++) {
			m_matrix[i][j] /= max_element;
		}
		m_free_terms[i] /= max_element;
	}

}

void SystemSolver_2::SetHollowMatrix(vector<vector<ldouble>>& hollow_matrix, vector<ldouble>& new_free_terms) const {

	//Просто за формулою створюємо матрицю з нулями на головній діагоналі
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
	const vector<vector<ldouble>> hollow_matrix,	//Не лякайся, у мене просто параметри функції
	const vector<ldouble> new_free_terms,			//не влізли в одну стрічку
	vector<ldouble> previous_roots) {

	// Просто ітераційний процес як в методичці. Розписувати не буду, бо то дуже довго
	// Якщо буде треба - поясню потім якось
	vector<ldouble> roots(m_matrix_size);

	for (int i = 0; i < m_matrix_size; i++) {
		roots[i] = 0;
		for (int j = 0; j < m_matrix_size; j++) {
			roots[i] += hollow_matrix[i][j] * previous_roots[j];
		}
		roots[i] += new_free_terms[i];
	}

	for (int i = 0; i < roots.size(); i++) {
		cout << roots[i] << "\t\t";
	}
	cout << endl << endl;

	CheckIfRootsFound(roots, previous_roots);

	return roots;
}

vector<ldouble> SystemSolver_2::FindCloserSeidel(
	const vector<vector<ldouble>> hollow_matrix,	// Тут теж не влізли :)
	const vector<ldouble> new_free_terms, 
	vector<ldouble> previous_roots) {

	//Трохи змінена функція FindCloserJacobi()
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

	for (int i = 0; i < roots.size(); i++) {
		cout << roots[i] << "\t\t";
	}
	cout << endl << endl;

	CheckIfRootsFound(roots, previous_roots);

	return roots;
}
void SystemSolver_2::CheckIfRootsFound(const vector<ldouble> roots, const vector<ldouble> previous_roots) {
	// Так само як на перевірку процесу на збіжність є перевірка на те,
	// що ми вже знайшли результат із заданою точністю. Умов всього три
	// і так само треба щоб викналася лише одна. Але мені було ліньки і
	// я просто третю не писав (+ вона майже така сама як друга)
	// 
	// До речі, заціни назву змінних у цьому методі :)

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


