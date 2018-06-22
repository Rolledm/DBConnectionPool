#include "ConnectionManagerTest.h"

TEST_F(ConManTest, init) {
    ASSERT_TRUE(conMan.getNumOfOpenedConnections() == Settings::getInstance().getNumOfConnections().first);
}

TEST_F(ConManTest, newConnection) {
    conMan.newConnection();
    ASSERT_TRUE(conMan.getNumOfOpenedConnections() == Settings::getInstance().getNumOfConnections().first + 1);
}

TEST_F(ConManTest, maxNumOfConnectionsTest) {
    for (int i = 0; i < Settings::getInstance().getNumOfConnections().second - Settings::getInstance().getNumOfConnections().first + 3; i++) {
        conMan.newConnection();
    }
    ASSERT_TRUE(conMan.getNumOfOpenedConnections() == Settings::getInstance().getNumOfConnections().second);    
}

TEST_F(ConManTest, wait_for_timeout) {
    conMan.newConnection();
    std::thread thread(&ConnectionManager::watchForUnusedConnections, &conMan);
    thread.detach();
    std::this_thread::sleep_for(std::chrono::seconds(Settings::getInstance().getTimeout()));
    ASSERT_TRUE(conMan.getNumOfOpenedConnections() == Settings::getInstance().getNumOfConnections().first);
}

TEST_F(ConManTest, simpleQuery) {
    conMan.start("show databases", conMan.findConnection());
    ASSERT_NO_THROW();
}