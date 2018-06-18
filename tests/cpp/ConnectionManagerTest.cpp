#include "ConnectionManagerTest.h"

TEST_F(ConManTest, init) {
    ASSERT_TRUE(conMan.getNumOfOpenedConnections() == conMan.getSettings().numOfConnections.first);
}

TEST_F(ConManTest, newConnection) {
    conMan.newConnection();
    ASSERT_TRUE(conMan.getNumOfOpenedConnections() == conMan.getSettings().numOfConnections.first + 1);
}

TEST_F(ConManTest, maxNumOfConnectionsTest) {
    for (int i = 0; i < conMan.getSettings().numOfConnections.second - conMan.getSettings().numOfConnections.first + 3; i++) {
        conMan.newConnection();
    }
    ASSERT_TRUE(conMan.getNumOfOpenedConnections() == conMan.getSettings().numOfConnections.second);    
}

TEST_F(ConManTest, wait_for_timeout) {
    conMan.newConnection();
    std::thread thread(&ConnectionManager::watchForUnusedConnections, &conMan);
    thread.detach();
    std::this_thread::sleep_for(std::chrono::seconds(conMan.getSettings().timeout));
    ASSERT_TRUE(conMan.getNumOfOpenedConnections() == conMan.getSettings().numOfConnections.first);
}

TEST_F(ConManTest, simpleQuery) {
    conMan.start("show databases", conMan.findConnection());
    ASSERT_NO_THROW();
}