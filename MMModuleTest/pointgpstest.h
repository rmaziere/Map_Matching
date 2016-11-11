#ifndef POINTGPSTEST_H
#define POINTGPSTEST_H

#include <QDateTime>

#include "../MMModule/pointGPS.h"
#include "gtest/gtest.h"

class PointGPSTest : public ::testing::Test {
protected:
    PointGPSTest() {}
    virtual ~PointGPSTest() {}
    virtual void SetUp() {}
    virtual void TearDown() {}

    // Objects declared here can be used by all tests in the test case for Point.
};

TEST_F(PointGPSTest, Constructeur_full)
{

    unsigned int timeStamp = QDateTime::currentDateTime().toTime_t();
    PointGPS pointgps_full = PointGPS(515, 1351453, 142, timeStamp);

    EXPECT_EQ(515, pointgps_full.x());
    EXPECT_EQ(1351453, pointgps_full.y());
    EXPECT_EQ(142, pointgps_full.altitude());
    EXPECT_EQ(timeStamp, pointgps_full.timeStamp());
}

#endif // POINTGPSTEST_H
