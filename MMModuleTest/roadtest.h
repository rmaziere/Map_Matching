#ifndef ROADTEST_H
#define ROADTEST_H

#include "../MMModule/road.h"
#include "gtest/gtest.h"

class RoadTest : public ::testing::Test {
protected:
    RoadTest() {}
    virtual ~RoadTest() {}
    virtual void SetUp() {}
    virtual void TearDown() {}
};

TEST_F(RoadTest, Constructeurs)
{
}

#endif // ROADTEST_H
