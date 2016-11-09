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

    //Trace1.~Track()

}

TEST_F(TrackTest, Ajouter_un_point) {

    Track Trace3 = Track();
    QDateTime timeStamp = QDateTime::currentDateTime();

    Trace3.addPoint(1321546, 3546843521, 125, timeStamp);
    EXPECT_EQ(1321546, Trace3.getPoints()[0]->getLatitude());
    EXPECT_EQ(3546843521, Trace3.getPoints()[0]->getLongitude());
    EXPECT_EQ(125, Trace3.getPoints()[0]->getAltitude());
    EXPECT_EQ(timeStamp, Trace3.getPoints()[0]->getTimeStamp());
    EXPECT_EQ(1, Trace3.getPoints().size());


    //Trace3.~Track();

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
    EXPECT_EQ(9, Trace2.getPoints().size());

    //Trace2.~Track();

}
TEST_F(TrackTest, readFromCSV) {

    Track Trace3 = Track();
    Trace3.readFromCSV("../Data/Unit_tests_data_set/readFromCsvExemple.csv");
    EXPECT_DOUBLE_EQ(1686462.894975865026936, Trace3.m_points[0]->m_x);
    EXPECT_DOUBLE_EQ(246133.881616829748964, Trace3.m_points[0]->m_y);
    EXPECT_FLOAT_EQ(47.6675,Trace3.m_points[1]->getLatitude());
    EXPECT_FLOAT_EQ(0, Trace3.m_points[1]->getAltitude());

}

#endif // TRACKTEST_H
