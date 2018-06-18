#ifndef QUEUEMANAGERTEST_H
#define QUEUEMANAGERTEST_H

#include <iostream>
#include <gtest/gtest.h>

#include "../../src/DBConnectionPool/DBConnectionPool.h"

class QueueManagerTest : public ::testing::Test {
protected:  
    void SetUp() {
        qm.connectionManager.getSettings().init(new InitByXML("../../../test.xml"));
        qm.connectionManager.init("file1");
    }
    void TearDown() {
    }
    QueueManager qm;
};

#endif