#include "ConnectionManagerTest.h"

TEST_F(ConManTest, init) { // checking if number of initialised connections is equal to number from settings
    ASSERT_TRUE(conMan.getNumOfOpenedConnections() == Settings::getInstance().getNumOfConnections().first);
}

TEST_F(ConManTest, newConnection) { // checking if number of connections increasing after opening new connection
    conMan.newConnection();
    ASSERT_TRUE(conMan.getNumOfOpenedConnections() == Settings::getInstance().getNumOfConnections().first + 1);
}

TEST_F(ConManTest, maxNumOfConnectionsTest) { // checking if number of connections cannot be higher than max num from settings
    for (int i = 0; i < Settings::getInstance().getNumOfConnections().second - Settings::getInstance().getNumOfConnections().first + 3; i++) {
        conMan.newConnection();
    }
    ASSERT_TRUE(conMan.getNumOfOpenedConnections() == Settings::getInstance().getNumOfConnections().second);    
}

TEST_F(ConManTest, wait_for_timeout) { // creating connection, waiting for timeout from settings
    conMan.newConnection();            // and checking if number of connections reduced to minimum
    std::thread thread(&ConnectionManager::watchForUnusedConnections, &conMan);
    thread.detach();
    std::this_thread::sleep_for(std::chrono::seconds(Settings::getInstance().getTimeout()));
    ASSERT_TRUE(conMan.getNumOfOpenedConnections() == Settings::getInstance().getNumOfConnections().first);
}

TEST_F(ConManTest, simpleQuery) {  // checking that programm will not fall after starting of simple query
    conMan.start("show databases", conMan.findConnection());
    ASSERT_NO_THROW();
}