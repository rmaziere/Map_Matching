#include <iostream>
#include "gtest/gtest.h"

#include "pointtest.h"
#include "tracktest.h"
#include "pointgpstest.h"
#include "gridtest.h"

using namespace std;

int main(int argc, char *argv[]) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
