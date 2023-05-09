#pragma once
#include <iostream>
#include <vector>

using namespace std;

class LeastSquares
{
public:
	// Те саме що і в п'ятій лабі
	LeastSquares() = delete;

	// Тут теж все схоже
	template <class T>
	LeastSquares(const T matrix, const size_t num_of_variables, const size_t num_of_equations, const vector<double> free_terms);

	// Так як лише треба реалізувати лише один метод (алгоритм), а не два, як завжди,
	// то я його ім'ям назвав клас, а функція  просто Find()
	vector<double> Find();

private:
	vector<vector<double>> m_matrix;
	vector<double> m_free_terms;
	size_t m_num_of_variables;
	size_t m_num_of_equation;

	//Це теж із п'ятої лаби
	template <typename T>
	vector<vector<double>> CopyMatrix(const T matrix, const size_t num_of_variables, const size_t num_of_equasions) const;

	// Транспонує (перевертає) матрицю
	vector<vector<double>> TranspondMatrix(const vector<vector<double>> matrix) const;

	//Множить матрицю на матрицю
	vector<vector<double>> MultiplyMatrixes(const vector<vector<double>> first_matrix, const vector<vector<double>> second_matrix) const;

	// Множить матрицю на стовпець
	vector<double> MultiplyMatrixAndColumn(const vector<vector<double>> matrix, const vector<double> column) const;

	// Шукає визначник
	double FindDeterminant(const vector<vector<double>> matrix) const;

	// Розбиває за методом квадратів матрицю на дві, які транспоновані одна відносно іншої
	// Повертаємо лише одну з них, а іншу робимо за допомогою TranspondMatrix() пізніше, 
	// не в цій функції
	vector<vector<double>> SplitMatrixIntoToTransponded(const vector<vector<double>> matrix) const;

	//Отримуємо стовпець Y
	vector<double> GetY(const vector<vector<double>> matrix, const vector<double> new_free_terms) const;

	//Отримуємо стовпець X
	vector<double> GetX(const vector<vector<double>> matrix, const vector<double> y) const;

};


//Реалізація шаблонних функцій (вгадай з якої лаби :)
template <typename T>
vector<vector<double>> LeastSquares::CopyMatrix(const T matrix, const size_t num_of_variables, const size_t num_of_equasions) const {
	vector<vector<double>> new_vector(num_of_equasions, vector<double>(num_of_variables));

	do {
		if (new_vector.empty())
			break;

		for (int i = 0; i < num_of_equasions; i++) {
			for (int j = 0; j < num_of_variables; j++) {
				new_vector[i][j] = matrix[i][j];
			}
		}

	} while (false);

	return new_vector;
}

template <class T>
LeastSquares::LeastSquares(const T matrix, const size_t num_of_variables, const size_t num_of_equations, const vector<double> free_terms) {
	
	this->m_num_of_equation = num_of_equations;
	this->m_num_of_variables = num_of_variables;
	this->m_matrix = CopyMatrix(matrix, num_of_variables, num_of_equations);
	this->m_free_terms = free_terms;
}