#ifndef NETWORKTEST_H
#define NETWORKTEST_H

#include "gtest/gtest.h"
#include "../MMModule/grid.h"


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

TEST_F(GridTest, LoadRoadFromFile)
{
    grid myGrid;
    myGrid.readFromCSV("../Data/Unit_tests_data_set/simpleNetworkLoaderExemple.csv");
    EXPECT_EQ(2, myGrid.m_road.size());
}

TEST_F(GridTest, LoadPointsFromFile)
{
    grid myGrid;
    myGrid.readFromCSV("../Data/Unit_tests_data_set/simpleNetworkLoaderExemple.csv");
    EXPECT_EQ(10, myGrid.m_road[0]->getListOfPoints().size());
    EXPECT_EQ(4, myGrid.m_road[1]->getListOfPoints().size());

    EXPECT_DOUBLE_EQ(1534446.378026439808309, myGrid.m_road[0]->getListOfPoints()[0]->m_x);
    EXPECT_DOUBLE_EQ(330422.365724511211738, myGrid.m_road[0]->getListOfPoints()[0]->m_y);

}





#endif // NETWORKTEST_H
