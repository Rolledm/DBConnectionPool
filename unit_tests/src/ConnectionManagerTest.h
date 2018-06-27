#ifndef CONNECTIONMANAGERTEST_H
#define CONNECTIONMANAGERTEST_H

#include <iostream>
#include <gtest/gtest.h>

#include "../../src/DBConnectionPool/DBConnectionPool_interface.h"

class ConManTest : public ::testing::Test {
protected:
    void SetUp() {
        Settings::getInstance().initFields(new InitByXML("../../../test.xml"));
        conMan.initOutFile("file1");
    }

    void TearDown() {
        conMan.endWork();
    }
    
    ConnectionManager conMan;
};

#endif