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

TEST(VectorTest, Length)
{
	Vector3D vector1(1.0, 0.0, 0.0);
	EXPECT_DOUBLE_EQ(1.0, vector1.Length());

	Vector3D vector2(-5.0, 4.0, 2.0);
	double absError = 0.000000001;
	EXPECT_NEAR(6.708203932, vector2.Length(), absError);
}

TEST(VectorTest, NormalizeZeroVector)
{
	Vector3D zeroVector;
	zeroVector.Normalize();

	EXPECT_DOUBLE_EQ(0.0, zeroVector.Length());
	EXPECT_DOUBLE_EQ(0.0, zeroVector.GetX());
	EXPECT_DOUBLE_EQ(0.0, zeroVector.GetY());
	EXPECT_DOUBLE_EQ(0.0, zeroVector.GetZ());
}

TEST(VectorTest, NormalizeUnitVector)
{
	Vector3D unitVector(0.0, 1.0, 0.0);
	unitVector.Normalize();

	EXPECT_DOUBLE_EQ(1.0, unitVector.Length());
	EXPECT_DOUBLE_EQ(0.0, unitVector.GetX());
	EXPECT_DOUBLE_EQ(1.0, unitVector.GetY());
	EXPECT_DOUBLE_EQ(0.0, unitVector.GetZ());
}

TEST(VectorTest, NormalizeVector)
{
	Vector3D vector(2.0, -2.0, 5.0);
	vector.Normalize();

	double absError = 0.000000001;
	EXPECT_DOUBLE_EQ(1.0, vector.Length());
	EXPECT_NEAR(0.3481553119, vector.GetX(), absError);
	EXPECT_NEAR(-0.3481553119, vector.GetY(), absError);
	EXPECT_NEAR(0.8703882798, vector.GetZ(), absError);
}
