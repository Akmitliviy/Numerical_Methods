#pragma once

#include <iostream>

// Про вектори я написав нижче, там де починаються функції
#include <vector>
#include <string>
#include <cmath>

using namespace std;

// Не знаю нащо я це зробив, але вже як є. Просто захотілося юзати long double :)
typedef long double ldouble;


// Клас, в якому реалізовані два методи знаходження коренів системи лінійних рівнянь
// Методом Якобі та Зейделя
class SystemSolver_2 {
public:

	// Стандартний конструктор ми видаляємо, щоб користувач одразу задавав матрицю
	// її розмір та набір вільних членів
	SystemSolver_2() = delete;


	// template <class T> - то є шаблон. Погугли, якщо не знаєш - класна штука
	// тут використовується для того, щоби користувач міг передати двовимірний
	// масив будь-якої розмірності. Всі конструктори та функції, що є шаблонними
	// (мають над собою оце "template <class T>") повинні бути реалізовані в 
	// header-файлі, там де сам клас, тобто в нашому випадку тут, в SystemSolver_2_Header.h
	// Їхня реалізація починається після класу (можна одразу в оголошенні, але,
	// як на мене то не дуже гарно виглядає)

	// Тут беремо матрицю, її розмір та вільні члени (B-стовпець розв'язків)
	template <class T>
	SystemSolver_2(const T matrix, const size_t matrix_size, const vector<ldouble> free_terms);
	
	// А тут те саме тільки замість стандартного epsilon (0.001) користувач вводить свій
	template <class T>
	SystemSolver_2(const T matrix, const size_t matrix_size, const vector<ldouble> free_terms, const ldouble epsilon);

	vector<ldouble> Jacobi(); //Метод Якобі
	vector<ldouble> Seidel(); //Метод Зейделя

private:
	vector<vector<ldouble>> m_matrix;
	vector<ldouble> m_free_terms;
	size_t m_matrix_size;
	bool m_is_roots_found;
	ldouble m_epsilon;

	// Усі інші функції я вирішив інкапсулювати (приховати) розмістивши в секції private,
	// бо нащо кристувачу знати про їхнє існування, правильно? 
	
	// Знову використовую шаблони, бо ця функція CopyMatrix() перекопіює мені матрицю зі звичайної
	// в матрицю задану векторами. Вектори - то по суті динамічні масиви, які самі займаються
	// виділенням і прибираннями динамічної пам'яті, що економить купу часу і дозволяє
	// зробити універсальну програму легшим способом (бо вручну виділяти пам'ять на двовимірний масив...)
	//
	// vector<vector<ldouble>> - векторний масив, кожен елемент якого є векторним масивом
	// кожен елемент якого є ldouble (long double). А якщо коротко - матриця.
	// Відповідно vector<ldouble> - масив, що містить ldouble.
	template <typename T>
	vector<vector<ldouble>> CopyMatrix(const T matrix, const size_t size);

	// Перевірка умов збіжності ітераційного процесу (виконуватися повинна хоча б одна)
	bool IsMatrixConvergent() const;

	// Якщо матриця така, що процес не буде збіжний то ми змінюємо матрицю таким 
	// чином, щоб він був збіжним (трохи більше в реалізації)
	void DivideByMaxElement();

	// Створюємо матрицю у якої на головній діагоналі нулі і побічно повертаємо
	// через параметри (тому вони передаються за адресою)
	void SetHollowMatrix(vector<vector<ldouble>>& hollow_matrix, vector<ldouble>& new_free_terms) const;

	// Перевірка, чи ми вже знайшли корені
	void CheckIfRootsFound(const vector<ldouble> roots, const vector<ldouble> previous_roots);

	// Функція яку ми викликаємо циклічно, поки не знайдемо корені. Шукає наближення за методом Якобі
	vector<ldouble> FindCloserJacobi(const vector<vector<ldouble>> hollow_matrix, const vector<ldouble> new_free_terms, vector<ldouble> previous_roots);

	// Шукає наближення за методом Зейделя (від Якобі відрізняється ну зовсім трохи,
	// тому вони майже однакові) 
	vector<ldouble> FindCloserSeidel(const vector<vector<ldouble>> hollow_matrix, const vector<ldouble> new_free_terms, vector<ldouble> previous_roots);

};


//Реалізація шаблонних конструкторів та методів
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