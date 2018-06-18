#include "QueueManagerTest.h"

TEST_F(QueueManagerTest, init) {
    ASSERT_TRUE(qm.connectionManager.getNumOfOpenedConnections() == qm.connectionManager.getSettings().numOfConnections.first);
}