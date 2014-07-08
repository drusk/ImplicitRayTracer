#include "vector.h"

#include "gtest/gtest.h"

TEST(VectorTest, ConstructEmptyGetValues)
{
	Vector3D vector;

	EXPECT_DOUBLE_EQ(0, vector.GetX());
	EXPECT_DOUBLE_EQ(0, vector.GetY());
	EXPECT_DOUBLE_EQ(0, vector.GetZ());
}

TEST(VectorTest, DotProduct)
{
	Vector3D vector1(1.0, 2.0, 3.0);
	Vector3D vector2(2.0, 2.0, 2.0);

	double dotProduct = vector1.DotProduct(vector2);

	EXPECT_DOUBLE_EQ(12.0, dotProduct);
}
