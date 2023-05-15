#include <iostream>
#include "CNumericalMethods.h"

int main()
{
	double epsilon = 0.0001;

	cout << "Iteration Method:\n\nx\t\ty\n";
	
	CNumericalMethods iter(2.5, 0.7, epsilon);
	SResult result = iter.Iteration();

	cout << "Final result is: x = " << result.x << ", y = " << result.y << "\n\n";


	cout << "Newthon Method:\n\nx\t\ty\n";

	CNumericalMethods newthon(0.65, 0.76, epsilon);
	result = newthon.Newthon();

	cout << "Final result is: x = " << result.x << ", y = " << result.y << "\n\n";

}