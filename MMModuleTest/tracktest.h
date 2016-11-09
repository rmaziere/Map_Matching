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

    vector<PointGPS*> VecteurPointsGPS = Trace.getPoints();

    Trace.addPoint(1321546, 3546843521, 125, currentDateTime());
    EXPECT_EQ(1321546, VecteurPointsGPS[0].getLatitude());
    EXPECT_EQ(3546843521, VecteurPointsGPS[0].getLongitude());
    EXPECT_EQ(125, VecteurPointsGPS[0].getAltitude());
    EXPECT_EQ(currentDateTime(), VecteurPointsGPS[0].getTimeStamp());
    //*/

    VecteurPointsGPS.~Track();
    EXPECT_EQ(0, VecteurPointsGPS.getPoints());

    int j = 0;
    int z = 0;
    for(int i=0; i<10; i++){
        VecteurPointsGPS.addPoint(i, j, z, currentDateTime());
        j++;
        z++;
    }
    VecteurPointsGPS.delPointGPS(VecteurPointsGPS.begin()+5);
    EXPECT_EQ(6, VecteurPointsGPS[5].getLatitude());
    EXPECT_EQ(6, VecteurPointsGPS[5].getLongitude());
    EXPECT_EQ(6, VecteurPointsGPS[5].getAltitude());
    EXPECT_EQ(currentDateTime(), VecteurPointsGPS[5].getTimeStamp());
    //*/

}

#endif // TRACKTEST_H
