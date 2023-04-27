#include "pch.h"

TEST(SystemSolver_2, Jacobi) {

	const size_t size{ 4 };
	ldouble matrix[size][size] = { { 24.67, 3.24,  5.45, 4.13},
							{ 4.46,  34.86,  3.12, -2.43},
							{ 3.87,  6.54,  45.44, 3.45},
							{ 2.45,  4.25,  5.45, 32.72} };

	vector<ldouble> B{ 80.41, 85.44, 187.84, 152.86 };

	const ldouble epsilon = 0.0001;

	SystemSolver_2 solver(matrix, size, B, epsilon);
	vector<ldouble> result = solver.Jacobi();

	EXPECT_TRUE(fabs(result[0] - 1.59999) < epsilon);
	EXPECT_TRUE(fabs(result[1] - 2.19985) < epsilon);
	EXPECT_TRUE(fabs(result[2] - 3.40001) < epsilon);
	EXPECT_TRUE(fabs(result[3] - 3.6999) < epsilon);

}

TEST(SystemSolver_2, Seidel) {

	const size_t size{ 4 };
	ldouble matrix[size][size] = { { 24.67, 3.24,  5.45, 4.13},
							{ 4.46,  34.86,  3.12, -2.43},
							{ 3.87,  6.54,  45.44, 3.45},
							{ 2.45,  4.25,  5.45, 32.72} };

	vector<ldouble> B{ 80.41, 85.44, 187.84, 152.86 };

	const ldouble epsilon = 0.0001;

	SystemSolver_2 solver(matrix, size, B, epsilon);
	vector<ldouble> result = solver.Seidel();

	EXPECT_TRUE(fabs(result[0] - 1.59999) < epsilon);
	EXPECT_TRUE(fabs(result[1] - 2.19985) < epsilon);
	EXPECT_TRUE(fabs(result[2] - 3.40001) < epsilon);
	EXPECT_TRUE(fabs(result[3] - 3.6999) < epsilon);

}