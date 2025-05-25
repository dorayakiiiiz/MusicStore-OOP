cmake_minimum_required(VERSION 3.10)
project(MusicStoreTests)

# Google Test requires at least C++11
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Force Google Test to use the same runtime library setting (/MD or /MT) as our project
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)

# Include the root directory for header files
include_directories(${CMAKE_SOURCE_DIR})

# Add GoogleTest as a subdirectory
add_subdirectory(googletest)

# Exclude main.cpp from source files list
file(GLOB_RECURSE SOURCE_FILES 
    "*.cpp"
    "*.h"
)
list(FILTER SOURCE_FILES EXCLUDE REGEX ".*main\\.cpp$")
list(FILTER SOURCE_FILES EXCLUDE REGEX ".*CMakeCXXCompilerId\\.cpp$")

# Tạo danh sách các file test
file(GLOB TEST_FILES "tests/*.cpp")

# Thêm executable cho các tests
add_executable(run_tests ${TEST_FILES} ${SOURCE_FILES})

# Link với Google Test libraries
target_link_libraries(run_tests gtest gtest_main)

# Thêm link với các thư viện khác
if(WIN32)
    target_link_libraries(run_tests ole32 odbc32)
endif()
