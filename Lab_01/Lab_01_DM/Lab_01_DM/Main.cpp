#include "Header.h"

int main() {
	ldouble left, right, eps;

	cout << "Enter left lim: ";
	cin >> left;
	cout << "Enter right lim: ";
	cin >> right;
	cout << "Enter epsilon: ";
	cin >> eps;
	cout << endl << endl << endl << "RESULT" << endl << endl;

	Dichotomy findDich(left, right, eps);
	Secant findSec(left, right, eps);

	SResult dichRes = findDich.Find();
	SResult secRes = findSec.Find();

	cout << "Dichotomy: " << endl << "Iterations: " << dichRes.iterations << endl << "Result: " << dichRes.result << endl << endl;
	cout << "Secant: " << endl << "Iterations: " << secRes.iterations << endl << "Result: " << secRes.result << endl << endl;

	return 0;
}