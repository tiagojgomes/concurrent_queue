cmake_minimum_required(VERSION 3.5)
project(queue_tests)

# Configuration for Google Test
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)

# Add the test executable and link with Google Test
add_executable(queue_test queue_test.cpp ../src/queue.cpp)
target_link_libraries(queue_test PRIVATE gtest_main)
