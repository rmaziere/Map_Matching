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

        PointGPS pointgps_vide = PointGPS();
        /*PointGPS pointgps = PointGPS(2455434, 474527452, 142, currentDateTime());

        EXPECT_EQ(0, pointgps_vide.m_latitude);
        EXPECT_EQ(0, pointgps_vide.m_longitude);
        EXPECT_EQ(0, pointgps_vide.m_timeStamp);
        EXPECT_EQ(currentDateTime(), pointgps_vide.m_timeStamp);

        EXPECT_EQ(2455434, pointgps.m_latitude);
        EXPECT_EQ(474527452, pointgps.m_longitude);
        EXPECT_EQ(142, pointgps.m_timeStamp);
        EXPECT_EQ(currentDateTime(), pointgps.m_timeStamp);
        //*/
    }

} // namespace

#endif // POINTGPSTEST_H
