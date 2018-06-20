#ifndef CONNECTIONMANAGERTEST_H
#define CONNECTIONMANAGERTEST_H

#include <iostream>
#include <gtest/gtest.h>

#include "../../src/DBConnectionPool/DBConnectionPool.h"

class ConManTest : public ::testing::Test {
protected:
    void SetUp() {
        conMan.getSettings().init(new InitByXML("../../../test.xml"));
        conMan.init("file1");
    }

    void TearDown() {
        conMan.endWork();
    }
    
    ConnectionManager conMan;
};

#endif