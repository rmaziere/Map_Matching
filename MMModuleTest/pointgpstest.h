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

TEST_F(PointGPSTest, Constructeur_zero)
{

    PointGPS pointgps_zero = PointGPS();

    EXPECT_EQ(0, pointgps_zero.getLatitude());
    EXPECT_EQ(0, pointgps_zero.getLongitude());
    EXPECT_EQ(0, pointgps_zero.getAltitude());
}

TEST_F(PointGPSTest, Constructeur)
{

    QDateTime timeStamp = QDateTime::currentDateTime();
    PointGPS pointgps = PointGPS(2455434, 474527452, 142, timeStamp);

    EXPECT_EQ(2455434, pointgps.getLatitude());
    EXPECT_EQ(474527452, pointgps.getLongitude());
    EXPECT_EQ(142, pointgps.getAltitude());
    EXPECT_EQ(timeStamp, pointgps.getTimeStamp());
}

TEST_F(PointGPSTest, Constructeur_full)
{

    QDateTime timeStamp = QDateTime::currentDateTime();
    PointGPS pointgps_full = PointGPS(515, 1351453, 2455434, 474527452, 142, timeStamp);

    EXPECT_EQ(515, pointgps_full.m_x);
    EXPECT_EQ(1351453, pointgps_full.m_y);
    EXPECT_EQ(2455434, pointgps_full.getLatitude());
    EXPECT_EQ(474527452, pointgps_full.getLongitude());
    EXPECT_EQ(142, pointgps_full.getAltitude());
    EXPECT_EQ(timeStamp, pointgps_full.getTimeStamp());
}

#endif // POINTGPSTEST_H
