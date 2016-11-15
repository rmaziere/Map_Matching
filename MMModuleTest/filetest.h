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

/*TEST_F(FileTest, Constructeurs)
{
    File test;
    test.splitPath("/home/user/Document/couche.ShP");

    EXPECT_STREQ("/home/user/Document/", test.filePath.at(0).toStdString());
    EXPECT_STREQ("couche", test.fileName.at(0).toStdString());
    EXPECT_STREQ("shp", test.fileExtension.at(0).toStdString());
    //EXPECT_STREQ("test", "test");
    std::cerr << "################################" << test.filePath.at(0).toStdString() << "################################" << endl;
}
*/

#endif // FILETEST_H
