#ifndef POINTTEST_H
#define POINTTEST_H

#include "gtest/gtest.h"
#include "math.h"
#include "../MMModule/point.h"

class PointTest : public ::testing::Test {
protected:
    PointTest() {}
    virtual ~PointTest() {}
    virtual void SetUp() {}
    virtual void TearDown() {}

    // Objects declared here can be used by all tests in the test case for Point.
};

TEST_F(PointTest, Constructeurs) {
    Point p0(1.0,0.0);
    EXPECT_DOUBLE_EQ(1, p0.m_x);
    EXPECT_EQ(0, p0.m_y);
    EXPECT_EQ(POINT_GPS, p0.m_id);

    Point p1(125, 2.0,45.451321331);
    EXPECT_DOUBLE_EQ(2, p1.m_x);
    EXPECT_EQ(45.451321331, p1.m_y);
    EXPECT_EQ(125, p1.m_id);
}

TEST_F(PointTest, samePoint) {
    Point p0(1.0,0.0);
    Point p1(1.0+0.4*EPS, 0.0);
    Point p2(1+2*EPS, 0.0);
    EXPECT_TRUE(p0.samePointAs(p1));
    EXPECT_FALSE(p0.samePointAs(p2)==true);

    /*Point A(0,0);
    Point B(0,10);
    Point C(1,11);
    EXPECT_EQ(1.41421,C.distance2ptsegment(A,B));
    EXPECT_EQ(10,A.distance2pt(B));*/
}

TEST_F(PointTest, distanceToPoint) {
    Point p0(0.0,0.0);
    Point p_up(2.0, 0.0);
    Point p_right(0.0,2.0);
    Point p_diag(1.0, 2.0);
    EXPECT_DOUBLE_EQ(p0.distance2pt(p_up), 2.0);
    EXPECT_DOUBLE_EQ(p0.distance2pt(p_right), 2.0);
    EXPECT_DOUBLE_EQ(p0.distance2pt(p_diag), sqrt(1+2*2.0));
}

TEST_F(PointTest, distanceToSegment) {
    Point p0(0.0,0.0);
    Point p1(0.0,1.0);
    Point p_right(2.0, 0.0);
    Point p_up(0.0,2.0);
    Point p_diag(1.0, 4.0);
    Point p_diag2(2.0,4.0);

    EXPECT_DOUBLE_EQ(p0.distance2ptsegment(p_diag, p_diag), sqrt(1+4*4));
    EXPECT_DOUBLE_EQ(p0.distance2ptsegment(p_up,p_diag), 2.0);
    EXPECT_DOUBLE_EQ(p1.distance2ptsegment(p_right, p_diag2), 2.0);
    EXPECT_DOUBLE_EQ(p1.distance2ptsegment(p0, p_up), 0.0);
    EXPECT_DOUBLE_EQ(p0.distance2ptsegment(p1, p_up), 1.0);
    EXPECT_DOUBLE_EQ(p0.distance2ptsegment(p_up, p1), 1.0);
    //EXPECT_DOUBLE_EQ(p0.distance2ptsegment(p_diag2, p0), 0.0);
    EXPECT_DOUBLE_EQ(p0.distance2ptsegment(p0, p_diag2), 0.0);

}

#endif // POINTTEST_H
