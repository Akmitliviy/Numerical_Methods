#include "pch.h"

//TEST(LeastSquares, TestVariant) {
//	const double result_accuracy = 0.0000000001;
//	const size_t num_of_equations{ 6 };
//	const size_t num_of_variables{ 3 };
//	double matrix[num_of_equations][num_of_variables] ={{ 1,  0,  0},
//														{ 1,  1,  0},
//														{ 1,  1,  1},
//														{ 0,  1,  0},
//														{ 0,  1,  1},
//														{ 0,  0,  1}};
//
//	vector<double> free_terms{ 1.4, -1.5, 3.2, 0.6, 4.3, 4.2 };
//
//	LeastSquares ls(matrix, num_of_variables, num_of_equations, free_terms);
//	vector<double> result = ls.Find();
//
//	EXPECT_TRUE(fabs(result[0] - (-0.1)) < result_accuracy);
//	EXPECT_TRUE(fabs(result[1] - (-0.4)) < result_accuracy);
//	EXPECT_TRUE(fabs(result[2] - ( 4.2)) < result_accuracy);
//}

TEST(LeastSquares, IsWorking) {
	const double result_accuracy = 0.0001;
	const size_t num_of_equations{ 5 };
	const size_t num_of_variables{ 3 };
	double matrix[num_of_equations][num_of_variables] = {{1,  3, -2},
														{-1,  2,  1},
														{ 3, -2, -2},
														{ 3,  1, -3},
														{ 1, -1, -7}};

	vector<double> free_terms{ -5, 1, -5, 1, 5 };



	LeastSquares ls(matrix, num_of_variables, num_of_equations, free_terms);
	vector<double> result = ls.Find();

	EXPECT_TRUE(fabs(result[0] - (-1.7163)) < result_accuracy);
	EXPECT_TRUE(fabs(result[1] - (-0.456919)) < result_accuracy);
	EXPECT_TRUE(fabs(result[2] - (-0.866864)) < result_accuracy);
}