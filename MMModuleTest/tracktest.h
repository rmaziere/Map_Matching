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

    Track Trace1 = Track();
    EXPECT_EQ(0, Trace1.getPoints().size());

    QDateTime timeStamp = QDateTime::currentDateTime();
    Trace1.addPoint(1321546, 3546843521, 125, timeStamp);
    EXPECT_EQ(1321546, Trace1.getPoints()[0]->getLatitude());
    EXPECT_EQ(3546843521, Trace1.getPoints()[0]->getLongitude());
    EXPECT_EQ(125, Trace1.getPoints()[0]->getAltitude());
    EXPECT_EQ(timeStamp, Trace1.getPoints()[0]->getTimeStamp());
    EXPECT_EQ(1, Trace1.getPoints().size());

    //Trace1.~Track();

}

TEST_F(TrackTest, Suppression) {

    Track Trace2 = Track();
    EXPECT_EQ(0, Trace2.getPoints().size());

    int j=0;
    int z=0;
    for(int i=0; i<10; i++){
        Trace2.addPoint(i, j, z, QDateTime::currentDateTime());
        j++;
        z++;
    }
    EXPECT_EQ(10, Trace2.getPoints().size());
    Trace2.delPointGPS(5); // supression
    EXPECT_EQ(6, Trace2.getPoints()[5]->getLatitude());
    EXPECT_EQ(6, Trace2.getPoints()[5]->getLongitude());
    EXPECT_EQ(6, Trace2.getPoints()[5]->getAltitude());
    EXPECT_EQ(QDateTime::currentDateTime(), Trace2.getPoints()[5]->getTimeStamp());
    EXPECT_EQ(9, Trace2.getPoints().size());

    //Trace2.~Track();

}

#endif // TRACKTEST_H
