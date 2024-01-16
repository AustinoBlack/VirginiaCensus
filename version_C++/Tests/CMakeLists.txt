cmake_minimum_required(VERSION 3.17)
project(VACensus_Tests)

set(CMAKE_CXX_STANDARD 17)
find_package(PostgreSQL REQUIRED)

include(CTest)
enable_testing()

add_executable( tests testing.cpp )

add_test( Test-1 "tests")

# Link to the name of the EXECUTABLE, not the project
target_link_libraries(tests PostgreSQL::PostgreSQL)