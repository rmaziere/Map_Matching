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

TEST_F(GridTest, Constructor)
{
    Grid grid;
    EXPECT_EQ(0, grid.getNoOfRoads());
    EXPECT_EQ(0, grid.getNoOfPoints());
}

TEST_F(GridTest, setBoundingBox)
{
    Grid grid;
    grid.setBoundingBox(10.0,418.0,30.012,50.2);
    EXPECT_DOUBLE_EQ(10.0, grid.xMin());
    EXPECT_DOUBLE_EQ(418.0, grid.xMax());
    EXPECT_DOUBLE_EQ(30.012, grid.yMin());
    EXPECT_DOUBLE_EQ(50.2, grid.yMax());
}

TEST_F(GridTest, InFootPrint)
{
    Grid myGrid;
    myGrid.setBoundingBox(1,8,3,50);
    ASSERT_TRUE(myGrid.inFootPrint(3,12));
    ASSERT_TRUE(myGrid.inFootPrint(1,48));
    ASSERT_FALSE(myGrid.inFootPrint(-200,12));
    ASSERT_FALSE(myGrid.inFootPrint(10,252));
}

TEST_F(GridTest, LoadRoadFromFile)
{
    Grid grid;
    grid.readFromCSV("../Data/Unit_tests_data_set/gridTestPointsHaveNoDuplicate.csv");
    EXPECT_EQ(3, grid.getNoOfRoads());
    EXPECT_EQ(5, grid.getNoOfPoints());
}

TEST_F(GridTest, LoadPointsFromFile)    // TODO revoir le test
{
/*    Grid myGrid;
    myGrid.setBoundingBox(0,std::numeric_limits<double>::max(),0,std::numeric_limits<double>::max());
    myGrid.readFromCSV("../Data/Unit_tests_data_set/simpleNetworkLoaderExemple.csv");
    EXPECT_EQ(10, myGrid.m_road[0]->getListOfPoints().size());
    EXPECT_EQ(4, myGrid.m_road[1]->getListOfPoints().size());

    EXPECT_DOUBLE_EQ(1534446.378026439808309, myGrid.m_road[0]->getListOfPoints()[0]->x());
    EXPECT_DOUBLE_EQ(330422.365724511211738, myGrid.m_road[0]->getListOfPoints()[0]->y());*/
}

TEST_F(GridTest, Neighbours)
{
    Grid grid;
    grid.readFromCSV("../Data/Unit_tests_data_set/gridTestPointsHaveNoDuplicate.csv");
    grid.buildMarkovMatrix();
    AllRoadMap::iterator got= grid.getRoadEntry(1000);
    EXPECT_EQ(got->second.getNoOfNeighbors(), 2);
    got= grid.getRoadEntry(2000);
    EXPECT_EQ(got->second.getNoOfNeighbors(), 3);
}

TEST_F(GridTest, updateGrid)
{
    Grid grid;
    grid.readFromCSV("../Data/Unit_tests_data_set/gridTestPointsHaveNoDuplicate.csv");
    EXPECT_DOUBLE_EQ(1.0, grid.xMinGrid());
    EXPECT_DOUBLE_EQ(10000.0, grid.xMaxGrid());
    EXPECT_DOUBLE_EQ(2.0, grid.yMinGrid());
    EXPECT_DOUBLE_EQ(11000.0, grid.yMaxGrid());
}

TEST_F(GridTest, trackInGrid)
{
    Grid grid;
    grid.setBoundingBox(1,5,30,50);
    grid.readFromCSV("../Data/Unit_tests_data_set/gridTestPointsHaveNoDuplicate.csv");
    ASSERT_TRUE(grid.trackInGrid());
}

#endif // GRIDTEST_H
