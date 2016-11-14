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
    unsigned int timeStamp = QDateTime::currentDateTime().toTime_t();

    Trace.addPoint(1321546, 3546843521, 125, timeStamp);
    EXPECT_DOUBLE_EQ(1321546, Trace.getPoints()[0]->x());
    EXPECT_DOUBLE_EQ(3546843521, Trace.getPoints()[0]->y());
    EXPECT_FLOAT_EQ(125, Trace.getPoints()[0]->altitude());
    EXPECT_EQ(timeStamp, Trace.getPoints()[0]->timeStamp());
    EXPECT_EQ(1, Trace.getPoints().size());
}

TEST_F(TrackTest, DeletePoint)
{

    Track Trace = Track();
    EXPECT_EQ(0, Trace.getPoints().size());

    int j = 0;
    int z = 0;
    for (int i = 0; i < 10; i++) {
        Trace.addPoint(i, j, z, QDateTime::currentDateTime().toTime_t());
        j++;
        z++;
    }
    EXPECT_EQ(10, Trace.getPoints().size());
    Trace.delPointGPS(5); // supression
    EXPECT_DOUBLE_EQ(6, Trace.getPoints()[5]->x());
    EXPECT_DOUBLE_EQ(6, Trace.getPoints()[5]->y());
    EXPECT_FLOAT_EQ(6, Trace.getPoints()[5]->altitude());
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

    Track Trace5 = Track();
    for (int i = 4; i < 11; i++) {
        Trace5.updateBox(i, i+2);
    }
    EXPECT_EQ(4, Trace5.m_xMin);
    EXPECT_EQ(10, Trace5.m_xMax);
    EXPECT_EQ(6, Trace5.m_yMin);
    EXPECT_EQ(12, Trace5.m_yMax);
}

TEST_F(TrackTest, spaceFilterY)
{

    Track Trace = Track();
    Trace.addPoint(0,0,0,QDateTime::currentDateTime().toTime_t());
    Trace.addPoint(0,1,0,QDateTime::currentDateTime().toTime_t());
    Trace.addPoint(0,2,0,QDateTime::currentDateTime().toTime_t());
    Trace.addPoint(0,3,0,QDateTime::currentDateTime().toTime_t());
    Trace.addPoint(0,4,0,QDateTime::currentDateTime().toTime_t());
    Trace.addPoint(0,5,0,QDateTime::currentDateTime().toTime_t());
    Trace.spaceFilter(2);

    EXPECT_EQ(3, Trace.getPoints().size());
    EXPECT_EQ(0, Trace.getPoints()[0]->y());
    EXPECT_EQ(2, Trace.getPoints()[1]->y());
    EXPECT_EQ(4, Trace.getPoints()[2]->y());
}
TEST_F(TrackTest, spaceFilterX)
    {
    Track Trace = Track();
    Trace.addPoint(0,0,0,QDateTime::currentDateTime().toTime_t());
    Trace.addPoint(1,0,0,QDateTime::currentDateTime().toTime_t());
    Trace.addPoint(2,0,0,QDateTime::currentDateTime().toTime_t());
    Trace.addPoint(3,0,0,QDateTime::currentDateTime().toTime_t());
    Trace.addPoint(4,0,0,QDateTime::currentDateTime().toTime_t());
    Trace.addPoint(5,0,0,QDateTime::currentDateTime().toTime_t());
    Trace.spaceFilter(2);

    EXPECT_EQ(3, Trace.getPoints().size());
    EXPECT_EQ(0, Trace.getPoints()[0]->x());
    EXPECT_EQ(2, Trace.getPoints()[1]->x());
    EXPECT_EQ(4, Trace.getPoints()[2]->x());
}

TEST_F(TrackTest, spaceFilterXY)
    {
    Track Trace = Track();
    Trace.addPoint(0,0,0,QDateTime::currentDateTime().toTime_t());
    Trace.addPoint(2,0,0,QDateTime::currentDateTime().toTime_t());
    Trace.addPoint(2,2,0,QDateTime::currentDateTime().toTime_t());
    Trace.addPoint(2,4,0,QDateTime::currentDateTime().toTime_t());
    Trace.addPoint(4,4,0,QDateTime::currentDateTime().toTime_t());
    Trace.addPoint(6,4,0,QDateTime::currentDateTime().toTime_t());
    Trace.spaceFilter(4);
    EXPECT_EQ(3, Trace.getPoints().size());
    cout << Trace.getPoints()[1]->x() << endl;

    cout << Trace.getPoints()[1]->y() << endl;
    EXPECT_TRUE(Trace.getPoints()[0]->x()==0 && Trace.getPoints()[0]->y()==0);
    EXPECT_TRUE(Trace.getPoints()[1]->x()==2 && Trace.getPoints()[1]->y()==4);
    EXPECT_TRUE(Trace.getPoints()[2]->x()==6 && Trace.getPoints()[2]->y()==4);
}


TEST_F(TrackTest, temporalFilter)
{

    Track Trace = Track();
    unsigned int time = QDateTime::fromString("2016-12-24 12:00:02", "yyyy-MM-dd hh:mm:ss").toTime_t();
    for (int i=0; i<10000; i++){
        Trace.addPoint(i ,i, i, time+ i);
    }
    int taille_init = Trace.getPoints().size();
    Trace.temporalFilter(10);
    int taille_fin = Trace.getPoints().size();
    cout << taille_fin << endl;

    /*cout << Trace.getPoints()[0]->x() << endl;
    cout << Trace.getPoints()[1]->x() << endl;
    cout << Trace.getPoints()[2]->x() << endl;
    cout << Trace.getPoints()[3]->x() << endl;*/

    EXPECT_GT(taille_init, taille_fin);

    int j = 0;
    for (int i=0; i<taille_fin; i ++){
        EXPECT_DOUBLE_EQ(j, Trace.getPoints()[i]->x());
        EXPECT_DOUBLE_EQ(j, Trace.getPoints()[i]->y());
        EXPECT_FLOAT_EQ(j, Trace.getPoints()[i]->altitude());
        j += 11;
    }
}
#endif // TRACKTEST_H
