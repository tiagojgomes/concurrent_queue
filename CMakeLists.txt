cmake_minimum_required(VERSION 3.5)
project(quest)

# Configuration for Google Test
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
add_subdirectory(tests/googletest)

# Include the directory containing your library's headers
include_directories(include)

# Add subdirectories for tests and source files
add_subdirectory(tests)
add_subdirectory(src)
