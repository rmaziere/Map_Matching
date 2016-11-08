#ifndef TRACKTEST_H
#define TRACKTEST_H

#include "gtest/gtest.h"

namespace {
#include "../MMModule/track.h"

    class TrackTest : public ::testing::Test {
    protected:
        TrackTest() {}
        virtual ~TrackTest() {}
        virtual void SetUp() {}
        virtual void TearDown() {}

        // Objects declared here can be used by all tests in the test case for Point.
    };

    TEST_F(TrackTest, Constructeurs) {
        Track VecteurPointsGPS = Track();
        /*EXPECT_EQ(0, VecteurPointsGPS.m_points);

        VecteurPointsGPS.addPoint(1321546, 3546843521, 125, dateTime.currentDateTime());
        EXPECT_EQ(1321546, VecteurPointsGPS.m_points.m_latitude);
        EXPECT_EQ(3546843521, VecteurPointsGPS.m_points.m_longitude);
        EXPECT_EQ(125, VecteurPointsGPS.m_points.m_altitude);
        EXPECT_EQ(dateTime.currentDateTime(), VecteurPointsGPS.m_points.m_timeStamp);*/
    }

} // namespace

#endif // TRACKTEST_H
