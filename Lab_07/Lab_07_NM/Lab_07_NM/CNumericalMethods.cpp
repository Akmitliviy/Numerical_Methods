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

double CNumericalMethods::GetDerivativeByX(double x){
	return sin(x - 1);
}

double CNumericalMethods::GetDerivativeByY(double y){
	return -sin(y);
}

bool CNumericalMethods::IsProcessConvergent(double first_derivative, double second_derivative) {
	return first_derivative < 1 && second_derivative < 1;
}

bool CNumericalMethods::GetCloser() {
	SResult previous = m_result;

	m_result.x = 2 + cos(m_result.y);
	m_result.y = 0.8 - cos(m_result.x - 1);

	return fabs(m_result.x - previous.x) + fabs(m_result.y - previous.y) < m_epsilon;
}

SResult CNumericalMethods::Iteration() {
	if (!IsProcessConvergent(GetDerivativeByX(m_result.x), GetDerivativeByY(m_result.y))) {
		m_result.x = NAN;
		m_result.y = NAN;
	}
	else {
		while (!GetCloser());
	}

	return m_result;

}