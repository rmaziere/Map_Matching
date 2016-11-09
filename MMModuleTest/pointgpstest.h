#ifndef POINTGPSTEST_H
#define POINTGPSTEST_H

#include <QDateTime>

#include "gtest/gtest.h"
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

    PointGPS pointgps_zero = PointGPS();

    EXPECT_EQ(0, pointgps_zero.getLatitude());
    EXPECT_EQ(0, pointgps_zero.getLongitude());
    EXPECT_EQ(0, pointgps_zero.getAltitude());
    EXPECT_EQ(currentDateTime(), pointgps_zero.getTimeStamp());

    PointGPS pointgps = PointGPS(2455434, 474527452, 142, currentDateTime());

    EXPECT_EQ(2455434, pointgps.getLatitude());
    EXPECT_EQ(474527452, pointgps.getLongitude());
    EXPECT_EQ(142, pointgps.getAltitude());
    EXPECT_EQ(currentDateTime(), pointgps.getTimeStamp());
}


#endif // POINTGPSTEST_H
