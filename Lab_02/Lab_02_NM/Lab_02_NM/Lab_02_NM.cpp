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

	Newton findNewt(left, right, eps);
	SimpleIterations findSimpIt(left, right, eps);

	//SResult newtRes = findNewt.Find();
	//cout << "Nwethon method:\n\nIterations: " << newtRes.iterations << endl << "Result: " << newtRes.result << endl << endl;

	SResult SimpItRes = findSimpIt.Find();
	cout << "Simple Iterations method:\n\nIterations: " << "Iterations: " << SimpItRes.iterations << endl << "Result: " << SimpItRes.result << endl << endl;

	return 0;
}