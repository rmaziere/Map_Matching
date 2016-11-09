#ifndef NETWORKTEST_H
#define NETWORKTEST_H

#include "gtest/gtest.h"
#include "../MMModule/grid.h"


class NetworkTest : public ::testing::Test {
protected:
    NetworkTest() {}
    virtual ~NetworkTest() {}
    virtual void SetUp() {}
    virtual void TearDown() {}

    // Objects declared here can be used by all tests in the test case for Point.
};

TEST_F(NetworkTest, Constructeurs)
{
    grid myNetwork;
    EXPECT_EQ(0, myNetwork.m_road.size());
}

TEST_F(NetworkTest, LoadFromFile)
{
    grid myNetwork2;
    myNetwork2.readFromCSV("../Data/Unit_tests_data_set/simpleNetworkLoaderExemple.csv");
    EXPECT_EQ(2, myNetwork2.m_road.size());
}




#endif // NETWORKTEST_H
