#include "CInterpolation.h"

CInterpolation::CInterpolation(double* x, double* y, size_t size) {
	for (int i = 0; i < size; i++) {
		this->m_x.push_back(x[i]);
		this->m_y.push_back(y[i]);
	}
	this->m_size = size;
}

vector<double> CInterpolation::Lagrange() const {
	vector<double> solution;
	vector<double> result;
	vector<double> temp;
	double free{ 0 };

	result.push_back(1);
	for (int i = 0; i < m_size; i++) {
		if (i != 0)
			result.push_back(0);
		temp.push_back(1);
		solution.push_back(0);
	}
	for (int uni = 0; uni < m_size; uni++) {

		for (int i = 0; i < m_size; i++) {
			if (uni == i) {
				free++;
				continue;
			}

			for (int j = 0; j < i + 1 - free; j++) {
				temp[j] *= -m_x[i];
				result[j + 1] += temp[j];
			}

			int j{ 0 };
			for (; j < i + 2 - free; j++) {
				temp[j] = result[j];
			}
		}

		double division{ 1 };
		for (int i = 0; i < m_size; i++) {
			if (i == uni)
				continue;

			division *= m_x[uni] - m_x[i];
		}

		for (int i = 0; i < m_size; i++) {
			result[i] *= m_y[uni];
			result[i] /= division;
			solution[i] += result[i];
		}

		division = 1;
		free = 0;
		for (int i = 0; i < m_size; i++) {
			temp[i] = 1;
			
			if (i == 0)
				result[i] = 1;
			else
				result[i] = 0;
		}
	}

	return solution;
}

double CInterpolation::FindByLagrange(double x) const{
	vector<double> polynom = Lagrange();

	double result{ 0 };

	for (int i = polynom.size() - 1; i >= 0; i--) {
		result = polynom[i] * pow(x, i);
	}

	return result;
}

double CInterpolation::FindDifferences(int difference_index, int x_index) const{
	double result{ 0 };
	if (x_index > m_size - difference_index - 2) {
		cout << "error" << endl << endl;
		result = 0;
	}
	else if (difference_index == 0) {
		result = m_y[x_index + 1] - m_y[x_index];
	}
	else {
		result = FindDifferences(difference_index - 1, x_index + 1) - FindDifferences(difference_index - 1, x_index);
	}

	return result;
}

double CInterpolation::FindQ(double x, double movable_x, double interpolation_step) const {
	return (x - movable_x) / interpolation_step;
}

vector<double> CInterpolation::Forward(double interpolation_step) const {
	vector<double> difference;
	vector<double> r;
	vector<double> solution;
	vector<double> result;
	vector<double> temp;

	difference.push_back(m_y[0]);
	result.push_back(1);
	for (int i = 0; i < m_size; i++) {
		if (i != 0)
			result.push_back(0);
		temp.push_back(1);

		solution.push_back(0);
		r.push_back(m_x[0] + i * interpolation_step);

		if (i != m_size - 1)
			difference.push_back(FindDifferences(i, 0));
	}

	for (int i = 0; i < m_size; i++) {

		for (int l = 0; l < i; l++) {

			for (int j = 0; j < l + 1; j++) {
				temp[j] *= -r[l];
				result[j + 1] += temp[j];

				
			}
			
			for (int k = 0; k < m_size; k++) {
				temp[k] = result[k];
			}
		}

		int j{ 0 };
		for (; j < m_size - i - 1; j++) {
			for (int k = 0; k < m_size - 1; k++)
			{
				if (k == 0) {
					temp[k] = 0;
				}
				temp[k + 1] = result[k];
			}

			for (int k = 0; k < m_size; k++)
				result[k] = temp[k];
		}

		double division = pow(interpolation_step, i);

		for (int j = 0; j < result.size(); j++) {
			if (result[j] != 0) {

				result[j] /= division;
				result[j] *= difference[i];
				result[j] /= Factorial(i);
			}

			solution[j] += result[j];
		}

		for (int i = 0; i < m_size; i++) {
			temp[i] = 1;

			if (i == 0)
				result[i] = 1;
			else
				result[i] = 0;
		}
	}

	return solution;
}

double CInterpolation::Factorial(int x) const{
	int result{ 0 };
	if (x == 0) {
		return 1;
	}
	else {
		result = x * Factorial(x - 1);
	}
	return result;
}

vector<double> CInterpolation::Newthon(double x) const{

	vector<double> result;
	bool isEquidistant{ true };

	double difference{ 0 };

	difference = m_x[1] - m_x[0];

		double interpolation_step = fabs(difference);
		if ((x - m_x[0]) < (m_x[m_x.size() - 1] - x)) {
			result = Forward(interpolation_step);
		}

	return result;
}

double CInterpolation::FindByNewthon(double x) const {
	vector<double> polynom = Newthon(x);

	double result{ 0 };

	for (int i = polynom.size() - 1; i >= 0; i--) {
		result = polynom[i] * pow(x, i);
	}

	return result;
}

//vector<double> CInterpolation::JustNewthon() const {
//
//}
