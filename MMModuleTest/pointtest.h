#ifndef POINTTEST_H
#define POINTTEST_H

#include "gtest/gtest.h"

namespace {

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
    EXPECT_EQ(-1, p0.m_id);

    Point p1(125, 2.0,45.451321331);
    EXPECT_DOUBLE_EQ(2, p1.m_x);
    EXPECT_EQ(45.451321331, p1.m_y);
    EXPECT_EQ(125, p1.m_id);
}


} // namespace

#endif // POINTTEST_H
