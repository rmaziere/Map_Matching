#ifndef TRACKTEST_H
#define TRACKTEST_H

#include <QDateTime>
#include <vector>

#include "gtest/gtest.h"
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

    Track Trace = Track();
    EXPECT_EQ(0, Trace.getPoints());

    Trace.addPoint(1321546, 3546843521, 125, currentDateTime());
    EXPECT_EQ(1321546, Trace.getPoints()[0]->getLatitude());
    EXPECT_EQ(3546843521, Trace.getPoints()[0]->getLongitude());
    EXPECT_EQ(125, Trace.getPoints()[0]->getAltitude());
    EXPECT_EQ(currentDateTime(), Trace.getPoints()[0]->getTimeStamp());

    Trace.~Track();
    EXPECT_EQ(nullptr, VecteurPointsGPS.getPoints());

    int j = 0;
    int z = 0;
    for(int i=0; i<10; i++){
        Trace.addPoint(i, j, z, currentDateTime());
        j++;
        z++;
    }
    Trace.delPointGPS(Trace.getPoints()[5]);
    EXPECT_EQ(6, Trace.getPoints()[5]->getLatitude());
    EXPECT_EQ(6, Trace.getPoints()[5]->getLongitude());
    EXPECT_EQ(6, Trace.getPoints()[5]->getAltitude());
    EXPECT_EQ(currentDateTime(), Trace.getPoints()[5]->getTimeStamp());

}

#endif // TRACKTEST_H
