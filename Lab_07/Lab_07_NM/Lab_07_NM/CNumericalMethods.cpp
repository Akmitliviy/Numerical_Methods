#include "CNumericalMethods.h"

CNumericalMethods::CNumericalMethods(double x, double y) {
	m_result.x = x;
	m_result.y = y;
	m_epsilon = 0.0001;
}
CNumericalMethods::CNumericalMethods(double x, double y, double epsilon) : m_epsilon(epsilon) {
	m_result.x = x;
	m_result.y = y;
}

double CNumericalMethods::Func1(double y) const {
	return 2 + cos(y);
}

double CNumericalMethods::Func2(double x) const{
	return 0.8 - cos(x - 1);
}

double CNumericalMethods::GetDerivativeByX(double x) const{
	return sin(x-1);
}

double CNumericalMethods::GetDerivativeByY(double y) const{
	return -sin(y);
}

bool CNumericalMethods::IsProcessConvergent(double first_derivative, double second_derivative) const {
	return first_derivative < 1 && second_derivative < 1;
}

bool CNumericalMethods::GetCloserIteration() {
	SResult previous = m_result;

	m_result.x = Func1(m_result.y);
	m_result.y = Func2(m_result.x);

	cout << m_result.x << "\t\t" << m_result.y << endl;

	return fabs(m_result.x - previous.x) + fabs(m_result.y - previous.y) < m_epsilon;
}

SResult CNumericalMethods::Iteration() {
	if (!IsProcessConvergent(GetDerivativeByX(m_result.x), GetDerivativeByY(m_result.y))) {
		m_result.x = NAN;
		m_result.y = NAN;
	}
	else {
		while (!GetCloserIteration());
	}

	return m_result;

}
void CNumericalMethods::SetTranspondedJ(vector<vector<double>>& matrix_j, double x, double y) const {
	
	matrix_j[0][0] = -1;
	matrix_j[0][1] = -GetDerivativeByY(y);
	matrix_j[1][0] = -GetDerivativeByX(x);
	matrix_j[1][1] = -1;
}
void CNumericalMethods::SetTranspondedJNewthon(vector<vector<double>>& matrix_j, double x, double y) const {

	matrix_j[0][0] = GByYDerivative(x, y);
	matrix_j[0][1] = -FByYDerivative(x, y);
	matrix_j[1][0] = -GByXDerivative(x, y);
	matrix_j[1][1] = FByXDerivative(x, y);
}
double CNumericalMethods::GetDeterminant(vector<vector<double>>& matrix_j) const {
	return matrix_j[0][0] * matrix_j[1][1] - (matrix_j[0][1] * matrix_j[1][0]);
}

vector<double> CNumericalMethods::MultiplyMatrixAndColumn(const vector<vector<double>> matrix, const vector<double> column) const {
	vector<double> local_column(column.size());

	double sum = 0;
	for (int i = 0; i < matrix.size(); i++) {
		for (int j = 0; j < matrix[0].size(); j++) {
			local_column[i] += matrix[i][j] * column[j];
		}
	}

	return local_column;
}
bool CNumericalMethods::GetCloserNewthon(vector<vector<double>>& matrix_j, vector<double> f) {
	SResult previous = m_result;
	
	SetTranspondedJNewthon(matrix_j, m_result.x, m_result.y);
	double determinant = GetDeterminant(matrix_j);
	f[0] = FByXY(m_result.x, m_result.y);
	f[1] = FByXY(m_result.x, m_result.y);

	for (int i = 0; i < matrix_j.size(); i++) {
		for (int j = 0; j < matrix_j.size(); j++) {
			matrix_j[i][j] *= (1/determinant);
		}
	}

	vector<double> j_and_f = MultiplyMatrixAndColumn(matrix_j, f);

	m_result.x = m_result.x - j_and_f[0];
	m_result.y = m_result.y - j_and_f[1];

	cout << m_result.x << "   \t" << m_result.y << endl;

	return fabs(m_result.x - previous.x) + fabs(m_result.y - previous.y) < m_epsilon;
}

SResult CNumericalMethods::Newthon() {
	vector<vector<double>> matrix_j(number_of_equasions, vector<double>(number_of_equasions));
	vector<double> f(number_of_equasions);

	if (!IsProcessConvergent(GetDerivativeByX(m_result.x), GetDerivativeByY(m_result.y))) {
		m_result.x = NAN;
		m_result.y = NAN;
	}
	else {
		while (!GetCloserNewthon(matrix_j, f));
	}

	return m_result;
}

double CNumericalMethods::FByXY(double x, double y) const {
	return sin(x + y) - 1.5 * x;
}

double CNumericalMethods::GByXY(double x, double y) const {
	return x * x + y * y - 1;
}



double CNumericalMethods::FByXDerivative(double x, double y) const{
	return cos(x + y) - 1.5;
}

double CNumericalMethods::FByYDerivative(double x, double y) const{
	return cos(x + y);
}

double CNumericalMethods::GByXDerivative(double x, double y) const{
	return 2 * x;
}

double CNumericalMethods::GByYDerivative(double x, double y) const{
	return 2 * y;
}
