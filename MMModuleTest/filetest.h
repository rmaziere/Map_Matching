#ifndef FILETEST_H
#define FILETEST_H

#include "../MMModule/file.h"
#include <QString>
#include <QStringList>
#include "gtest/gtest.h"

class FileTest : public ::testing::Test {
protected:
    FileTest() {}
    virtual ~FileTest() {}
    virtual void SetUp() {}
    virtual void TearDown() {}

    // Objects declared here can be used by all tests in the test case for File.
};



#endif // FILETEST_H
