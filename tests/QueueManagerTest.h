#ifndef QUEUEMANAGERTEST_H
#define QUEUEMANAGERTEST_H

#include <iostream>
#include <gtest/gtest.h>

#include "../src/DBConnectionPool/DBConnectionPool.h"

class QueueManagerTest : public ::testing::Test {
protected:  
    void SetUp() {
        init = new InitByXML("../../test.xml");
        init->initSettings(&qm.connectionManager.settings);
        conMan.init();        
        qm.connectionManager.outFile = "/home/rolledm/file1";
    }
    void TearDown() {
        delete init;
    }
    QueueManager qm;
    Initialisable* init;
};

#endif