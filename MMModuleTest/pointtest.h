#ifndef POINTTEST_H
#define POINTTEST_H

#include "../MMModule/point.h"
#include "math.h"
#include "gtest/gtest.h"

class PointTest : public ::testing::Test {
protected:
    PointTest() {}
    virtual ~PointTest() {}
    virtual void SetUp() {}
    virtual void TearDown() {}

    // Objects declared here can be used by all tests in the test case for Point.
};

TEST_F(PointTest, Constructeurs)
{
    Point p0(1.0, 0.0);
    EXPECT_DOUBLE_EQ(1, p0.x());
    EXPECT_EQ(0, p0.y());
}

TEST_F(PointTest, samePoint)
{
    Point p0(1.0, 0.0);
    Point p1(1.0 + 0.4 * EPS, 0.0);
    Point p2(1 + 2 * EPS, 0.0);
    EXPECT_TRUE(p0.samePointAs(p1));
    EXPECT_FALSE(p0.samePointAs(p2) == true);
}

TEST_F(PointTest, distanceToPoint)
{
    Point p0(0.0, 0.0);
    Point p_up(2.0, 0.0);
    Point p_right(0.0, 2.0);
    Point p_diag(1.0, 2.0);
    EXPECT_DOUBLE_EQ(p0.distanceToPoint(p_up), 2.0);
    EXPECT_DOUBLE_EQ(p0.distanceToPoint(p_right), 2.0);
    EXPECT_DOUBLE_EQ(p0.distanceToPoint(p_diag), sqrt(1 + 2 * 2.0));
}

TEST_F(PointTest, distanceToSegment)
{
    Point p0(0.0, 0.0);
    Point p1(0.0, 1.0);
    Point p_right(2.0, 0.0);
    Point p_up(0.0, 2.0);
    Point p_diag(1.0, 4.0);
    Point p_diag2(2.0, 4.0);

    EXPECT_DOUBLE_EQ(p0.distanceToSegment(p_diag, p_diag), sqrt(1 + 4 * 4));
    EXPECT_DOUBLE_EQ(p0.distanceToSegment(p_up, p_diag), 2.0);
    EXPECT_DOUBLE_EQ(p1.distanceToSegment(p_right, p_diag2), 2.0);
    EXPECT_DOUBLE_EQ(p1.distanceToSegment(p0, p_up), 0.0);
    EXPECT_DOUBLE_EQ(p0.distanceToSegment(p1, p_up), 1.0);
    EXPECT_DOUBLE_EQ(p0.distanceToSegment(p_up, p1), 1.0);
    //EXPECT_FLOAT_EQ(p0.distanceToSegment(p_diag2, p0), 0.0);      // error if double or float comparison
    EXPECT_DOUBLE_EQ(p0.distanceToSegment(p0, p_diag2), 0.0);
}

#endif // POINTTEST_H
