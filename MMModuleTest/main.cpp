#include "gtest/gtest.h"
#include <iostream>

#include "gridtest.h"
#include "pointgpstest.h"
#include "pointtest.h"
#include "tracktest.h"
#include "filetest.h"

using namespace std;

int main(int argc, char* argv[])
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
