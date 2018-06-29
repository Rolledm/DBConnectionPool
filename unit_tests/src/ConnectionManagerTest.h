#ifndef CONNECTIONMANAGERTEST_H
#define CONNECTIONMANAGERTEST_H

#include <iostream>
#include <gtest/gtest.h>

#include "../../src/DBConnectionPool_interface.h"

class ConManTest : public ::testing::Test {
protected:
    void SetUp() {
        Settings::getInstance().initFields(new InitByXML("../../cfg/test.xml"));        
        conMan = new ConnectionManager();
    }

    void TearDown() {
        delete conMan;
    }
    
    ConnectionManager* conMan;
};

#endif