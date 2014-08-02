#include "vector3d.h"

#include "gtest/gtest.h"

TEST(VectorTest, ConstructEmptyGetValues)
{
    Vector3D vector;

    EXPECT_DOUBLE_EQ(0, vector.GetX());
    EXPECT_DOUBLE_EQ(0, vector.GetY());
    EXPECT_DOUBLE_EQ(0, vector.GetZ());
}

TEST(VectorTest, ConstructConstantValue)
{
    double value = 5.0;
    Vector3D vector(value);

    EXPECT_DOUBLE_EQ(value, vector.GetX());
    EXPECT_DOUBLE_EQ(value, vector.GetY());
    EXPECT_DOUBLE_EQ(value, vector.GetZ());
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

TEST(VectorTest, ReverseVector)
{
    Vector3D vector(2.0, -2.0, 5.0);
    vector.Reverse();

    EXPECT_DOUBLE_EQ(-2.0, vector.GetX());
    EXPECT_DOUBLE_EQ(2.0, vector.GetY());
    EXPECT_DOUBLE_EQ(-5.0, vector.GetZ());
}

TEST(VectorTest, Add)
{
    Vector3D vector1(1.0, 2.0, 3.0);
    Vector3D vector2(4.0, 5.0, 6.0);

    Vector3D sumVector = vector1 + vector2;

    EXPECT_DOUBLE_EQ(5.0, sumVector.GetX());
    EXPECT_DOUBLE_EQ(7.0, sumVector.GetY());
    EXPECT_DOUBLE_EQ(9.0, sumVector.GetZ());
}

TEST(VectorTest, Subtract)
{
    Vector3D vector1(1.0, 5.0, 6.0);
    Vector3D vector2(4.0, 1.0, 6.0);

    Vector3D diffVector = vector1 - vector2;

    EXPECT_DOUBLE_EQ(-3.0, diffVector.GetX());
    EXPECT_DOUBLE_EQ(4.0, diffVector.GetY());
    EXPECT_DOUBLE_EQ(0.0, diffVector.GetZ());
}

TEST(VectorTest, MultiplyConstantRight)
{
    Vector3D vector1(1.0, 2.0, 3.0);

    Vector3D prodVector = vector1 * 2.5;

    EXPECT_DOUBLE_EQ(2.5, prodVector.GetX());
    EXPECT_DOUBLE_EQ(5.0, prodVector.GetY());
    EXPECT_DOUBLE_EQ(7.5, prodVector.GetZ());
}

TEST(VectorTest, MultiplyConstantLeft)
{
    Vector3D vector1(1.0, 2.0, 3.0);

    Vector3D prodVector = 2.5 * vector1;

    EXPECT_DOUBLE_EQ(2.5, prodVector.GetX());
    EXPECT_DOUBLE_EQ(5.0, prodVector.GetY());
    EXPECT_DOUBLE_EQ(7.5, prodVector.GetZ());
}


TEST(VectorTest, MultiplyVector)
{
    Vector3D vector1(-1.0, 2.0, 3.0);
    Vector3D vector2(4.0, 5.0, 6.0);

    Vector3D prodVector = vector1 * vector2;

    EXPECT_DOUBLE_EQ(-4.0, prodVector.GetX());
    EXPECT_DOUBLE_EQ(10.0, prodVector.GetY());
    EXPECT_DOUBLE_EQ(18.0, prodVector.GetZ());
}

TEST(VectorTest, PlusEquals)
{
    Vector3D vector1(-1.0, 2.0, 3.0);
    Vector3D vector2(4.0, 5.0, 6.0);

    vector1 += vector2;

    EXPECT_DOUBLE_EQ(3.0, vector1.GetX());
    EXPECT_DOUBLE_EQ(7.0, vector1.GetY());
    EXPECT_DOUBLE_EQ(9.0, vector1.GetZ());
}
