#ifndef POINTGPSTEST_H
#define POINTGPSTEST_H

#include <QDateTime>

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

        /*QDateTime TimeDate = currentDateTime();
        PointGPS pointgps_vide = PointGPS();
        PointGPS pointgps = PointGPS(2455434, 474527452, 142, TimeDate);

        EXPECT_EQ(0, pointgps_vide.getLatitude());
        EXPECT_EQ(0, pointgps_vide.getLongitude());
        EXPECT_EQ(0, pointgps_vide.getAltitude());
        EXPECT_EQ(TimeDate, pointgps_vide.getTimeStamp());

        EXPECT_EQ(2455434, pointgps.getLatitude());
        EXPECT_EQ(474527452, pointgps.getLongitude());
        EXPECT_EQ(142, pointgps.getAltitude());
        EXPECT_EQ(TimeDate, pointgps.getTimeStamp());
        //*/
    }

} // namespace

#endif // POINTGPSTEST_H
