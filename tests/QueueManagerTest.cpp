#include "QueueManagerTest.h"

TEST_F(QueueManagerTest, init) {
    ASSERT_TRUE(qm.connectionManager.connections.size() == qm.connectionManager.settings.numOfConnections.first);
}