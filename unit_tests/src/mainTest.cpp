#include <iostream>
#include <gtest/gtest.h>

#include "../../src/DBConnectionPool/DBConnectionPool_interface.h"

int main(int argc, char** argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}