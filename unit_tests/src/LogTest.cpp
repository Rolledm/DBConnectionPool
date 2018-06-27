#include <iostream>
#include <gtest/gtest.h>

#include "../../src/DBConnectionPool/DBConnectionPool_interface.h"

int numOfStrings(std::string filename);
void log_init_and_write(std::string seg_lvl);

TEST (LogTest, debug) {
    Logger::getInstance().init("debug");
    log_init_and_write("debug");    
    ASSERT_TRUE(numOfStrings("sample_0.log") == 5);   
}

TEST (LogTest, noString) {
    log_init_and_write("");
    ASSERT_TRUE(numOfStrings("sample_0.log") == 5);   
}

TEST (LogTest, info) {
    log_init_and_write("info");
    ASSERT_TRUE(numOfStrings("sample_0.log") == 4);   
}

TEST (LogTest, warning) {
    log_init_and_write("warning");
    ASSERT_TRUE(numOfStrings("sample_0.log") == 3);   
}

TEST (LogTest, error) {
    log_init_and_write("error");
    ASSERT_TRUE(numOfStrings("sample_0.log") == 2);   
}

TEST (LogTest, fatal) {
    log_init_and_write("fatal");
    ASSERT_TRUE(numOfStrings("sample_0.log") == 1);   
}

int numOfStrings(std::string filename) {
    std::ifstream file(filename);
    if (!file) return 0;

    int num = 0;
    std::string temp;
    while (std::getline(file, temp)) num++;

    file.close();
    return num;
}

void log_init_and_write(std::string seg_lvl) {
    std::ofstream file("sample_0.log");
    file.close();
    Logger::getInstance().changeSeverity(seg_lvl);
    BOOST_LOG_SEV(Logger::getInstance().lg, debug) << "debug";
    BOOST_LOG_SEV(Logger::getInstance().lg, info) << "info";
    BOOST_LOG_SEV(Logger::getInstance().lg, warning) << "warning";
    BOOST_LOG_SEV(Logger::getInstance().lg, error) << "error";
    BOOST_LOG_SEV(Logger::getInstance().lg, fatal) << "fatal";
}