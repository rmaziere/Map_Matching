#ifndef TRACKTEST_H
#define TRACKTEST_H

#include <QDateTime>
#include <vector>

#include "../MMModule/track.h"
#include "gtest/gtest.h"

class TrackTest : public ::testing::Test {
protected:
    TrackTest() {}
    virtual ~TrackTest() {}
    virtual void SetUp() {}
    virtual void TearDown() {}

    // Objects declared here can be used by all tests in the test case for Point.
};

TEST_F(TrackTest, Constructeurs)
{

    Track Trace = Track();
    EXPECT_EQ(0, Trace.getPoints().size());
}

TEST_F(TrackTest, AddPoint)
{

    Track Trace = Track();
    QDateTime timeStamp = QDateTime::currentDateTime();

    Trace.addPoint(1321546, 3546843521, 125, timeStamp);
    EXPECT_EQ(1321546, Trace.getPoints()[0]->getLatitude());
    EXPECT_EQ(3546843521, Trace.getPoints()[0]->getLongitude());
    EXPECT_EQ(125, Trace.getPoints()[0]->getAltitude());
    EXPECT_EQ(timeStamp, Trace.getPoints()[0]->getTimeStamp());
    EXPECT_EQ(1, Trace.getPoints().size());
}

TEST_F(TrackTest, DeletePoint)
{

    Track Trace = Track();
    EXPECT_EQ(0, Trace.getPoints().size());

    int j = 0;
    int z = 0;
    for (int i = 0; i < 10; i++) {
        Trace2.addPoint(i, j, z, QDateTime::currentDateTime());
        j++;
        z++;
    }
    EXPECT_EQ(10, Trace.getPoints().size());
    Trace.delPointGPS(5); // supression
    EXPECT_EQ(6, Trace.getPoints()[5]->getLatitude());
    EXPECT_EQ(6, Trace.getPoints()[5]->getLongitude());
    EXPECT_EQ(6, Trace.getPoints()[5]->getAltitude());
    EXPECT_EQ(9, Trace.getPoints().size());
}
/*
TEST_F(TrackTest, readFromCSV)
{

    Track Trace = Track();
    Trace.readFromCSV("../Data/Unit_tests_data_set/readFromCsvExemple.csv");
    EXPECT_DOUBLE_EQ(1686462.894975865026936, Trace.getPoints()[0]->m_x);
    EXPECT_DOUBLE_EQ(246133.881616829748964, Trace.getPoints()[0]->m_y);
    EXPECT_FLOAT_EQ(47.6675, Trace.getPoints()[1]->getLatitude());
    EXPECT_FLOAT_EQ(0, Trace.getPoints()[1]->getAltitude());
}
*/
TEST_F(TrackTest, includingRectangle)
{

    Track Trace = Track();
    for (int i = 4; i < 11; i++) {
        Trace.includingRectangle(i, i+2);
    }
<<<<<<< HEAD
    EXPECT_EQ(4, Trace5.m_xmin);
    EXPECT_EQ(10, Trace5.m_xmax);
    EXPECT_EQ(6, Trace5.m_ymin);
    EXPECT_EQ(12, Trace5.m_ymax);
=======
    EXPECT_EQ(4, Trace.xmin);
    EXPECT_EQ(10, Trace.xmax);
    EXPECT_EQ(6, Trace.ymin);
    EXPECT_EQ(12, Trace.ymax);
}

TEST_F(TrackTest, spaceFilter)
{

    Track Trace = Track();
}

TEST_F(TrackTest, temporalFilter)
{

    Track Trace = Track();
>>>>>>> 44689e7da3fcceb05558ab607270ab99c969c81b
}
#endif // TRACKTEST_H
