#ifndef POINTGPSTEST_H
#define POINTGPSTEST_H

#include "gtest/gtest.h"

namespace {
#include "../MMModule/pointGPS.h"

    class PointGPSTest : public ::testing::Test {
    protected:
        PointGPSTest() {}
        virtual ~PointGPSTest() {}
        virtual void SetUp() {}
        virtual void TearDown() {}

        // Objects declared here can be used by all tests in the test case for Point.
    };

    TEST_F(PointGPSTest, Constructeurs) {
        /*Track PointsGPS = PointGPS();
        EXPECT_EQ(0, PointsGPS.m_latitude);
        EXPECT_EQ(0, PointsGPS.m_longitude);
        EXPECT_EQ(0, PointsGPS.m_timeStamp);
        EXPECT_EQ(currentDateTime(), PointsGPS.m_timeStamp);*/
    }

} // namespace

#endif // POINTGPSTEST_H
