#include "pch.h"

TEST(CNumericalMethods, IterationMethod) {
	double epsilon = 0.0001;
	CNumericalMethods nm(2.5, 0.7, epsilon);
	SResult result = nm.Iteration();

	EXPECT_TRUE(fabs(cos(result.x - 1) + result.y - 0.8) < epsilon);
	EXPECT_TRUE(fabs(result.x - cos(result.y) - 2) < epsilon);
}