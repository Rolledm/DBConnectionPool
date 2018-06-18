cmake_minimum_required(VERSION 2.6)
set(CMAKE_CXX_STANDARD 11) # C++11...
set(CMAKE_CXX_STANDARD_REQUIRED ON) #...is required...
set(CMAKE_CXX_EXTENSIONS OFF) #...without compiler extensions like gnu++11

#find_package(GTest REQUIRED)
find_package(Boost COMPONENTS log REQUIRED)
find_package(Threads)

include_directories(${GTEST_INCLUDE_DIRS} /usr/include/mysql ${Boost_INCLUDE_DIR})

add_executable(main main.cpp DBConnectionPool/DBConnectionPool.cpp DBConnectionPool/QueueManager/QueueManager.cpp
                Logger/Logger.cpp ConnectionManager/Initialisable/InitByXML.cpp ConnectionManager/Connection/Connection.cpp
                ConnectionManager/ConnectionManager.cpp ConnectionManager/Settings/Settings.cpp)

target_link_libraries(main mysqlclient ${GTEST_LIBRARIES} ${Boost_LOG_LIBRARY} 
                        ${CMAKE_THREAD_LIBS_INIT} -lz -lm -lrt -latomic -ldl 
                        -lboost_system -lboost_log_setup -lboost_log -lboost_thread -lpthread -lgcov)

set(CMAKE_EXE_LINKER_FLAGS "-lpthread -lz -lm -lrt -latomic -ldl -lboost_system -lboost_log_setup -lboost_log -lboost_thread -lgcov")
ADD_DEFINITIONS(-DBOOST_LOG_DYN_LINK)
set(CMAKE_CXX_FLAGS "-O0 -g -fprofile-arcs -ftest-coverage ${CMAKE_CXX_FLAGS} --coverage")