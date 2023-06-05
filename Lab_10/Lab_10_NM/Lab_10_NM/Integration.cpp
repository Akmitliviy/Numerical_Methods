#include "Integration.h"

Integration::Integration(double left_border, double right_border, unsigned int n, double (*func)(double x)) {
	m_left_border = left_border;
	m_right_border = right_border;
	m_func = func;
	m_num_of_steps = n;

	double mid = fabs(right_border - left_border) / n;
	m_step = mid;

	double x{ left_border };
	for (int i = 0; i <= n; i++) {
		m_x.push_back(x);
		m_y.push_back(func(x));

		x += mid;
	}
}

double Integration::RiemannRightSum() {
	return m_step * accumulate(m_y.begin(), m_y.end() - 1, 0.0);
}
double Integration::RiemannLeftSum() {
	return m_step * accumulate(m_y.begin() + 1, m_y.end(), 0.0);
}
double Integration::RiemannMiddleSum() {
	vector<double> special_y;
	for (const auto& element : m_x) {
		special_y.push_back(m_func(element + m_step / 2.0));
	}
	return m_step * accumulate(special_y.begin(), special_y.end() - 1, 0.0);
}

double Integration::GetSecondDerivative(double x) {
	return -pow(x, 3) * sin(x) + 6 * pow(x, 2) * cos(x) + 6 * x * sin(x);
	//return -0.0225 / pow(0.3 * x + 1.2, 3.0 / 2.0);
}

double Integration::GetFourthDerivative(double x) {
	return pow(x, 3) * sin(x) - 12 * pow(x, 2) * cos(x) - 36 * x * sin(x) + 24 * cos(x);
	//return -0.00759375 / pow(0.3 * x + 1.2, 7.0 / 2.0);
}

double Integration::GetError(ETypes type) {
	double result{ 0 };

	switch (type) {
	case e_riemann:
		result = GetSecondDerivative(m_left_border) * (m_right_border - m_left_border) * pow(m_step, 2) / 24;
		break;
	case e_trapezoidal:
		result = -GetSecondDerivative(m_left_border) * (m_right_border - m_left_border) * pow(m_step, 2) / 12;
		break;
	case e_simpson:
		result = -GetM() * pow(m_right_border - m_left_border, 5) / (180 * pow(m_num_of_steps, 4));
		break;
	default:
		break;
	}

	return result;
}

double Integration::Trapezoidal() {
	double accum{ accumulate(m_y.begin() + 1, m_y.end() - 1, 0.0) };
	double first{ *m_y.begin() };
	double end{ *(m_y.end() - 1) };
	double funcs{ (first + end) / 2.0 };

	return m_step * (funcs + accum);
}

double Integration::Simpson() {
	vector<double> _2i_minus_1;
	vector<double> _2i;

	for (int i = 1; i < m_num_of_steps; i++) {
		if (!(i % 2))
			_2i_minus_1.push_back(m_y[i]);
		else
			_2i.push_back(m_y[i]);
	}

	return (m_step / 3.0) * (*m_y.begin() + *(m_y.end() - 1.0) + 4.0 * accumulate(_2i_minus_1.begin(), _2i_minus_1.end(), 0.0) + 2.0 * accumulate(_2i.begin(), _2i.end(), 0.0));
}

double Integration::GetM() {

	double max{ fabs(GetFourthDerivative(m_left_border)) };

	for (const double& element : m_x) {
		if (fabs(GetFourthDerivative(element)) > max)
			max = fabs(GetFourthDerivative(element));
	}

	return max;
}

double Integration::FindStep(double epsilon) {
	double max_derivative{ GetM() };

	return pow(0.5 * epsilon * 180.0 / ((m_right_border - m_left_border) * max_derivative), 1.0 / 4.0);
}