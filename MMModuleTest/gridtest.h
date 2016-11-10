#ifndef GRIDTEST_H
#define GRIDTEST_H

#include <limits>

#include "../MMModule/grid.h"
#include "../MMModule/track.h"
#include "gtest/gtest.h"

class GridTest : public ::testing::Test {
protected:
    GridTest() {}
    virtual ~GridTest() {}
    virtual void SetUp() {}
    virtual void TearDown() {}

    // Objects declared here can be used by all tests in the test case for Point.
};

TEST_F(GridTest, Constructeurs)
{
    grid myGrid;
    EXPECT_EQ(0, myGrid.m_road.size());
}

TEST_F(GridTest, SetZone)
{
    grid myGrid;
    myGrid.setZone(1,8,3,50);
    EXPECT_EQ(-199, myGrid.latMin);
    EXPECT_EQ(208, myGrid.latMax);
    EXPECT_EQ(-197, myGrid.longMin);
    EXPECT_EQ(250, myGrid.longMax);
}

TEST_F(GridTest, LoadRoadFromFile)
{
    grid myGrid;
    myGrid.setZone(0,100000000,0,10000000000);
    myGrid.readFromCSV("../Data/Unit_tests_data_set/simpleNetworkLoaderExemple.csv");
    EXPECT_EQ(2, myGrid.m_road.size());
}

TEST_F(GridTest, LoadPointsFromFile)
{
    grid myGrid;
    myGrid.setZone(0,std::numeric_limits<double>::max(),0,std::numeric_limits<double>::max());
    myGrid.readFromCSV("../Data/Unit_tests_data_set/simpleNetworkLoaderExemple.csv");
    EXPECT_EQ(10, myGrid.m_road[0]->getListOfPoints().size());
    EXPECT_EQ(4, myGrid.m_road[1]->getListOfPoints().size());

    EXPECT_DOUBLE_EQ(1534446.378026439808309, myGrid.m_road[0]->getListOfPoints()[0]->m_x);
    EXPECT_DOUBLE_EQ(330422.365724511211738, myGrid.m_road[0]->getListOfPoints()[0]->m_y);
}

TEST_F(GridTest, InFootPrint)
{
    grid myGrid;
    myGrid.setZone(1,8,3,50);
    cout << myGrid.inFootPrint(3,12);
    ASSERT_TRUE(myGrid.inFootPrint(3,12));
    ASSERT_TRUE(myGrid.inFootPrint(1,48));
    ASSERT_FALSE(myGrid.inFootPrint(-200,12));
    ASSERT_FALSE(myGrid.inFootPrint(10,252));
}


#endif // GRIDTEST_H
