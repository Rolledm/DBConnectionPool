#ifndef CONNECTIONMANAGERTEST_H
#define CONNECTIONMANAGERTEST_H

#include <iostream>
#include <gtest/gtest.h>

#include "../src/DBConnectionPool/DBConnectionPool.h"

class ConManTest : public ::testing::Test {
protected:
    void SetUp() {
        init = new InitByXML("../../test.xml");
        init->initSettings(&conMan.settings);
        conMan.init();
        conMan.outFile = "/home/rolledm/file1";

    }

    void TearDown() {
        delete init;
    }
    
    ConnectionManager conMan;
    Initialisable* init;
};

#endif