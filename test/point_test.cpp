#include "point.h"

#include "gtest/gtest.h"

TEST(PointTest, GetXGetY)
{
	double x = -5.0;
	double y = 6.0;
	Point point(x, y);

	EXPECT_DOUBLE_EQ(x, point.GetX());
	EXPECT_DOUBLE_EQ(y, point.GetY());
}
