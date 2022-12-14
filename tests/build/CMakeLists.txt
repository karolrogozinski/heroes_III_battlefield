cmake_minimum_required(VERSION 2.6)

# Locate GTest
find_package(GTest REQUIRED)
include_directories(${GTEST_INCLUDE_DIRS})
link_directories(${GTEST_INCLUDE_DIRS})
 
# Link runTests with what we want to test and the GTest and pthread library
add_executable(unitTest ../unitTest.cpp)
add_executable(stackTest ../stackTest.cpp)
target_link_libraries(unitTest ${GTEST_LIBRARIES} pthread)
target_link_libraries(stackTest ${GTEST_LIBRARIES} pthread)